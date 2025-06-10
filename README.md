Here’s a sample `README.md` for a C++ application that demonstrates how to **test the use of foreign keys in SQLite3**:

---

````markdown
# SQLite3 Foreign Key Test (C++)

This is a simple C++ command-line application that demonstrates how to test the usage of **foreign keys** in SQLite3. It allows you to toggle foreign key constraints and observe how SQLite enforces them.

## Features

- Creates `Parent` and `Child` tables with a foreign key constraint.
- Inserts data with or without violating the constraint.
- Enables or disables foreign key enforcement (`PRAGMA foreign_keys = ON/OFF`).
- Uses `sqlite3_exec` and C-style callbacks to interact with the database.

## Requirements

- C++ compiler with C++20 or later
- SQLite3 development libraries

## Compilation

```bash
g++ -std=c++20 main.cpp -lsqlite3 -o foreign_key_test
````

## Usage

```bash
./foreign_key_test <mode>
```

### `<mode>` can be:

| Mode | Description                                                            |
| ---- | ---------------------------------------------------------------------- |
| `1`  | Create tables with foreign key                                         |
| `2`  | Insert valid parent and child data                                     |
| `3`  | Insert child data with **invalid** parent (expect failure if FK is ON) |
| `4`  | Query both tables                                                      |
| `5`  | Toggle foreign key support OFF                                         |
| `6`  | Toggle foreign key support ON                                          |

### Example Workflow

```bash
./foreign_key_test 6     # Enable foreign key enforcement
./foreign_key_test 1     # Create tables
./foreign_key_test 2     # Insert valid data
./foreign_key_test 3     # Try inserting invalid child (should fail)
./foreign_key_test 4     # View table contents
```

## Notes

* SQLite disables foreign key enforcement by default. Use `PRAGMA foreign_keys = ON;` to enable it.
* To confirm foreign key status, run `PRAGMA foreign_keys;` query.
* This project demonstrates how foreign keys **must be explicitly enabled per connection** in SQLite.

```

---

Let me know if you'd like the matching `main.cpp` template that includes the creation of `Parent` and `Child` tables with foreign keys, and executes the modes listed here.
```
