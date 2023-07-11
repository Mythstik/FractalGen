# FractalGen
2 programs i wrote that generate fractals

Compile it using:

```bash
gcc -o main mandelbrot.c -lm
```
Replace madelbrot.c with julia.c depending on which one you want to generate.

The controls are:

```
Up: Up arrow
Down: Down arrow
Left: Left Arrow
Right: Right Arrow

Zoom in: Z
Zoom Out: X
```

To change the iterations/quality of the set generate modify the MAXCOUNT definitions at the top of the file.
Change the resolution by modifying the WIDTH and HEIGHT definitions.

Change the colors of the set by adding or removing colors from this, the colors can be any amount. It uses the RGBA format the alpha doesnt matter.

SDL_Color palette[] = {
    {  10,  15,  20, 255 }, // Dark blue-gray
    {  20,  30,  40, 255 }, // Deep blue-gray
    {  30,  45,  60, 255 }, // Blue-gray
    {  40,  60,  80, 255 }, // Medium blue-gray
    {  50,  75, 100, 255 }, // Light blue-gray
    {  60,  90, 120, 255 }, // Bright blue-gray
    {  70, 105, 140, 255 }, // Pale blue-gray
    {  80, 120, 160, 255 }, // Gray-blue
    {  90, 135, 180, 255 }, // Blue
    { 100, 150, 200, 255 }, // Light blue
    { 110, 165, 220, 255 }, // Powder blue
    { 120, 180, 240, 255 }, // Sky blue
    { 130, 195, 255, 255 }, // Light sky blue
    { 140, 210, 255, 255 }, // Pale blue
    { 150, 225, 255, 255 }, // Baby blue
    { 160, 240, 255, 255 }, // Ice blue
    { 170, 255, 255, 255 }, // Light cyan
    { 200, 255, 255, 255 }, // Cyan
    { 230, 255, 255, 255 }, // Pale cyan
    { 255, 255, 255, 255 }, // White
    { 220, 220, 220, 255 }, // Light gray
    { 200, 200, 200, 255 }, // Gray
    { 180, 180, 180, 255 }, // Dark gray
    { 150, 150, 150, 255 }, // Charcoal
    { 120, 120, 120, 255 }, // Dark charcoal
    {  90,  90,  90, 255 }, // Black
    {  50,  75, 100, 255 }, // Blue-gray (repeat)
};
