// Noah Giles
#include "mylib.h"
#include "titlescreen.h"
#include "timesymbol.h"
#include "topimage.h"
#include "gameover.h"

int main() {
	REG_DISPCNT = MODE3 | BG2_ENABLE;

	// Start off at the title screen
	enum GBAState state = TITLE;

	// Declare and initialize a player and timer struct
	PLAYER cube = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	TIMER count = {130, 130, 10};

	// Control variable so we only draw things once
	int control = 1;

	int randseed = 0;

	// Game loop
	while(1) {
		waitForVblank();
		switch(state) {
		case TITLE:
			// Display the title screen
			drawImage3(0, 0, 240, 160, titlescreen);
			control = 1; // Can set up screen again

			// Start for easy, A for medium, B for hard mazes
			if (KEY_DOWN_NOW(BUTTON_START)) {
				state = EASY;
			}
			if (KEY_DOWN_NOW(BUTTON_A)) {
				state = MEDIUM;
			}
			if (KEY_DOWN_NOW(BUTTON_B)) {
				state = HARD;
			}
			randseed += 1; // Count number of blanks on title screen to use as a seed

			break;
		case EASY:
			// Display and set up screen
			if (control) {
				drawBlankScreen();
				generateEasyMaze(randseed);
				drawImage3(140, 5, 53, 11, timesymbol);
				drawImage3(1, 10, 220, 28, topimage);
				cube.row = 80;
				cube.col = 30;
				cube.size = 5;
				cube.rd = 1;
				cube.cd = 1;
				cube.oldRow = cube.row;
				cube.oldCol = cube.col;
				drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
				drawRect(31, 171, 69, 99, LIGHTGREEN);
				drawRect(141, 70, count.t, 10, RED);
				count.t = 130;
				count.oldt = 130;
				count.timekeep = 20;
				control = 0;
			}

			// Select to get back to title screen
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = TITLE;
			}

			// Movement and collision
			int noCollision = 1;
			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				for (int i = cube.col; i <= cube.col + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(cube.row + cube.size - 1 + cube.rd, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row += cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_UP)) {
				for (int i = cube.col + cube.size - 1; i >= cube.col; i--) {
					if (videoBuffer[OFFSET(cube.row - 1, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row -= cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				for (int i = cube.row; i <= cube.row + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == WHITE) {
						noCollision = 0;
					} else if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == LIGHTGREEN) {
						if (count.timekeep > 5) {
							count.timekeep -= 5;
						}
						control = 1;
						randseed += 100;
					}
				}
				if (noCollision) {
	            	cube.col += cube.cd;
	        	}
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				for (int i = cube.row + cube.size - 1; i >= cube.row; i--) {
					if (videoBuffer[OFFSET(i, cube.col - 1, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
	            	cube.col -= cube.cd;
	        	}
			}
			if (cube.row < 0) {
	            cube.row = 0;
			}
			if (cube.row > 159 - cube.size + 1) {
	            cube.row = 159 - cube.size + 1;
			}
			if (cube.col < 0) {
	            cube.col = 0;
			}
			if (cube.col > 239 - cube.size + 1) {
	            cube.col = 239 - cube.size + 1;
	        }
	        
	        if (cube.row != cube.oldRow || cube.col != cube.oldCol) {
	            drawRect(cube.oldRow, cube.oldCol, cube.oldSize, cube.oldSize, BLACK);
	            drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
			}

			cube.oldRow = cube.row;
			cube.oldCol = cube.col;
			cube.oldSize = cube.size;

			// Timer
			if (count.t > 0) {
				if (count.timekeep == 0) {
					count.timekeep = 10;
					count.t--;
				}
				count.timekeep--;
			}
			if (count.t != count.oldt && count.t > 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				drawRect(141, 70, count.t, 10, RED);
				count.oldt = count.t;
			} else if (count.t == 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				state = GAMEOVER;
				control = 1;
			}

			break;
		case MEDIUM:
			// Display and set up screen
			if (control) {
				drawBlankScreen();
				generateMediumMaze(randseed);
				drawImage3(140, 5, 53, 11, timesymbol);
				drawImage3(1, 10, 220, 28, topimage);
				cube.row = 80;
				cube.col = 30;
				cube.size = 5;
				cube.rd = 1;
				cube.cd = 1;
				cube.oldRow = cube.row;
				cube.oldCol = cube.col;
				drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
				drawRect(31, 171, 69, 99, LIGHTGREEN);
				drawRect(141, 70, count.t, 10, RED);
				count.t = 130;
				count.oldt = 130;
				count.timekeep = 10;
				control = 0;
			}

			// Select to get back to title screen
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = TITLE;
			}

			// Movement and collision
			noCollision = 1;
			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				for (int i = cube.col; i <= cube.col + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(cube.row + cube.size - 1 + cube.rd, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row += cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_UP)) {
				for (int i = cube.col + cube.size - 1; i >= cube.col; i--) {
					if (videoBuffer[OFFSET(cube.row - 1, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row -= cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				for (int i = cube.row; i <= cube.row + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == WHITE) {
						noCollision = 0;
					} else if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == LIGHTGREEN) {
						if (count.timekeep > 5) {
							count.timekeep -= 5;
						}
						control = 1;
						randseed += 100;
					}
				}
				if (noCollision) {
	            	cube.col += cube.cd;
	        	}
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				for (int i = cube.row + cube.size - 1; i >= cube.row; i--) {
					if (videoBuffer[OFFSET(i, cube.col - 1, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
	            	cube.col -= cube.cd;
	        	}
			}
			if (cube.row < 0) {
	            cube.row = 0;
			}
			if (cube.row > 159 - cube.size + 1) {
	            cube.row = 159 - cube.size + 1;
			}
			if (cube.col < 0) {
	            cube.col = 0;
			}
			if (cube.col > 239 - cube.size + 1) {
	            cube.col = 239 - cube.size + 1;
	        }
	        
	        if (cube.row != cube.oldRow || cube.col != cube.oldCol) {
	            drawRect(cube.oldRow, cube.oldCol, cube.oldSize, cube.oldSize, BLACK);
	            drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
			}

			cube.oldRow = cube.row;
			cube.oldCol = cube.col;
			cube.oldSize = cube.size;

			// Timer
			if (count.t > 0) {
				if (count.timekeep == 0) {
					count.timekeep = 10;
					count.t--;
				}
				count.timekeep--;
			}
			if (count.t != count.oldt && count.t > 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				drawRect(141, 70, count.t, 10, RED);
				count.oldt = count.t;
			} else if (count.t == 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				state = GAMEOVER;
				control = 1;
			}

			break;
		case HARD:
			// Display and set up screen
			if (control) {
				drawBlankScreen();
				generateHardMaze(randseed);
				drawImage3(140, 5, 53, 11, timesymbol);
				drawImage3(1, 10, 220, 28, topimage);
				cube.row = 80;
				cube.col = 30;
				cube.size = 2;
				cube.rd = 1;
				cube.cd = 1;
				cube.oldRow = cube.row;
				cube.oldCol = cube.col;
				drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
				drawRect(31, 171, 69, 99, LIGHTGREEN);
				drawRect(141, 70, count.t, 10, RED);
				count.t = 130;
				count.oldt = 130;
				count.timekeep = 30;
				control = 0;
			}

			// Select to get back to title screen
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = TITLE;
			}

			// Movement and collision
			noCollision = 1;
			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				for (int i = cube.col; i <= cube.col + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(cube.row + cube.size - 1 + cube.rd, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row += cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_UP)) {
				for (int i = cube.col + cube.size - 1; i >= cube.col; i--) {
					if (videoBuffer[OFFSET(cube.row - 1, i, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
					cube.row -= cube.rd;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				for (int i = cube.row; i <= cube.row + cube.size - 1; i++) {
					if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == WHITE) {
						noCollision = 0;
					} else if (videoBuffer[OFFSET(i, cube.col + cube.size - 1 + cube.cd, 240)] == LIGHTGREEN) {
						if (count.timekeep > 5) {
							count.timekeep -= 5;
						}
						control = 1;
						randseed += 100;
					}
				}
				if (noCollision) {
	            	cube.col += cube.cd;
	        	}
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				for (int i = cube.row + cube.size - 1; i >= cube.row; i--) {
					if (videoBuffer[OFFSET(i, cube.col - 1, 240)] == WHITE) {
						noCollision = 0;
					}
				}
				if (noCollision) {
	            	cube.col -= cube.cd;
	        	}
			}
			if (cube.row < 0) {
	            cube.row = 0;
			}
			if (cube.row > 159 - cube.size + 1) {
	            cube.row = 159 - cube.size + 1;
			}
			if (cube.col < 0) {
	            cube.col = 0;
			}
			if (cube.col > 239 - cube.size + 1) {
	            cube.col = 239 - cube.size + 1;
	        }
	        
	        if (cube.row != cube.oldRow || cube.col != cube.oldCol) {
	            drawRect(cube.oldRow, cube.oldCol, cube.oldSize, cube.oldSize, BLACK);
	            drawRect(cube.row, cube.col, cube.size, cube.size, CYAN);
			}

			cube.oldRow = cube.row;
			cube.oldCol = cube.col;
			cube.oldSize = cube.size;

			// Timer
			if (count.t > 0) {
				if (count.timekeep == 0) {
					count.timekeep = 10;
					count.t--;
				}
				count.timekeep--;
			}
			if (count.t != count.oldt && count.t > 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				drawRect(141, 70, count.t, 10, RED);
				count.oldt = count.t;
			} else if (count.t == 0) {
				drawRect(141, 70, count.oldt, 10, BLACK);
				state = GAMEOVER;
				control = 1;
			}

			break;
		case GAMEOVER:
			// Display game over screen
			if (control) {
				drawImage3(0, 0, 240, 160, gameover);
				control = 0;
			}

			// Press select to get back to title screen
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = TITLE;
			}

			break;
		}
	}
	return 0;
}
