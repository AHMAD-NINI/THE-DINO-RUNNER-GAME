#include <iostream>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 40;
const int height = 10;
int dinoY;
int dinoVelocity;
const int gravity = 1;
int obstacleX;
int score;
int obstacleSpeed = 1;


void clearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void setup() {
    gameOver = false;
    dinoY = height - 2;
    dinoVelocity = 0;
    obstacleX = width - 1;
    score = 0;
}

void draw() {
    clearScreen(); 

    
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0) cout << "#"; 

            if (x == 5 && y == dinoY)
                cout << "D"; 
            else if (x == obstacleX && y == height - 2)
                cout << "|"; 
            else
                cout << " "; 

            if (x == width - 1) cout << "#"; // Right border
        }
        cout << endl;
    }

    
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    
    cout << "Score: " << score << endl;
    cout << "Press SPACE to jump\n";
}

void input() {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        if (dinoY == height - 2)
            dinoVelocity = -2; 
    }
}

void logic() {
    dinoY += dinoVelocity;
    if (dinoY < height - 2)
        dinoVelocity += gravity; 
    else {
        dinoY = height - 2;      
        dinoVelocity = 0;
    }

    obstacleX -= obstacleSpeed;
    if (obstacleX < 0) {
        obstacleX = width - 1;
        score++;
        
        if (score % 5 == 0) obstacleSpeed++;
    }


    if (obstacleX == 5 && dinoY == height - 2)
        gameOver = true;
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(20); 
    }

    clearScreen();
    cout << "GAME OVER!\n";
    cout << "FINAL SCORE: " << score << endl;

    return 0;
}
