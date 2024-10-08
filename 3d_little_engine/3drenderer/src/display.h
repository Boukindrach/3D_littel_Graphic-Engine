#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

// Screen dimensions
#define WIDTH 800
#define HEIGHT 600

// External declarations for global variables
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

/////////////////////////////////////////////////////
// Function prototypes
/////////////////////////////////////////////////////

bool initialize_window(void);
void draw_grid(uint32_t color);
void draw_rectangle(int x, int y, int height, int width, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif
