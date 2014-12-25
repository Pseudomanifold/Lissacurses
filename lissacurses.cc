/*
 * Lissacurses --- Lissajous curves on the console
 *
 * Copyright (c) 2014 Bastian Rieck
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <ncurses.h>
#include <unistd.h>

int num_colours = 0;
int rows	= 0;
int cols	= 0;

/*!
 *
 * Draws the Lissajous curve described by the equation
 *
 *	x = sin(a*t+delta)
 *	y = sin(b*t+epsilon)
 *
 * on stdscr. The curve will \e not be cut off because the function uses the
 * rows and cols variables to determine where to draw. One period of the
 * x-values will be drawn to the screen.
 *
 */

void draw_lissajous_curve( double a, double delta,
                           double b)
{
  for(double t = 0.0; t <= 2*M_PI; t += (2*M_PI/(rows*cols)))
  {
    double x = std::sin(a*t+delta);
    double y = std::sin(b*t);

    unsigned int x_coord = static_cast<unsigned int>(cols*static_cast<double>((x+1.0)/2.0));
    unsigned int y_coord = static_cast<unsigned int>((rows-1)*static_cast<double>((y+1.0)/2.0))+1;

    int colour = static_cast<int>(rand() % num_colours);
    attron(COLOR_PAIR(colour));
    mvprintw(y_coord, x_coord, "*");
    attroff(COLOR_PAIR(colour));
  }

  refresh();
}

int main(int, char**)
{
  std::srand( std::time( NULL ) );

  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);

  if(has_colors() == FALSE)
    return -1;

  // Init colour pairs

  start_color();
  num_colours = 6; // change if you want to use more combinations

  init_pair(1, COLOR_RED,	COLOR_BLACK);
  init_pair(2, COLOR_GREEN,	COLOR_BLACK);
  init_pair(3, COLOR_YELLOW,	COLOR_BLACK);
  init_pair(4, COLOR_BLUE,	COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA,	COLOR_BLACK);
  init_pair(5, COLOR_CYAN,	COLOR_BLACK);
  init_pair(6, COLOR_WHITE,	COLOR_BLACK);

  // Set number of rows & colums

  getmaxyx(stdscr, rows, cols);
  if(rows*cols <= 0)
    return -1;

  double a		= 2.0;
  double b		= 3.0;
  double delta		= 0.0;
  double a_prev		= -1.0;
  double b_prev		= -1.0;
  double delta_prev	= -1.0;

  int c;
  while(tolower(c = getch()) != 'q')
  {
    switch(c)
    {
      case 'A':
        a += 1.0;
        break;
      case 'a':
        a -= 1.0;
        break;
      case 'B':
        b += 1.0;
        break;
      case 'b':
        b -= 1.0;
        break;
      case '+':
        delta += 0.025;
        break;
      case '-':
        delta -= 0.025;
        break;

      // no input waiting--sleep
      case ERR:
        usleep(100);
        break;
      default:
        break;
    }

    if(	a != a_prev || delta != delta_prev ||
        b != b_prev)
    {
      delta = std::fmod(delta, 2*M_PI);

      a_prev		= a;
      b_prev		= b;
      delta_prev	= delta;

      clear();
      mvprintw(0, 0, "a = %f, b = %f, delta = %f", a, b, delta);
      draw_lissajous_curve(a, delta, b);
    }
  }

  curs_set(1);
  endwin();

  return 0;
}
