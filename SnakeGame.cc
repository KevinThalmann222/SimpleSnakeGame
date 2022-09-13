#include <iostream>
using namespace std;

const int height = 30;
const int width = 60;
bool gameover = false;

void GameArea()
{
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
}

int main()
{
    GameArea();
    return 0;
}
