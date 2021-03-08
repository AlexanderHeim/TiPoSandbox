#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "Finals.h"

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("Hello World!", WINDOW_STARTPOS_X, WINDOW_STARTPOS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

	uint32_t* texture_pixels = calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(uint32_t));

	int left_mousebutton_down = 0;
	int keep_window_open = 1;
	while (keep_window_open)
	{
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
					texture_pixels[mouseY * WINDOW_WIDTH + mouseX] = 320000;
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

