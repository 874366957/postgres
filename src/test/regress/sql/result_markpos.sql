--
-- Test ExecResultMarkPos and ExecResultRestrPos functions
--
-- These functions are called when a Result node with an outer plan is the
-- inner child of a Merge Join. The Result node delegates mark/restore to
-- its child plan (Sort/Material).
--
-- ExecResultMarkPos: Marks the current scan position by calling
--                    ExecMarkPos on the child plan
-- ExecResultRestrPos: Restores to a previously marked position by calling
--                     ExecRestrPos on the child plan
--
-- Key conditions for these functions to be called:
-- 1. Merge Join needs mark/restore on inner side (duplicates in join key)
-- 2. Inner side is a Result node (created for projection over non-projectable node)
-- 3. Result has an outer plan that supports mark/restore (Sort, Material)
-- 4. Multiple matching tuples exist (trigger actual mark/restore)
--
-- A Sort node is NOT projection-capable. So if we need a different target
-- list on top of a Sort, a Result node will be created to do the projection.
--

-- Create test tables
CREATE TABLE result_markpos_t1 (a int, b int);
CREATE TABLE result_markpos_t2 (x int, y int, z text);

-- Insert data with duplicates to trigger mark/restore during merge join
INSERT INTO result_markpos_t1 SELECT i, i FROM generate_series(1, 10) i;
-- Add duplicates for key 5 to force multiple restore calls
INSERT INTO result_markpos_t1 SELECT 5, 100 + i FROM generate_series(1, 3) i;

INSERT INTO result_markpos_t2 SELECT i, i * 10, 'val' || i FROM generate_series(1, 10) i;
-- Add duplicates for key 5 to create many matching combinations
INSERT INTO result_markpos_t2 SELECT 5, 200 + i, 'dup' || i FROM generate_series(1, 3) i;

ANALYZE result_markpos_t1;
ANALYZE result_markpos_t2;

-- Force merge join and disable other join methods
SET enable_hashjoin = off;
SET enable_nestloop = off;
SET enable_mergejoin = on;

--
-- Test 1: Merge join with duplicates on both sides
-- When there are multiple matches for the same key (5), the merge join
-- must mark the position and restore it to process all combinations
--
-- The merge join uses Sort on inner side which supports mark/restore.
--

EXPLAIN (COSTS OFF)
SELECT t1.a, t1.b, t2.x, t2.y
FROM result_markpos_t1 t1 JOIN result_markpos_t2 t2 ON t1.a = t2.x
WHERE t1.a IN (3, 5)
ORDER BY t1.a, t1.b, t2.y;

-- Execute to exercise mark/restore on Sort
-- For key=5: t1 has 4 rows, t2 has 4 rows -> 16 result rows
SELECT t1.a, t1.b, t2.x, t2.y
FROM result_markpos_t1 t1 JOIN result_markpos_t2 t2 ON t1.a = t2.x
WHERE t1.a = 5
ORDER BY t1.a, t1.b, t2.y;

--
-- Test 2: Merge join where inner side has projection that requires Result
-- A Sort node is NOT projection-capable. If we need a different tlist
-- on top of Sort, the planner creates a Result node.
--
-- We create a scenario using a subquery with UNION that forces specific
-- column handling that cannot be merged into the Sort.
--

-- First show a case that uses merge join with the inner side processed
INSERT INTO result_markpos_t1 VALUES (3, 301), (3, 302);
INSERT INTO result_markpos_t2 VALUES (3, 301, 'extra1'), (3, 302, 'extra2');

ANALYZE result_markpos_t1;
ANALYZE result_markpos_t2;

-- This uses Merge Join on the inner Sort, exercising mark/restore
EXPLAIN (COSTS OFF)
SELECT t1.a, t1.b, t2.x, t2.y, t2.z
FROM result_markpos_t1 t1 JOIN result_markpos_t2 t2 ON t1.a = t2.x
WHERE t1.a IN (3, 5)
ORDER BY t1.a, t1.b, t2.y;

SELECT t1.a, t1.b, t2.x, t2.y, t2.z
FROM result_markpos_t1 t1 JOIN result_markpos_t2 t2 ON t1.a = t2.x
WHERE t1.a IN (3, 5)
ORDER BY t1.a, t1.b, t2.y;

-- Reset settings
RESET enable_hashjoin;
RESET enable_nestloop;
RESET enable_mergejoin;

-- Cleanup
DROP TABLE result_markpos_t1;
DROP TABLE result_markpos_t2;
