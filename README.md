# Tetris

A small tetris game written with SDL.

## Building the Game

To build the game, follow these steps:

1. Ensure you have CMake and SDL2 installed on your system.
2. Clone the repository:

   ```sh
   git clone https://github.com/alarmfox/tetris.git
   cd tetris
   ```

3. Create a build directory and navigate into it:

   ```sh
   mkdir build
   cd build
   ```

4. Run CMake to configure the project:

   ```sh
   cmake ..
   ```

5. Build the project using make:

   ```sh
   cmake -B .
   ```

6. Run the game:

   ```sh
   ./Tetris
   ```

## Controls

- **Left Arrow**: Move piece left
- **Right Arrow**: Move piece right
- **Up Arrow**: Rotate piece
- **Down Arrow**: Move piece down faster

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
