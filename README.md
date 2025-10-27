### · · ───────────────────────── ·𖥸· ───────────────────────── · ·
# Snake in C🐍
<img alt="GitHub commit activity" src="https://img.shields.io/github/commit-activity/t/min174/snake-game-c?style=flat-square&label=%E2%99%A1%20commits%20%E2%99%A1&labelColor=ffc8dd&color=cdb4db">

## 𓆗 Description 𓆗
I wanted to refresh my memory on coding in C. I wanted a project that I could have fun with and be able to expand while I grow as a C developer. I love video games so what better than to start with one of the classics? (I named the snake, Sally)

## 𓆙 Features 𓆙

- Snake Growth  
- Score Tracking 
- Snake moves faster as the score increases
- Main Menu
- Play again menu   
- Pause function
- Different options of fruit (coming soon!)
- Leaderboard (coming soon!)
  
## 𓆓 Prerequisites 𓆓

Please make sure that you have a C compiler.
- **Windows:** You can install MinGW-w64 via [MSYS2](https://www.msys2.org/).
- **macOS:** Install the Xcode Command Line Tools by running `xcode-select --install` in your terminal.
- **Linux (Ubuntu/Debian):** Install the build essentials package by running `sudo apt install build-essential`.

## 𓆚 Building and Running 𓆚

- **Navigate to the project directory:**
  ```bash
  cd snake-in-c
  ```

- **Compile the source code:**
Use the `gcc` compiler to compile all the `.c` source files and create an executable named `snake.exe` (or just `snake` on Mac/Linux).

  ```bash
  gcc src/main.c src/gameplay.c src/menu.c -o snake.exe
  ```

- **Run the game:**
Execute the compiled program from your terminal.

  **On Windows:**
  ```bash
  .\snake.exe
  ```

  **On macOS/Linux:**
  ```bash
  ./snake
  ```
### · · ───────────────────────── ·𖥸· ───────────────────────── · ·
