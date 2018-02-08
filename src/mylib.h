//Noah Giles

typedef unsigned short u16;

typedef struct {
	int row;
	int col;
	int rd;
	int cd;
	int size;
	int oldRow;
	int oldCol;
	int oldSize;
	u16 color;
} PLAYER;

typedef struct {
	int t;
	int oldt;
	int timekeep;
} TIMER;

extern u16 *videoBuffer;

// Definitions
#define REG_DISPCNT *(u16*) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define SCANLINECOUNTER * (volatile u16 *) 0x4000006
#define OFFSET(r, c, rowLength) ((r) * (rowLength) + (c))

// GBA Buttons
#define BUTTON_A 		(1 << 0)
#define BUTTON_B 		(1 << 1)
#define BUTTON_SELECT 	(1 << 2)
#define BUTTON_START 	(1 << 3)
#define BUTTON_RIGHT 	(1 << 4)
#define BUTTON_LEFT 	(1 << 5)
#define BUTTON_UP 		(1 << 6)
#define BUTTON_DOWN 	(1 << 7)
#define BUTTON_R 		(1 << 8)
#define BUTTON_L 		(1 << 9)
#define BUTTONS *(volatile unsigned int *) 0x4000130
#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)

// Colors
#define RGB(r, g, b) ((r) | (g) << 5 | (b) << 10)
#define WHITE RGB(31, 31, 31)
#define BLACK 0
#define RED RGB(31, 0, 0)
#define GREEN RGB(0, 31, 0)
#define BLUE RGB(0, 0, 31)
#define YELLOW RGB(31, 31, 0)
#define CYAN RGB(0, 31, 31)
#define PURPLE RGB(31, 0, 31)
#define LIGHTGREEN RGB(13, 31, 13)

// DMA
typedef struct {
	const volatile void *src;
	const volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x40000B0)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_ON (1 << 31)

// States
enum GBAState {
	TITLE,
	EASY,
	MEDIUM,
	HARD,
	GAMEOVER
};

// Function prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawBlankScreen();
void waitForVblank();
void generateEasyMaze(int seed);
void generateMediumMaze(int seed);
void generateHardMaze(int seed);
