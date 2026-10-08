# Product manager with MySQL

**CMPS 3680 Server-Side Web**, Lab 6

## What it does

Moves the product manager's storage into MySQL. `sql/sqlTools.php` adds, removes, lists and clears products in the `product` table and checks that IDs are unique, and `add.php` and `remove.php` now call it instead of the JSON file.

## How to run

From this folder:

```bash
# one time: create a MySQL database and user, then put them in config.php
php sql/create.php        # creates the table
php -S localhost:8000
# open http://localhost:8000/add.php
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Concepts

- CRUD with MySQL
- Prepared statements
- Moving from files to a database

[Back to CMPS 3680](../)
