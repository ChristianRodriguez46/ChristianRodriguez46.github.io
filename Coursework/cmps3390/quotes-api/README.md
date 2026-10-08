# Quotes API

**CMPS 3390 Application Development**, Quotes API

## What it does

`index.php` returns a random quote as JSON from one of three categories: `book`, `movie` or `game`. The quotes live in `docs/<category>.json`. A missing or unknown category returns HTTP 400 with a JSON error.

## How to run

From this folder:

```bash
php -S localhost:8000

# in another terminal
curl 'localhost:8000/index.php?category=movie'
# returns a random quote, e.g. {"quote":"May the Force be with you.","author":"Star Wars"}
```

Requires: PHP 7.4 or later for the PHP labs (its built-in server is enough). `g++` for lab 1.

## Concepts

- REST-style endpoints
- Input validation with a whitelist
- JSON responses

[Back to CMPS 3390](../)
