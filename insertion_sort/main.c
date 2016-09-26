#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "random.h"

#define LEN 128
#define RANGE 128

// The height of a graph bar is DRAW_HEIGHT_MULT * height
// height is defined as 0 to RANGE
#define DRAW_HEIGHT_MULT 3
// Width of each graph bar
#define DRAW_WIDTH 3
// Space between each graph bar
#define DRAW_SPACE 2
// Delay time in ms between operations
#define DELAY 2

int width = DRAW_SPACE * (LEN + 1) + DRAW_WIDTH * LEN;
int height = DRAW_HEIGHT_MULT * RANGE + DRAW_SPACE * 2;

int array[LEN];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Initialize SDL (return true if successful, false otherwise)
bool init_sdl() {

	// Initialize SDL_video
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: Failed to init SDL2: %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(
		"Insertion Sort",         // window title
		SDL_WINDOWPOS_UNDEFINED,      // initial x position
		SDL_WINDOWPOS_UNDEFINED,      // initial y position
		width,                        // width, in pixels
		height,                       // height, in pixels
		SDL_WINDOW_OPENGL             // flags - see below
	);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	// Initialize Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		printf("Could not init renderer: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void draw_graph() {

	// Clear the screen with a white background
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	// Draw each bar
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	for(int i = 0; i < LEN; i++) {
		SDL_Rect bar = {
			DRAW_SPACE + i * (DRAW_SPACE + DRAW_WIDTH),
			height - DRAW_SPACE - DRAW_HEIGHT_MULT * array[i],
			DRAW_WIDTH,
			DRAW_HEIGHT_MULT * array[i]
		};
		SDL_RenderFillRect(renderer, &bar);
	}

	SDL_RenderPresent(renderer);
}

void quit_sdl() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void check_input() {
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT) {
			quit_sdl();
			exit(0);
		}
	}
}

void visual_insertion_sort(int *array, int len) {
	for(int i = 1; i < len; i++) {
		for(int j = i; j > 0; j--) {
			if(array[j-1] > array[j]) {
				// Previous value is less, swap them
				int temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			} else {
				break;
			}
			check_input();
			draw_graph();
			SDL_Delay(DELAY);
		}
	}
}

int main() {

	init_sdl();

	// Visulaizer operates with line heights in multiples of RANGE
	populate_array(array, LEN, 1, RANGE);

	// Show unsorted array for 2 seconds
	draw_graph();
	SDL_Delay(2000);

	visual_insertion_sort(array, LEN);

	while(true) {
		check_input();
	}

	return 0;

}