#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#define WIDTH 800
#define HEIGHT 600

bool is_running;
SDL_Window *window;
SDL_Renderer *renderer;
uint32_t *color_buffer;
SDL_Texture *color_buffer_texture;


bool initialize_window(void);
void draw_grid(void);
void draw_rectangle(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);

#endif
