#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "board.h"

using namespace std;

class Xwindow
{
  Display *d;
  Window window;
  int s;
  GC gc;
  vector<unsigned long> colours;
  int width;
  int height;

  Pixmap backBuffer;
  GC backBufferGC;

public:
  Xwindow(int width = 500, int height = 500); // Constructor; displays the window.
  ~Xwindow();                                 // Destructor; destroys the window.
  Xwindow(const Xwindow &) = delete;
  Xwindow &operator=(const Xwindow &) = delete;

  enum Color
  {
    White = 0,
    Black,
    Grey,
    Orange,
    LightBlue,
    Blue,
    Purple,
    Yellow,
    Green,
    Red,
  }; // Available colours.

  unordered_map<Color, std::string> colorValues = {
      {White, "#FFFFFF"},
      {Black, "#000000"},
      {Grey, "#808080"},
      {Orange, "#FFA500"},
      {LightBlue, "#ADD8E6"},
      {Blue, "#0000FF"},
      {Purple, "#800080"},
      {Yellow, "#FFFF00"},
      {Green, "#008000"},
      {Red, "#FF0000"}};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour = Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawBoard(Board &board, int startX, int startY, int squareWidth);

  void drawGrid(int startX, int startY, int squareWidth);

  void drawScreen(Board &b1, Board &b2);
};

#endif
