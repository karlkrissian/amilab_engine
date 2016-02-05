#include <ncurses.h>

int tty_break()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  return 0;
}


int tty_fix()
{
  endwin();
  return 0;
}
