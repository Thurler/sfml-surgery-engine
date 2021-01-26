# SFML Surgery Engine

A game engine written in C++ for a surgery simulation game.
Uses SFML as a graphics library.

### Build Instructions

Install SFML 2.5.1 and its dependencies, and a C++ compiler. Use the command below if you're using g++:

```g++ *.cpp objects/*.cpp states/*.cpp states/tools/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -O2 -o surgery.exe```
