#include <stdio.h>
#include <sgtty.h>

static struct sgttyb savemodes;
static int havemodes = 0;

int tty_break()
{
  struct sgttyb modmodes;
  if(ioctl(fileno(stdin), TIOCGETP, &savemodes) < 0)
    return -1;
  havemodes = 1;
  modmodes = savemodes;
  modmodes.sg_flags |= CBREAK;
  return ioctl(fileno(stdin), TIOCSETN, &modmodes);
}

int tty_getchar()
{
  return getchar();
}

int tty_fix()
{
  if(!havemodes)
    return 0;
  return ioctl(fileno(stdin), TIOCSETN, &savemodes);
}
