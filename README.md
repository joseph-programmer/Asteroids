# Asteroids Game

![AsteroidsGame](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-green.svg)

## Introduction

AsteroidsGame is a simple 2D game inspired by the classic arcade game "Asteroids". The game is built using the [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine), a lightweight game engine for C++.

## Features

- Control a spaceship that can rotate and move in 2D space.
- Fire bullets to destroy randomly spawning asteroids.
- Score points for destroying asteroids.
- Simple collision detection and game over logic.

## Requirements

- A C++17 compatible compiler.
- CMake 3.10 or higher.
- olcPixelGameEngine (included in the `external/include` directory).

## Project Structure

```plaintext
project_root/
├── CMakeLists.txt            # CMake build configuration
├── External/
│   └── olcPixelGameEngine/
│   	└── Include/
│       	└── olcPixelGameEngine.h   # PixelGameEngine header
├── Include/
│   └── AsteroidsGame.h       # Game header
└── Src/
    ├── main.cpp              # Main entry point
    └── AsteroidsGame.cpp     # Game logic implementation
```

## Building the Project

1. **Clone the Repository**

    ```bash
    git clone https://github.com/yourusername/AsteroidsGame.git
    cd AsteroidsGame
    ```

2. **Create a Build Directory**

    ```bash
    mkdir build
    cd build
    ```

3. **Generate the Makefile with CMake**

    ```bash
    cmake ..
    ```

4. **Build the Project**

    ```bash
    make
    ```

5. **Run the Game**

    ```bash
    ./AsteroidsGame
    ```

## How to Play

- **Movement**: Use the arrow keys to rotate and move the spaceship.
- **Shoot**: Press the spacebar to shoot bullets.
- **Objective**: Destroy all asteroids while avoiding collisions.
- **Game Over**: The game ends when you lose all your lives.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## Acknowledgements

- [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) by OneLoneCoder for the game engine.
- Inspired by the classic "Asteroids" arcade game.



