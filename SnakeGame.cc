//#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;

const int height = 20;
const int width = 60;
bool gameover = false;
int score = -1;
int x_fruit, y_fruit;
int x_snake = width / 2;
int y_snake = height / 2;


enum snake_direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
snake_direction dir;

void GameSetup()
{
    // random number in range 1 to width-5
    x_fruit = rand() % (width - 5) + 1;
    // random number in range 5 to height-1
    y_fruit = rand() % (height - 5) + 1;
    //score + 1
    score++;
}

void MoveSetting()
{
    switch (getchar())
    {
    case 'q':
        dir = STOP;
        break;
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    }
}

void MoveSnake()
{
    switch (dir)
    {
    case STOP:
        gameover = true;
        break;
    case LEFT:
        x_snake--;
        break;
    case RIGHT:
        x_snake++;
        break;
    case UP:
        y_snake--;
        break;
    case DOWN:
        y_snake++;
        break;
    }
}

void GameArea()
{
    system("clear");
    // Ausgabe der oberen Reihe
    for (int x = 0; x < width; x++)
    {
        cout << "-";
    }
    cout << endl;
    // Ausgabe der seitlichen Reihen
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1)
            {
                cout << "|";
            }
            else if (x == x_snake && y == y_snake)
            {
                cout << "O";
            }
            else if (x == x_fruit && y == y_fruit)
            {
                cout << "F";
            }
            else if (x_snake == x_fruit && y_snake == y_fruit)
            {
                GameSetup();
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    // Ausgabe der unteren Reihe
    for (int x = 0; x < width; x++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "Fruit X-Pos: " << x_fruit;
    cout << " | Fruit Y-Pos: " << y_fruit << endl;
    cout << "Your Score is: " << score << endl;
}

int main()
{
    GameSetup();
    while (!gameover)
    {
        GameArea();
        MoveSetting();
        MoveSnake();
        // 50ms wird gewartet
        //Sleep(50);
    }

    return 0;
}
