#include <iostream>  // For _kbhit() and _getch()
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For seeding the random number generator


using namespace std;

// Constants
const int width = 20;    // Width of the game area
const int height = 10;   // Height of the game area
int carPos = width / 2;  // Initial position of the car
int score = 0;           // Player's score
bool gameOver = false;   // Game state

// Obstacles
int obstacleX[height];   // Obstacles' horizontal positions
int obstacleY[height];   // Obstacles' vertical positions

// Function to initialize the game
void initializeGame() {
    srand(time(0));
    for (int i = 0; i < height; i++) {
        obstacleX[i] = rand() % width;
        obstacleY[i] = i * -2;  // Obstacles start off-screen
    }
}

// Function to draw the game area
void draw() {
    system("cls");  // Clear the screen

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == height - 1 && x == carPos) {
                cout << "^";  // Car
            } else {
                bool isObstacle = false;
                for (int i = 0; i < height; i++) {
                    if (obstacleY[i] == y && obstacleX[i] == x) {
                        cout << "X";  // Obstacle
                        isObstacle = true;
                        break;
                    }
                }
                if (!isObstacle) {
                    cout << " ";  // Empty space
                }
            }
        }
        cout << endl;
    }

    cout << "\nScore: " << score << endl;
}

// Function to handle user input
void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' || key == 'A') {
            if (carPos > 0) carPos--;  // Move left
        } else if (key == 'd' || key == 'D') {
            if (carPos < width - 1) carPos++;  // Move right
        } else if (key == 'q' || key == 'Q') {
            gameOver = true;  // Quit the game
        }
    }
}

// Function to update the game state
void update() {
    // Move obstacles downward
    for (int i = 0; i < height; i++) {
        obstacleY[i]++;
        if (obstacleY[i] >= height) {
            obstacleY[i] = 0;            // Reset to the top
            obstacleX[i] = rand() % width;  // Randomize horizontal position
            score++;  // Increment score for dodging
        }

        // Check for collision
        if (obstacleY[i] == height - 1 && obstacleX[i] == carPos) {
            gameOver = true;
        }
    }
}

int main() {
    initializeGame();

    while (!gameOver) {
        draw();
        input();
        update();
        Sleep(100);  // Control the game speed
    }

    cout << "\nGame Over! Your final score is: " << score << endl;
    return 0;
}
