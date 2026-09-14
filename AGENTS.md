# 42_cli AI Agent Conventions & Architecture

This repository (`42_cli`) is a native C++20 terminal client for 42 Intra (`intra.42.fr`) built with `ncursesw`, `libcurl`, and `pthread`.

## Available Specialized Agents & Skills

When working on features, bug fixes, or design improvements in this repository, leverage the global agents installed on the system:

1. **`@orchestrator` (`agent-orchestrator`)**:
   - Run `agent-orchestrator plan "<feature>"` to analyze feature requirements, gather dependencies, and structure execution steps.
2. **`@ui-tux-specialist` (`tux-advisor`)**:
   - Check keybindings and TUI ergonomics: `tux-advisor --audit src/`
   - Guidelines: Esc must have low latency (`set_escdelay(25)`), arrow keys + vim `h`/`j`/`k`/`l` support, `KEY_RESIZE` / `SIGWINCH` dynamic layout recalculation, and high-contrast color pairs.
   - For chat previews, generate interactive HTML artifacts styled with Tailwind CSS.
3. **`@opencli-scraper` (`opencli-scrape`)**:
   - For web data gathering and documentation extraction: `opencli-scrape <site> <query> -f json`
   - Powered by `@jackwener/opencli` and browser bridge (port 19825).
4. **`@tool-chooser` (`tool-chooser`)**:
   - Benchmark proposed dependencies and tools: `tool-chooser -f "<requirement>" --stack "cpp"`

## Build and Verification
- Native Build: `make` (binary: `./42_cli`)
- TUX Audit: `tux-advisor --audit src/`
