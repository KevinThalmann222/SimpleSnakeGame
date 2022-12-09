//#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDRED "\033[1m\033[31m"

using namespace std;

const int height = 20;
const int width = 60;
bool gameover = false;
int score = -1;
int x_fruit, y_fruit;
int x_snake = width / 2;
int y_snake = height / 2;
int snake_tail_x[100];
int snake_tail_y[100];
int snake_tail_len;
char key_press = 'w';

enum snake_direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

snake_direction snake_dir;

void DropFruit()
{
    // random number in range 1 to width-5
    x_fruit = rand() % (width - 5) + 1;
    // random number in range 5 to height-1
    y_fruit = rand() % (height - 5) + 1;
    // score + 1
    score++;
    // snake tail + 1
    snake_tail_len++;
}

void KeyPress()
{
    // Prüft ob eine Taste gedrückt ist.
    // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    if (GetAsyncKeyState(0x57))
        key_press = 'w';
    else if (GetAsyncKeyState(0x41))
        key_press = 'a';
    else if (GetAsyncKeyState(0x53))
        key_press = 's';
    else if (GetAsyncKeyState(0x44))
        key_press = 'd';
    else if (GetAsyncKeyState(0x51))
        key_press = 'q';
}

void MoveSetting()
{
    switch (key_press)
    {
    case 'a':
        snake_dir = LEFT;
        break;
    case 'd':
        snake_dir = RIGHT;
        break;
    case 'w':
        snake_dir = UP;
        break;
    case 's':
        snake_dir = DOWN;
        break;
    case 'q':
        snake_dir = STOP;
        break;
    }
}

void MoveSnake()
{
    switch (snake_dir)
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

void SnakeLength()
{
    int prev_x = snake_tail_x[0];
    int prev_y = snake_tail_y[0];
    int prev_x2, prev_y2;
    // snake tail 0 is on ...
    // the same pos as the snakehead
    snake_tail_x[0] = x_snake;
    snake_tail_y[0] = y_snake;
    for (int i = 1; i < snake_tail_len; i++)
    {
        prev_x2 = snake_tail_x[i];
        prev_y2 = snake_tail_y[i];
        snake_tail_x[i] = prev_x;
        snake_tail_y[i] = prev_y;
        prev_x = prev_x2;
        prev_y = prev_y2;
    }
}

void SnakeCollision()
{
    for (int i = 0; i < snake_tail_len; i++)
    {
        if (x_snake == snake_tail_x[i] && y_snake == snake_tail_y[i])
            gameover = true;
    }
}

void GameLogic()
{
    system("clear");
    SnakeLength();
    // Ausgabe der oberen Reihe
    for (int x = 0; x < width; x++)
    {
        cout << BOLDBLUE << "#";
    }
    cout << endl;
    // Ausgabe der seitlichen Reihen
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1)
                cout << BOLDBLUE << "#" << RESET;
            else if (x == x_snake && y == y_snake)
                cout << BOLDRED << "0" << RESET;
            else if (x == x_fruit && y == y_fruit)
                cout << BOLDGREEN << "F" << RESET;
            else if (x_snake == x_fruit && y_snake == y_fruit)
                DropFruit();
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
            {
                bool print_tail = false;
                for (int k = 0; k < snake_tail_len; k++)
                {

                    if (snake_tail_x[k] == x && snake_tail_y[k] == y)
                    {
                        cout << BOLDRED << "o" << RESET;
                        print_tail = true;
                    }
                }
                if (!print_tail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    // Ausgabe der unteren Reihe
    for (int x = 0; x < width; x++)
        cout << BOLDBLUE << "#" << RESET;
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
    DropFruit();
    while (!gameover)
    {
        Sleep(1);
        GameLogic();
        MoveSetting();
        KeyPress();
        MoveSnake();
        SnakeCollision();
    }
    system("clear");
    cout << "------------------------" << endl;
    cout << "   <<< GAMEOVER >>>     " << endl;
    cout << "     Highscore: " << score << endl;
    cout << "------------------------" << endl;
    return 0;
}
