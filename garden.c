#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL2/SDL.h>

const char *generator = "F-F-F-F";
const char *grammar = "F-F+F+F-F";
const int max_depth = 3;

// Define the L-system parameters
const float angle = 90.0f;	 // angle in degrees
const float scale = 700.0f; // length of each line segment

typedef struct
{
	float x;
	float y;
	float angle;
} TurtleState;

// Define a function to interpret & draw the L-system sequence
void interpret_sequence(SDL_Renderer *renderer, const char *sequence, TurtleState *state, float length)
{
	while (*sequence)
	{
		switch (*sequence)
		{
		case 'F': // move forward
			float x1 = state->x;
			float y1 = state->y;
			state->x += length * cos(state->angle * M_PI / 180.0f);
			state->y += length * sin(state->angle * M_PI / 180.0f);
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

void recursive_interpret_sequence(SDL_Renderer *renderer, const char *generator, const char *sequence, TurtleState *state, int depth, const int max_depth, const float length)
{
	if (depth >= max_depth)
	{ // base case: draw the line.
		// draw the generator instead of sequence if n=0
		if (max_depth == 0)
			interpret_sequence(renderer, generator, state, length);
		else
			interpret_sequence(renderer, sequence, state, length);
		return;
	}
	else if (depth == 0)
	{ // depth == 0 means we are at the first iteration, aka replacing the edges of the generator
		++depth;
		while (*generator)
		{
			switch (*generator)
			{
			case 'F':
				recursive_interpret_sequence(renderer, generator, sequence, state, depth, max_depth, length / 4);
				break;
			case '+':
				state->angle += angle;
				break;
			case '-':
				state->angle -= angle;
				break;
			}
			++generator;
		};
	}
	else
	{ // in every other case, we are replacing the edges of the sequence
		++depth;
		const char *original_sequence = sequence;
		while (*sequence)
		{
			switch (*sequence)
			{
			case 'F': // move forward
				recursive_interpret_sequence(renderer, generator, original_sequence, state, depth, max_depth, length / 4);
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
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Garden Box",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640, 480, // updated the window size to better center the image
							  SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Clear the screen to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Draw a point in the middle of the screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Set the initial turtle state
	TurtleState state = {220.0f, 340.0f, 0.0f};

	// Recursively interpret the L-system sequence and draw the corresponding lines
	recursive_interpret_sequence(renderer, generator, grammar, &state, 0, max_depth, scale);

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
