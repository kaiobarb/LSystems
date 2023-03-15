#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("Garden Box",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640, 480,
							  SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Clear the screen to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	// Draw a point in the middle of the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_Rect pixelRect = { 80, 60, 1, 1 };
	SDL_RenderFillRect(renderer, &pixelRect);
	SDL_RenderDrawPoint(renderer, 320, 190);
	
	// Scale
	SDL_RenderSetScale(renderer, 4, 4);

	// Update the screen
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	// Clean Up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
