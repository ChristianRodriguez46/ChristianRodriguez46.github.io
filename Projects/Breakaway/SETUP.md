# Setup — Breakaway

How to run, test and edit Breakaway on **Windows with WSL2 (Ubuntu) and VS Code**.

> Draft from 2026-10-19. Sections marked *(scaffold)* get their exact commands once the project
> files exist.

Breakaway is a static web game: the browser runs everything. You only need Node.js to run the
tests and development tools, and a tiny local web server to play it while you work.

## Prerequisites

**Checked on your laptop on 2026-10-19:** Git 2.34.1, Node v24.14.0, npm 11.9.0, Python 3.10.12,
VS Code 1.142.0, repo at `~/REPO/ChristianRodriguez46.github.io`. Everything below is already
installed; the install steps are here for a new machine.

Run every command in this guide in your **WSL (Ubuntu) terminal**, not PowerShell.

| Tool | Version | Install (official source) | Verify |
|---|---|---|---|
| WSL2 + Ubuntu | WSL 2 | Already installed. Guide: [learn.microsoft.com/windows/wsl/install](https://learn.microsoft.com/windows/wsl/install) | In PowerShell: `wsl -l -v` shows `VERSION 2` |
| Git | any recent | `sudo apt update && sudo apt install git` ([git-scm.com](https://git-scm.com/downloads)) | `git --version` |
| Node.js | 24 LTS | nvm, below ([nodejs.org](https://nodejs.org)) | `node -v` prints `v24.…` |
| npm | comes with Node | — | `npm -v` |
| Python 3 | any 3.x | Comes with Ubuntu; else `sudo apt install python3` | `python3 --version` |
| VS Code + WSL extension | current | [code.visualstudio.com](https://code.visualstudio.com) on Windows, then the **WSL** extension by Microsoft | `code --version` (from the WSL terminal) |

### Install Node.js with nvm

nvm (Node Version Manager) installs Node in your home folder, so no `sudo`, and you can switch
versions per project. The command below is from the official
[nvm README](https://github.com/nvm-sh/nvm#install--update-script); check it for a newer version.

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.7/install.sh | bash
# Close and reopen the terminal, then:
nvm install 24
nvm alias default 24
node -v   # v24.x.x
```

Why 24: it is the newest Long-Term Support line today. Node 26 becomes LTS later this month;
either works, because the game itself doesn't run on Node.

### Where your files should live

Keep the repo **inside the Linux file system**, as yours already is at
`~/REPO/ChristianRodriguez46.github.io`, not under `/mnt/c/...`. Linux tools run much faster there, and file watching works.

```bash
pwd                 # should start with /home/<you>, not /mnt/c
git remote -v       # should show ChristianRodriguez46/ChristianRodriguez46.github.io
```

If a clone is ever on the C: drive, clone a fresh copy into `~/REPO` and work there.

## 1. Get the code

```bash
mkdir -p ~/REPO && cd ~/REPO
git clone https://github.com/ChristianRodriguez46/ChristianRodriguez46.github.io.git
cd ChristianRodriguez46.github.io
git pull            # if you already had it
```

## 2. Install dependencies *(scaffold)*

The game has no runtime dependencies. Development tools only:

```bash
cd Projects/Breakaway
npm install         # installs dev tools into node_modules/ (never committed)
```

## 3. Configure

Nothing to configure. There are no secrets, environment variables or API keys.

## 4. Data

There is no database. The game saves the best score and settings in the browser's `localStorage`
on the player's own device. To clear it while testing, use the game's "Reset saved data" button,
or in the browser press F12 → Application → Local Storage → `http://localhost:4101` → delete the
`breakaway.*` keys.

## 5. Run it

Serve the **repository root** (not the game folder), so the shared nav styles at `../../style/`
resolve the same way they do on GitHub Pages:

```bash
cd ~/REPO/ChristianRodriguez46.github.io
python3 -m http.server 4101
```

Then open **http://localhost:4101/Projects/Breakaway/** in Chrome or Edge on Windows. WSL2
forwards `localhost` to Windows automatically. Stop the server with Ctrl+C.

Why a server at all: browsers refuse to load ES modules from `file://` paths, so double-clicking
`index.html` shows a blank page with a CORS error in the console.

## 6. Run the tests *(scaffold)*

```bash
cd ~/REPO/ChristianRodriguez46.github.io/Projects/Breakaway
npm test            # runs node --test
```

Passing looks like a summary ending in `# fail 0`.

## 7. Open it in your editor

```bash
cd ~/REPO/ChristianRodriguez46.github.io
code .
```

VS Code opens connected to WSL (bottom-left corner shows **WSL: Ubuntu**). Recommended
extensions are listed in `.vscode/extensions.json` *(scaffold)*.

**Debugging:** open the game in Chrome or Edge, press F12, and use the **Sources** tab to set
breakpoints in the game's modules.

## Troubleshooting (WSL2)

| Problem | Fix |
|---|---|
| `nvm: command not found` right after installing | Close and reopen the terminal, or run `source ~/.bashrc`. |
| `node -v` shows an old version | `nvm use 24`, and `nvm alias default 24` so it sticks. |
| Blank game page, console says CORS or "Failed to load module script" | You opened the file directly. Serve the repo root and use the `http://localhost:4101/...` URL. |
| Page loads but has no nav styles | You served `Projects/Breakaway` instead of the repo root. |
| `localhost:4101` doesn't open on Windows | Check the server is still running; try `http://127.0.0.1:4101/`. Restart WSL with `wsl --shutdown` in PowerShell if forwarding stopped. |
| Address already in use | Another server is on that port: use `python3 -m http.server 4102`. |
| Git shows every file as changed | Line endings: `git config --global core.autocrlf input`, and don't edit the repo from `/mnt/c`. |
| `code .` not found | Install VS Code on Windows with "Add to PATH" ticked, then reopen the WSL terminal. |

## Deploying

Commit and push to `main`. GitHub Pages publishes the site, usually within a minute or two, at
**https://christianrodriguez46.github.io/Projects/Breakaway/**. The full checklist is in
`DEPLOY_CHECKLIST.md` *(delivery)*.
