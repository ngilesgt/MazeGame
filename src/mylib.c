// Noah Giles

#include "mylib.h"
#include <stdlib.h> // For rand()

unsigned short *videoBuffer = (u16*) 0x6000000;

// Functions

// A function to set pixel (r, c) to the color passed in
void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

// A function to draw a filled rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color) {
	for (int i = 0; i < height; i++) {
		if (width > 0) {
			DMA[3].src = &color;
			DMA[3].dst = &videoBuffer[OFFSET(r + i, c, 240)];
			DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
		}
	}
}

// A function to draw a hollow rectangle starting at (r, c)
void drawHollowRect(int r, int c, int width, int height, u16 color) {
	for (int i = 0; i < height; i++) {
		setPixel(r + i, c, color);
		setPixel(r + i, c + width, color);
	}
	for (int i = 0; i < width; i++) {
		setPixel(r, c + i, color);
		setPixel(r + height, c + i, color);
	}
}

/* drawImage3
 * A function that will draw an arbitrary sized image onto the screen
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the image
 * @param height height of the image
 * @param image Pointer to the first element of the image
 */
void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int i = r; i < (height + r); i++) {
		for (int j = c; j < (width + c); j++) {
			videoBuffer[OFFSET(i, j, 240)] = image[OFFSET((i - r), (j - c), width)];
		}
	}
}

// Uses DMA to draw a blank screen
void drawBlankScreen() {
	DMA[3].src = 0;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

// Function to draw on the screen at the correct time
// to avoid tearing
void waitForVblank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void generateEasyMaze(int seed) {
	// Start with a 5x5 grid
	drawHollowRect(30, 70, 100, 100, WHITE);
	drawHollowRect(30, 0, 240, 0, WHITE);
	drawHollowRect(130, 0, 240, 0, WHITE);
	for (int i = 90; i < 170; i += 20) {
		drawHollowRect(30, i, 0, 100, WHITE);
	}
	for (int i = 50; i < 130; i += 20) {
		drawHollowRect(i, 70, 100, 0, WHITE);
	}

	// BST Algorithm
	srand(seed); // Pseudorandom seed

	// This is a BST algorithm that utilizes
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int k = rand() % 2; // 0 or 1
			if ((i == 4 && j != 4) || (k && i < 4 && j < 4)) {
				drawRect(31 + (20 * i), 90 + (20 * j), 1, 19, BLACK); // Carve passage right
			} else if ((j == 4 && i != 4) || (!k && j < 4 && i < 4)) {
				drawRect(50 + (20 * i), 71 + (20 * j), 19, 1, BLACK); // Carve passage down
			}
		}
	}
	drawRect(71, 70, 1, 19, BLACK); // Entrance
	drawRect(71, 170, 1, 19, BLACK); // Exit
}

void generateMediumMaze(int seed) {
	// Start with a 10 x 10 grid
	drawHollowRect(30, 70, 100, 100, WHITE);
	drawHollowRect(30, 0, 240, 0, WHITE);
	drawHollowRect(130, 0, 240, 0, WHITE);
	for (int i = 80; i < 170; i += 10) {
		drawHollowRect(30, i, 0, 100, WHITE);
	}
	for (int i = 40; i < 130; i += 10) {
		drawHollowRect(i, 70, 100, 0, WHITE);
	}

	// BST Algorithm
	srand(seed); // Fairly random seed

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int k = rand() % 2; // 0 or 1
			if ((i == 9 && j != 9) || (k && i < 9 && j < 9)) {
				drawRect(31 + (10 * i), 80 + (10 * j), 1, 9, BLACK); // Carve passage right
			} else if ((j == 9 && i != 9) || (!k && j < 9 && i < 9)) {
				drawRect(40 + (10 * i), 71 + (10 * j), 9, 1, BLACK); // Carve passage down
			}
		}
	}
	drawRect(71, 70, 1, 19, BLACK); // Entrance
	drawRect(71, 170, 1, 9, BLACK); // Exit
}

void generateHardMaze(int seed) {
	// Start with a 25 x 25 grid
	drawHollowRect(30, 70, 100, 100, WHITE);
	drawHollowRect(30, 0, 240, 0, WHITE);
	drawHollowRect(130, 0, 240, 0, WHITE);
	for (int i = 74; i < 170; i += 4) {
		drawHollowRect(30, i, 0, 100, WHITE);
	}
	for (int i = 34; i < 130; i += 4) {
		drawHollowRect(i, 70, 100, 0, WHITE);
	}

	// BST Algorithm
	srand(seed); // Fairly random seed

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			int k = rand() % 2; // 0 or 1
			if ((i == 24 && j != 24) || (k && i < 24 && j < 24)) {
				drawRect(31 + (4 * i), 74 + (4 * j), 1, 3, BLACK); // Carve passage right
			} else if ((j == 24 && i != 24) || (!k && j < 24 && i < 24)) {
				drawRect(34 + (4 * i), 71 + (4 * j), 3, 1, BLACK); // Carve passage down
			}
		}
	}
	drawRect(78, 70, 1, 4, BLACK); // Entrance
	drawRect(78, 170, 1, 4, BLACK); // Exit
}
