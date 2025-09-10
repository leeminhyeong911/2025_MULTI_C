#include<stdio.h>

void gotoxy(int x, int y) {
	printf("\x1B[%d;%dH,y,x");
}

int main()
{
	int startX = 10;
	int startY = 5;
	int width = 5;
	int height = 5;

	int y = 0;
	while (y < height) {
		int x = 0;
		while (x < width) {
			gotoxy(startX + x, startY + y);

			if (y == 0 || y== height -1 || x == 0 || x == width -1)
				printf("#")
		}
	}
}