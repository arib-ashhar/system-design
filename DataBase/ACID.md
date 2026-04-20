# ACID Properties

ACID defines the 4 guarantees a database transaction should provide so data stays correct even with failures or concurrent access.

## What is a transaction?

A transaction is a group of database operations treated as one unit of work.
It either fully succeeds or fully fails. There should be no partial state.

## 1. Atomicity

All-or-nothing execution.

- If any step in a transaction fails, the whole transaction is rolled back.
- Prevents partial updates like money debited from one account but not credited to another.

How it is implemented:

- Write-Ahead Log (WAL) / transaction log records changes before applying them.
- `BEGIN`, `COMMIT`, and `ROLLBACK` control whether changes are finalized or undone.

## 2. Consistency

A transaction must move the database from one valid state to another valid state.

- Rules must remain true before and after commit.
- If a transaction violates constraints, it does not commit.

What enforces it:

- Schema constraints: `PRIMARY KEY`, `FOREIGN KEY`, `UNIQUE`, `NOT NULL`, `CHECK`
- Triggers and stored procedures
- Application-level business validations

## 3. Isolation

Concurrent transactions should not interfere with each other’s intermediate state.

- Each transaction should behave as if it ran alone.
- Uncommitted changes should not leak into other transactions.

Common anomalies:

- Dirty read: read uncommitted data
- Non-repeatable read: same row read twice gives different values
- Phantom read: same query returns different row sets

Isolation levels:

- Read Uncommitted: allows dirty reads
- Read Committed: prevents dirty reads
- Repeatable Read: prevents dirty + non-repeatable reads
- Serializable: strongest; behaves like serial execution

How databases enforce it:

- Locking
- MVCC (Multi-Version Concurrency Control)
- Snapshot isolation

## 4. Durability

Once a transaction commits, its data must survive crashes, restarts, or power loss.

- Committed data should not disappear after the system says "success".

How it is implemented:

- WAL: persist log first, then update main data files
- Recovery uses redo for committed work and undo for incomplete work
- Replication improves fault tolerance
- Backups protect against severe corruption or disasters

## One-line memory trick

`A` = all or nothing  
`C` = rules stay valid  
`I` = concurrent transactions do not clash  
`D` = committed data survives
