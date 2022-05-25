# CUB3D
## Raycasting (3D graphics in C)

In collaboration with <a href="https://github.com/jroth42/">jroth</a>

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

<img width="1251" alt="Screen Shot 2022-05-25 at 4 50 03 PM" src="https://user-images.githubusercontent.com/56739088/170291718-c9429ceb-3d58-4f0d-9456-b669a03062cb.png">

The project uses a small graphics library <a href="https://github.com/codam-coding-college/MLX42">MLX42</a> to render the graphics, which inturn uses <a href="https://github.com/glfw/glfw">GLFW</a>. 

Camera rotation and movement is also created.The camera can moved using keys W, A, S, and D, for rotation LEFT and RIGHT arrow keys are used.

## Installation
- Run `./setup_mlx.sh` to pull the `MLX42` submodule from github
- Install glfw 
  - `brew install glfw` on mac
  - `sudo apt install glfw` on linux
- `make mlx` to compile the `MLX42` library
- `make` to compile the `Cub3D`

## Usage
- `./cub3D <path_to_map>`
  - e.g `./cub3D map.cub`
