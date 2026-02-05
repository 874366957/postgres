# INSERT ... ON CONFLICT test: Simple demonstration of specConflict = true
#
# This test demonstrates when specConflict is set to true in PostgreSQL's
# speculative insertion mechanism.
#
# Background:
# -----------
# When executing INSERT ... ON CONFLICT, PostgreSQL uses "speculative insertion":
# 1. First, it checks if there's a potential conflict (ExecCheckIndexConstraints)
# 2. If no conflict found, it speculatively inserts the tuple and index entries
# 3. During index insertion, if a conflict is detected (another concurrent
#    transaction inserted the same key), specConflict is set to true
# 4. When specConflict = true, the speculative tuple is killed and the process
#    restarts from the beginning (goto vlock in nodeModifyTable.c)
#
# The specConflict = true scenario occurs when:
# - Two sessions concurrently try to INSERT ... ON CONFLICT with the same key
# - Both pass the initial conflict check (no committed conflict exists)
# - Both speculatively insert their tuples
# - One session completes first and confirms its insertion
# - The other session detects the conflict during index insertion
#   -> specConflict is set to true
#   -> Its speculative tuple is killed
#   -> It retries and now finds the committed conflict
#
# Key code locations:
# - execIndexing.c line 513-514: if (indexRelation->rd_index->indimmediate && specConflict)
#                                    *specConflict = true;
# - nodeModifyTable.c line 1223: if (specConflict) { goto vlock; }

setup
{
    CREATE TABLE conflict_demo(id int PRIMARY KEY, value text);
}

teardown
{
    DROP TABLE conflict_demo;
}

session s1
setup
{
    SET default_transaction_isolation = 'read committed';
}
step s1_upsert { INSERT INTO conflict_demo(id, value) VALUES(1, 'session1') ON CONFLICT (id) DO UPDATE SET value = conflict_demo.value || '+s1'; }

session s2
setup
{
    SET default_transaction_isolation = 'read committed';
}
step s2_upsert { INSERT INTO conflict_demo(id, value) VALUES(1, 'session2') ON CONFLICT (id) DO UPDATE SET value = conflict_demo.value || '+s2'; }

session controller
step show { SELECT * FROM conflict_demo; }

# Permutation 1: Both sessions insert concurrently
# One will win the race, the other will hit specConflict = true and retry
permutation s1_upsert s2_upsert show

# Permutation 2: Sequential inserts - s1 inserts first, s2 updates
# In this case, s2 finds the committed conflict in pre-check, no specConflict
permutation s1_upsert show s2_upsert show
