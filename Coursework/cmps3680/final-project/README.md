# Car detailing site with PHP and MySQL

**CMPS 3680 Server-Side Web**, Final project

## What it does

The CMPS 2680 car detailing site rebuilt with a backend:

- **Booking** (`booking.php`) validates the appointment on the server and saves it to MySQL with a random unique order number, then shows the saved appointment. The chosen interior and exterior services are stored as JSON columns.
- **Accounts** (`login.php`) let customers sign up and log in. Passwords are hashed with `password_hash` and checked with `password_verify`, and the login is kept in a PHP session.
- **Contact** (`contact.php`) validates the message, checks the order number against the database, and sends it with PHP's `mail()`.
- `sql/sqlTools.php` holds the database functions, using prepared statements.

## How to run

From this folder:

```bash
# one time: create a MySQL database and user, then put them in config.php
php sql/create.php        # creates the table
php -S localhost:8000
# open http://localhost:8000/home.html
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Note

The database login for this project is in `sql/config.php`. `sql/create.php` defines both the `appointments` and `users` tables. The `appointments` statement is commented out because that table already existed on the course server; uncomment it on a fresh database. The contact form needs a mail server to actually send email.

## Concepts

- PHP and MySQL
- Password hashing and sessions
- Server-side validation

[Back to CMPS 3680](../)
