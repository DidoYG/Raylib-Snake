#include <iostream>
#include <vector>
#include <random>
#include "raylib.h"
using namespace std;

const int SCREEN_W = 1200;
const int SCREEN_H = 800;

enum Direction{UP, DOWN, LEFT, RIGHT, STOP};

struct Node{
    int xPos;
    int yPos;
    int length;
    Direction dir;

    Node(int xPos, int yPos, int length, Direction dir){
        this->xPos = xPos;
        this->yPos = yPos;
        this->length = length;
        this->dir = dir;
    }
};

Node createNode(int xPos, int yPos, int length, Direction dir=STOP){
    return Node(xPos, yPos, length, dir);
}

void resetSnake(vector<Node>& snake, int nodeLength){
    snake.clear();
    snake.push_back(createNode((SCREEN_W - nodeLength) / 2, (SCREEN_H - nodeLength) / 2, nodeLength));
}

int getRandomInt(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void moveSnake(vector<Node>& snake, string& text, bool& isGameOver){
    int lastXPos = snake[0].xPos;
    int lastYPos = snake[0].yPos;

    if(snake[0].dir == UP){
        snake[0].yPos -= snake[0].length;
    }
    else if(snake[0].dir == DOWN){
        snake[0].yPos += snake[0].length;
    }
    else if(snake[0].dir == LEFT){
        snake[0].xPos -= snake[0].length;
    }
    else if(snake[0].dir == RIGHT){
        snake[0].xPos += snake[0].length;
    }

    if(snake[0].yPos < 10 || snake[0].yPos > SCREEN_H - 20 || snake[0].xPos < 10 || snake[0].xPos > SCREEN_W - 20){
        text = "Game Over";
        isGameOver = true;
    }

    for(int i = 1; i < snake.size(); i++){
        int tmpX = snake[i].xPos;
        int tmpY = snake[i].yPos;

        snake[i].xPos = lastXPos;
        snake[i].yPos = lastYPos;

        lastXPos = tmpX;
        lastYPos = tmpY;

        if(snake[0].xPos == snake[i].xPos && snake[0].yPos == snake[i].yPos){
            text = "Game Over";
            isGameOver = true;
        }
    }

    if(snake[snake.size() - 1].yPos < lastYPos){
        snake[snake.size() - 1].dir = UP;
    }
    else if(snake[snake.size() - 1].yPos > lastYPos){
        snake[snake.size() - 1].dir = DOWN;
    }
    else if(snake[snake.size() - 1].xPos < lastXPos){
        snake[snake.size() - 1].dir = LEFT;
    }
    else if(snake[snake.size() - 1].xPos > lastXPos){
        snake[snake.size() - 1].dir = RIGHT;
    }
}

void growSnake(vector<Node>& snake){
    int lastNode = snake.size() - 1;

    if(snake[lastNode].dir == UP){
        snake.push_back(createNode(snake[lastNode].xPos, snake[lastNode].yPos + snake[lastNode].length, snake[lastNode].length, snake[lastNode].dir));
    }
    else if(snake[lastNode].dir == DOWN){
        snake.push_back(createNode(snake[lastNode].xPos, snake[lastNode].yPos - snake[lastNode].length, snake[lastNode].length, snake[lastNode].dir));
    }
    else if(snake[lastNode].dir == LEFT){
        snake.push_back(createNode(snake[lastNode].xPos + snake[lastNode].length, snake[lastNode].yPos, snake[lastNode].length, snake[lastNode].dir));
    }
    else if(snake[lastNode].dir == RIGHT){
        snake.push_back(createNode(snake[lastNode].xPos - snake[lastNode].length, snake[lastNode].yPos, snake[lastNode].length, snake[lastNode].dir));
    }
}

Node spawnFruit(const vector<Node>& snake, int nodeLength){
    bool isValidSpawn = false;
    int xPos, yPos;

    while(!isValidSpawn){
        xPos = (getRandomInt(1, 59) * nodeLength) - (nodeLength / 2);
        yPos = (getRandomInt(1, 39) * nodeLength) - (nodeLength / 2);
    
        isValidSpawn = true;
    
        for(int i = 0; i < snake.size(); i++){
            if(snake[i].xPos == xPos && snake[i].yPos == yPos){
                isValidSpawn = false;
                break;
            }
        }
    }
    
    return createNode(xPos, yPos, nodeLength);
}

void draw(const vector<Node>& snake, const Node& fruit, const string& text){
    BeginDrawing();
    ClearBackground(Color{194, 178, 128});

    DrawRectangle(0, 0, SCREEN_W, 10, Color{0, 105, 148, 255});
    DrawRectangle(0, SCREEN_H - 10, SCREEN_W, 10, Color{0, 105, 148, 255});
    DrawRectangle(0, 0, 10, SCREEN_H, Color{0, 105, 148, 255});
    DrawRectangle(SCREEN_W - 10, 0, 10, SCREEN_H, Color{0, 105, 148, 255});
    DrawRectangle(fruit.xPos, fruit.yPos, fruit.length, fruit.length, Color{204, 0, 102, 255});
    
    for(int i = 0; i < snake.size(); i++){
        DrawRectangle(snake[i].xPos, snake[i].yPos, snake[i].length, snake[i].length, DARKGREEN);
    }

    if(text != ""){
        int fontText = 50;
        int widthText = MeasureText(text.c_str(), fontText);
        int xText = (SCREEN_W - widthText) / 2;
        int yText = (SCREEN_H - fontText) / 2;

        DrawText(text.c_str(), xText, yText, fontText, DARKGRAY);
    }

    EndDrawing();
}

int main(){
    InitWindow(SCREEN_W, SCREEN_H, "Snake");
    SetTargetFPS(60);

    int nodeLength = 20;
    int timer = 0;

    string text = "";

    bool isPaused = false;
    bool isGameOver = false;

    vector<Node> snake;

    Node fruit = spawnFruit(snake, nodeLength);

    snake.push_back(createNode((SCREEN_W - nodeLength) / 2, (SCREEN_H - nodeLength) / 2, nodeLength));

    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_UP) && snake[0].dir != DOWN && !isGameOver){
            snake[0].dir = UP;
            
            if(isPaused){
                text = "";
                isPaused = false;
            }
        }
        
        if(IsKeyPressed(KEY_DOWN)  && snake[0].dir != UP && !isGameOver){
            snake[0].dir = DOWN;
            
            if(isPaused){
                text = "";
                isPaused = false;
            }
        }
        
        if(IsKeyPressed(KEY_LEFT) && snake[0].dir != RIGHT && !isGameOver){
            snake[0].dir = LEFT;

            if(isPaused){
                text = "";
                isPaused = false;
            }
        }
        
        if(IsKeyPressed(KEY_RIGHT) && snake[0].dir != LEFT && !isGameOver){
            snake[0].dir = RIGHT;
            
            if(isPaused){
                text = "";
                isPaused = false;
            }
        }
        
        if(IsKeyPressed(KEY_P)){
            text = "Paused";
            isPaused = true;
        }

        if((IsKeyPressed(KEY_SPACE) && isPaused) || (IsKeyPressed(KEY_SPACE) && isGameOver)){
            timer = 0;
            text = "";
            isPaused = false;
            isGameOver = false;
            resetSnake(snake, nodeLength);
        }

        if(timer >= GetFPS() && text == ""){
            timer = 0;
            moveSnake(snake, text, isGameOver);
        }
        else{
            timer += 10;
        }

        if(snake[0].xPos == fruit.xPos && snake[0].yPos == fruit.yPos){
            growSnake(snake);
            fruit = spawnFruit(snake, nodeLength);
        }

        draw(snake, fruit, text);    
    }
    
    CloseWindow();
    return 0;
}
