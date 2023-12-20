
#include <iostream>
#include <conio.h>

using namespace std;

bool IsGameRunning;

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
  IsGameRunning = true;
  CurrentDirection = STOP;
  srand(time(0));
  SnakeCoordinateX[0] = rand() % (width - 1);
  SnakeCoordinateY[0] = rand() % (height - 1);
  AppleCoordinateX = rand() % (width - 1);
  AppleCoordinateY = rand() % (height - 1);
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
        bool PrintTail = false;

        for (int TailIndex = 1; TailIndex < CurrentSnakeLen; ++TailIndex) {
          if (InternalBoundIndex == SnakeCoordinateY[TailIndex] &&
              ColumnIndex == SnakeCoordinateX[TailIndex]) {
            PrintTail = true;

            cout << SnakeTail;
          }
        }
        if (!PrintTail) {
          cout << " ";
        }
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

  for (int TailIndex = CurrentSnakeLen - 2; TailIndex >= 0; --TailIndex) {
    SnakeCoordinateX[TailIndex + 1] = SnakeCoordinateX[TailIndex];
    SnakeCoordinateY[TailIndex + 1] = SnakeCoordinateY[TailIndex];
  }

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

  if (SnakeCoordinateX[0] > (width - 2) || 
      SnakeCoordinateX[0] < 0 || 
      SnakeCoordinateY[0] > (height - 2) || 
      SnakeCoordinateY[0] < 0) {
    IsGameRunning = false;
  }

  for (int SnakeLenIndex = 1; SnakeLenIndex < CurrentSnakeLen; ++SnakeLenIndex) {
    if (SnakeCoordinateX[0] == SnakeCoordinateX[SnakeLenIndex] &&
        SnakeCoordinateY[0] == SnakeCoordinateY[SnakeLenIndex]) {
      IsGameRunning = false;
      continue;
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

  while (IsGameRunning) {
    if ((clock() - time) / CLOCKS_PER_SEC >= 0.3) {
      time = clock();
      input();
      logic();
      draw();
    }
  }

  return 0;
}
