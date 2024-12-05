# shader-fractals

Playing around with OpenGL, GLSL, GLFW, GLEW by making Interactive Fractal Visualizations for Mandelbrot, Julia and more.

## Dependencies

This program requires the following dependencies to compile and run:

- GLEW: The OpenGL Extension Wrangler Library, for managing OpenGL extensions.
- GLFW: A library for creating windows, contexts, and handling inputs for OpenGL.
- OpenGL: For rendering graphics.
- Standard build tools: gcc, make.

## Building

To build the program, run the following command:

```bash
./compile.sh
```

This will create two executable named `mandelbrot` and `julia` in the current directory.

## Running

To run the program, execute the following command:

```bash
./mandelbrot

# or

./julia
```

## Keybindings

Both programs have the following keybindings:

- `c`: Change the color mode.
- `i`: Invert the color mode gradient.
- `q`: Quit the program.
- `>`: Increase MaxIterations by 100.
- `<`: Decrease MaxIterations by 100.

Julia specific keybindings:

- `r`: Increase Real part of the julia constant complex number.
- `f`: Decrease Real part of the julia constant complex number.
- `t`: Increase Imaginary part of the julia constant complex number.
- `g`: Decrease Imaginary part of the julia constant complex number.

## Contributing

I'm actively supporting FOSS collaboration, so, if you feel like you can help in any way, file an issue in the *Issues* tab or submit a Pull Request and I will go through it.

## License

Copyright (C) xAlpharax

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program. If not, see https://www.gnu.org/licenses/.
