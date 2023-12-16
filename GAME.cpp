
#include <iostream>
#include <Windows.h>

using namespace std;

const int width = 17;
const int height = 10;
const int MaxLenSnake = (width - 3) * (height - 2);

int UP = 0;
int LEFT = 1;
int DOWN = 2;
int RIGHT = 3;

int SnakeDirection = UP;

bool GameRunning = true;

char map[] =
"################\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"################\n";

char snake = '0';
char apple = 'A';

int SnakeCoordinateX[MaxLenSnake] = { 0 };
int SnakeCoordinateY[MaxLenSnake] = { 0 };
int SnakeLen = 1;
int AppleCoordinateX = 1 + (rand() % (width - 3));
int AppleCoordinateY = 1 + (rand() % (height - 2));

int main() {
  SnakeCoordinateX[0] = width / 2;
  SnakeCoordinateY[0] = height / 2;

  while (GameRunning) {
    if (GetKeyState('W') & 0x8000) {
      if (SnakeDirection != DOWN) {
        SnakeDirection = UP;
      }
    }
    if (GetKeyState('A') & 0x8000) {
      if (SnakeDirection != RIGHT) {
        SnakeDirection = LEFT;
      }
    }
    if (GetKeyState('S') & 0x8000) {
      if (SnakeDirection != UP) {
        SnakeDirection = DOWN;
      }
    }
    if (GetKeyState('D') & 0x8000) {
      if (SnakeDirection != LEFT) {
        SnakeDirection = RIGHT;
      }
    }

    Sleep(200);

    if (SnakeCoordinateX[0] == AppleCoordinateX && SnakeCoordinateY[0] == AppleCoordinateY) {
      ++SnakeLen;
      AppleCoordinateX = 1 + (rand() % (width - 3));
      AppleCoordinateY = 1 + (rand() % (height - 2));
    }

    for (int SnakeMoveIndex = SnakeLen - 2; SnakeMoveIndex >= 0; --SnakeMoveIndex) {
      SnakeCoordinateX[SnakeMoveIndex + 1] = SnakeCoordinateX[SnakeMoveIndex];
      SnakeCoordinateY[SnakeMoveIndex + 1] = SnakeCoordinateY[SnakeMoveIndex];
    }

    if (SnakeDirection == UP) {
      --SnakeCoordinateY[0];
    }
    if (SnakeDirection == LEFT) {
      --SnakeCoordinateX[0];
    }
    if (SnakeDirection == DOWN) {
      ++SnakeCoordinateY[0];
    }
    if (SnakeDirection == RIGHT) {
      ++SnakeCoordinateX[0];
    }

    if (SnakeCoordinateX[0] == 0 || SnakeCoordinateY[0] == 0 || SnakeCoordinateX[0] == width - 2 || SnakeCoordinateY[0] == height - 1) {
      GameRunning = false;
    }

    for (int SnakeTailIndex = 1; SnakeTailIndex < SnakeLen; ++SnakeTailIndex) {
      if (SnakeCoordinateX[0] == SnakeCoordinateX[SnakeTailIndex] && SnakeCoordinateY[0] == SnakeCoordinateY[SnakeTailIndex]) {
        GameRunning = false;
        SnakeTailIndex = SnakeLen;
      }
    }

    system("cls");

    map[AppleCoordinateY * width + AppleCoordinateX] = apple;

    for (int SnakeOutputIndex = 0; SnakeOutputIndex < SnakeLen; ++SnakeOutputIndex) {
      map[SnakeCoordinateY[SnakeOutputIndex] * width + SnakeCoordinateX[SnakeOutputIndex]] = snake;
    }

    cout << map;

    for (int SnakeOutputIndex = 0; SnakeOutputIndex < SnakeLen; ++SnakeOutputIndex) {
      map[SnakeCoordinateY[SnakeOutputIndex] * width + SnakeCoordinateX[SnakeOutputIndex]] = ' ';
    }
  }
  cout << "Score:" << SnakeLen - 1;
}
