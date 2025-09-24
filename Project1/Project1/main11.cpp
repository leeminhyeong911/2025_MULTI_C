#include <stdio.h>
#include <Windows.h>

#define PI 3.14159226535897

void moveCursor(int x, int y) { printf("\x1b[%d;%dH", y, x); }

// isExploded: 0=폭발 전, 1=폭발
void printBomb(int isExploded) {
    if (isExploded) {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else printf("(  b  )");
}

/* ==== 위치/길이 조절용 파라미터 ==== */
#define STAR_X 14
#define STAR_Y 9
#define FUSE_SEGMENTS 10        // 심지 팔 개수(짧게): 6→-2칸, 10→-3칸, 14→-4칸 정도 왼쪽/위로 이동
#define BOMB_OFFSET_X (-7)      // 폭탄 폭(7칸) 만큼 왼쪽에 붙임
#define BOMB_OFFSET_Y (-1)      // 한 줄 위로 올려 “왼쪽 위” 배치

int main(void)
{
    /* 1) 별(*) 초기 위치 */
    moveCursor(STAR_X, STAR_Y);
    printf("*");

    /* 2) 반시계(위→왼→아래→오른쪽) 나선 경로 생성 */
    const int MAXP = 512;
    int pathX[MAXP], pathY[MAXP], n = 0;

    int cx = STAR_X, cy = STAR_Y;
    int dx[4] = { 0, -1, 0,  1 };   // Up, Left, Down, Right
    int dy[4] = { -1,  0, 1,  0 };
    int dir = 0;                    // Up부터
    int len = 1;

    for (int s = 0; s < FUSE_SEGMENTS && n < MAXP; ++s) {
        for (int k = 0; k < len && n < MAXP; ++k) {
            cx += dx[dir];
            cy += dy[dir];
            pathX[n] = cx;
            pathY[n] = cy;
            ++n;
        }
        dir = (dir + 1) % 4;
        if (s % 2 == 1) ++len;     // 두 번 진행할 때마다 길이 +1
    }

    /* 2-1) 심지(#) 그리기 */
    for (int i = 0; i < n; ++i) {
        moveCursor(pathX[i], pathY[i]);
        printf("#");
    }

    /* 3) 심지 시작점(끝단)에 폭탄을 왼쪽 위로 배치 */
    int fuseStartX = pathX[n - 1];
    int fuseStartY = pathY[n - 1];
    int bombX = fuseStartX + BOMB_OFFSET_X;
    int bombY = fuseStartY + BOMB_OFFSET_Y;

    moveCursor(bombX, bombY);
    printBomb(0);                   // 폭발 전 폭탄

    /* 4) 200ms마다 심지를 태우며 이동 */
    int px = STAR_X, py = STAR_Y;
    for (int i = 0; i < n; ++i) {
        // 이전 별 지우기
        moveCursor(px, py);
        printf(" ");

        // 다음 칸에 별 표시
        moveCursor(pathX[i], pathY[i]);
        printf("*");
        Sleep(200);

        px = pathX[i];
        py = pathY[i];
    }

    // 마지막 별 지우고 폭발
    moveCursor(px, py);
    printf(" ");
    moveCursor(bombX, bombY);
    printBomb(1);

    moveCursor(10, 20);
    return 0;
}
