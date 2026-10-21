# Setup

How I run, test and edit Breakaway on Windows with WSL2 (Ubuntu) and VS Code.

Breakaway is a static web game, so the browser runs everything. I only need Node.js for the tests and development tools, and a small local web server to play it while I work.

## Prerequisites

I run every command in my WSL (Ubuntu) terminal, not PowerShell.

| Tool | Version | Install (official source) | Verify |
|---|---|---|---|
| WSL2 with Ubuntu | WSL 2 | Already installed. Guide: [learn.microsoft.com/windows/wsl/install](https://learn.microsoft.com/windows/wsl/install) | In PowerShell, `wsl -l -v` shows `VERSION 2` |
| Git | any recent | `sudo apt update && sudo apt install git` ([git-scm.com](https://git-scm.com/downloads)) | `git --version` |
| Node.js | 24 LTS | nvm, below ([nodejs.org](https://nodejs.org)) | `node -v` prints `v24.x` |
| npm | comes with Node | none | `npm -v` |
| Python 3 | any 3.x | Comes with Ubuntu, or `sudo apt install python3` | `python3 --version` |
| VS Code with the WSL extension | current | [code.visualstudio.com](https://code.visualstudio.com) on Windows, then the **WSL** extension by Microsoft | `code --version` from the WSL terminal |

### Install Node.js with nvm

nvm (Node Version Manager) installs Node in my home folder. No `sudo`, and I can switch versions per project. The command below is from the official [nvm README](https://github.com/nvm-sh/nvm#install--update-script). I check it for a newer version first.

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.7/install.sh | bash
# Close and reopen the terminal, then:
nvm install 24
nvm alias default 24
node -v   # v24.x.x
```

I use 24 because it is the Long-Term Support line I started with. The game itself doesn't run on Node, so a newer LTS works too.

### Where the files live

I keep the repo inside the Linux file system, at `~/REPO/ChristianRodriguez46.github.io`, not under `/mnt/c/...`. Linux tools are much faster there, and file watching works.

```bash
pwd                 # should start with /home/<me>, not /mnt/c
git remote -v       # should show ChristianRodriguez46/ChristianRodriguez46.github.io
```

If a clone ever ends up on the C: drive, I clone a fresh copy into `~/REPO` and work there.

## Get the code

I clone the repository, or pull if I already have it:

```bash
mkdir -p ~/REPO && cd ~/REPO
git clone https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io.git
cd ChristianRodriguez46.github.io
git pull            # if I already had it
```

## Install dependencies

The game has no runtime dependencies. This installs the development tools only:

```bash
cd Projects/Breakaway
npm install         # installs dev tools into node_modules/ (never committed)
```

## Configuration

There is nothing to configure. No secrets, environment variables or API keys.

## Saved data

There is no database. The game saves the best score and settings in the browser's `localStorage`, on the player's device. To clear it while testing, I use the game's "Reset saved data" button. Or in the browser I press F12, then Application, Local Storage, `http://localhost:4101`, and delete the `breakaway.*` keys.

## Run it

I serve the repository root, not the game folder, so the shared nav styles at `../../style/` resolve the same way they do on GitHub Pages:

```bash
cd ~/REPO/ChristianRodriguez46.github.io
python3 -m http.server 4101
```

Then I open **http://localhost:4101/Projects/Breakaway/** in Chrome or Edge on Windows. WSL2 forwards `localhost` to Windows. Ctrl+C stops the server.

Why a server: browsers refuse to load ES modules from `file://` paths, so double-clicking `index.html` shows a blank page with a CORS error in the console.

## Run the tests

```bash
cd ~/REPO/ChristianRodriguez46.github.io/Projects/Breakaway
npm test            # runs node --test
```

A pass is a summary ending in `# fail 0`. Type checking is `npm run check`.

## Open it in my editor

```bash
cd ~/REPO/ChristianRodriguez46.github.io
code .
```

VS Code opens connected to WSL (the bottom-left corner says **WSL: Ubuntu**). Recommended extensions are in `.vscode/extensions.json`.

For debugging, I open the game in Chrome or Edge, press F12, and use the Sources tab to set breakpoints in the game's modules.

## Troubleshooting on WSL2

| Problem | Fix |
|---|---|
| `nvm: command not found` right after installing | Close and reopen the terminal, or run `source ~/.bashrc` |
| `node -v` shows an old version | `nvm use 24`, and `nvm alias default 24` so it sticks |
| Blank game page, console says CORS or "Failed to load module script" | I opened the file directly. Serve the repo root and use the `http://localhost:4101/...` URL |
| Page loads but has no nav styles | I served `Projects/Breakaway` instead of the repo root |
| `localhost:4101` doesn't open on Windows | Check the server is still running. Try `http://127.0.0.1:4101/`. Run `wsl --shutdown` in PowerShell if forwarding stopped |
| Address already in use | Another server is on that port. Use `python3 -m http.server 4102` |
| Git shows every file as changed | Line endings. `git config --global core.autocrlf input`, and don't edit the repo from `/mnt/c` |
| `code .` not found | Install VS Code on Windows with "Add to PATH" ticked, then reopen the WSL terminal |

## Deploying

I run `npm test`, then commit and push to `main`. GitHub Pages publishes the site, usually within a minute or two, at **https://christianrodriguez46.github.io/Projects/Breakaway/**.

## Changelog

- 2026-10-21: Rewrote this guide in first person and removed the numbered headings.
- 2026-10-20: Added the troubleshooting table for WSL2.
- 2026-10-19: First version.
