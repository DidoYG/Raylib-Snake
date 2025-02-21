# Raylib-Snake
Simple Snake game made with C++ Raylib

This is a simple Snake game made with C++ using the graphics library Raylib. The game has the basics that everybody knows and love.

You start as a small one segment-long snake. One by one, on the screen, fruits start appearing. If a snake eats a fruit it grows with one segment in size. Everything sounds good, right. Yep, the only thing to remember is not to get too close to the edge or you may lose the game. Also try not to bite our tail, because it may not end well.

Now you know everything. Why not just hop on and play some Snake.


Controls:

Move with arrow keys. Just press a key and the snake will start going in that direction until you change it.

Press 'p' for pause. When paused press an arrow key to continue playing, or press 'Space' to restart.

If 'Game Over' press 'Space' to restart.


Requirements:

To play the game you need to have Raylib on your system. You can find out more by googling Raylib GitHub. 
Now when you have Raylib, run this command in order to compile the main.cpp file: g++ main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

And that is it. Now execute the output file called 'main' and have fun!
