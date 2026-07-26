#include <stdio.h>

#define BOARD_WIDTH 25
#define BOARD_LENGTH 80
#define RACKET_LEFT_X 5
#define RACKET_RIGHT_X 74
#define BALL_START_X 40
#define BALL_START_Y 13
#define RACKET_START 13
#define WIN_SCORE 21

int FunctionInput();
void Otrisovka(int ballx, int bally, int rocketka_1, int rocketka_2, int chet_1,
               int chet_2);
int DvijenieRocket_1(char deystvie, int p_r1);
int DvijenieRocket_2(char deystvie, int p_r2);
int DvijenieBall_x(int bx, int dirx);
int DvijenieBall_y(int by, int diry);
int WallCollision(int y, int bdir);
int RocketCollision_x(int by, int ry);

int main() {
    int ballx = BALL_START_X, bally = BALL_START_Y;
    int rocketka_1 = RACKET_START, rocketka_2 = RACKET_START;
    int ball_directx = 1, ball_directy = 1;
    int chet_1 = 0, chet_2 = 0;
    int game = 1;
    while (game) {
        Otrisovka(ballx, bally, rocketka_1, rocketka_2, chet_1, chet_2);
        int vvod = FunctionInput();
        rocketka_1 = DvijenieRocket_1(vvod, rocketka_1);
        rocketka_2 = DvijenieRocket_2(vvod, rocketka_2);
        ball_directy = WallCollision(bally, ball_directy);
        if (bally <= 0)
            bally = 0;
        else if (bally >= BOARD_WIDTH - 1) {
            bally = BOARD_WIDTH - 1;
        }
        if (ballx == 74 || ballx == 6) {
            int current_rocket = (ballx == 74) ? rocketka_2 : rocketka_1;
            ball_directx *= RocketCollision_x(bally, current_rocket);
            if (bally < current_rocket) {
                ball_directy = -1;
            } else if (bally > current_rocket) {
                ball_directy = 1;
            }
        }
        if (ballx == 1 || ballx == 79) {
            if (ballx == 1)
                chet_2 = chet_2 + 1;
            else {
                chet_1 = chet_1 + 1;
            }
            ballx = BALL_START_X;
            bally = BALL_START_Y;
            rocketka_1 = RACKET_START;
            rocketka_2 = RACKET_START;
            ball_directx = (ballx == 1) ? 1 : -1;
            ball_directy = 1;
        }
        if (chet_1 >= WIN_SCORE) {
            printf("\nPlayer 1 win with a score - %d:%d\n", chet_1, chet_2);
            game = 0;
        }
        if (chet_2 >= WIN_SCORE) {
            printf("\nPlayer 2 win with a score - %d:%d\n", chet_1, chet_2);
            game = 0;
        }
        ballx = DvijenieBall_x(ballx, ball_directx);
        bally = DvijenieBall_y(bally, ball_directy);
    }
    return 0;
}
void Otrisovka(int ballx, int bally, int rocketka_1, int rocketka_2, int chet_1,
               int chet_2) {
    char ball = 'O';
    char toe = '|';
    char space = ' ';
    char rocket = '|';
    for (int j = 0; j <= BOARD_LENGTH + 1; j++) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < BOARD_WIDTH; i++) {
        printf("|");
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (i == bally && j == ballx) {
                printf("%c", ball);
            } else if ((i == rocketka_1 - 1 || i == rocketka_1 ||
                        i == rocketka_1 + 1) &&
                       j == RACKET_LEFT_X) {
                printf("%c", rocket);
            } else if ((i == rocketka_2 - 1 || i == rocketka_2 ||
                        i == rocketka_2 + 1) &&
                       j == RACKET_RIGHT_X) {
                printf("%c", rocket);
            } else if (j == BOARD_LENGTH / 2) {
                printf("%c", toe);
            } else {
                printf("%c", space);
            }
        }
        printf("|\n");
    }
    for (int j = 0; j <= BOARD_LENGTH + 1; j++) {
        printf("-");
    }
    printf("\n");
    printf("Player 1: %d", chet_1);
    for (int p = 0; p < 60; p++) {
        printf(" ");
    }
    printf("Player 2: %d\n", chet_2);
}

int FunctionInput() {
    int vvod;
    while ((vvod = getchar()) != 'A' && vvod != 'Z' && vvod != 'K' &&
           vvod != 'M' && vvod != ' ') {
        while (getchar() != '\n') {
        }
    }
    while (getchar() != '\n') {
    }
    return vvod;
}

int DvijenieRocket_1(char deystvie, int p_r1) {
    if (deystvie == 'A') {
        if (p_r1 > 1) {
            p_r1 = p_r1 - 1;
        }
    } else if (deystvie == 'Z') {
        if (p_r1 < BOARD_WIDTH - 2) {
            p_r1 = p_r1 + 1;
        }
    }
    return p_r1;
}

int DvijenieRocket_2(char deystvie, int p_r2) {
    if (deystvie == 'K') {
        if (p_r2 > 1) {
            p_r2 = p_r2 - 1;
        }
    } else if (deystvie == 'M') {
        if (p_r2 < BOARD_WIDTH - 2) {
            p_r2 = p_r2 + 1;
        }
    }
    return p_r2;
}

int DvijenieBall_x(int bx, int dirx) { return bx + dirx; }

int DvijenieBall_y(int by, int diry) { return by + diry; }

int WallCollision(int y, int bdir) {
    if (y <= 0 || y >= BOARD_WIDTH - 1) {
        bdir = -bdir;
    }
    return bdir;
}

int RocketCollision_x(int by, int ry) {
    int bdir = 1;
    if (by >= (ry - 1) && by <= (ry + 1)) {
        bdir = -1;
    }
    return bdir;
}