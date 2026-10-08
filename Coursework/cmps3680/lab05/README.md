# Setting up MySQL

**CMPS 3680 Server-Side Web**, Lab 5

## What it does

The lab 4 app plus a `sql/` folder: `sqlTools.php` opens and closes a MySQL connection, `create.php` and `drop.php` create and remove the `product` table, and `test.php` checks the connection. Products are still stored in JSON in this lab.

## How to run

From this folder:

```bash
# one time: create a MySQL database and user, then put them in config.php
php sql/create.php        # creates the table
php -S localhost:8000
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Concepts

- Connecting to MySQL with `mysqli`
- Creating tables

[Back to CMPS 3680](../)
