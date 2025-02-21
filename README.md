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

## Cool stuff

Mandelbrot Set Visuals:

![image1](https://github.com/user-attachments/assets/000217e9-8f50-4a05-a64b-54bcd8689f73)

![image2](https://github.com/user-attachments/assets/650dd352-4d70-4a29-998d-a8d54accf915)

![image3](https://github.com/user-attachments/assets/57bf2319-8a70-4770-96e7-f011b2bedf02)

Julia Set Visuals:

![image4](https://github.com/user-attachments/assets/e8294a9f-1e9f-4bb8-9eb4-dcbafe712abb)

![image5](https://github.com/user-attachments/assets/bc630b22-ee00-42a1-bcaa-6501df514f46)

## Contributing

I'm actively supporting FOSS collaboration, so, if you feel like you can help in any way, file an issue in the *Issues* tab or submit a Pull Request and I will go through it.

## License

Copyright (C) xAlpharax

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program. If not, see https://www.gnu.org/licenses/.
