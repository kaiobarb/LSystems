#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL2/SDL.h>

const char *grammar = "F+F-F-F+F-";

// Define the L-system parameters
const float angle = 90.0f; // angle in degrees
const float scale = 10.0f; // length of each line segment

typedef struct
{
	float x;
	float y;
	float angle;
} TurtleState;

// Define a function to interpret the L-system sequence
void interpret_sequence(SDL_Renderer *renderer, const char *sequence, TurtleState *state)
{
	while (*sequence)
	{
		switch (*sequence)
		{
		case 'F': // move forward
			float x1 = state->x;
			float y1 = state->y;
			state->x += scale * cos(state->angle * M_PI / 180.0f);
			state->y += scale * sin(state->angle * M_PI / 180.0f);
			float x2 = state->x;
			float y2 = state->y;
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
			break;
		case '+': // turn left
			state->angle += angle;
			break;
		case '-': // turn right
			state->angle -= angle;
			break;
		}
		++sequence;
	}
}

int main(int argc, char *argv[])
{
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Set the initial turtle state
	TurtleState state = {320.0f, 240.0f, 0.0f};

	// Interpret the L-system sequence and draw the corresponding lines
	for (int i = 0; i < 4; ++i)
	{
		interpret_sequence(renderer, grammar, &state);
	}

	// Scale
	SDL_RenderSetScale(renderer, 2, 2);

	// Update the screen
	SDL_RenderPresent(renderer);

	// Wait for the user to quit the application
	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			break;
		}
	}

	// Clean Up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
