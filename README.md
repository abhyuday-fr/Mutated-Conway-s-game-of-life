# Conway's Game of Life - Classic & Mutating Variants

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![raylib](https://img.shields.io/badge/raylib-4.x-red.svg)](https://www.raylib.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)](https://github.com/raysan5/raylib)

Two implementations of Conway's Game of Life: the **classic stable version** and an **experimental mutating variant** where rules evolve over time.

![Game of Life Banner](https://img.shields.io/badge/🧬-Life-brightgreen) ![Mutation](https://img.shields.io/badge/🔀-Mutation-orange) ![Chaos](https://img.shields.io/badge/⚡-Chaos-red)

---

## 📚 Table of Contents

- [Overview](#overview)
- [Two Variants Explained](#two-variants-explained)
- [Tech Stack](#tech-stack)
- [Installation](#installation)
- [Controls Reference](#controls-reference)
- [Building & Running](#building--running)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

This project provides two distinct implementations of cellular automata:

1. **Classic Conway's Game of Life** - The original B3/S23 ruleset with stable, predictable behavior
2. **Mutating Game of Life** - An experimental variant where rules evolve every N generations, creating emergent chaos

Both versions feature:
- ✅ Clean, efficient C++ implementation
- ✅ Smooth 60 FPS graphics using raylib
- ✅ Interactive pattern drawing
- ✅ Adjustable simulation speed
- ✅ 30×30 toroidal grid (wraps at edges)

---

## 🎮 Two Variants Explained

### 🟢 Classic Variant (`gameoflife_original`)

The traditional implementation following John Conway's original 1970 rules.

#### Rules: **B3/S23**
- **Birth (B3)**: A dead cell with exactly **3** live neighbors becomes alive
- **Survival (S23)**: A live cell with **2 or 3** neighbors survives
- **Death**: All other cells die or stay dead

#### Characteristics:
- ✨ **Predictable** - Same patterns always behave the same way
- 🔄 **Well-studied** - Famous patterns like gliders, oscillators, spaceships
- 📐 **Mathematically proven** - Turing complete, capable of universal computation
- 🎯 **Educational** - Perfect for learning cellular automata principles

#### Famous Patterns:
- **Still lifes**: Block, Beehive, Boat
- **Oscillators**: Blinker, Toad, Pulsar
- **Spaceships**: Glider, LWSS
- **Infinite growth**: Glider guns, Methuselahs

#### Use Cases:
- Learning cellular automata theory
- Studying emergent complexity from simple rules
- Testing known patterns and configurations
- Educational demonstrations

---

### 🔀 Mutating Variant (`gameoflife_mutating`)

An experimental implementation where rules **evolve over time**, creating unpredictable emergent behavior.

#### Dynamic Rules System
Rules automatically mutate every **N generations** (default: 50, configurable) using one of four strategies:

| Strategy | Probability | Effect | Example |
|----------|-------------|--------|---------|
| **Survival Mutation** | 30% | Add/remove survival counts | S23 → S234 |
| **Birth Mutation** | 30% | Add/remove birth counts | B3 → B36 |
| **Count Shifting** | 20% | Shift all counts by ±1 | B3/S23 → B4/S34 |
| **Randomization** | 20% | Complete rule reset | B3/S23 → B2457/S0136 |

#### Rule Notation: **B{birth}/S{survival}**
- **B** = Birth counts (neighbor counts that create life)
- **S** = Survival counts (neighbor counts that keep cells alive)
- Numbers = 0-8 (possible neighbor counts)

Examples:
- `B3/S23` - Classic Conway
- `B36/S23` - HighLife (replicators)
- `B2/S` - Seeds (exploding patterns)
- `B3/S12345` - Maze (dense structures)

#### Characteristics:
- 🎲 **Unpredictable** - Rules change creates emergent surprises
- 🌊 **Dynamic** - Oscillates between order and chaos
- 🧬 **Evolutionary** - System adapts and discovers new states
- 🎨 **Visually interesting** - Constant transformation and novelty

#### Emergent Phenomena:
1. **Population Explosions** - Permissive rules cause rapid growth
2. **Mass Extinctions** - Strict rules decimate populations
3. **Pattern Metamorphosis** - Gliders transform, oscillators mutate
4. **Novel Attractors** - New stable states emerge
5. **Chaos Cycling** - Oscillation between ordered and chaotic states

#### Use Cases:
- Exploring adaptive systems and emergent behavior
- Discovering new interesting cellular automaton rulesets
- Studying sensitivity to rule changes
- Creating dynamic, evolving visual art
- Demonstrating controlled collapse (System Collapse Hackathon)

#### Visual Feedback:
The mutating variant includes an on-screen UI showing:
- Current generation count
- Active rules (e.g., "B36/S234")
- Countdown to next mutation
- Mutation interval setting
- Control hints

---

## 🛠️ Tech Stack

### Core Technologies

| Component | Technology | Version | Purpose |
|-----------|-----------|---------|---------|
| **Language** | C++ | 17+ | Core implementation, performance |
| **Graphics Library** | [raylib](https://www.raylib.com/) | 4.x+ | Window management, rendering, input |
| **Build System** | GNU Make | 4.x+ | Compilation and linking |
| **Compiler** | g++ / clang++ | - | C++ compilation |

### Why These Technologies?

#### C++17
- **Performance**: Native compiled code, minimal overhead
- **Efficiency**: Direct memory management for grid operations
- **STL**: Modern C++ containers (vectors) for clean code
- **Compatibility**: Cross-platform support

#### raylib
- **Simplicity**: Easy-to-use API, no boilerplate
- **Performance**: Hardware-accelerated rendering
- **Cross-platform**: Linux, macOS, Windows, even Web (with Emscripten)
- **Minimal dependencies**: Self-contained library
- **Perfect for**: 2D games, simulations, visual applications

Benefits:
```cpp
// Clean, readable code
DrawRectangle(x, y, width, height, color);
if (IsKeyPressed(KEY_SPACE)) { /* ... */ }
```

#### GNU Make
- **Standard**: Universal build tool
- **Simple**: Easy-to-read Makefiles
- **Efficient**: Incremental compilation
- **Portable**: Works everywhere

### Dependencies

**Required:**
- C++ compiler with C++17 support
- raylib 4.x or higher
- Standard build tools (make)

**Optional:**
- pkg-config (for dependency checking)

### Platform Support

| Platform | Status | Notes |
|----------|--------|-------|
| 🐧 **Linux** | ✅ Fully Supported | Primary development platform |
| 🍎 **macOS** | ✅ Supported | via Homebrew raylib |
| 🪟 **Windows** | ✅ Supported | via MinGW/MSVC + raylib |
| 🌐 **Web** | ⚠️ Experimental | Possible with Emscripten |

---

## 📦 Installation

### Prerequisites

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential libraylib-dev
```

#### Arch Linux
```bash
sudo pacman -S base-devel raylib
```

#### macOS
```bash
brew install raylib
```

#### Windows (MSYS2/MinGW)
```bash
pacman -S mingw-w64-x86_64-raylib
```

### Clone Repository
```bash
git clone https://github.com/yourusername/Mutated-Conway-s-game-of-life.git
cd Mutated-Conway-s-game-of-life
```

### Verify Setup
```bash
./setup.sh
```

This script checks for:
- ✓ raylib installation
- ✓ C++ compiler (g++)
- ✓ Make utility

---

## 🎮 Controls Reference

### 🟢 Classic Variant Controls

| Key | Action | Description |
|-----|--------|-------------|
| <kbd>ENTER</kbd> | **Start** | Begin simulation |
| <kbd>SPACE</kbd> | **Pause** | Stop simulation |
| <kbd>R</kbd> | **Random** | Fill grid with random pattern |
| <kbd>C</kbd> | **Clear** | Clear all cells |
| <kbd>F</kbd> | **Faster** | Increase FPS (+2) |
| <kbd>S</kbd> | **Slower** | Decrease FPS (-2, min 5) |
| <kbd>Mouse Left</kbd> | **Draw** | Toggle cells (when paused) |

#### Basic Workflow (Classic):
```
1. Click cells to draw pattern (or press R for random)
2. Press ENTER to start
3. Press SPACE to pause
4. Press F/S to adjust speed
5. Press C to clear and start over
```

---

### 🔀 Mutating Variant Controls

All classic controls **PLUS** mutation-specific features:

| Key | Action | Description |
|-----|--------|-------------|
| <kbd>ENTER</kbd> | **Start** | Begin simulation |
| <kbd>SPACE</kbd> | **Pause** | Stop simulation |
| <kbd>R</kbd> | **Random** | Fill grid with random pattern |
| <kbd>C</kbd> | **Clear** | Clear all cells |
| <kbd>F</kbd> | **Faster** | Increase FPS (+2) |
| <kbd>S</kbd> | **Slower** | Decrease FPS (-2, min 5) |
| <kbd>M</kbd> | **Mutate NOW** | Force immediate rule mutation |
| <kbd>T</kbd> | **Reset Rules** | Return to classic Conway (B3/S23) |
| <kbd>+</kbd> or <kbd>=</kbd> | **Longer Interval** | Mutation every +10 generations |
| <kbd>-</kbd> | **Shorter Interval** | Mutation every -10 generations |
| <kbd>Mouse Left</kbd> | **Draw** | Toggle cells (when paused) |

#### Advanced Workflow (Mutating):
```
1. Press R for random pattern (or draw manually)
2. Press ENTER to start
3. Watch rules evolve automatically (default: every 50 gen)
4. Press M to force mutation at interesting moments
5. Press +/- to adjust mutation frequency
6. Press T to reset to classic Conway rules
7. Experiment and discover emergent patterns!
```

#### Pro Tips:
- **Long intervals (100+)**: Gradual, observable evolution
- **Short intervals (20-30)**: Rapid, chaotic changes
- **Manual mutations (M)**: Test pattern resilience
- **Reset (T)**: Return to familiar behavior

---

## 🔨 Building & Running

### Quick Start

```bash
# Build and run the mutating variant (recommended)
make run-mutating

# Build and run the classic variant
make run-original
```

### Build Options

```bash
# Build both variants
make all

# Build only classic variant
make original

# Build only mutating variant
make mutating

# Clean build files
make clean

# Rebuild everything from scratch
make rebuild
```

### Manual Compilation

If you prefer manual compilation:

```bash
# Classic variant
g++ -std=c++17 -O2 main.cpp simulation.cpp grid.cpp \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o gameoflife_original

# Mutating variant
g++ -std=c++17 -O2 main_mutating.cpp simulation_mutating.cpp grid.cpp \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o gameoflife_mutating
```

---
### File Responsibilities

| File | Lines | Purpose |
|------|-------|---------|
| `grid.cpp/hpp` | ~100 | Cell storage, rendering, boundary checking |
| `simulation.cpp/hpp` | ~150 | Classic Conway logic, neighbor counting |
| `simulation_mutating.cpp/hpp` | ~400 | Mutation system, rule evolution |
| `main.cpp` | ~100 | Classic game loop, input handling |
| `main_mutating.cpp` | ~150 | Enhanced game loop, UI rendering |

---

## 📖 Documentation

### Learning Path

1. **New to Conway's Life?** → Start with classic variant + QUICKSTART.md
2. **Want to experiment?** → Jump to mutating variant + controls reference
3. **Technical details?** → Read MUTATION_GUIDE.md
4. **Complete understanding?** → Read PROJECT_SUMMARY.md

### External Resources

- [Conway's Game of Life - Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- [LifeWiki - Comprehensive pattern database](https://conwaylife.com/wiki/)
- [raylib - Official documentation](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [Cellular Automaton - Wolfram MathWorld](https://mathworld.wolfram.com/CellularAutomaton.html)

---

## 🎯 Use Cases & Applications

### Classic Variant

**Education:**
- Teaching cellular automata principles
- Demonstrating emergence from simple rules
- Computer science coursework

**Research:**
- Pattern analysis and classification
- Algorithm testing
- Complexity theory studies

**Recreation:**
- Pattern design and discovery
- Zen-like observation
- Programming practice

### Mutating Variant

**Experimentation:**
- Discovering new cellular automaton rulesets
- Studying adaptive systems
- Exploring emergent behavior

**Art & Visualization:**
- Generative art creation
- Dynamic visual experiences
- Live coding performances

**Chaos Theory:**
- Observing controlled collapse
- Edge-of-chaos phenomena
- Sensitivity to rule changes

**Game Development:**
- Procedural level generation inspiration
- Dynamic difficulty adjustment research
- Evolutionary game mechanics

---

## 🏆 System Collapse Hackathon

The mutating variant was created for the [System Collapse Hackathon](https://systemcollapse.dev/) - a 72-hour challenge to build systems that **get more interesting when they break**.

### Hackathon Alignment

✅ **Adaptive Rules Mechanic** - Logic rewrites itself every N generations  
✅ **Emergent Behavior** - Simple mutations create complex outcomes  
✅ **Controlled Collapse** - Lives between order and chaos  
✅ **Technical Excellence** - Clean C++ implementation  
✅ **Surprising Results** - Creates patterns never explicitly programmed  

### Key Innovation

Most Game of Life implementations are **static** - they follow fixed rules forever. This variant is **dynamic** - rules evolve, creating a journey through rule-space that generates emergent phenomena impossible with static rules.

---

## 🧪 Interesting Experiments

### Classic Variant

Try these famous patterns:

**Glider (5 cells):**
```
. # .
. . #
# # #
```

**Blinker (3 cells - oscillator):**
```
# # #
```

**Glider Gun (36 cells - infinite growth):**
[See LifeWiki for pattern]

### Mutating Variant

**Experiment Ideas:**

1. **Glider Survival Test**
   - Draw a glider
   - Start simulation
   - Watch how mutations affect it

2. **Population Dynamics**
   - Start with random pattern
   - Observe population over time
   - Note explosion vs. extinction patterns

3. **Rule Discovery**
   - Run for 500+ generations
   - Note interesting rules that appear
   - Try them manually with reset (T) + custom code

4. **Chaos Edge**
   - Set mutation interval to 20 (very fast)
   - Watch rapid rule changes
   - Observe fleeting order in chaos

---

## 🤝 Contributing

Contributions welcome! Here's how:

### Ideas for Contributions

**Features:**
- [ ] Save/load patterns
- [ ] Export GIF animations
- [ ] Rule history visualization
- [ ] Custom color schemes
- [ ] Larger grid sizes
- [ ] Multi-state cells (>2 states)

**Improvements:**
- [ ] Performance optimizations
- [ ] Better UI/UX
- [ ] More mutation strategies
- [ ] Statistical analysis
- [ ] Web version (Emscripten)

### How to Contribute

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open Pull Request

---

## 📄 License

This project is open source and available under the MIT License.

```
MIT License

Copyright (c) 2024 [Your Name]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🙏 Acknowledgments

- **John Conway** - Creator of the original Game of Life (1970)
- **raylib community** - For the excellent graphics library
- **System Collapse Hackathon** - Inspiration for the mutating variant
- **Cellular automata researchers** - Decades of pattern discovery

---

## 🌟 Star History

If you find this project interesting, give it a ⭐!

---

<div align="center">

### 🧬 Built with curiosity, powered by emergence

**"Between rigid order and total chaos lies the sweet spot where interesting things happen."**

[⬆ Back to Top](#conways-game-of-life---classic--mutating-variants)

</div>
