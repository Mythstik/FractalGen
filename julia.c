#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAXCOUNT 500
#define WIDTH 640
#define HEIGHT 480

typedef struct Complex {
    float real;
    float imaginary;
} Complex;

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
const int num_layers = sizeof(palette) / sizeof(SDL_Color);

// Function to draw julia set with multiple colors
#define fractal(renderer, width, height, left, top, xside, yside) \
    do { \
        float xscale = (xside) / (width); \
        float yscale = (yside) / (height); \
        Complex c = { -0.8f, 0.156f }; \
        for (int y = 0; y < (height); y++) { \
            for (int x = 0; x < (width); x++) { \
                Complex z = { \
                    (x) * xscale + (left), \
                    (y) * yscale + (top) \
                }; \
                int count = 0; \
                while ((z.real * z.real + z.imaginary * z.imaginary < 4) && (count < MAXCOUNT)) { \
                    Complex temp = { \
                        z.real * z.real - z.imaginary * z.imaginary + c.real, \
                        2 * z.real * z.imaginary + c.imaginary \
                    }; \
                    z = temp; \
                    count++; \
                } \
                int layer = count / (MAXCOUNT / num_layers); \
                SDL_Color color = palette[layer]; \
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255); \
                SDL_RenderDrawPoint(renderer, x, y); \
            } \
        } \
    } while(0)

// Zoom in on a specific portion of the Mandelbrot set
void zoom_in(float* left, float* top, float* xside, float* yside, float zoom_factor)
{
    float new_xside = *xside / zoom_factor;
    float new_yside = *yside / zoom_factor;
    float center_x = *left + (*xside / 2);
    float center_y = *top + (*yside / 2);
    *xside = new_xside;
    *yside = new_yside;
    *left = center_x - (*xside / 2);
    *top = center_y - (*yside / 2);
}

void zoom_out(float* left, float* top, float* xside, float* yside, float zoom_factor)
{
    float new_xside = *xside * zoom_factor;
    float new_yside = *yside * zoom_factor;
    float center_x = *left + (*xside / 2);
    float center_y = *top + (*yside / 2);
    *xside = new_xside;
    *yside = new_yside;
    *left = center_x - (*xside / 2);
    *top = center_y - (*yside / 2);
}

// Move the view left, right, up, or down by a given amount
void move_view(float* left, float* top, float* xside, float* yside, float x_offset, float y_offset)
{
    float x_scale = *xside / WIDTH;
    float y_scale = *yside / HEIGHT;
    *left += x_scale * x_offset;
    *top += y_scale * y_offset;
}

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    float left = -2.0f;
    float top = -1.0f;
    float xside = 3.0f;
    float yside = 2.0f;



    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_UP:
                    move_view(&left, &top, &xside, &yside, 0.0f, -50.0f);
                    break;
                case SDLK_DOWN:
                    move_view(&left, &top, &xside, &yside, 0.0f, 50.0f);
                    break;
                case SDLK_LEFT:
                    move_view(&left, &top, &xside, &yside, -50.0f, 0.0f);
                    break;
                case SDLK_RIGHT:
                    move_view(&left, &top, &xside, &yside, 50.0f, 0.0f);
                    break;
                case SDLK_p:
                    zoom_in(&left, &top, &xside, &yside, 1.1f);
                    break;
                case SDLK_o:
                    zoom_out(&left, &top, &xside, &yside, 1.1f);
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        fractal(renderer, WIDTH, HEIGHT, left, top, xside, yside);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

