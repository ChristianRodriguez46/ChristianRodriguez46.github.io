# JSON search and replace endpoints

**CMPS 3390 Application Development**, Lab 8

Read this lab with snapshots and notes on every file: [https://christianrodriguez46.github.io/Coursework/cmps3390/lab08/](https://christianrodriguez46.github.io/Coursework/cmps3390/lab08/)

## What it does

Two PHP endpoints that take a JSON body:

- `search.php` expects `search` and `text`, and returns the text as HTML with every match highlighted.
- `replace.php` expects `find`, `replace` and `text`, and returns the text with each whole-word match replaced and highlighted.

Missing fields return HTTP 400 with an error message. `lib.php` holds the shared response helpers.

## How to run

From this folder:

```bash
php -S localhost:8000

# in another terminal
curl -X POST localhost:8000/replace.php \
  -d '{"find":"cat","replace":"dog","text":"The cat sat."}'
```

Requires: PHP 7.4 or later for the PHP labs (its built-in server is enough). `g++` for lab 1.

## Concepts

- Reading JSON request bodies
- Regular expressions
- HTTP status codes

[Back to CMPS 3390](../)
