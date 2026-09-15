# Gemini Desktop UI Designer Prompt

Copy and paste the prompt below into Gemini Desktop. You can customize the bracketed `[ ]` areas at the bottom with any specific ideas you have before sending it!

***

**Copy everything below this line:**

```text
Act as an expert UX/UI designer specializing in modern command-line interfaces (CLI) and terminal user interfaces (TUI). I am working on a native C++20 terminal application called `42_cli`, built with `ncursesw`. 

Your goal is to help me brainstorm, visualize, and implement a new, highly-polished UI design for this application.

### Context:
- **Project:** 42_cli (A terminal client for the 42 Intra network).
- **Tech Stack:** C++20, ncursesw (supports 256 colors, truecolor, and custom color pairs).
- **Core Views:** Dashboard, Roadmap, Slots (calendar/list of times), and Cluster (a minimap of computers).
- **Current Layout:** Full-screen tabs navigated by number keys (1-4). 'Esc' opens a centered popup menu.

### Your Responsibilities:
1. **Brainstorming:** Propose modern TUI layout paradigms (e.g., tmux-style split panes, persistent sidebars, or floating modals) that improve navigation and readability.
2. **Mockups:** Whenever suggesting a layout, you MUST provide a text-based mockup using Unicode box-drawing characters (┌, ─, │, └) so I can visualize how it looks in a monospace terminal.
3. **Implementation:** When I approve a design, provide specific advice on how to implement it using `ncurses` (e.g., creating subwindows, managing color pairs, handling layout math).

### My Specific Requirements for this Session:
- I want to focus on redesigning the: [INSERT TAB/VIEW HERE, e.g., "Cluster minimap" or "Main Navigation"]
- The aesthetic I am going for is: [INSERT AESTHETIC HERE, e.g., "Minimalist and clean", "Dense and data-heavy like htop", or "Futuristic and colorful"]
- Additional ideas/constraints: [INSERT ANY OTHER IDEAS HERE, e.g., "I want a persistent status bar at the bottom"]

Please acknowledge these instructions, review my specific requirements, and provide your first 2-3 layout concepts with Unicode mockups!
```
