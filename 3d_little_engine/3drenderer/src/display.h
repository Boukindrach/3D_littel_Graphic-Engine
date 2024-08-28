#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#define WIDTH 800
#define HEIGHT 600

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;


bool initialize_window(void);
void draw_grid(uint32_t color);
void draw_rectangle(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);

#endif
