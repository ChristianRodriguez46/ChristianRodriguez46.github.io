# Templated product catalog

**CMPS 3680 Server-Side Web**, Lab 3

## What it does

A small storefront built from reusable `header.php` and `footer.php` includes. `products.php` reads `products.json`, sorts the items and lists them; `eproducts.php` is a variation.

## How to run

From this folder:

```bash
php -S localhost:8000
# open http://localhost:8000/home.php
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Concepts

- PHP includes
- Reading JSON
- Sorting arrays

[Back to CMPS 3680](../)
