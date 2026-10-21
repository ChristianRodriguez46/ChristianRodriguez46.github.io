<div id="top">

<!-- HEADER STYLE: CLASSIC -->
<div align="center">


# CHRISTIANRODRIGUEZ46.GITHUB.IO

<em>My portfolio: personal projects, Computer Science coursework and my CV</em>

<!-- BADGES -->
<img src="https://img.shields.io/static/v1?label=license&amp;message=MIT&amp;color=0080ff&amp;style=flat" alt="license (at generation)">
<img src="https://img.shields.io/static/v1?label=commit+date&amp;message=2026-10-21&amp;color=0080ff&amp;style=flat" alt="commit date (at generation)">
<img src="https://img.shields.io/static/v1?label=language&amp;message=HTML&amp;color=0080ff&amp;style=flat" alt="language (at generation)">
<img src="https://img.shields.io/static/v1?label=languages&amp;message=17&amp;color=0080ff&amp;style=flat" alt="languages (at generation)">

<em>Built with the tools and technologies:</em>

<img src="https://img.shields.io/badge/JSON-000000.svg?style=flat&logo=JSON&logoColor=white" alt="JSON">
<img src="https://img.shields.io/badge/Markdown-000000.svg?style=flat&logo=Markdown&logoColor=white" alt="Markdown">
<img src="https://img.shields.io/badge/npm-CB3837.svg?style=flat&logo=npm&logoColor=white" alt="npm">
<img src="https://img.shields.io/badge/JavaScript-F7DF1E.svg?style=flat&logo=JavaScript&logoColor=black" alt="JavaScript">
<img src="https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=flat&logo=GNU-Bash&logoColor=white" alt="GNU%20Bash">
<img src="https://img.shields.io/badge/ReadMe-018EF5.svg?style=flat&logo=ReadMe&logoColor=white" alt="ReadMe">
<img src="https://img.shields.io/badge/C++-00599C.svg?style=flat&logo=C++&logoColor=white" alt="C++">
<img src="https://img.shields.io/badge/XML-005FAD.svg?style=flat&logo=XML&logoColor=white" alt="XML">
<br>
<img src="https://img.shields.io/badge/Python-3776AB.svg?style=flat&logo=Python&logoColor=white" alt="Python">
<img src="https://img.shields.io/badge/TypeScript-3178C6.svg?style=flat&logo=TypeScript&logoColor=white" alt="TypeScript">
<img src="https://img.shields.io/badge/C-A8B9CC.svg?style=flat&logo=C&logoColor=black" alt="C">
<img src="https://img.shields.io/badge/GitHub%20Actions-2088FF.svg?style=flat&logo=GitHub-Actions&logoColor=white" alt="GitHub%20Actions">
<img src="https://img.shields.io/badge/Perl-39457E.svg?style=flat&logo=Perl&logoColor=white" alt="Perl">
<img src="https://img.shields.io/badge/PHP-777BB4.svg?style=flat&logo=PHP&logoColor=white" alt="PHP">
<img src="https://img.shields.io/badge/ESLint-4B32C3.svg?style=flat&logo=ESLint&logoColor=white" alt="ESLint">

</div>
<br>

---

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
    - [Usage](#usage)
    - [Testing](#testing)
- [Features](#features)
- [Project Structure](#project-structure)
    - [Project Index](#project-index)
- [License](#license)

---

## Overview

This is my portfolio site, served by GitHub Pages at
[christianrodriguez46.github.io](https://christianrodriguez46.github.io/). It shows my personal
projects, my coursework from Computer Science at CSU Bakersfield, and my CV.

What the repository contains:

- **A static site with no build step:** plain HTML, CSS and JavaScript. I edit a file, commit and
  push, and GitHub Pages publishes it.
- **Personal projects that run in the browser:** Breakaway, a hockey shootout against an AI goalie,
  and Hangman.
- **Coursework from thirteen courses:** each lab has its own page explaining what the program does,
  what I wrote and how to build and run it. The PHP projects are posted as code, since GitHub Pages
  doesn't run PHP.
- **Automated tests for Breakaway:** a GitHub Actions workflow runs the game's tests on every push
  that changes it.

---

## Features

| Component | Details |
| :--- | :--- |
| **Architecture** | <ul><li>Static site hosted on GitHub Pages</li><li>Separate pages for the homepage, Projects, each project and every coursework lab</li><li>Plain HTML, CSS and JavaScript; no framework and no build step</li></ul> |
| **Design** | <ul><li>Design tokens (colors, type, sizes) at the top of <code>style/main.css</code></li><li>Dark theme that follows the visitor's system setting</li><li>The same navigation bar on every page</li></ul> |
| **Code quality** | <ul><li>Every file starts with a comment block listing its sections and common problems to check</li><li>Breakaway keeps its game rules in plain modules separate from browser code, with JSDoc types checked by TypeScript</li></ul> |
| **Documentation** | <ul><li>A README for every course and lab</li><li>Breakaway has docs for its physics, goalie AI, rules and browser code, a decisions document, a changelog and an iteration log</li></ul> |
| **Testing** | <ul><li>Breakaway has unit, integration, statistics and site tests that run with Node's built-in test runner</li><li>GitHub Actions runs them on every push that changes the game (<code>.github/workflows/breakaway-tests.yml</code>)</li></ul> |
| **Accessibility** | <ul><li>Skip links, keyboard navigation and visible focus</li><li>Animations are skipped when the visitor's system has "Reduce motion" turned on</li></ul> |
| **Privacy** | <ul><li>No analytics, cookies or tracking</li><li>Breakaway saves only its settings and best scores in the visitor's browser, and nothing is sent anywhere</li></ul> |
| **Dependencies** | <ul><li>The site has none to install. The homepage loads the Inter font from Google Fonts and anime.js from cdnjs</li><li>Breakaway's <code>package.json</code> lists development tools only (Playwright, ESLint, TypeScript)</li></ul> |

---

## Project Structure

```sh
└── ChristianRodriguez46.github.io/
    ├── .github
    │   └── workflows
    ├── .nojekyll
    ├── Coursework
    │   ├── README.md
    │   ├── cmps2010
    │   ├── cmps2020
    │   ├── cmps2650
    │   ├── cmps2680
    │   ├── cmps3120
    │   ├── cmps3350
    │   ├── cmps3390
    │   ├── cmps3500
    │   ├── cmps3560
    │   ├── cmps3600
    │   ├── cmps3620
    │   ├── cmps3640
    │   ├── cmps3680
    │   ├── index.html
    │   └── snapshots
    ├── LICENSE
    ├── Projects
    │   ├── Breakaway
    │   ├── Hangman
    │   └── index.html
    ├── README.md
    ├── images
    │   ├── apple-touch-icon.png
    │   ├── logo.png
    │   └── logo.svg
    ├── index.html
    ├── js
    │   └── main.js
    ├── resume
    │   └── Christian_Rodriguez_Resume.pdf
    └── style
        ├── coursework.css
        └── main.css
```

---

### Project Index

<details open>
	<summary><b><code>CHRISTIANRODRIGUEZ46.GITHUB.IO/</code></b></summary>
	<!-- __root__ Submodule -->
	<details>
		<summary><b>__root__</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/README.md'>README.md</a></b></td>
					<td style='padding: 8px;'>- This file: an overview of the repository, how to run the site locally and what each folder holds.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/index.html'>index.html</a></b></td>
					<td style='padding: 8px;'>- My homepage: introduction, tiles for Coursework, Breakaway and Hangman, About me and Contact.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/LICENSE'>LICENSE</a></b></td>
					<td style='padding: 8px;'>- The MIT License for the code I wrote. The License section below lists what it doesn't cover.</td>
				</tr>
			</table>
		</blockquote>
	</details>
	<!-- .github Submodule -->
	<details>
		<summary><b>.github</b></summary>
		<blockquote>
			<!-- workflows Submodule -->
			<details>
				<summary><b>workflows</b></summary>
				<blockquote>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/.github/workflows/breakaway-tests.yml'>breakaway-tests.yml</a></b></td>
							<td style='padding: 8px;'>- Automates testing of Breakaways core game code on every code change, ensuring ongoing code quality and stability<br>- Integrates with GitHub workflows to run the Node.js test suite within the projects specific directory, providing continuous validation without affecting deployment or publishing processes<br>- This setup maintains reliable development cycles and early detection of issues in the game development pipeline.</td>
						</tr>
					</table>
				</blockquote>
			</details>
		</blockquote>
	</details>
	<!-- Coursework Submodule -->
	<details>
		<summary><b>Coursework</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/index.html'>index.html</a></b></td>
					<td style='padding: 8px;'>- OverviewThe <code>Coursework/index.html</code> file serves as the main entry point for a personal portfolio website showcasing Christian Rodriguezs academic projects and coursework from CSU Bakersfield<br>- It provides a structured, visually engaging interface that introduces visitors to his lab work and programming projects<br>- Within the broader codebase, this file functions as the central HTML document that organizes and displays the content, integrating styles and scripts to deliver a polished, responsive user experience.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/README.md'>README.md</a></b></td>
					<td style='padding: 8px;'>- Provides a comprehensive collection of coursework projects across multiple computer science disciplines, showcasing practical implementations and demonstrations<br>- Serves as an educational resource illustrating foundational programming concepts, data structures, algorithms, web development, and system administration through hands-on labs and projects<br>- Facilitates learning and experimentation within a structured, course-based architecture.</td>
				</tr>
			</table>
			<!-- cmps2010 Submodule -->
			<details>
				<summary><b>cmps2010</b></summary>
				<blockquote>
					<!-- final-project Submodule -->
					<details>
						<summary><b>final-project</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/final-project/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Facilitates user interaction for reviewing restaurants by collecting details such as name, type, style, location count, and rating<br>- Stores input in dynamic Restaurant objects and outputs the compiled reviews as CSV lines into reviews.csv<br>- Serves as the main interface within the overall architecture, enabling data entry, object management, and file export for the restaurant review application.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/final-project/Main.cpp'>Main.cpp</a></b></td>
									<td style='padding: 8px;'>- Facilitates user input to gather restaurant details and stores them in a dynamic array<br>- Generates a CSV report summarizing each restaurants information, supporting data analysis and review management within the overall application architecture<br>- Ensures proper memory management and file handling to maintain data integrity and program stability.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/final-project/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates user input to gather restaurant details, storing reviews in a dynamic array of Restaurant objects<br>- Ensures data persistence by exporting the collected reviews to a CSV file, enabling organized review management within the overall application architecture<br>- This component serves as the core interface for user interaction and data collection in the restaurant review system.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/final-project/Restaurant.cpp'>Restaurant.cpp</a></b></td>
									<td style='padding: 8px;'>- Defines the Restaurant class, encapsulating restaurant attributes such as name, type, style, number of locations, and score<br>- Facilitates creation, initialization, and serialization of restaurant data into CSV format, supporting data management and interchange within the broader application architecture<br>- Serves as a core data model for representing restaurant entities across the system.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/final-project/Restaurant.h'>Restaurant.h</a></b></td>
									<td style='padding: 8px;'>- Defines the Restaurant class, encapsulating key attributes such as name, type, style, number of locations, and score<br>- Serves as a foundational component within the project’s architecture to model restaurant entities, enabling data management and manipulation for applications related to restaurant information, analysis, or display<br>- Facilitates structured representation and export of restaurant data in CSV format.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/lab01/helo.cpp'>helo.cpp</a></b></td>
									<td style='padding: 8px;'>- Outputs a simple greeting message to verify the basic functionality of the development environment<br>- It serves as an introductory exercise within the coursework, demonstrating fundamental programming concepts such as input/output operations and program structure, and establishing a foundation for understanding how individual components integrate within the overall project architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2010/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of the coursework project focused on introductory C++ programming<br>- Demonstrates fundamental programming concepts such as output, arithmetic operations, and modular arithmetic through simple programs<br>- Serves as an educational resource illustrating basic syntax, library usage, and program structure within the broader architecture of foundational programming labs.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps2020 Submodule -->
			<details>
				<summary><b>cmps2020</b></summary>
				<blockquote>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/baseProg.cpp'>baseProg.cpp</a></b></td>
							<td style='padding: 8px;'>- Establishes a foundational entry point for the project, serving as the initial execution point within the overall architecture<br>- It provides a minimal structure to facilitate further development and integration of core functionalities, ensuring the program can be compiled and run successfully as part of the broader coursework framework.</td>
						</tr>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/baseProg.cpp.html'>baseProg.cpp.html</a></b></td>
							<td style='padding: 8px;'>- Provides a foundational C++ template with an empty main function, streamlining the creation of new lab programs within the coursework<br>- Serves as a standardized starting point, ensuring consistency across assignments while including essential libraries and minimal structure for quick setup and development.</td>
						</tr>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/README.md'>README.md</a></b></td>
							<td style='padding: 8px;'>- Provides foundational structure and setup for weekly data structures labs in C++, enabling students to develop and test implementations of various concepts such as arrays, linked lists, stacks, queues, and trees<br>- Serves as a starting point for coding exercises, ensuring a consistent environment across assignments and facilitating incremental learning of core data structures within the broader coursework architecture.</td>
						</tr>
					</table>
					<!-- review2 Submodule -->
					<details>
						<summary><b>review2</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/review2/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Implements a dynamic array class, SmartArray, to store strings with automatic resizing capabilities<br>- Facilitates adding and displaying elements, demonstrating concepts of memory management, resizing, and class design in C++<br>- Serves as an educational example for understanding dynamic data structures and memory handling within the broader coursework on data structures and algorithms.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/review2/r1.cpp'>r1.cpp</a></b></td>
									<td style='padding: 8px;'>- Implements a dynamic array structure that manages a collection of strings, allowing efficient addition and automatic resizing as the collection grows<br>- Serves as a core utility within the project to handle variable-sized data storage, supporting flexible data management and demonstrating fundamental object-oriented programming principles in the overall architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/review2/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Implements a SmartArray class that dynamically resizes by doubling its capacity when full, facilitating efficient management of array storage<br>- Serves as a practice exercise for understanding dynamic arrays and resizing techniques, contributing to the overall data structures curriculum and exam preparation<br>- This core component demonstrates fundamental concepts of memory management and scalable array design.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- wk02 Submodule -->
					<details>
						<summary><b>wk02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2020/wk02/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Defines the webpage structure for Week 2 coursework on classes and operator overloading in C++<br>- It presents an overview of lab activities, concepts, and code implementations related to Point and Map classes, emphasizing operator overloading and class design<br>- Serves as the main interface for students to access project details, instructions, and related resources within the course architecture.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps2650 Submodule -->
			<details>
				<summary><b>cmps2650</b></summary>
				<blockquote>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/index.html'>index.html</a></b></td>
							<td style='padding: 8px;'>- This HTML file serves as the central webpage for displaying and organizing the answers to CMPS 2650 Linux Labs<br>- It functions as an interactive, navigable interface that categorizes each lab within distinct sections, allowing users to easily access and review lab solutions<br>- Overall, it provides a structured and user-friendly presentation layer for the coursework content, integrating styling and navigation to support efficient learning and reference within the broader project architecture.</td>
						</tr>
					</table>
					<!-- lab04 Submodule -->
					<details>
						<summary><b>lab04</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab04/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates understanding of basic text pattern matching using grep with regular expressions in a Linux environment<br>- Demonstrates practical command usage on sample data, supporting foundational skills in text processing and command-line tools essential for system administration and scripting tasks within the broader course architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab04/text.txt'>text.txt</a></b></td>
									<td style='padding: 8px;'>- Provides a curated list of diverse textual data, including names, locations, brands, and entities, serving as a foundational dataset for text processing, analysis, or natural language processing tasks within the project<br>- It supports the development of features such as search, categorization, or pattern recognition by offering varied real-world examples to enhance model training or testing.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab06 Submodule -->
					<details>
						<summary><b>lab06</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab06/hello.cpp'>hello.cpp</a></b></td>
									<td style='padding: 8px;'>- Implements an infinite loop that continuously outputs the message hello to the console, serving as a basic demonstration of control flow and output operations within the project<br>- It exemplifies fundamental programming constructs used for understanding program execution flow, contributing to foundational learning in the context of the overall coursework architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab06/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates practice in vim editing techniques and shell customization within a Linux environment<br>- It demonstrates code re-indentation, folding, and shell profile adjustments to enhance command-line efficiency<br>- The focus is on developing skills for navigating and formatting code effectively, supporting foundational Linux and programming workflows in the context of coursework.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab07 Submodule -->
					<details>
						<summary><b>lab07</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab07/argcount.cpp'>argcount.cpp</a></b></td>
									<td style='padding: 8px;'>- Counts and reports the number of command-line arguments provided, excluding the program name<br>- It serves as a utility within the project to process input parameters, facilitating argument validation or dynamic behavior based on user input<br>- This component integrates into the overall architecture by enabling argument-based control flow and input handling for the application.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2650/lab07/hello.cpp'>hello.cpp</a></b></td>
									<td style='padding: 8px;'>- Provides a foundational entry point for the project by setting up the main execution flow<br>- It initializes the program, serving as the starting point for further development and integration within the overall architecture<br>- This file establishes the basic structure necessary for executing and testing core functionalities in the coursework environment.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps2680 Submodule -->
			<details>
				<summary><b>cmps2680</b></summary>
				<blockquote>
					<!-- final-project Submodule -->
					<details>
						<summary><b>final-project</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/booking.html'>booking.html</a></b></td>
									<td style='padding: 8px;'>- Provides a user-friendly interface for scheduling vehicle detailing appointments, capturing personal information, selecting service packages, and customizing specific exterior and interior treatments<br>- Integrates form validation and dynamic content updates to facilitate seamless booking management within the overall website architecture for Wise Choice Detailing.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/contact.html'>contact.html</a></b></td>
									<td style='padding: 8px;'>- Provides the structure and content for the contact page, enabling users to submit personal information and messages to Wise Choice Detailing<br>- Facilitates user interaction through a contact form, integrates styling and scripts for dynamic behavior, and includes navigation and social media links to support seamless communication within the websites architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/contact.js'>contact.js</a></b></td>
									<td style='padding: 8px;'>- Facilitates user interaction by handling form submissions, validating input fields, and providing immediate feedback<br>- Ensures users fill out all required information before displaying a personalized confirmation message<br>- Integrates seamlessly into the contact section of the website, enhancing user experience through real-time validation and acknowledgment within the overall web application architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/gallery.html'>gallery.html</a></b></td>
									<td style='padding: 8px;'>- The <code>gallery.html</code> file serves as the central interface for displaying a visual collection of images within the web application<br>- It provides a user-friendly gallery view that showcases images related to Wise Choice Detailing, enabling users to browse and interact with visual content seamlessly<br>- This component integrates styling and scripting to facilitate dynamic image presentation and user interactions, forming a key part of the application's frontend architecture dedicated to visual content management and display.</td>
								</tr>
							</table>
							<!-- experiments Submodule -->
							<details>
								<summary><b>experiments</b></summary>
								<blockquote>
									<table style='width: 100%; border-collapse: collapse;'>
									<thead>
										<tr style='background-color: #f8f9fa;'>
											<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
											<th style='text-align: left; padding: 8px;'>Summary</th>
										</tr>
									</thead>
										<tr style='border-bottom: 1px solid #eee;'>
											<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/experiments/e1.html'>e1.html</a></b></td>
											<td style='padding: 8px;'>- Defines a comprehensive booking interface for Wise Choice Detailing, enabling users to input personal details, select service packages, and customize interior and exterior detailing options<br>- Facilitates user data collection and validation, supporting the overall architecture of an online appointment scheduling system within the web application.</td>
										</tr>
										<tr style='border-bottom: 1px solid #eee;'>
											<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/experiments/form-check.js'>form-check.js</a></b></td>
											<td style='padding: 8px;'>- Implements client-side form validation by disabling submission for invalid fields, ensuring user input adheres to specified constraints before processing<br>- Integrates seamlessly with Bootstrap styles to provide visual feedback on validation status, enhancing user experience and data integrity across the applications user interface.</td>
										</tr>
										<tr style='border-bottom: 1px solid #eee;'>
											<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps2680/final-project/experiments/script1.js'>script1.js</a></b></td>
											<td style='padding: 8px;'>- Facilitates dynamic display and validation of user input from URL parameters and form selections, ensuring accurate presentation of personal information and selected services<br>- Enhances user experience by validating form submissions and rendering personalized summaries, supporting the overall architecture of an interactive web application that manages service packages and individual service choices.</td>
										</tr>
									</table>
								</blockquote>
							</details>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3120 Submodule -->
			<details>
				<summary><b>cmps3120</b></summary>
				<blockquote>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/factorial.c'>factorial.c</a></b></td>
							<td style='padding: 8px;'>- Calculates the factorial of a user-provided non-negative integer, serving as a fundamental utility within the project to demonstrate basic control structures and input handling in C<br>- It supports core computational functionality, enabling further integration or extension in larger applications or educational contexts focused on algorithm implementation.</td>
						</tr>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/factorial.c.html'>factorial.c.html</a></b></td>
							<td style='padding: 8px;'>- Implements a factorial calculator that reads an integer input, validates for negativity, and computes its factorial using a loop within an unsigned long long type<br>- Handles overflow for inputs above 20 by wrapping around, providing user feedback for invalid inputs<br>- Serves as a core component for demonstrating input validation, looping constructs, and factorial computation within the overall programming coursework architecture.</td>
						</tr>
					</table>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Generates all valid stack-based push/pop sequences (stacky strings) of length 2n, verifying their count against Catalan numbers, and enumerates permutations producible by a stack<br>- Additionally, tests random permutations to identify stackability, supporting analysis of stack operations and combinatorial properties within the broader algorithmic and data structure architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/lab01/lab1.c'>lab1.c</a></b></td>
									<td style='padding: 8px;'>- Generates and analyzes stacky strings and permutations, providing counts based on combinatorial formulas and verifying permutation properties<br>- Facilitates exploration of stack-based structures, enabling enumeration, validation, and random generation of stacky sequences within the broader architecture focused on combinatorial and permutation analysis.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/lab01/output.txt'>output.txt</a></b></td>
									<td style='padding: 8px;'>- Generates and verifies stacky strings and permutations of a specified length, illustrating combinatorial structures and their counts<br>- Facilitates exploration of stacky sequence properties, enumeration, and validation within the broader project architecture focused on combinatorial analysis and sequence generation<br>- Supports understanding of stack-based arrangements and their mathematical characteristics across different sizes.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Generates all valid stack push/pop sequences of length 2n, verifies their count against Catalan numbers, and explores stack-sortable permutations<br>- Facilitates understanding of stack operations, combinatorial structures, and permutation sorting properties, serving as a foundational tool for analyzing stack-based algorithms and their theoretical limits within the project’s architecture.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab02 Submodule -->
					<details>
						<summary><b>lab02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3120/lab02/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Implements four guessing strategies against a black box with a hidden number, measuring their efficiency through timing<br>- Facilitates comparison of linear search, random guessing, and halving methods, demonstrating concepts like binary search and randomized search within the overall coursework architecture<br>- Integrates with instructor-provided black-box functions to validate solutions and record performance data.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3350 Submodule -->
			<details>
				<summary><b>cmps3350</b></summary>
				<blockquote>
					<!-- casino-game Submodule -->
					<details>
						<summary><b>casino-game</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/akoli.cpp'>akoli.cpp</a></b></td>
									<td style='padding: 8px;'>- The <code>akoli.cpp</code> file serves as the core implementation for the slot machine component within the overall casino game architecture<br>- It orchestrates the games main functionalities, including rendering graphics, managing user interactions, and controlling game logic related to the slot machine mechanics<br>- By integrating various modules such as fonts, images, reels, and global settings, this file ensures a cohesive and interactive experience, acting as the central hub that ties together the visual presentation and gameplay flow of the slot machine feature in the project.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/bolayvar.cpp'>bolayvar.cpp</a></b></td>
									<td style='padding: 8px;'>- The <code>bolayvar.cpp</code> file serves as a central implementation component within the casino game project, specifically supporting the Blackjack module<br>- It orchestrates core game functionalities such as managing game state, handling user interactions, and integrating visual elements through OpenGL and X11 libraries<br>- By including various headers related to game components, graphics, and input handling, this file facilitates the overall gameplay experience, ensuring seamless interaction between the user interface and game logic<br>- In the broader architecture, <code>bolayvar.cpp</code> acts as a pivotal link that enables the Blackjack game to operate smoothly within the applications graphical environment, contributing to the modular and interactive design of the casino game system.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/button.cpp'>button.cpp</a></b></td>
									<td style='padding: 8px;'>- Defines and initializes multiple button objects used for user interaction within the casino game interface<br>- These buttons facilitate navigation, game selection, and control functions, integrating with the overall architecture to enable seamless user input handling and enhance the interactive experience across different game modules.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/crodriguez4.cpp'>crodriguez4.cpp</a></b></td>
									<td style='padding: 8px;'>- The <code>crodriguez4.cpp</code> file serves as a central component of the casino game project, primarily responsible for managing the core game logic and rendering functionalities<br>- It integrates graphical assets such as dice and chip textures, facilitating visual representation of game elements<br>- This file orchestrates interactions related to the casino game, including dice rolls and chip handling, contributing to the overall architecture by linking game mechanics with graphical output<br>- Its role is essential in delivering an interactive and visually engaging user experience within the broader system.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/hchen.cpp'>hchen.cpp</a></b></td>
									<td style='padding: 8px;'>- The <code>hchen.cpp</code> file serves as a core component of the casino game project, primarily responsible for managing the introductory animation, displaying game information, and implementing the core logic for the Blackjack game<br>- It integrates visual elements and game mechanics to deliver an engaging user experience within the overall architecture, which includes modules for graphics rendering, user interface, and game state management<br>- This file acts as a pivotal link between visual presentation and game functionality, contributing to the seamless operation of the casino game application.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/image.cpp'>image.cpp</a></b></td>
									<td style='padding: 8px;'>- Loads and converts image files into an in-memory pixel data structure, supporting both direct PPM files and other formats via conversion<br>- Facilitates image data access for rendering or processing within the broader casino game project, enabling visual representation and manipulation of graphical assets essential for the applications graphical interface.</td>
								</tr>
							</table>
							<!-- include Submodule -->
							<details>
								<summary><b>include</b></summary>
								<blockquote>
									<table style='width: 100%; border-collapse: collapse;'>
									<thead>
										<tr style='background-color: #f8f9fa;'>
											<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
											<th style='text-align: left; padding: 8px;'>Summary</th>
										</tr>
									</thead>
										<tr style='border-bottom: 1px solid #eee;'>
											<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3350/casino-game/include/blackjack.h'>blackjack.h</a></b></td>
											<td style='padding: 8px;'>- Defines the core data structures and state management for a blackjack game, encapsulating card representations, player and dealer hands, game status flags, and betting information<br>- Serves as the foundational component for orchestrating game logic, ensuring consistent handling of game states, card operations, and user interactions within the overall casino game architecture.</td>
										</tr>
									</table>
								</blockquote>
							</details>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3390 Submodule -->
			<details>
				<summary><b>cmps3390</b></summary>
				<blockquote>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab01/app.cpp'>app.cpp</a></b></td>
									<td style='padding: 8px;'>- Provides a foundational entry point for the application, displaying a welcome message to users<br>- It serves as the initial interaction within the overall project architecture, confirming successful setup and execution<br>- This simple interface helps verify that the environment is correctly configured, supporting further development and integration of additional features within the courseworks broader software structure.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides a comprehensive webpage for Lab 1, showcasing a simple C++ programs execution and demonstrating version control practices<br>- It guides users through building, running, and managing the project with Git, while integrating navigation, styling, and visual elements to support educational engagement within the coursework architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab01/README-original.md'>README-original.md</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of fundamental version control concepts through a simple application, illustrating key workflows such as staging, committing, branching, merging, and collaborating via Git and GitHub<br>- Serves as an educational tool to demonstrate essential practices for managing code changes, fostering collaboration, and understanding the core mechanics of version control within a learning environment.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates hands-on practice with core Git and GitHub workflows through a minimal C++ application, enabling students to master version control concepts such as staging, committing, branching, merging, and collaboration via pull requests within the context of application development<br>- Serves as an educational tool to reinforce understanding of version management in software projects.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab08 Submodule -->
					<details>
						<summary><b>lab08</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab08/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of the Lab 8 web interface for JSON search and replace functionalities<br>- It presents a user-friendly HTML page that guides users through the purpose of the PHP endpoints, demonstrating how they highlight or replace whole-word matches in text<br>- Serves as the primary front-end for interacting with server-side scripts within the overall application architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3390/lab08/lib.php'>lib.php</a></b></td>
									<td style='padding: 8px;'>- Provides foundational utility functions for handling HTML responses and error reporting within the web application<br>- Ensures consistent formatting of error messages and successful responses, facilitating smooth communication between server and client<br>- Supports the overall architecture by standardizing output and error handling, thereby enhancing robustness and maintainability of the project’s web interface.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3500 Submodule -->
			<details>
				<summary><b>cmps3500</b></summary>
				<blockquote>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab01/hello.c'>hello.c</a></b></td>
									<td style='padding: 8px;'>- Provides a fundamental entry point for the project by outputting a greeting message, demonstrating basic program structure and I/O operations<br>- Serves as an initial step in understanding core programming concepts within the coursework, establishing a foundation for more complex functionalities in the overall codebase<br>- Acts as a simple example of compiling and executing C programs in the learning environment.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of the lab session focused on fundamental Linux and C programming tasks<br>- Demonstrates writing, backing up, and securing files, managing processes, terminating shells, compiling and executing a C program, and recording the session for replay<br>- Serves as an instructional guide illustrating essential command-line operations and scripting techniques within the courses Linux environment.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab01/lab1.txt'>lab1.txt</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of the initial lab activity within the coursework, establishing foundational understanding for subsequent project components<br>- Serves as an introductory reference point that contextualizes the beginning of the learning journey in the broader codebase architecture, emphasizing the importance of foundational knowledge for progressing through the project.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates the compilation and execution of a basic C program on the Linux server, capturing the terminal session output for review<br>- It serves as an introductory step in the coursework to demonstrate fundamental C programming, compilation, and session recording techniques within the courses architecture, supporting students understanding of programming workflows and environment setup.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab02 Submodule -->
					<details>
						<summary><b>lab02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab02/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Overview of <code>index.html</code>This HTML file serves as the main webpage for the CMPS 3500 Lab 02 project, providing an interface to demonstrate the functionality of a C++ template class <code>List</code> with fixed capacity and exception handling<br>- It presents an educational visualization of how the <code>List</code> class manages data, including filling lists with random values, handling index errors through custom exceptions, and logging these events<br>- Overall, it acts as the user-facing component that showcases the core concepts of C++ templates, exception handling, and program robustness within the context of the lab assignment.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3500/lab02/lab02.cpp'>lab02.cpp</a></b></td>
									<td style='padding: 8px;'>- Implements a test harness for a generic List class, demonstrating core functionalities such as adding, sorting, swapping, and comparing elements across different data types<br>- It validates list operations, handles exceptions, and verifies object copying, thereby ensuring robustness and correctness within the overall system architecture.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3560 Submodule -->
			<details>
				<summary><b>cmps3560</b></summary>
				<blockquote>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab01/expsys.cpp'>expsys.cpp</a></b></td>
									<td style='padding: 8px;'>- Implements a rule-based classification system for iris dataset samples, predicting species based on petal length<br>- It reads data from a CSV, applies a simple expert rule to classify each sample, and evaluates prediction accuracy against ground truth labels<br>- This component facilitates understanding of basic decision rules within the broader machine learning or data analysis architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Implements a web-based demonstration of a simple rule-based classifier for iris flowers, showcasing how petal width above 1.6 predicts Virginica, otherwise Versicolor<br>- It processes the iris dataset, displays individual predictions alongside true labels, and reports overall accuracy, serving as an educational tool within the broader AI coursework architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Implements a rule-based classification system for iris flowers by reading CSV data and applying handcrafted rules to distinguish between Versicolor and Virginica<br>- It outputs predictions alongside true labels, demonstrating fundamental expert system concepts and data processing within the broader AI coursework architecture.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab02 Submodule -->
					<details>
						<summary><b>lab02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab02/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Implements forward chaining inference over a small rule base by iteratively applying rules to known facts, inferring new conclusions until no further changes occur<br>- Facilitates understanding of rule-based reasoning processes, demonstrating how facts and rules interact to derive new knowledge in an AI context<br>- Serves as an educational example within the coursework architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab02/Lab2.py'>Lab2.py</a></b></td>
									<td style='padding: 8px;'>- Implements a forward chaining inference engine to derive new facts from initial data and rules<br>- It iteratively applies logical rules to expand the knowledge base until no further inferences can be made, enabling automated reasoning about object classifications based on observed attributes within the knowledge architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3560/lab02/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Implements forward chaining inference by iteratively applying rules to a facts database, expanding knowledge until no new facts emerge<br>- Serves as a core component for rule-based reasoning within the project, demonstrating how logical inference progresses through systematic rule application in an AI context<br>- Facilitates understanding of automated knowledge acquisition processes.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3600 Submodule -->
			<details>
				<summary><b>cmps3600</b></summary>
				<blockquote>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of Lab 1s webpage, highlighting its purpose to showcase a project that demonstrates replacing C++ standard library I/O with POSIX system calls<br>- It guides users through the projects context, implementation details, and usage instructions, emphasizing the educational focus on system call-based file operations within the broader operating systems coursework.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/lab1.c'>lab1.c</a></b></td>
									<td style='padding: 8px;'>- Facilitates user interaction by prompting for a name and number, then computes the sum from 1 to the provided number<br>- Stores the users name and the calculated summation in a log file, supporting data collection and record-keeping within the overall application architecture<br>- This component enables basic input processing and persistent data logging functionality.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/lab1.cpp'>lab1.cpp</a></b></td>
									<td style='padding: 8px;'>- Facilitates user input collection and logs personal information along with the calculated summation of numbers up to a specified value<br>- Integrates basic file handling to record data, serving as an introductory example of input/output operations within the broader codebase focused on foundational programming concepts.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/log'>log</a></b></td>
									<td style='padding: 8px;'>- Provides a log entry capturing the outcome of a summation operation from 1 to 6218, resulting in 19334871<br>- Serves as a record within the overall project architecture, likely supporting validation or debugging processes by documenting computational results during development or testing phases<br>- Facilitates tracking of numerical computations integral to the projects functionality.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/Makefile'>Makefile</a></b></td>
									<td style='padding: 8px;'>- Defines build rules for compiling multiple C and C++ programs, ensuring proper dependencies and compilation commands<br>- Facilitates efficient project management by automating the creation of executable files for different components, supporting the overall architecture of the coursework project<br>- Serves as the central Makefile orchestrating the build process across various source files within the codebase.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3600/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Implements a low-level C program that reads user input, performs a summation calculation, and logs the output using system calls<br>- It demonstrates fundamental file and I/O operations in Linux, replacing standard C++ library functions with direct system call interfaces<br>- This code serves as a foundational example of operating system interactions and file management within the broader architecture of the coursework.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3620 Submodule -->
			<details>
				<summary><b>cmps3620</b></summary>
				<blockquote>
					<!-- homework02 Submodule -->
					<details>
						<summary><b>homework02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/homework02/answer.tex'>answer.tex</a></b></td>
									<td style='padding: 8px;'>- Provides comprehensive solutions to fundamental networking and communication problems, including data rate calculations under various channel conditions, advantages of fiber optics, satellite transmission delays, encoding techniques, and network topology analyses<br>- Serves as an educational resource to reinforce core concepts in digital communication, network architecture, and signal processing within the broader coursework.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/homework02/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides a comprehensive overview of the physical-layer problem solutions for CMPS 3620 Homework 2, including detailed calculations, signal processing steps, and encoding techniques<br>- Serves as the primary reference for understanding the problem-solving approach, supporting the overall coursework by demonstrating applied concepts like Nyquist and Shannon limits, CDMA decoding, and signal encoding within the project structure.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/homework02/questions.txt'>questions.txt</a></b></td>
									<td style='padding: 8px;'>- Provides a comprehensive set of networking and communication questions covering data transmission, encoding, modulation, satellite communication, and network topologies<br>- Serves as an educational resource to reinforce key concepts in digital communication systems, emphasizing theoretical understanding and problem-solving skills within the broader coursework on communication networks.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/homework02/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Provides solutions to textbook questions on physical layer concepts, including maximum data rates over noiseless and noisy channels, based on Nyquist and Shannon limits<br>- Serves as a comprehensive reference for understanding signal encoding and channel capacity within the coursework, supporting students in analyzing and applying fundamental principles of digital communication systems.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides a comprehensive overview of network diagnostic tools and their outputs, serving as an instructional resource within the coursework<br>- It demonstrates practical applications of tools like dig, ping, traceroute, ss, and telnet, illustrating their roles in analyzing DNS records, network routes, and socket states, thereby supporting understanding of core networking concepts in the broader course architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3620/lab01/lab-writeup.tex'>lab-writeup.tex</a></b></td>
									<td style='padding: 8px;'>- Provides a comprehensive overview of network diagnostic tools and DNS querying techniques within the Odin environment<br>- It demonstrates how to interpret command outputs, troubleshoot connectivity issues, and analyze network services, emphasizing understanding of DNS records, socket states, and network reachability<br>- This documentation supports effective network troubleshooting and system administration within the broader infrastructure.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3640 Submodule -->
			<details>
				<summary><b>cmps3640</b></summary>
				<blockquote>
					<!-- lab01 Submodule -->
					<details>
						<summary><b>lab01</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab01/ArrayOp.cpp'>ArrayOp.cpp</a></b></td>
									<td style='padding: 8px;'>- Performs large-scale array operations with optional multithreading to optimize computational efficiency<br>- It initializes, processes, and measures execution time of element-wise cosine and sine calculations across extensive datasets, supporting both sequential and parallel execution modes<br>- This component is integral to the architecture by demonstrating scalable, high-performance numerical computations within the overall system.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab01/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Provides an overview of the lab assignment focused on benchmarking multithreaded array operations in C++<br>- It details the purpose of timing sequential and parallel executions, measuring speedup across varying thread counts, and visualizing performance results<br>- The page integrates instructions, snapshots, and links to relevant code, supporting understanding of parallel computation concepts within the project architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab01/output.txt'>output.txt</a></b></td>
									<td style='padding: 8px;'>- Provides performance metrics for a multithreaded application, capturing execution times across multiple runs with specified thread counts<br>- Serves as a benchmarking record within the project, enabling analysis of parallel processing efficiency and consistency, and supporting performance optimization efforts across the overall codebase architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab01/README.md'>README.md</a></b></td>
									<td style='padding: 8px;'>- Facilitates performance measurement of large array addition using multithreading, enabling comparison of execution times across varying thread counts<br>- It demonstrates how parallelism impacts computational speedup, serving as an educational tool within the broader context of distributed and parallel computation<br>- The code supports analyzing efficiency gains in multi-core environments, integral to understanding scalable parallel algorithms.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab01/runlab'>runlab</a></b></td>
									<td style='padding: 8px;'>- Automates the execution of the ArrayOp program multiple times based on user input, facilitating batch testing or performance evaluation<br>- It manages command-line arguments to run ArrayOp with or without parameters, streamlining repetitive testing processes within the coursework environment and supporting the overall architecture of the lab by ensuring consistent program execution.</td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- lab02 Submodule -->
					<details>
						<summary><b>lab02</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3640/lab02/ArrayOpOMP.cpp'>ArrayOpOMP.cpp</a></b></td>
									<td style='padding: 8px;'>- Performs parallel array operations using OpenMP to compute a mathematical transformation on large datasets<br>- It initializes two arrays with random values, then applies a cosine and sine combination to produce a third array, leveraging multiple threads for efficiency<br>- This component is integral to the project’s focus on high-performance, parallelized numerical computations within the overall architecture.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- cmps3680 Submodule -->
			<details>
				<summary><b>cmps3680</b></summary>
				<blockquote>
					<!-- final-project Submodule -->
					<details>
						<summary><b>final-project</b></summary>
						<blockquote>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/booking.php'>booking.php</a></b></td>
									<td style='padding: 8px;'>- Booking.phpThis file serves as the core processing script for handling booking requests within the application<br>- It manages user input validation, sanitization, and error handling for booking forms, ensuring that customer data and service selections are correctly captured before being stored or further processed<br>- As a central component of the booking workflow, it facilitates the collection of essential customer information and service choices, contributing to the overall architecture by enabling reliable and secure booking operations.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/contact.html'>contact.html</a></b></td>
									<td style='padding: 8px;'>- Provides a user-friendly contact interface for Wise Choice Detailing, enabling visitors to submit inquiries, service requests, or order modifications<br>- Integrates a structured form for capturing personal details and messages, complemented by navigation and branding elements<br>- Facilitates communication between customers and the business, supporting engagement and service management within the overall website architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/contact.php'>contact.php</a></b></td>
									<td style='padding: 8px;'>- Handles contact form submissions by validating user input, compiling message details, and sending email notifications to the designated recipient<br>- Integrates form processing with user feedback display and maintains consistent site navigation and styling, supporting seamless user communication and ensuring data integrity within the overall website architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/gallery.html'>gallery.html</a></b></td>
									<td style='padding: 8px;'>- Overview of <code>gallery.html</code>The <code>gallery.html</code> file serves as the main interface for displaying a visual collection of images within the project<br>- It functions as the central component of the applications user interface, providing users with an organized and responsive gallery view<br>- This file integrates Bootstrap for styling and layout, ensuring a polished and accessible presentation across devices<br>- Additionally, it links to a dedicated JavaScript file (<code>gallery.js</code>) that manages dynamic interactions, such as loading images, handling user actions, and updating the gallery content in real-time<br>- Overall, <code>gallery.html</code> is pivotal in delivering an engaging and interactive visual browsing experience, forming the core of the application's front-end architecture for image display.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/home.html'>home.html</a></b></td>
									<td style='padding: 8px;'>- Provides the main structure and content for the homepage of Wise Choice Detailing, showcasing the businesss services, background, and social media integration<br>- It establishes the websites visual layout, navigation, and branding elements, serving as the primary entry point that introduces visitors to the company's mission, offerings, and online presence within the overall web architecture.</td>
								</tr>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Coursework/cmps3680/final-project/index.html'>index.html</a></b></td>
									<td style='padding: 8px;'>- Index.htmlThis file serves as the main entry point for the Wise Choice Detailing website, providing the foundational structure and user interface for the car detailing service<br>- It orchestrates the presentation layer, enabling customers to view service options, book appointments, and submit contact inquiries<br>- Within the overall architecture, <code>index.html</code> integrates with backend PHP scripts and a MySQL database to facilitate appointment scheduling, order validation, and contact form processing, ensuring a seamless and interactive user experience for the mobile car detailing business.</td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
		</blockquote>
	</details>
	<!-- Projects Submodule -->
	<details>
		<summary><b>Projects</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/index.html'>index.html</a></b></td>
					<td style='padding: 8px;'>- My Projects page: a tile for each personal project with links to play it, read about it and view the code.</td>
				</tr>
			</table>
	<!-- Breakaway Submodule -->
	<details>
		<summary><b>Breakaway</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/index.html'>index.html</a></b></td>
					<td style='padding: 8px;'>- The game page: the site navigation, score strip, rink canvas, touch controls, screens and dialogs.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/about.html'>about.html</a></b></td>
					<td style='padding: 8px;'>- The About page on my site: screenshots, how to play, how I built it, and links to the detailed docs.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/README.md'>README.md</a></b></td>
					<td style='padding: 8px;'>- What Breakaway is, how to play, how to run it locally and how to run the tests.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/style.css'>style.css</a></b></td>
					<td style='padding: 8px;'>- The game's design tokens and layout for phones and laptops.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/src/core'>src/core/</a></b></td>
					<td style='padding: 8px;'>- The game rules as plain JavaScript modules with no browser code: physics, collisions, goalie AI, difficulty, scoring and saved-settings validation.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/src/browser'>src/browser/</a></b></td>
					<td style='padding: 8px;'>- The browser side: the fixed-step game loop, canvas drawing, keyboard and touch input, sound, saved data and the screens.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/docs'>docs/</a></b></td>
					<td style='padding: 8px;'>- How the game works (physics, goalie AI, rules and scoring, browser), the decisions behind it, and my study notes and exercises.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/tests'>tests/</a></b></td>
					<td style='padding: 8px;'>- Unit, integration, statistics and site tests run with Node's built-in test runner, plus Playwright browser test setup.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/CHANGELOG.md'>CHANGELOG.md</a></b></td>
					<td style='padding: 8px;'>- Every change to the game, newest first.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/ITERATION_LOG.md'>ITERATION_LOG.md</a></b></td>
					<td style='padding: 8px;'>- Problems I found while building and testing, how I found them and how I fixed them.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Breakaway/SETUP.md'>SETUP.md</a></b></td>
					<td style='padding: 8px;'>- How to set up, run and test the game on Windows with WSL2 and VS Code.</td>
				</tr>
			</table>
		</blockquote>
	</details>
	<!-- Hangman Submodule -->
	<details>
		<summary><b>Hangman</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Hangman/index.html'>index.html</a></b></td>
					<td style='padding: 8px;'>- The Hangman game: clickable letters, an SVG drawing of the hangman and win and lose screens.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Hangman/hangman_word_bank.js'>hangman_word_bank.js</a></b></td>
					<td style='padding: 8px;'>- A bank of 150 programming terms, each with a short hint.</td>
				</tr>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/Projects/Hangman/style.css'>style.css</a></b></td>
					<td style='padding: 8px;'>- The game's styles and animated background.</td>
				</tr>
			</table>
		</blockquote>
	</details>
		</blockquote>
	</details>
	<!-- js Submodule -->
	<details>
		<summary><b>js</b></summary>
		<blockquote>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io/blob/main/js/main.js'>main.js</a></b></td>
					<td style='padding: 8px;'>- Implements core site interactions and animations, enhancing user experience across pages<br>- Manages mobile navigation toggling, orchestrates hero section introductions, animates scroll-triggered elements like hangman tiles and course cards, and synchronizes navigation highlights with content sections<br>- Ensures accessibility and responsiveness, providing smooth, engaging transitions while maintaining functionality on all devices and respecting user motion preferences.</td>
				</tr>
			</table>
		</blockquote>
	</details>
</details>

---

## Getting Started

### Prerequisites

- **To view the site:** any modern browser. Nothing to install.
- **To run it locally:** Git and Python 3 (for a small local web server).
- **To run Breakaway's tests:** Node.js 24 or later.

### Installation

There is nothing to build. Clone the repository:

```sh
git clone https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io
cd ChristianRodriguez46.github.io
```

### Usage

Serve the repository root with a local web server (pages that use JavaScript modules don't load
from `file://`):

```sh
python3 -m http.server 4101
```

Then open [http://localhost:4101/](http://localhost:4101/) in a browser. Stop the server with Ctrl+C.

### Testing

Breakaway is the only part of the site with tests. They use Node's built-in test runner, so
`npm install` isn't needed:

```sh
(cd Projects/Breakaway && npm test)
```

GitHub Actions runs the same tests on every push and pull request that changes the game.

---

## License

The code I wrote in this repository is released under the [MIT License](LICENSE).

These are **not** covered by the MIT License:

- `resume/`: my CV. All rights reserved.
- `images/`: my logo and its icon versions. All rights reserved.
- Images, photos, GIFs and logos inside `Coursework/` that I didn't create, including team and
  school logos (for example the NHL, AHL and ECHL logos in CMPS 2680 `project1` and the CSU
  Bakersfield logo). They belong to their owners and are shown here only as part of class work.
- Code written together with classmates in team projects (CMPS 3350 Software Engineering). It
  belongs to all of its authors.
- Starter code, data files and figures provided by instructors or textbooks. They belong to their
  authors.

---

<div align="left"><a href="#top">Back to top</a></div>

---
