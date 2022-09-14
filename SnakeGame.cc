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

void GameLogic()
{
    system("clear");
    // Ausgabe der oberen Reihe
    for (int x = 0; x < width; x++)
        cout << "#";
    cout << endl;
    // Ausgabe der seitlichen Reihen
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1)
                cout << "#";
            else if (x == x_snake && y == y_snake)
                cout << "O";
            else if (x == x_fruit && y == y_fruit)
                cout << "F";
            else if (x_snake == x_fruit && y_snake == y_fruit)
                GameSetup();
            // Wallrunning
            else if (x_snake == 1)
                x_snake = width - 2;
            else if (x_snake == width - 1)
                x_snake = 2;
            else if (y_snake == -1)
                y_snake = height - 1;
            else if (y_snake == height)
                y_snake = 0;
            // Wallrunning end
            else
                cout << " ";
        }
        cout << endl;
    }
    // Ausgabe der unteren Reihe
    for (int x = 0; x < width; x++)
        cout << "#";
    cout << endl;
    cout << "<< SnakeGame by Kevin Thalmann >>" << endl;
    cout << "---------------------------------" << endl;
    cout << "    Press: w + Enter for UP      " << endl;
    cout << "    Press: s + Enter for DOWN    " << endl;
    cout << "    Press: a + Enter for LEFT    " << endl;
    cout << "    Press: d + Enter for RIGHT   " << endl;
    cout << "    Press: q + Enter for QUIT    " << endl;
    cout << "---------------------------------" << endl;
    cout << "Snake X-Pos: " << x_snake;
    cout << " | Snake Y-Pos: " << y_snake << endl;
    cout << "Your Score is: " << score << endl;
}

int main()
{
    GameSetup();
    while (!gameover)
    {
        GameLogic();
        MoveSetting();
        MoveSnake();
        // 50ms wird gewartet
        //Sleep(50);
    }

    return 0;
}
