// Updated word & hint bank for Hangman Coding Edition
// 150 distinct terms aligned by index with concise beginner-friendly hints

export const words = [
    // --- Languages & Runtimes ---
    'javascript', 'typescript', 'python', 'java', 'kotlin', 'swift', 'golang', 'rust', 'php', 'ruby',
    'csharp', 'cplusplus', 'dart', 'scala', 'lua', 'perl', 'haskell', 'elixir', 'clojure', 'solidity',

    // --- Markup / Styling ---
    'html', 'css', 'sass', 'less', 'markdown', 'json', 'xml', 'yaml', 'svg', 'canvas',

    // --- Front-End Libraries & Frameworks ---
    'react', 'angular', 'vue', 'svelte', 'jquery', 'nextjs', 'nuxtjs', 'astro', 'solidjs', 'lit',

    // --- Build & Tooling ---
    'webpack', 'vite', 'parcel', 'rollup', 'babel', 'eslint', 'prettier', 'pnpm', 'npm', 'yarn',

    // --- Testing & QA ---
    'jest', 'vitest', 'mocha', 'chai', 'cypress', 'playwright', 'puppeteer', 'selenium', 'storybook', 'axe',

    // --- Node & Back-End Frameworks ---
    'nodejs', 'express', 'fastify', 'nestjs', 'deno', 'django', 'flask', 'spring', 'laravel', 'symfony',

    // --- Databases & Query ---
    'mysql', 'postgres', 'mongodb', 'redis', 'sqlite', 'dynamodb', 'cassandra', 'neo4j', 'graphql', 'prisma',

    // --- DevOps & Cloud ---
    'docker', 'kubernetes', 'ansible', 'terraform', 'jenkins', 'github', 'gitlab', 'bitbucket', 'actions', 'travis',

    // --- Networking & Security ---
    'restapi', 'websocket', 'jwt', 'oauth', 'bcrypt', 'https', 'tls', 'cors', 'csrf', 'ratelimit',

    // --- Data Structures & Algorithms ---
    'array', 'stack', 'queue', 'linkedlist', 'graph', 'tree', 'hashmap', 'sorting', 'searching', 'recursion',

    // --- Patterns & Concepts ---
    'promise', 'callback', 'async', 'await', 'closure', 'prototype', 'inheritance', 'polymorphism', 'encapsulation', 'abstraction',

    // --- Design Patterns ---
    'singleton', 'observer', 'decorator', 'factory', 'command', 'strategy', 'adapter', 'facade', 'iterator', 'mediator',

    // --- Misc Useful Terms ---
    'throttle', 'debounce', 'memoization', 'responsive', 'accessibility', 'linting', 'minification', 'bundling', 'gzip', 'cache'
];

export const hints = [
    // Languages & Runtimes
    'Dynamic language powering most front-end interactions',
    'Typed superset that compiles to JavaScript',
    'Interpreted language known for readability and indents',
    'Object-oriented language running on the JVM',
    'JetBrains language used heavily for Android apps',
    'Apple language for iOS and macOS apps',
    'Compiled language by Google, famous for concurrency',
    'Memory-safe systems language with “borrow checker”',
    'Server-side scripting language, core of WordPress',
    'Dynamic language behind the Rails framework',
    'Microsoft language on .NET platform',
    'C with OOP extensions, used for performance',
    'Google language for Flutter mobile apps',
    'JVM language that mixes OOP and FP',
    'Lightweight embeddable scripting language',
    'Classic scripting language with strong regex support',
    'Pure functional language with strong static types',
    'Erlang-based functional language for fault tolerance',
    'Lisp dialect running on the JVM',
    'Smart-contract language for Ethereum',

    // Markup / Styling
    'Markup language that structures web documents',
    'Styles web pages with selectors and rules',
    'CSS extension adding variables and nesting',
    'Another CSS pre-processor using @import',
    'Lightweight markup for README files',
    'Lightweight data-interchange format (key:value)',
    'Markup with angle-bracket tags for data',
    'Human-readable data serialization with indentation',
    'XML-based vector image format',
    'HTML element for pixel-graphics drawing',

    // Front-End Frameworks
    'Component-based UI library by Meta',
    "Google's opinionated SPA framework",
    'Progressive framework using template syntax',
    'Compiler that turns components into minimal JS',
    'Early DOM manipulation helper library',
    'React framework for server-side rendering',
    'Vue framework for server-side rendering',
    'Content-focused static-site builder',
    'Declarative UI library with fine-grain reactivity',
    'Lightweight web components library',

    // Build & Tooling
    'Bundler that builds dependency graph',
    'Fast dev server & bundler from Evan You',
    'Zero-config web-app bundler',
    'ES-module-first JavaScript bundler',
    'JS compiler transforming modern syntax',
    'Linter enforcing code quality',
    'Opinionated code formatter',
    'Fast disk-efficient package manager',
    'Default Node package manager',
    'Alternative package manager by Facebook',

    // Testing & QA
    'Delightful JS unit-testing framework',
    'Vite-first test runner',
    'Feature-rich JS test runner',
    'Assertion library for JS tests',
    'End-to-end browser testing tool',
    "Microsoft's E2E test runner",
    'Headless Chrome Node API',
    'Browser automation for multiple langs',
    'Isolated UI component dev environment',
    'Accessibility testing engine',

    // Node & Back-End
    'JS runtime built on Chrome V8',
    'Minimalist Node web framework',
    'Fast low-overhead Node framework',
    'TypeScript Node framework, opinionated',
    'Secure JS/TS runtime by Dino',
    'High-level Python web framework',
    'Micro Python web framework',
    'Java enterprise framework',
    'Elegant PHP framework',
    'Reusable PHP components & MVC',

    // Databases
    'Open-source relational database by Oracle',
    'Advanced open-source relational database',
    'NoSQL document database',
    'In-memory key-value store',
    'Lightweight file-based SQL engine',
    'AWS NoSQL key-value service',
    'Wide-column NoSQL DB for big data',
    'Graph database with Cypher query',
    'Query language for APIs',
    'Next-gen TypeScript ORM',

    // DevOps & Cloud
    'Containerization platform',
    'Container orchestration platform',
    'IT automation tool by Red Hat',
    'Infrastructure-as-Code CLI',
    'Extensible CI/CD automation server',
    'Largest code hosting platform',
    'Git hosting with CI/CD',
    'Atlassian Git hosting',
    'GitHub workflow automation',
    'Legacy CI service for open source',

    // Networking & Security
    'Stateless HTTP API architecture',
    'Full-duplex browser-server comms',
    'Token standard for auth',
    'Delegated auth protocol',
    'Password-hashing algorithm',
    'Secure HTTP protocol',
    'Encryption successor to SSL',
    'Browser header for cross-origin',
    'Attack exploiting auth state',
    'Middleware limiting request rate',

    // Data Structures & Algorithms
    'Indexed collection of elements',
    'LIFO collection',
    'FIFO collection',
    'Nodes with pointers forward',
    'Vertices & edges structure',
    'Hierarchical parent-child structure',
    'Key-value pair structure',
    'Re-ordering items algorithm',
    'Finding item algorithm',
    'Function that calls itself',

    // Patterns & Concepts
    'Represents future value',
    'Function passed as arg',
    'Enable non-blocking code',
    'Waits for Promise',
    'Function with closed scope',
    'Object from which others inherit',
    'Deriving new classes',
    'Many forms of same func',
    'Hide data & expose API',
    'Hide complexity behind API',

    // Design Patterns
    'Ensure single instance class',
    'Pub-sub notification pattern',
    'Add behavior dynamically',
    'Create objects without new',
    'Encapsulates request as object',
    'Select algorithm at runtime',
    'Convert interface to another',
    'Provide unified higher API',
    'Sequential access to elements',
    'Define communication between objs',

    // Miscellaneous
    'Limit calls in interval',
    'Delay until idle input',
    'Cache expensive results',
    'Adapts to screen width',
    'Designing for all users',
    'Static code quality check',
    'Reduce file size',
    'Combine many files',
    'Compression format for HTTP',
    'Temporarily store data'
];

/****************************************************************
 * 2. Prevent back-to-back duplicate words via sessionStorage
 ****************************************************************/
const lastIdx = +sessionStorage.getItem('lastWordIdx') || -1;
let idx;
do { idx = Math.floor(Math.random() * words.length); } while (idx === lastIdx);
sessionStorage.setItem('lastWordIdx', idx);

/****************************************************************
 * 3. Export convenience getters (for plug-in to main script)
 ****************************************************************/
export const getRandomWord = () => words[idx];
export const getHint = () => hints[idx];
  