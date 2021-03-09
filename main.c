#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include <Windows.h>
#include "Finals.h"

typedef struct Pixel {
	uint32_t color;
} pixel;

uint32_t map_mouse_pos(int mouseX, int mouseY) {
	return (mouseX / PIXEL_SIZE + (WINDOW_WIDTH / PIXEL_SIZE) * (mouseY / PIXEL_SIZE));
}

void update_texture(pixel* pixels, uint32_t* texture_pixels) {
	for (int i = 0; i < (WINDOW_WIDTH / PIXEL_SIZE) * (WINDOW_HEIGHT / PIXEL_SIZE); i++) {
		for (int x = 0; x < PIXEL_SIZE; x++) {
			for (int y = 0; y < PIXEL_SIZE; y++) {
				texture_pixels[y*WINDOW_WIDTH + i * PIXEL_SIZE + x] = pixels[i].color;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("Hello World!", WINDOW_STARTPOS_X, WINDOW_STARTPOS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

	uint32_t* texture_pixels = calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(uint32_t));
	pixel* pixels = calloc((WINDOW_WIDTH / PIXEL_SIZE) * (WINDOW_HEIGHT / PIXEL_SIZE), sizeof(pixel));
	pixels[230].color = 320000;
	pixels[231].color = 320000;
	pixels[234].color = 320000;
	int left_mousebutton_down = 0;
	int keep_window_open = 1;
	while (keep_window_open)
	{
		update_texture(pixels, texture_pixels);
		SDL_UpdateTexture(texture, NULL, texture_pixels, WINDOW_WIDTH * sizeof(Uint32));
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				keep_window_open = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
					left_mousebutton_down = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
					left_mousebutton_down = 1;
			case SDL_MOUSEMOTION:
				if (left_mousebutton_down)
				{
					int mouseX = e.motion.x;
					int mouseY = e.motion.y;
					pixels[map_mouse_pos(mouseX, mouseY)].color = 320000;
				}
				break;
			}
			SDL_UpdateWindowSurface(window);
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

