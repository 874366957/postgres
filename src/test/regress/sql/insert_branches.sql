--
-- Test cases for INSERT branches in ModifyTable (ExecInsert function)
-- This test file covers all execution paths in nodeModifyTable.c ExecInsert()
--

-- =============================================================================
-- Setup: Create test users, schemas, and functions
-- =============================================================================

-- Create roles for RLS testing
CREATE USER regress_insert_user1 NOLOGIN;
CREATE USER regress_insert_user2 NOLOGIN;

-- =============================================================================
-- BRANCH 1: Normal table insert (standard path without any special features)
-- Lines 1232-1243 in nodeModifyTable.c
-- =============================================================================

CREATE TABLE insert_normal (
    id serial PRIMARY KEY,
    data text
);

-- Basic insert
INSERT INTO insert_normal (data) VALUES ('simple insert');
SELECT * FROM insert_normal;

-- Multi-row insert
INSERT INTO insert_normal (data) VALUES ('row1'), ('row2'), ('row3');
SELECT * FROM insert_normal;

-- Insert with DEFAULT
INSERT INTO insert_normal DEFAULT VALUES;
SELECT * FROM insert_normal;

DROP TABLE insert_normal;

-- =============================================================================
-- BRANCH 2: Insert with indexes (lines 892-894)
-- ExecOpenIndices is called when table has indexes
-- =============================================================================

CREATE TABLE insert_with_index (
    id int PRIMARY KEY,
    data text,
    value int
);

CREATE INDEX idx_insert_data ON insert_with_index(data);
CREATE INDEX idx_insert_value ON insert_with_index(value);

-- Insert should open indexes and create index entries
INSERT INTO insert_with_index VALUES (1, 'test1', 100);
INSERT INTO insert_with_index VALUES (2, 'test2', 200);
INSERT INTO insert_with_index VALUES (3, 'test3', 300);

-- Verify data and index usage
SELECT * FROM insert_with_index ORDER BY id;
EXPLAIN (COSTS OFF) SELECT * FROM insert_with_index WHERE data = 'test2';

DROP TABLE insert_with_index;

-- =============================================================================
-- BRANCH 3: BEFORE ROW INSERT Triggers (lines 905-914)
-- Tests ExecBRInsertTriggers path
-- =============================================================================

CREATE TABLE insert_before_trigger (
    id serial PRIMARY KEY,
    data text,
    modified_by_trigger boolean DEFAULT false
);

-- Trigger that modifies the row
CREATE FUNCTION before_insert_modify_func() RETURNS trigger AS $$
BEGIN
    NEW.modified_by_trigger := true;
    NEW.data := NEW.data || ' (modified)';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER before_insert_modify
    BEFORE INSERT ON insert_before_trigger
    FOR EACH ROW EXECUTE FUNCTION before_insert_modify_func();

-- Insert should be modified by trigger
INSERT INTO insert_before_trigger (data) VALUES ('original');
SELECT * FROM insert_before_trigger;

-- "do nothing" trigger - returns NULL to suppress insert
CREATE OR REPLACE FUNCTION before_insert_do_nothing_func() RETURNS trigger AS $$
BEGIN
    RAISE NOTICE 'before insert do nothing triggered for: %', NEW.data;
    IF NEW.data LIKE '%skip%' THEN
        RETURN NULL;  -- Suppress the insert
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER before_insert_modify ON insert_before_trigger;
CREATE TRIGGER before_insert_do_nothing
    BEFORE INSERT ON insert_before_trigger
    FOR EACH ROW EXECUTE FUNCTION before_insert_do_nothing_func();

-- This insert should be suppressed
INSERT INTO insert_before_trigger (data) VALUES ('skip this row');
-- This insert should succeed
INSERT INTO insert_before_trigger (data) VALUES ('keep this row');
SELECT * FROM insert_before_trigger;

DROP TABLE insert_before_trigger;
DROP FUNCTION before_insert_modify_func();
DROP FUNCTION before_insert_do_nothing_func();

-- =============================================================================
-- BRANCH 4: INSTEAD OF INSERT Triggers (lines 917-922)
-- Tests ExecIRInsertTriggers path on views
-- =============================================================================

CREATE TABLE insert_base_table (
    id serial PRIMARY KEY,
    name text
);

CREATE VIEW insert_view AS SELECT id, name FROM insert_base_table;

-- Create INSTEAD OF trigger
CREATE FUNCTION instead_of_insert_func() RETURNS trigger AS $$
BEGIN
    INSERT INTO insert_base_table (name) VALUES (NEW.name || ' via view');
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER instead_of_insert_trig
    INSTEAD OF INSERT ON insert_view
    FOR EACH ROW EXECUTE FUNCTION instead_of_insert_func();

-- Insert through view using INSTEAD OF trigger
INSERT INTO insert_view (name) VALUES ('test1');
INSERT INTO insert_view (name) VALUES ('test2');

SELECT * FROM insert_base_table ORDER BY id;
SELECT * FROM insert_view ORDER BY id;

-- INSTEAD OF trigger that returns NULL (do nothing)
CREATE OR REPLACE FUNCTION instead_of_insert_func() RETURNS trigger AS $$
BEGIN
    IF NEW.name LIKE '%reject%' THEN
        RETURN NULL;  -- Reject the insert
    END IF;
    INSERT INTO insert_base_table (name) VALUES (NEW.name);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

INSERT INTO insert_view (name) VALUES ('reject this');
INSERT INTO insert_view (name) VALUES ('accept this');
SELECT * FROM insert_view ORDER BY id;

DROP VIEW insert_view;
DROP TABLE insert_base_table;
DROP FUNCTION instead_of_insert_func();

-- =============================================================================
-- BRANCH 5: Generated stored columns (lines 934-937, 1059-1062)
-- Tests ExecComputeStoredGenerated path
-- =============================================================================

CREATE TABLE insert_generated (
    id serial PRIMARY KEY,
    a int,
    b int,
    sum_ab int GENERATED ALWAYS AS (a + b) STORED,
    product_ab int GENERATED ALWAYS AS (a * b) STORED
);

-- Insert with generated columns
INSERT INTO insert_generated (a, b) VALUES (3, 5);
INSERT INTO insert_generated (a, b) VALUES (10, 20);
INSERT INTO insert_generated (a, b) VALUES (7, -3);

SELECT * FROM insert_generated ORDER BY id;

-- Multi-row insert with generated columns
INSERT INTO insert_generated (a, b) VALUES (1, 1), (2, 2), (3, 3);
SELECT * FROM insert_generated ORDER BY id;

-- Attempt to insert into generated column should fail
INSERT INTO insert_generated (a, b, sum_ab) VALUES (1, 2, 100);

DROP TABLE insert_generated;

-- =============================================================================
-- BRANCH 6: Partition tuple routing (lines 874-882)
-- Tests ExecPrepareTupleRouting path
-- =============================================================================

-- Range partitioning
CREATE TABLE insert_range_part (
    id int,
    value int,
    data text
) PARTITION BY RANGE (id);

CREATE TABLE insert_range_part_1 PARTITION OF insert_range_part FOR VALUES FROM (1) TO (100);
CREATE TABLE insert_range_part_2 PARTITION OF insert_range_part FOR VALUES FROM (100) TO (200);
CREATE TABLE insert_range_part_3 PARTITION OF insert_range_part FOR VALUES FROM (200) TO (300);

-- Inserts routed to different partitions
INSERT INTO insert_range_part VALUES (50, 1, 'goes to part_1');
INSERT INTO insert_range_part VALUES (150, 2, 'goes to part_2');
INSERT INTO insert_range_part VALUES (250, 3, 'goes to part_3');

SELECT tableoid::regclass, * FROM insert_range_part ORDER BY id;

-- Multi-row insert with routing
INSERT INTO insert_range_part VALUES
    (10, 1, 'batch_part_1'),
    (110, 2, 'batch_part_2'),
    (210, 3, 'batch_part_3');

SELECT tableoid::regclass, * FROM insert_range_part ORDER BY id;

DROP TABLE insert_range_part;

-- List partitioning
CREATE TABLE insert_list_part (
    category text,
    value int
) PARTITION BY LIST (category);

CREATE TABLE insert_list_part_a PARTITION OF insert_list_part FOR VALUES IN ('A', 'a');
CREATE TABLE insert_list_part_b PARTITION OF insert_list_part FOR VALUES IN ('B', 'b');
CREATE TABLE insert_list_part_default PARTITION OF insert_list_part DEFAULT;

INSERT INTO insert_list_part VALUES ('A', 1), ('B', 2), ('a', 3), ('b', 4), ('C', 5);

SELECT tableoid::regclass, * FROM insert_list_part ORDER BY category, value;

DROP TABLE insert_list_part;

-- Hash partitioning
CREATE TABLE insert_hash_part (
    id int,
    data text
) PARTITION BY HASH (id);

CREATE TABLE insert_hash_part_0 PARTITION OF insert_hash_part FOR VALUES WITH (MODULUS 4, REMAINDER 0);
CREATE TABLE insert_hash_part_1 PARTITION OF insert_hash_part FOR VALUES WITH (MODULUS 4, REMAINDER 1);
CREATE TABLE insert_hash_part_2 PARTITION OF insert_hash_part FOR VALUES WITH (MODULUS 4, REMAINDER 2);
CREATE TABLE insert_hash_part_3 PARTITION OF insert_hash_part FOR VALUES WITH (MODULUS 4, REMAINDER 3);

INSERT INTO insert_hash_part SELECT g, 'data_' || g FROM generate_series(1, 10) g;

SELECT tableoid::regclass, * FROM insert_hash_part ORDER BY id;

DROP TABLE insert_hash_part;

-- Multi-level partitioning
CREATE TABLE insert_multi_level_part (
    year int,
    month int,
    data text
) PARTITION BY RANGE (year);

CREATE TABLE insert_multi_level_2023 PARTITION OF insert_multi_level_part
    FOR VALUES FROM (2023) TO (2024) PARTITION BY RANGE (month);
CREATE TABLE insert_multi_level_2023_q1 PARTITION OF insert_multi_level_2023
    FOR VALUES FROM (1) TO (4);
CREATE TABLE insert_multi_level_2023_q2 PARTITION OF insert_multi_level_2023
    FOR VALUES FROM (4) TO (7);

CREATE TABLE insert_multi_level_2024 PARTITION OF insert_multi_level_part
    FOR VALUES FROM (2024) TO (2025) PARTITION BY RANGE (month);
CREATE TABLE insert_multi_level_2024_q1 PARTITION OF insert_multi_level_2024
    FOR VALUES FROM (1) TO (4);

INSERT INTO insert_multi_level_part VALUES (2023, 2, 'feb 2023');
INSERT INTO insert_multi_level_part VALUES (2023, 5, 'may 2023');
INSERT INTO insert_multi_level_part VALUES (2024, 1, 'jan 2024');

SELECT tableoid::regclass, * FROM insert_multi_level_part ORDER BY year, month;

DROP TABLE insert_multi_level_part;

-- =============================================================================
-- BRANCH 7: Partition constraint check (lines 1102-1106)
-- Tests ExecPartitionCheck path
-- =============================================================================

CREATE TABLE insert_part_constraint (
    id int,
    category text
) PARTITION BY LIST (category);

CREATE TABLE insert_part_constraint_a PARTITION OF insert_part_constraint FOR VALUES IN ('A');
CREATE TABLE insert_part_constraint_b PARTITION OF insert_part_constraint FOR VALUES IN ('B');

-- Direct insert into partition should check constraints
INSERT INTO insert_part_constraint_a VALUES (1, 'A');  -- OK
INSERT INTO insert_part_constraint_a VALUES (2, 'B');  -- Should fail

SELECT * FROM insert_part_constraint ORDER BY id;

DROP TABLE insert_part_constraint;

-- =============================================================================
-- BRANCH 8: Table constraints (line 1094-1095)
-- Tests ExecConstraints path
-- =============================================================================

CREATE TABLE insert_constraints (
    id int PRIMARY KEY,
    positive_value int CHECK (positive_value > 0),
    not_null_col text NOT NULL,
    unique_col int UNIQUE
);

-- Successful inserts
INSERT INTO insert_constraints VALUES (1, 10, 'test', 100);
INSERT INTO insert_constraints VALUES (2, 20, 'test2', 200);

-- CHECK constraint violation
INSERT INTO insert_constraints VALUES (3, -5, 'test3', 300);

-- NOT NULL constraint violation
INSERT INTO insert_constraints VALUES (4, 40, NULL, 400);

-- UNIQUE constraint violation
INSERT INTO insert_constraints VALUES (5, 50, 'test5', 100);

-- PRIMARY KEY constraint violation
INSERT INTO insert_constraints VALUES (1, 60, 'test6', 600);

SELECT * FROM insert_constraints ORDER BY id;

DROP TABLE insert_constraints;

-- =============================================================================
-- BRANCH 9: RLS WITH CHECK policies (lines 1076-1089)
-- Tests ExecWithCheckOptions for RLS INSERT policies
-- =============================================================================

CREATE TABLE insert_rls (
    id serial PRIMARY KEY,
    owner_name text,
    data text
);

ALTER TABLE insert_rls ENABLE ROW LEVEL SECURITY;

-- Policy: users can only insert rows with their own name as owner
CREATE POLICY insert_own_rows ON insert_rls
    FOR INSERT
    WITH CHECK (owner_name = current_user);

-- Policy for SELECT to allow viewing own rows
CREATE POLICY select_own_rows ON insert_rls
    FOR SELECT
    USING (owner_name = current_user);

GRANT ALL ON insert_rls TO regress_insert_user1;
GRANT ALL ON insert_rls TO regress_insert_user2;
GRANT USAGE ON SEQUENCE insert_rls_id_seq TO regress_insert_user1;
GRANT USAGE ON SEQUENCE insert_rls_id_seq TO regress_insert_user2;

SET SESSION AUTHORIZATION regress_insert_user1;

-- Should succeed - owner matches current_user
INSERT INTO insert_rls (owner_name, data) VALUES ('regress_insert_user1', 'user1 data');

-- Should fail - owner doesn't match current_user
INSERT INTO insert_rls (owner_name, data) VALUES ('regress_insert_user2', 'wrong owner');

SELECT * FROM insert_rls;

SET SESSION AUTHORIZATION regress_insert_user2;

-- Should succeed
INSERT INTO insert_rls (owner_name, data) VALUES ('regress_insert_user2', 'user2 data');

SELECT * FROM insert_rls;

RESET SESSION AUTHORIZATION;

-- Verify all rows as superuser
SELECT * FROM insert_rls ORDER BY id;

DROP TABLE insert_rls;

-- =============================================================================
-- BRANCH 10: ON CONFLICT DO NOTHING (lines 1161-1179)
-- Tests speculative insert with DO NOTHING
-- =============================================================================

CREATE TABLE insert_conflict_nothing (
    id int PRIMARY KEY,
    data text,
    counter int DEFAULT 0
);

-- Initial insert
INSERT INTO insert_conflict_nothing VALUES (1, 'first', 1);

-- Conflict with DO NOTHING - should be silently ignored
INSERT INTO insert_conflict_nothing VALUES (1, 'duplicate', 2) ON CONFLICT DO NOTHING;
INSERT INTO insert_conflict_nothing VALUES (2, 'second', 1) ON CONFLICT DO NOTHING;
INSERT INTO insert_conflict_nothing VALUES (2, 'duplicate2', 2) ON CONFLICT DO NOTHING;

SELECT * FROM insert_conflict_nothing ORDER BY id;

-- With specific conflict target
INSERT INTO insert_conflict_nothing VALUES (3, 'third', 1) ON CONFLICT (id) DO NOTHING;
INSERT INTO insert_conflict_nothing VALUES (3, 'duplicate3', 2) ON CONFLICT (id) DO NOTHING;

SELECT * FROM insert_conflict_nothing ORDER BY id;

DROP TABLE insert_conflict_nothing;

-- =============================================================================
-- BRANCH 11: ON CONFLICT DO UPDATE (lines 1141-1159)
-- Tests speculative insert with DO UPDATE and retry loop
-- =============================================================================

CREATE TABLE insert_conflict_update (
    id int PRIMARY KEY,
    data text,
    counter int DEFAULT 1
);

-- Initial inserts
INSERT INTO insert_conflict_update VALUES (1, 'first', 1);
INSERT INTO insert_conflict_update VALUES (2, 'second', 1);

-- Conflict with DO UPDATE
INSERT INTO insert_conflict_update VALUES (1, 'updated_first', 100)
    ON CONFLICT (id) DO UPDATE SET data = EXCLUDED.data, counter = insert_conflict_update.counter + 1;

INSERT INTO insert_conflict_update VALUES (2, 'updated_second', 100)
    ON CONFLICT (id) DO UPDATE SET counter = insert_conflict_update.counter + EXCLUDED.counter;

SELECT * FROM insert_conflict_update ORDER BY id;

-- Multiple conflicts in single statement
INSERT INTO insert_conflict_update VALUES (1, 'multi1', 10), (2, 'multi2', 20), (3, 'new', 1)
    ON CONFLICT (id) DO UPDATE SET counter = insert_conflict_update.counter + 1;

SELECT * FROM insert_conflict_update ORDER BY id;

-- ON CONFLICT with WHERE clause
INSERT INTO insert_conflict_update VALUES (1, 'conditional', 100)
    ON CONFLICT (id) DO UPDATE SET data = EXCLUDED.data
    WHERE insert_conflict_update.counter > 2;

SELECT * FROM insert_conflict_update ORDER BY id;

-- ON CONFLICT with RETURNING
INSERT INTO insert_conflict_update VALUES (1, 'returning_test', 1)
    ON CONFLICT (id) DO UPDATE SET counter = insert_conflict_update.counter + 1
    RETURNING *;

DROP TABLE insert_conflict_update;

-- =============================================================================
-- BRANCH 12: Speculative insert with expression index
-- Tests more complex conflict detection scenarios
-- =============================================================================

CREATE TABLE insert_expr_conflict (
    id int,
    data text,
    lower_data text GENERATED ALWAYS AS (lower(data)) STORED
);

CREATE UNIQUE INDEX insert_expr_conflict_lower_idx ON insert_expr_conflict (lower_data);

INSERT INTO insert_expr_conflict (id, data) VALUES (1, 'HELLO');
INSERT INTO insert_expr_conflict (id, data) VALUES (2, 'hello')
    ON CONFLICT (lower_data) DO NOTHING;
INSERT INTO insert_expr_conflict (id, data) VALUES (3, 'Hello')
    ON CONFLICT (lower_data) DO UPDATE SET id = EXCLUDED.id;

SELECT * FROM insert_expr_conflict ORDER BY id;

DROP TABLE insert_expr_conflict;

-- =============================================================================
-- BRANCH 13: AFTER ROW INSERT Triggers (lines 1276-1278)
-- Tests ExecARInsertTriggers path
-- =============================================================================

CREATE TABLE insert_after_trigger (
    id serial PRIMARY KEY,
    data text
);

CREATE TABLE insert_audit_log (
    action text,
    table_name text,
    row_id int,
    logged_at timestamp DEFAULT now()
);

CREATE FUNCTION after_insert_audit_func() RETURNS trigger AS $$
BEGIN
    INSERT INTO insert_audit_log (action, table_name, row_id)
    VALUES ('INSERT', TG_TABLE_NAME, NEW.id);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER after_insert_audit
    AFTER INSERT ON insert_after_trigger
    FOR EACH ROW EXECUTE FUNCTION after_insert_audit_func();

INSERT INTO insert_after_trigger (data) VALUES ('row1');
INSERT INTO insert_after_trigger (data) VALUES ('row2');
INSERT INTO insert_after_trigger (data) VALUES ('row3');

SELECT * FROM insert_after_trigger ORDER BY id;
SELECT action, table_name, row_id FROM insert_audit_log ORDER BY row_id;

DROP TABLE insert_after_trigger CASCADE;
DROP TABLE insert_audit_log;
DROP FUNCTION after_insert_audit_func();

-- =============================================================================
-- BRANCH 14: View WITH CHECK OPTION (lines 1294-1295)
-- Tests ExecWithCheckOptions for view check options
-- =============================================================================

CREATE TABLE insert_view_base (
    id serial PRIMARY KEY,
    category text,
    value int
);

CREATE VIEW insert_view_with_check AS
    SELECT * FROM insert_view_base WHERE category = 'A'
    WITH CHECK OPTION;

-- Should succeed
INSERT INTO insert_view_with_check (category, value) VALUES ('A', 100);

-- Should fail due to WITH CHECK OPTION
INSERT INTO insert_view_with_check (category, value) VALUES ('B', 200);

SELECT * FROM insert_view_base ORDER BY id;

-- Cascaded check option with nested views
CREATE VIEW insert_view_level2 AS
    SELECT * FROM insert_view_with_check WHERE value > 50
    WITH CASCADED CHECK OPTION;

-- Should succeed
INSERT INTO insert_view_level2 (category, value) VALUES ('A', 150);

-- Should fail - violates parent view's check (category must be 'A')
INSERT INTO insert_view_level2 (category, value) VALUES ('B', 150);

-- Should fail - violates this view's check (value must be > 50)
INSERT INTO insert_view_level2 (category, value) VALUES ('A', 30);

SELECT * FROM insert_view_base ORDER BY id;

DROP VIEW insert_view_level2;
DROP VIEW insert_view_with_check;
DROP TABLE insert_view_base;

-- =============================================================================
-- BRANCH 15: RETURNING clause (lines 1298-1348)
-- Tests ExecProcessReturning path
-- =============================================================================

CREATE TABLE insert_returning (
    id serial PRIMARY KEY,
    name text,
    value int
);

-- Basic RETURNING
INSERT INTO insert_returning (name, value) VALUES ('test1', 100) RETURNING *;

-- RETURNING specific columns
INSERT INTO insert_returning (name, value) VALUES ('test2', 200) RETURNING id, name;

-- RETURNING with expressions
INSERT INTO insert_returning (name, value) VALUES ('test3', 300) RETURNING id, name, value * 2 AS double_value;

-- RETURNING with function calls
INSERT INTO insert_returning (name, value) VALUES ('test4', 400) RETURNING id, upper(name) AS upper_name;

-- Multi-row insert with RETURNING
INSERT INTO insert_returning (name, value) VALUES ('multi1', 10), ('multi2', 20), ('multi3', 30) RETURNING *;

-- RETURNING with subquery
INSERT INTO insert_returning (name, value)
VALUES ('sub1', 500)
RETURNING *, (SELECT count(*) FROM insert_returning) AS total_rows;

SELECT * FROM insert_returning ORDER BY id;

DROP TABLE insert_returning;

-- =============================================================================
-- BRANCH 16: Cross-partition UPDATE insert (lines 1257-1267)
-- Tests transition capture for partition key update
-- =============================================================================

CREATE TABLE insert_cross_part (
    id int,
    partition_key int,
    data text
) PARTITION BY RANGE (partition_key);

CREATE TABLE insert_cross_part_1 PARTITION OF insert_cross_part FOR VALUES FROM (1) TO (100);
CREATE TABLE insert_cross_part_2 PARTITION OF insert_cross_part FOR VALUES FROM (100) TO (200);

-- Insert initial data
INSERT INTO insert_cross_part VALUES (1, 50, 'initially in part1');

SELECT tableoid::regclass, * FROM insert_cross_part;

-- Update that moves row to different partition (involves DELETE + INSERT internally)
UPDATE insert_cross_part SET partition_key = 150 WHERE id = 1;

SELECT tableoid::regclass, * FROM insert_cross_part;

-- Test with transition tables to capture the insert
CREATE TABLE insert_cross_part_log (
    old_partition_key int,
    new_partition_key int,
    data text
);

CREATE FUNCTION log_cross_partition_update() RETURNS trigger AS $$
BEGIN
    INSERT INTO insert_cross_part_log
    SELECT o.partition_key, n.partition_key, n.data
    FROM old_table o, new_table n
    WHERE o.id = n.id;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER cross_partition_trigger
    AFTER UPDATE ON insert_cross_part
    REFERENCING OLD TABLE AS old_table NEW TABLE AS new_table
    FOR EACH STATEMENT EXECUTE FUNCTION log_cross_partition_update();

-- Insert and then move across partitions
INSERT INTO insert_cross_part VALUES (2, 10, 'will move');
UPDATE insert_cross_part SET partition_key = 110 WHERE id = 2;

SELECT * FROM insert_cross_part_log;

DROP TABLE insert_cross_part CASCADE;
DROP TABLE insert_cross_part_log;
DROP FUNCTION log_cross_partition_update();

-- =============================================================================
-- BRANCH 17: Insert with both BEFORE and AFTER triggers
-- Tests combined trigger execution path
-- =============================================================================

CREATE TABLE insert_both_triggers (
    id serial PRIMARY KEY,
    data text,
    before_modified boolean DEFAULT false,
    after_logged boolean DEFAULT false
);

CREATE TABLE trigger_log (log_entry text);

CREATE FUNCTION both_before_func() RETURNS trigger AS $$
BEGIN
    NEW.before_modified := true;
    NEW.data := NEW.data || ' [before]';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE FUNCTION both_after_func() RETURNS trigger AS $$
BEGIN
    INSERT INTO trigger_log VALUES ('After trigger executed for id: ' || NEW.id);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER both_before_trig
    BEFORE INSERT ON insert_both_triggers
    FOR EACH ROW EXECUTE FUNCTION both_before_func();

CREATE TRIGGER both_after_trig
    AFTER INSERT ON insert_both_triggers
    FOR EACH ROW EXECUTE FUNCTION both_after_func();

INSERT INTO insert_both_triggers (data) VALUES ('test');

SELECT * FROM insert_both_triggers;
SELECT * FROM trigger_log;

DROP TABLE insert_both_triggers CASCADE;
DROP TABLE trigger_log;
DROP FUNCTION both_before_func();
DROP FUNCTION both_after_func();

-- =============================================================================
-- BRANCH 18: INSERT with partition routing and triggers
-- Tests combined partition routing and trigger execution
-- =============================================================================

CREATE TABLE insert_part_trigger (
    id int,
    category text,
    data text
) PARTITION BY LIST (category);

CREATE TABLE insert_part_trigger_a PARTITION OF insert_part_trigger FOR VALUES IN ('A');
CREATE TABLE insert_part_trigger_b PARTITION OF insert_part_trigger FOR VALUES IN ('B');

CREATE FUNCTION part_trigger_func() RETURNS trigger AS $$
BEGIN
    NEW.data := NEW.data || ' [trigger on ' || TG_TABLE_NAME || ']';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Triggers on partitions
CREATE TRIGGER part_a_trigger
    BEFORE INSERT ON insert_part_trigger_a
    FOR EACH ROW EXECUTE FUNCTION part_trigger_func();

CREATE TRIGGER part_b_trigger
    BEFORE INSERT ON insert_part_trigger_b
    FOR EACH ROW EXECUTE FUNCTION part_trigger_func();

INSERT INTO insert_part_trigger VALUES (1, 'A', 'data_a');
INSERT INTO insert_part_trigger VALUES (2, 'B', 'data_b');

SELECT tableoid::regclass, * FROM insert_part_trigger ORDER BY id;

DROP TABLE insert_part_trigger;
DROP FUNCTION part_trigger_func();

-- =============================================================================
-- BRANCH 19: INSERT with ON CONFLICT on partitioned table
-- Tests speculative insert with partition routing
-- =============================================================================

CREATE TABLE insert_part_conflict (
    id int,
    category text,
    counter int DEFAULT 1,
    PRIMARY KEY (id, category)
) PARTITION BY LIST (category);

CREATE TABLE insert_part_conflict_a PARTITION OF insert_part_conflict FOR VALUES IN ('A');
CREATE TABLE insert_part_conflict_b PARTITION OF insert_part_conflict FOR VALUES IN ('B');

INSERT INTO insert_part_conflict VALUES (1, 'A', 1);
INSERT INTO insert_part_conflict VALUES (1, 'B', 1);

-- ON CONFLICT on partitioned table
INSERT INTO insert_part_conflict VALUES (1, 'A', 10)
    ON CONFLICT (id, category) DO UPDATE SET counter = insert_part_conflict.counter + 1;

INSERT INTO insert_part_conflict VALUES (2, 'A', 1)
    ON CONFLICT (id, category) DO NOTHING;

SELECT tableoid::regclass, * FROM insert_part_conflict ORDER BY category, id;

DROP TABLE insert_part_conflict;

-- =============================================================================
-- BRANCH 20: INSERT with generated columns and constraints
-- Tests generated columns with constraint checking
-- =============================================================================

CREATE TABLE insert_gen_constraint (
    id serial PRIMARY KEY,
    a int NOT NULL,
    b int NOT NULL,
    sum_ab int GENERATED ALWAYS AS (a + b) STORED,
    CHECK (sum_ab <= 100)
);

-- Should succeed
INSERT INTO insert_gen_constraint (a, b) VALUES (30, 40);  -- sum = 70
INSERT INTO insert_gen_constraint (a, b) VALUES (10, 20);  -- sum = 30

-- Should fail due to CHECK constraint on generated column
INSERT INTO insert_gen_constraint (a, b) VALUES (60, 50);  -- sum = 110

SELECT * FROM insert_gen_constraint ORDER BY id;

DROP TABLE insert_gen_constraint;

-- =============================================================================
-- BRANCH 21: INSERT with RLS and RETURNING
-- Tests RLS policy check with RETURNING clause
-- =============================================================================

CREATE TABLE insert_rls_returning (
    id serial PRIMARY KEY,
    owner_name text,
    data text
);

ALTER TABLE insert_rls_returning ENABLE ROW LEVEL SECURITY;

CREATE POLICY insert_policy ON insert_rls_returning
    FOR INSERT
    WITH CHECK (owner_name = current_user);

CREATE POLICY select_policy ON insert_rls_returning
    FOR SELECT
    USING (owner_name = current_user);

GRANT ALL ON insert_rls_returning TO regress_insert_user1;
GRANT USAGE ON SEQUENCE insert_rls_returning_id_seq TO regress_insert_user1;

SET SESSION AUTHORIZATION regress_insert_user1;

-- Should succeed with RETURNING
INSERT INTO insert_rls_returning (owner_name, data) VALUES ('regress_insert_user1', 'test') RETURNING *;

RESET SESSION AUTHORIZATION;

DROP TABLE insert_rls_returning;

-- =============================================================================
-- BRANCH 22: INSERT with MERGE operation (lines 1078-1080)
-- Tests INSERT action within MERGE command
-- =============================================================================

CREATE TABLE insert_merge_target (
    id int PRIMARY KEY,
    data text,
    counter int DEFAULT 0
);

CREATE TABLE insert_merge_source (
    id int PRIMARY KEY,
    data text
);

INSERT INTO insert_merge_source VALUES (1, 'existing'), (2, 'new');
INSERT INTO insert_merge_target VALUES (1, 'original', 1);

-- MERGE with INSERT action
MERGE INTO insert_merge_target t
USING insert_merge_source s
ON t.id = s.id
WHEN MATCHED THEN
    UPDATE SET data = s.data, counter = t.counter + 1
WHEN NOT MATCHED THEN
    INSERT (id, data, counter) VALUES (s.id, s.data, 1);

SELECT * FROM insert_merge_target ORDER BY id;

DROP TABLE insert_merge_target;
DROP TABLE insert_merge_source;

-- =============================================================================
-- Cleanup: Drop test users
-- =============================================================================

DROP USER regress_insert_user1;
DROP USER regress_insert_user2;
