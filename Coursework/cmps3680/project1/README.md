# Quiz app

**CMPS 3680 Server-Side Web**, Project 1

## What it does

`takeQuiz.php?q=geo` (or `mov`, `mus`) loads a geography, movie or music quiz from `quizzes/*.json` and renders it as a form; `gradeQuiz.php` scores the submitted answers. The quiz name is validated before any file is opened.

## How to run

From this folder:

```bash
php -S localhost:8000
# open http://localhost:8000/takeQuiz.php?q=geo
```

Requires: PHP 7.4 or later; labs 5, 6 and the final project also need MySQL (or MariaDB) and the PHP `mysqli` extension. Run each folder with PHP's built-in server: `php -S localhost:8000`.

## Concepts

- Generating forms from data
- Input validation
- Grading on the server

[Back to CMPS 3680](../)
