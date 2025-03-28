# so_long

`so_long` is a project from the 42 curriculum that involves creating a simple 2D game using the MiniLibX library. The objective is to navigate a player through a map, collecting items and reaching an exit while adhering to specific constraints.

## Objectives

This project focuses on developing the following skills:
- Parsing and handling 2D arrays
- File reading and validation
- Rendering graphics with MiniLibX
- Event-driven programming (keyboard hooks)
- Memory management and error handling

The game requirements include:
- Development in C with no memory leaks
- Exclusive use of MiniLibX for rendering
- Graceful handling of invalid maps and errors

## Preview

<p>
  <img src="./textures/preview.gif" alt="Gameplay GIF" width="400"/>
</p>

## Features

- Grid-based 2D gameplay
- Player movement via keyboard inputs
- Collectible items and an exit point
- Comprehensive map validation and error handling

## Getting Started

### Prerequisites

- A Linux-based operating system

1. Clone the repository:
	```bash
	git clone https://github.com/yahyaeb/so_long.git
	cd so_long
	```

2. Compile the project:
	```bash
	make
	```

3. Run the game:
	```bash
	./so_long maps/map.ber
	```

> Having issues? Check the [Troubleshooting](#troubleshooting) section.

## Controls

- **W**: Move up
- **A**: Move left
- **S**: Move down
- **D**: Move right
- **ESC**: Exit the game

## Map Format

- The map must be a `.ber` file.
- It must be rectangular and surrounded by walls (`1`).
- It must include:
- It must include:
  - At least one player (`P`)
  - At least one collectible (`C`)
  - Exactly one exit (`E`)

Example map:
```
111111
1P0C01
1000E1
111111
```
- `1`: Wall  
- `0`: Empty space  
- `P`: Player start  
- `C`: Collectible  
- `E`: Exit  

## Gameplay

- Collect all the stars before the exit becomes accessible.

## Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Project Guidelines](https://github.com/42School)

## Troubleshooting

### Common Errors and Fixes

1. **"Can't find a suitable X11 include directory"**  
   Ensure the required X11 development libraries are installed:
   ```bash
   sudo apt update
   sudo apt install libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
   ```

2. **"Cannot find -lbsd: No such file or directory"**  
   Install the development version of `libbsd`:
   ```bash
   sudo apt install libbsd-dev
   ```

3. **Error related to `ft_printf`**  
   Navigate to the `ft_printf` folder and rebuild:
   ```bash
   make re
   ```

## Author

- **Yahia El Boukili** - [GitHub Profile](https://github.com/yahyaeb)