#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAP_LEFT_END 4
#define MAP_RIGHT_END 13
#define MAP_TOP_END 4
#define MAP_BOTTOM_END 28
#define MAP_WIDTH 10
#define MAP_LENGTH 25

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void createMap(void) {
	gotoxy((MAP_LEFT_END - 1) * 2, MAP_TOP_END - 1);
	printf("▣▣▣▣▣▣▣▣▣▣▣▣");
	for (int i = MAP_LEFT_END; i <= MAP_BOTTOM_END; ++i) {
		gotoxy((MAP_LEFT_END - 1) * 2, i);
		printf("▣                    ▣");
	}
	gotoxy((MAP_LEFT_END - 1) * 2, MAP_BOTTOM_END + 1);
	printf("▣▣▣▣▣▣▣▣▣▣▣▣");
}

void releaseRuleLine(char map[MAP_LENGTH][MAP_WIDTH], int nowLocation[4][2]) {
	for (int j = 0; j < MAP_WIDTH; ++j) {
		gotoxy(2 * (MAP_LEFT_END + j), MAP_TOP_END + 4);
		if (map[4][j] != 2) {
			printf("--");
		}
	}
}

// 블록, x좌표, y좌표를 입력받으면 좌표부터 시작하여 블록을 그리는 함수입니다. 
void drawingBlock(char blockName[4][4], char map[MAP_LENGTH][MAP_WIDTH], int blocksLocation[4][2], int nowLocation[2]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			gotoxy((nowLocation[0] + i)*2, nowLocation[1] + j);
			if (blockName[j][i] == 0 && ((nowLocation[0] +i >= MAP_LEFT_END && nowLocation[0] +i <= MAP_RIGHT_END) && (nowLocation[1] +j >= MAP_TOP_END && nowLocation[1] +j <= MAP_BOTTOM_END))) {
				if (map[nowLocation[1] + j - MAP_TOP_END][nowLocation[0] + i - MAP_LEFT_END] != 2) {
					if (j + nowLocation[1] != 8) {
						printf("  ");
					}
				}
				//printf("  ");
			}
			else if (blockName[j][i] == 1 && ((nowLocation[0] + i >= MAP_LEFT_END && nowLocation[0] + i <= MAP_RIGHT_END) && (nowLocation[1] + j >= MAP_TOP_END && nowLocation[1] + j <= MAP_BOTTOM_END))) {
				if (map[nowLocation[1] + j - MAP_TOP_END][nowLocation[0] + i - MAP_LEFT_END] != 2) {
					printf("□");
				}
				//printf("□");
			}
		}
	}
}

void copyBlock(char desBlock[4][4], char strBlock[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			desBlock[i][j] = strBlock[i][j];
		}
	}
}

void blocksXYPrint(char blockName[4][4], int nowBlocksLocation[4][2], int nowLocation[2]) {
	int xycount = 0, maxX = 0, maxY = 0, minX = MAP_RIGHT_END, minY = MAP_TOP_END;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (blockName[j][i] == 1) {
				gotoxy(60, 10 + xycount);
				nowBlocksLocation[xycount][0] = nowLocation[0] + i;
				nowBlocksLocation[xycount][1] = nowLocation[1] + j;
				//printf("%02d, %02d\n", nowlocation[xycount][0], nowlocation[xycount][1]);
				xycount++;
			}
		}
	}
}

int maxXis(char blockName[4][4], int nowLocation[2]) {
	int maxX = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (blockName[j][i] == 1) {
				if (nowLocation[0] + i > maxX) maxX = (nowLocation[0] + i);
			}
		}
	}
	//gotoxy(60, 15);
	//printf("maxX: %02d", maxX);
	return maxX;
}

int minXis(char blockName[4][4], int nowLocation[2]) {
	int minX = MAP_RIGHT_END;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (blockName[j][i] == 1) {
				if (nowLocation[0] + i < minX) minX = nowLocation[0] + i;
			}
		}
	}
	//gotoxy(60, 16);
	//printf("minX: %02d", minX);
	return minX;
}

int maxYis(char blockName[4][4], int nowLocation[2]) {
	int maxY = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (blockName[j][i] == 1) {
				if (nowLocation[1] + j > maxY) maxY = nowLocation[1] + j;
			}
		}
	}
	//gotoxy(60, 17);
	//printf("maxY: %02d", maxY);
	return maxY;
}

int minYis(char blockName[4][4], int nowLocation[2]) {
	int  minY = MAP_BOTTOM_END;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (blockName[j][i] == 1) {
				if (nowLocation[1] + j < minY) minY = nowLocation[1] + j;
			}
		}
	}
	//gotoxy(60, 18);
	//printf("minY: %02d", minY);
	return minY;
}

void releaseBlocksLocation(char blockName[4][4], int blocksLocation[4][2], int nowLocation[2]) {
	maxXis(blockName, nowLocation);
	minXis(blockName, nowLocation);
	maxYis(blockName, nowLocation);
	minYis(blockName, nowLocation);
	blocksXYPrint(blockName, blocksLocation, nowLocation);
}

void blockOrderShuffle(int blockOrder[7]) {
	int bufferArray[7] = {0,1,2,3,4,5,6};
	srand(time(NULL));
	for (int i = 0; i < 7; ++i) {
		int num = (rand() % 7);
		int temp = 0;
		temp = bufferArray[i];
		bufferArray[i] = bufferArray[num];
		bufferArray[num] = temp;
	}
	for (int i = 0; i < 7; ++i) {
		blockOrder[i] = bufferArray[i];
	}
	/*gotoxy(80, 5);
	for (int i = 0; i < 7; ++i) {
		printf("%02d ", blockOrder[i]);
	}
	*/
}

void changeBlock(char desBlock[4][4], int blockOrder[7], int* nowOrder) {
	// 7종의 블록을 선언합니다
	char oBlock[4][4] =
	{	{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0} };

	char iBlock[4][4] =
	{	{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0} };

	char tBlock[4][4] =
	{	{0,0,0,0},
		{1,1,1,0},
		{0,1,0,0},
		{0,0,0,0} };

	char sBlock[4][4] =
	{	{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0} };

	char zBlock[4][4] =
	{	{0,0,0,0},
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0} };

	char jBlock[4][4] =
	{	{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0} };

	char lBlock[4][4] =
	{	{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0} };

	int noworder = *nowOrder;
	int randomBlock = blockOrder[noworder];

	switch (randomBlock) {
	case 0: // oBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = oBlock[j][i];

			}
		}
		break;
	case 1: // iBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = iBlock[j][i];

			}
		}
		break;
	case 2: // tBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = tBlock[j][i];

			}
		}
		break;
	case 3: // sBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = sBlock[j][i];

			}
		}
		break;
	case 4: // zBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = zBlock[j][i];

			}
		}
		break;
	case 5: // jBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = jBlock[j][i];

			}
		}
		break;
	case 6: // lBlock
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				desBlock[j][i] = lBlock[j][i];

			}
		}
		break;
	}
}

//블록을 시계방향으로 회전시키는 함수입니다. 
void spinBlock(char desBlock[4][4], char map[MAP_LENGTH][MAP_WIDTH], int nowLocation[2]) {
	char bufferBlock[4][4] =
	{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0} };

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			bufferBlock[i][3-j] = desBlock[j][i];
		}
	}

	int spinAbleCount = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (bufferBlock[i][j] == 1 && map[nowLocation[1] + i - MAP_TOP_END][nowLocation[0] + j - MAP_LEFT_END] != 2) spinAbleCount++;
		}
	}
	

	if (spinAbleCount == 4) {
		copyBlock(desBlock, bufferBlock);
	}
}

void drawingMap(char map[MAP_LENGTH][MAP_WIDTH]) {
	for (int i = 0; i < MAP_LENGTH; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			gotoxy((MAP_LEFT_END + j) * 2, MAP_TOP_END + i);
			if (map[i][j] == 0) {
				printf("  ");
			}
			else if (map[i][j] == 2) {
				printf("■");
			}
		}
	}
	
}

void clearLine(char map[MAP_LENGTH][MAP_WIDTH]) {
	for (int i = 0; i < MAP_LENGTH; ++i) {
		int lineCounter = 0;
		for (int j = 0; j < MAP_WIDTH; ++j) {
			lineCounter += map[i][j];
		}
		if (lineCounter >= 20) {

			for (int k = i; k > 0; --k) {
				for (int j = 0; j < MAP_WIDTH; ++j) {
					map[k][j] = map[k - 1][j];
				}
			}
			for (int j = 0; j < MAP_WIDTH; ++j) {
				map[0][j] = 0;
			}
		}


	}
}

void overLine(char map[MAP_LENGTH][MAP_WIDTH], int* gameOver) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j] == 2) {
				*gameOver = 1;
				return;
			}
		}
	}
}

void drawingNextBlock(char blockName[4][4]) {
	gotoxy(40, 4);
	printf("----Next Block----");
	for (int i = 0; i < 4; ++i) {
		gotoxy(44, 6 + i);
		for (int j = 0; j < 4; ++j) {
			if (blockName[i][j] == 0) {
				printf("  ");
			}
			else if (blockName[i][j] == 1) {
				printf("□");
			}
		}
		
	}
	gotoxy(40, 10);
	printf("------------------");
} 

void pixBlock(char blockName[4][4], char nextBlock[4][4], int blocksLocation[4][2], char map[MAP_LENGTH][MAP_WIDTH], int nowLocation[2], int blockOrder[7], int* nowOrder) {
	
	for (int i = 0; i < 4; ++i) {
		map[blocksLocation[i][1] - MAP_TOP_END][blocksLocation[i][0] - MAP_LEFT_END] = 2;
	} 

	if ((*nowOrder) < 6) {
		(*nowOrder)++;
	}
	else {
		for (int i = 0; i < 7; ++i) {
			blockOrderShuffle(blockOrder);
			(*nowOrder) = 0;
		}
	}

	clearLine(map);
	nowLocation[0] = 6;
	nowLocation[1] = 4;
	copyBlock(blockName, nextBlock);
	changeBlock(nextBlock, blockOrder, nowOrder);
	drawingNextBlock(nextBlock);
	releaseBlocksLocation(blockName, blocksLocation, nowLocation);
	releaseRuleLine(map, nowLocation);
	drawingMap(map);
}

void blockDrop(char blockName[4][4], char nextBlock[4][4], int blocksLocation[4][2], char map[MAP_LENGTH][MAP_WIDTH], int nowLocation[2], int blockOrder[7], int *nowOrder) {

	char deleteBlock[4][4] =
	{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}, };

	int downAbleCount = 0;

	if (maxYis(blockName, nowLocation) < MAP_BOTTOM_END) {
		
		for (int i = 0; i < 4; i++) {
			if (map[blocksLocation[i][1]] - MAP_TOP_END >= MAP_BOTTOM_END && (map[blocksLocation[i][1] - MAP_TOP_END + 1][blocksLocation[i][0] - MAP_LEFT_END] != 2)) {
				downAbleCount++;
			}
			
		}
		if (downAbleCount == 4) {
			drawingBlock(deleteBlock, map, blocksLocation, nowLocation);
			++nowLocation[1];
			releaseBlocksLocation(blockName, blocksLocation, nowLocation);
			drawingBlock(blockName, map, blocksLocation, nowLocation);
		}
		else pixBlock(blockName, nextBlock, blocksLocation, map, nowLocation, blockOrder, nowOrder);
		releaseRuleLine(map, nowLocation);
	}
	else pixBlock(blockName, nextBlock, blocksLocation, map, nowLocation, blockOrder, nowOrder);
	releaseRuleLine(map, nowLocation);
}

int main(void) {

	// 콘솔창의 이름과 면적을 설정하는 코드입니다. 
	system("mode con cols=70 lines=38 | title TETRIS");


	// 커서를 제거하는 함수입니다. 
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// 테트리스의 타이틀 화면입니다. 
	while (_kbhit() != 1) {
		gotoxy(10, 7);
		printf("==================================================");
		gotoxy(32, 10);
		printf("TETRIS");
		gotoxy(27, 12);
		printf("Press any key...");
		gotoxy(10, 15);
		printf("==================================================");
		gotoxy(10, 25);
		printf("←↓→ : move\t\tUP : spin\tESC : exit");
	}
	system("cls");

	// 블록을 지우기 위해 사용하는 딜리트블록입니다. 블록 이동을 할 때 딜리트블록으로 해당 위치를 비운 후 좌표를 연산하고 블록을 다시 그립니다. 
	char deleteBlock[4][4] =
	{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}, };

	
	/*char map[MAP_LENGTH][MAP_WIDTH] =
	{	{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}	};
	*/
	
	char** map = NULL;
	map = (char**)malloc(MAP_LENGTH * sizeof(char*));
	for (int i = 0; i < MAP_LENGTH; ++i) {
		map[i] = (char*)malloc(MAP_WIDTH * sizeof(char));
		memset(map[i], 0, MAP_WIDTH * sizeof(char));
	}
	

	// 현재 블록
	char nowBlock[4][4] = 
	{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}, };
	
	// 다음 블록
	char nextBlock[4][4] = 
	{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}, };

	// 현재 블록이 생성될 위치
	int nowLocation[2] = { 6, 4 };

	// 키보드 입력값을 저장할 변수를 선언합니다. 
	unsigned char kb_input = 0;
	unsigned char kb_arrow = 0;

	int nowBlocksLocation[4][2] =
	{	{0,0},
		{0,0},
		{0,0},
		{0,0} };

	int blockOrder[7] = { 0,0,0,0,0,0,0 };

	int nowOrder = 0;
	int* p_nowOrder = &nowOrder;

	blockOrderShuffle(blockOrder);

	createMap();
	drawingMap(map);
	releaseRuleLine(map, nowBlocksLocation);
	changeBlock(nowBlock, blockOrder, p_nowOrder);
	(*p_nowOrder)++;
	changeBlock(nextBlock, blockOrder, p_nowOrder);
	drawingNextBlock(nextBlock);
	drawingBlock(nowBlock, map, nowBlocksLocation, nowLocation);
	releaseBlocksLocation(nowBlock, nowBlocksLocation, nowLocation);

	gotoxy(40, 25);
	printf("←↓→ : move");
	gotoxy(40, 26);
	printf("UP : spin");
	gotoxy(40, 27);
	printf("ESC : exit");

	int gameOver = 0;
	int* p_gameOver = &gameOver;
	unsigned int gameSpeed = 1000;
	unsigned int lastMoveTime = GetTickCount64();

	while (*p_gameOver != 1) {

		unsigned int currentTime = GetTickCount64();
		unsigned int elapsedTime = currentTime - lastMoveTime;

		if (elapsedTime >= gameSpeed) { // gameSpeed millsec이 지날 때마다 
			blockDrop(nowBlock, nextBlock, nowBlocksLocation, map, nowLocation, blockOrder, p_nowOrder);
			overLine(map, p_gameOver);
			clearLine(map);
			drawingMap(map);
			releaseRuleLine(map, nowBlocksLocation);
			drawingBlock(nowBlock, map, nowBlocksLocation, nowLocation);
			lastMoveTime = GetTickCount64();
		}

		if (_kbhit()) {
			kb_input = _getch();
			switch (kb_input) {
			case 0xE0: // 방향키 입력
				kb_arrow = _getch();
				switch (kb_arrow) {
				case 0x4B: // left 키 입력
					drawingBlock(deleteBlock, map, nowBlocksLocation, nowLocation);
					if (minXis(nowBlock, nowLocation) > MAP_LEFT_END) {
						int ableCounter = 0;
						for (int i = 0; i < 4; ++i) {
							if (map[nowBlocksLocation[i][1] - MAP_TOP_END][nowBlocksLocation[i][0] - MAP_LEFT_END - 1] != 2) ableCounter++;
						}
						if (ableCounter == 4) --nowLocation[0];
					} 
					releaseBlocksLocation(nowBlock, nowBlocksLocation, nowLocation);
					releaseRuleLine(map, nowLocation);
					break;
				case 0x4D: // right 키 입력
					drawingBlock(deleteBlock, map, nowBlocksLocation, nowLocation);
					if (maxXis(nowBlock, nowLocation) < MAP_RIGHT_END) {
						int ableCounter = 0;
						for (int i = 0; i < 4; ++i) {
							if (map[nowBlocksLocation[i][1] - MAP_TOP_END][nowBlocksLocation[i][0] - MAP_LEFT_END + 1] != 2) ableCounter++;
						}
						if (ableCounter == 4) ++nowLocation[0];
					} 
					releaseBlocksLocation(nowBlock, nowBlocksLocation, nowLocation);
					releaseRuleLine(map, nowLocation);
					break;
				case 0x50: //down 키 입력
					blockDrop(nowBlock, nextBlock, nowBlocksLocation, map, nowLocation, blockOrder, p_nowOrder);
					overLine(map, p_gameOver);
					clearLine(map);
					lastMoveTime = GetTickCount64();
					break;
				case 0x48: // up 키 입력
					spinBlock(nowBlock, map, nowLocation);
					releaseBlocksLocation(nowBlock, nowBlocksLocation, nowLocation);
					break;
				}
				break;
			

			case 0x1B:
				*p_gameOver = 1;
				break;
			}
			
			drawingBlock(nowBlock, map, nowBlocksLocation, nowLocation);
			releaseBlocksLocation(nowBlock, nowBlocksLocation, nowLocation);


		}
		
	}

	gotoxy(12, 6);
	printf("------------");
	gotoxy(12, 7);
	printf(" GAME OVER");
	gotoxy(12, 8);
	printf("---------------");

	
	for (int i = 0; i < MAP_LENGTH; ++i) {
		free(map[i]);
	}
	free(map);
	

	gotoxy(0, 30);
	return 0;
}