# Product manager with a JSON file

**CMPS 3680 Server-Side Web**, Lab 4

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3680/lab04/](https://christianrodriguez46.github.io/Coursework/cmps3680/lab04/)

## What it does

`add.php` is a form for adding a product (ID, name, vendor, phone, quantity, last purchase date); `validate.php` checks every field on the server, and `productTools.php` saves products to `data/products.json`. `remove.php` deletes a product by ID or clears them all.

## How to run

From this folder:

```bash
php -S localhost:8000
# open http://localhost:8000/add.php
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Concepts

- Server-side validation
- POST forms
- JSON file storage

[Back to CMPS 3680](../)
