// Browser tests (TEST_PLAN §1). Serves the repo root so ../../style/main.css resolves.
import { defineConfig, devices } from '@playwright/test';

const BASE_URL = 'http://127.0.0.1:4120/Projects/Breakaway/';

export default defineConfig({
    testDir: 'tests/e2e',
    retries: 0,
    fullyParallel: true,
    reporter: [['list']],
    use: { baseURL: BASE_URL, trace: 'retain-on-failure' },
    webServer: {
        command: 'python3 -m http.server 4120 --bind 127.0.0.1',
        cwd: '../..',
        url: BASE_URL,
        reuseExistingServer: true
    },
    projects: [
        { name: 'desktop', use: { ...devices['Desktop Chrome'], viewport: { width: 1280, height: 800 }, deviceScaleFactor: 1 } },
        { name: 'mobile', use: { ...devices['Pixel 7'], viewport: { width: 375, height: 812 }, deviceScaleFactor: 2, hasTouch: true, isMobile: true } },
        { name: 'narrow', use: { ...devices['Desktop Chrome'], viewport: { width: 320, height: 568 } } }
    ]
});
