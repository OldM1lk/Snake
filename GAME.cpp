
#include <iostream>
#include <conio.h>

using namespace std;

bool isGameRunning;

const int fieldWidth = 20;
const int fieldHeight = 20;
const int maxLenSnake = (fieldWidth - 2) * (fieldHeight - 2);

enum snakeDirection { STOP = 0, UP, LEFT, DOWN, RIGHT };
snakeDirection currentDirection;

char field = '#';
char snakeHead = '0';
char SnakeTail = 'o';
char apple = 'A';

int snakeCoordinateX[maxLenSnake] = { 0 };
int snakeCoordinateY[maxLenSnake] = { 0 };
int appleCoordinateX, appleCoordinateY, currentSnakeLen;

void config() {
  isGameRunning = true;
  currentDirection = STOP;
  srand(time(0));
  snakeCoordinateX[0] = rand() % (fieldWidth - 1);
  snakeCoordinateY[0] = rand() % (fieldHeight - 1);
  appleCoordinateX = rand() % (fieldWidth - 1);
  appleCoordinateY = rand() % (fieldHeight - 1);
  currentSnakeLen = 1;
}

void draw() {
  system("cls");

  cout << "Score: " << currentSnakeLen - 1 << endl;

  for (int upperBoundIndex = 0; upperBoundIndex <= fieldWidth; ++upperBoundIndex) {
    cout << field;
  }
  cout << endl;

  for (int internalBoundIndex = 0; internalBoundIndex < fieldHeight; ++internalBoundIndex) {
    for (int columnIndex = 0; columnIndex < fieldWidth; ++columnIndex) {
      if (columnIndex == 0 || columnIndex == fieldWidth - 1) {
        cout << field;
      }

      if (internalBoundIndex == snakeCoordinateY[0] && columnIndex == snakeCoordinateX[0]) {
        cout << snakeHead;
      } else if (internalBoundIndex == appleCoordinateY && columnIndex == appleCoordinateX) {
        cout << apple;
      } else {
        bool printTail = false;

        for (int tailIndex = 1; tailIndex < currentSnakeLen; ++tailIndex) {
          if (internalBoundIndex == snakeCoordinateY[tailIndex] &&
              columnIndex == snakeCoordinateX[tailIndex]) {
            printTail = true;

            cout << SnakeTail;
          }
        }
        if (!printTail) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }

  for (int lowerBoundIndex = 0; lowerBoundIndex <= fieldWidth; ++lowerBoundIndex) {
    cout << field;
  }

  cout << endl;
}

void input() {
  if (_kbhit()) {
    switch (_getch()) {
    case 'w':
      if (currentDirection != DOWN) {
        currentDirection = UP;
      }
      break;
    case 'a':
      if (currentDirection != RIGHT) {
        currentDirection = LEFT;
      }
      break;
    case 's':
      if (currentDirection != UP) {
        currentDirection = DOWN;
      }
      break;
    case 'd':
      if (currentDirection != LEFT) {
        currentDirection = RIGHT;
      }
      break;
    }
  }
}

void logic() {

  for (int tailIndex = currentSnakeLen - 2; tailIndex >= 0; --tailIndex) {
    snakeCoordinateX[tailIndex + 1] = snakeCoordinateX[tailIndex];
    snakeCoordinateY[tailIndex + 1] = snakeCoordinateY[tailIndex];
  }

  switch (currentDirection) {
  case UP:
    --snakeCoordinateY[0];
    break;
  case LEFT:
    --snakeCoordinateX[0];
    break;
  case DOWN:
    ++snakeCoordinateY[0];
    break;
  case RIGHT:
    ++snakeCoordinateX[0];
  }

  if (snakeCoordinateX[0] > (fieldWidth - 2) || 
      snakeCoordinateX[0] < 0 || 
      snakeCoordinateY[0] > (fieldHeight - 2) || 
      snakeCoordinateY[0] < 0) {
    isGameRunning = false;
  }

  for (int snakeLenIndex = 1; snakeLenIndex < currentSnakeLen; ++snakeLenIndex) {
    if (snakeCoordinateX[0] == snakeCoordinateX[snakeLenIndex] &&
        snakeCoordinateY[0] == snakeCoordinateY[snakeLenIndex]) {
      isGameRunning = false;
      continue;
    }
  }

  if (snakeCoordinateX[0] == appleCoordinateX && snakeCoordinateY[0] == appleCoordinateY) {
    ++currentSnakeLen;
    appleCoordinateX = rand() % (fieldWidth - 1);
    appleCoordinateY = rand() % (fieldHeight - 1);
  }
}

int main() {
  double clockedTime = clock();
  double howTimeSlowed = 0.5;

  config();

  while (isGameRunning) {
    if ((clock() - clockedTime) / CLOCKS_PER_SEC >= howTimeSlowed) {
      clockedTime = clock();
      input();
      logic();
      draw();
    }
  }

  return 0;
}
