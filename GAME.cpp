
#include <iostream>
#include <conio.h>

using namespace std;

bool GameRunning;

const int width = 20;
const int height = 20;
const int MaxLenSnake = (width - 2) * (height - 2);

enum SnakeDirection { STOP = 0, UP, LEFT, DOWN, RIGHT };
SnakeDirection CurrentDirection;

char field = '#';
char SnakeHead = '0';
char SnakeTail = 'o';
char apple = 'A';

int SnakeCoordinateX[MaxLenSnake] = { 0 };
int SnakeCoordinateY[MaxLenSnake] = { 0 };
int AppleCoordinateX, AppleCoordinateY, CurrentSnakeLen;

void config() {
  GameRunning = true;
  CurrentDirection = STOP;
  SnakeCoordinateX[0] = (width / 2) - 1;
  SnakeCoordinateY[0] = (height / 2) - 1;
  AppleCoordinateX = rand() % width;
  AppleCoordinateY = rand() % height;
  CurrentSnakeLen = 1;
}

void draw() {
  system("cls");

  cout << "Score: " << CurrentSnakeLen - 1 << endl;

  for (int UpperBoundIndex = 0; UpperBoundIndex <= width; ++UpperBoundIndex) {
    cout << field;
  }
  cout << endl;

  for (int InternalBoundIndex = 0; InternalBoundIndex < height; ++InternalBoundIndex) {
    for (int ColumnIndex = 0; ColumnIndex < width; ++ColumnIndex) {
      if (ColumnIndex == 0 || ColumnIndex == width - 1) {
        cout << field;
      }
      if (InternalBoundIndex == SnakeCoordinateY[0] && ColumnIndex == SnakeCoordinateX[0]) {
        cout << SnakeHead;
      } else if (InternalBoundIndex == AppleCoordinateY && ColumnIndex == AppleCoordinateX) {
        cout << apple;
      } else {
          cout << " ";
      }
    }
    cout << endl;
  }

  for (int LowerBoundIndex = 0; LowerBoundIndex <= width; ++LowerBoundIndex) {
    cout << field;
  }
  cout << endl;
}

void input() {
  if (_kbhit()) {
    switch (_getch()) {
    case 'w':
      if (CurrentDirection != DOWN) {
        CurrentDirection = UP;
      }
      break;
    case 'a':
      if (CurrentDirection != RIGHT) {
        CurrentDirection = LEFT;
      }
      break;
    case 's':
      if (CurrentDirection != UP) {
        CurrentDirection = DOWN;
      }
      break;
    case 'd':
      if (CurrentDirection != LEFT) {
        CurrentDirection = RIGHT;
      }
      break;
    }
  }
}

void logic() {
  switch (CurrentDirection) {
  case UP:
    --SnakeCoordinateY[0];
    break;
  case LEFT:
    --SnakeCoordinateX[0];
    break;
  case DOWN:
    ++SnakeCoordinateY[0];
    break;
  case RIGHT:
    ++SnakeCoordinateX[0];
  }

  if (SnakeCoordinateX[0] > width || 
      SnakeCoordinateX[0] < 0 || 
      SnakeCoordinateY[0] > height || 
      SnakeCoordinateY[0] < 0) {
    GameRunning = false;
  }

  for (int SnakeLenIndex = 1; SnakeLenIndex < CurrentSnakeLen; ++SnakeLenIndex) {
    if (SnakeCoordinateX[0] == SnakeCoordinateX[SnakeLenIndex] &&
        SnakeCoordinateY[0] == SnakeCoordinateY[SnakeLenIndex]) {
      GameRunning = false;
      SnakeLenIndex = CurrentSnakeLen;
    }
  }

  if (SnakeCoordinateX[0] == AppleCoordinateX && SnakeCoordinateY[0] == AppleCoordinateY) {
    ++CurrentSnakeLen;
    AppleCoordinateX = rand() % width;
    AppleCoordinateY = rand() % height;
  }
}

int main() {
  double time = clock();

  config();

  while (GameRunning) {
    if ((clock() - time) / CLOCKS_PER_SEC >= 0.25) {
      time = clock();
      input();
      draw();
      logic();
    }
  }

  return 0;
}
