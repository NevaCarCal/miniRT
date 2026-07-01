*This project has been created as part of the 42 curriculum by brimarti, ncarrera.*

## Description

cub3D is a real-time raycasting engine written in C, inspired by the classic Wolfenstein 3D. It renders a 3D first-person view from a 2D map using the DDA (Digital Differential Analyzer) algorithm, built on top of the MinilibX graphics library.

### Features

- cub3D is a project in which, leveraging the Minilibx library, we will implement what can be seen as the first steps towards making something to the likes of Diablo, Duke Nukem, and others. It currently contains no game logic, and is only a renderization project.
- It currently does have implementations for, for example, wall collision which is present in the aforementioned games.
- You can walka round, rotate the camera, configure the colours / textures for the surroundings, and parse any correctly formatted map of your own.
- All kinds of errors that may be encountered during the execution of this program (Incorrect map, textures, player setting, etc) are handled cleanly and without memory leaks.

## Instructions

### Compilation

Once you have cloned / downloaded the repo, you can run:

```bash
make
```
This will build all the necessary elements from the Minilibx and cub3D, and compile them into a file named `cub3D`.

### Execution

Inside the same directory you just ran `make` from, you can now run;

```bash
./cub3D maps/basic.cub
```

This will launch cub3D with the specified map. The argument can be replaced with the path to any custom map of your own, or you can alter the file `basic.cub`.

### Controls

| Key | Action |
|-----|--------|
| W / ↑ | Move forward |
| S / ↓ | Move backward |
| A | Strafe left |
| D | Strafe right |
| ← / → | Rotate left / right |
| ESC | Quit |

### Map format

Maps are `.cub` files containing:

```
NO path/to/north.xpm
SO path/to/south.xpm
WE path/to/west.xpm
EA path/to/east.xpm

F R,G,B
C R,G,B

1111111111
1000000001
1000001001
10001N0001
1111111111
```

- Four texture paths (`NO`, `SO`, `WE`, `EA`) must be valid XPM files.
- `F` sets floor color, `C` sets ceiling color (RGB 0-255 separated by commas).
- The map can take any shape as long as it's closed by walls (`1`), and contains exactly one player spawn point (`N`, `S`, `W`, `E`, you may put one of these in the map to change which direction the player faces as they spawn).

### Cleaning

```bash
make clean    # removes object files
make fclean   # removes object files + binary
make re       # clean + rebuild
make reclean  # re + clean
```

## Resources

- [Ray Casting (C++) – Ismail Assil](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13) — Article explaining the raycasting algorithm, DDA steps, and wall rendering math.
- [Let's Make a Raycaster! – YouTube playlist by Ckladmlo](https://www.youtube.com/watch?v=gYRrGTC7GtA&list=PLCWsH9Tj9oWyDM4W43VMj5yo2PdyYMGst) — Video tutorial series covering pixel drawing, player movement, and texture mapping from scratch.

## AI Usage

AI was used during development for the following tasks:

- **Research and algorithm validation**: Checking the correctness of the DDA implementation, particularly the perpendicular distance formula and fish-eye correction.
- **Debugging edge cases**: Identifying potential integer truncation bugs in wall height calculation (e.g., `line_height` becoming zero when the distance exceeds window height) and proposing safe integer clamps.
- **Code architecture feedback**: Reviewing file organization, function granularity, and suggesting improvements for readability and norm compliance.
- **Documentation**: Assisting with README composition and technical explanations.

AI was not used to generate gameplay logic, core rendering code, or map parsing logic from scratch; all engine code was written manually and iteratively tested.
