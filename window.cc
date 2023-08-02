#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height}
{

  d = XOpenDisplay(NULL);
  if (d == NULL)
  {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  window = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                               BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, window, ExposureMask | KeyPressMask);
  XMapRaised(d, window);

  Pixmap pix = XCreatePixmap(d, window, width,
                             height, DefaultDepth(d, DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0, (XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  cmap = DefaultColormap(d, DefaultScreen(d));
  for (int i = 0; i < static_cast<int>(colorValues.size()); i++)
  {
    XParseColor(d, cmap, colorValues[static_cast<Color>(i)].c_str(), &xcolour);
    XAllocColor(d, cmap, &xcolour);
    colours.push_back(xcolour.pixel);
  }

  XSetForeground(d, gc, colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, window, &hints);

  XSynchronize(d, True);

  backBuffer = XCreatePixmap(d, window, width, height, DefaultDepth(d, DefaultScreen(d)));
  backBufferGC = XCreateGC(d, backBuffer, 0, (XGCValues *)0);
  // usleep(1000);
}

Xwindow::~Xwindow()
{
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour)
{
  XSetForeground(d, backBufferGC, colours[colour]);
  XFillRectangle(d, backBuffer, backBufferGC, x, y, width, height);
  XSetForeground(d, backBufferGC, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg)
{
  XSetForeground(d, backBufferGC, colours[White]);
  XDrawString(d, backBuffer, backBufferGC, x, y, msg.c_str(), msg.length());
}

void Xwindow::drawGrid(int startX, int startY, int squareWidth)
{
  // draw grid
  int border = squareWidth;
  // x, y, width, height, color
  fillRectangle(startX, startY + 18 * squareWidth, 13 * squareWidth, border, 2);
  fillRectangle(startX, startY, border, squareWidth * 18, 2);
  fillRectangle(startX + 12 * squareWidth, startY, border, squareWidth * 18, 2);

  fillRectangle(startX + squareWidth, startY, 11 * squareWidth, squareWidth * 18, 1);

  fillRectangle(startX + 13 * squareWidth, startY + 4 * squareWidth, 4 * squareWidth, squareWidth, Grey);
  fillRectangle(startX + 17 * squareWidth, startY, squareWidth, 5 * squareWidth, Grey);
}

int GetColor(char type)
{
  int color = 0;
  switch (type)
  {
  case 'I':
    color = 4;
    break;
  case 'J':
    color = 5;
    break;
  case 'L':
    color = 3;
    break;
  case 'O':
    color = 7;
    break;
  case 'S':
    color = 8;
    break;
  case 'T':
    color = 6;
    break;
  case 'Z':
    color = 9;
    break;
  case '*':
    color = 2;
    break;
  default:
    break;
  }
  return color;
}

void Xwindow::drawBoard(Board &board, int startX, int startY, int squareWidth)
{
  drawGrid(startX, startY, squareWidth);
  for (int j = 0; j < 18; j++)
  {
    for (int i = 0; i < 11; i++)
    {
      if (board.GetGrid()[j][i].first != ' ')
      {
        int color = GetColor(board.GetGrid()[j][i].first);
        fillRectangle(startX + (i + 1) * squareWidth, startY + j * squareWidth, squareWidth, squareWidth, color);
      }
    }
  }
  Block &b = board.GetCurrBlock();
  const vector<pair<int, int>> &coords = b.getCoords();
  for (int i = 0; i < static_cast<int>(coords.size()); i++)
  {
    int color = GetColor(b.GetType());
    fillRectangle(startX + (coords[i].second + 1) * squareWidth, startY + coords[i].first * squareWidth, squareWidth, squareWidth, color);
  }

  fillRectangle(startX + 13 * squareWidth, startY + 0 * squareWidth, 4 * squareWidth, 4 * squareWidth, Black);

  // draw next block
  const Block &next = board.GetNextBlock();
  const vector<pair<int, int>> &newCoords = next.getCoords();
  const pair<int, int> &left = next.getLeft();
  const int &color = GetColor(next.GetType());
  int newX = 13;
  int newY = 3;
  for (int i = 0; i < static_cast<int>(newCoords.size()); i++)
  {
    fillRectangle(startX + (newCoords[i].second - left.second + newX) * squareWidth, startY + (newCoords[i].first - left.first + newY) * squareWidth, squareWidth, squareWidth, color);
  }
}

void Xwindow::drawScreen(Board &b1, Board &b2)
{
  int blockWidth = height / 25;
  fillRectangle(0, 0, width, blockWidth + 60, Grey);

  drawString(width / 2 - 1.5 * blockWidth, blockWidth, "High: " + to_string(b1.GetHighScore()));
  drawString(blockWidth, blockWidth + 20, "Level: " + to_string(b1.GetLevel()));
  drawString(blockWidth, blockWidth + 40, "Score: " + to_string(b1.GetScore()));
  drawString(13 * blockWidth, blockWidth + 40, "Next Block");

  drawString(width / 2 + blockWidth, blockWidth + 20, "Level: " + to_string(b2.GetLevel()));
  drawString(width / 2 + blockWidth, blockWidth + 40, "Score: " + to_string(b2.GetScore()));
  drawString(width / 2 + 13 * blockWidth, blockWidth + 40, "Next Block");

  drawBoard(b1, 0, blockWidth + 60, blockWidth);
  drawBoard(b2, width / 2, blockWidth + 60, blockWidth);
  //  Copy the back buffer to the window (swap the buffers)
  XCopyArea(d, backBuffer, window, backBufferGC, 0, 0, width, height, 0, 0);
  // Flush the output to make sure the update is visible
  XFlush(d);
}

