see: http://c-faq.com/osdep/cbreak.html
question 19.1

Q: How can I read a single character from the keyboard without waiting for the RETURN key? How can I stop characters from being echoed on the screen as they're typed?

A: Alas, there is no standard or portable way to do these things in C. Concepts such as screens and keyboards are not even mentioned in the Standard, which deals only with simple I/O ``streams'' of characters.

Input to a computer program typically passes through several stages. At the lowest level, device-dependent routines within the operating system handle the details of interfacing with particular devices such as keyboards, serial lines, disk drives, etc. Above that, modern operating systems tend to have a device-independent I/O layer, unifying access to any file or device. Finally, a C program is usually insulated from the operating system's I/O facilities by the portable functions of the stdio library.

At some level, interactive keyboard input is usually collected and presented to the requesting program a line at a time. This gives the operating system a chance to support input line editing (backspace/delete/rubout, etc.) in a consistent way, without requiring that it be built into every program. Only when the user is satisfied and presses the RETURN key (or equivalent) is the line made available to the calling program. Even if the calling program appears to be reading input a character at a time (with getchar or the like), the first call blocks until the user has typed an entire line, at which point potentially many characters become available and many character requests (e.g. getchar calls) are satisfied in quick succession.

When a program wants to read each character immediately as it arrives, its course of action will depend on where in the input stream the line collection is happening and how it can be disabled. Under some systems (e.g. MS-DOS, VMS in some modes), a program can use a different or modified set of OS-level input calls to bypass line-at-a-time input processing. Under other systems (e.g. Unix, VMS in other modes), the part of the operating system responsible for serial input (often called the ``terminal driver'') must be placed in a mode which turns off line-at-a-time processing, after which all calls to the usual input routines (e.g. read, getchar, etc.) will return characters immediately. Finally, a few systems (particularly older, batch-oriented mainframes) perform input processing in peripheral processors which cannot be told to do anything other than line-at-a-time input.

Therefore, when you need to do character-at-a-time input (or disable keyboard echo, which is an analogous problem), you will have to use a technique specific to the system you're using, assuming it provides one. Since comp.lang.c is oriented towards those topics that the C language has defined support for, you will usually get better answers to other questions by referring to a system-specific newsgroup such as comp.unix.questions or comp.os.msdos.programmer, and to the FAQ lists for these groups. Note that the answers may differ even across variants of otherwise similar systems (e.g. across different variants of Unix); bear in mind when answering system-specific questions that the answer that applies to your system may not apply to everyone else's.

However, since these questions are frequently asked here, here are brief answers for some common situations.

Depending on which operating system you're using and what libraries you have available, you may be able to use one (or more!) of the following techniques:

If you can use the ``curses'' library, you can call cbreak [footnote] (and perhaps noecho), after which calls to getch will return characters immediately.
If all you're trying to do is read a short password without echo, you may be able to use a function called getpass, if it's available. (Another possibility for hiding typed passwords is to select black characters on a black background.)
Under ``classic'' versions of Unix, use ioctl and the TIOCGETP and TIOCSETP (or TIOCSETN) requests on file descriptor 0 to manipulate the sgttyb structure, defined in <sgtty.h> and documented in tty(4). In the sg_flags field, set the CBREAK (or RAW) bit, and perhaps clear the ECHO bit.
Under System V Unix, use ioctl and the TCGETAW and TCSETAW requests on file descriptor 0 to manipulate the termio structure, defined in <termio.h>. In the c_lflag field, clear the ICANON (and perhaps ECHO) bits. Also, set c_cc[VMIN] to 1 and c_cc[VTIME] to 0.
Under any operating system (Unix or otherwise) offering POSIX compatibility, use the tcgetattr and tcsetattr calls on file descriptor 0 to manipulate the termios structure, defined in <termios.h>. In the c_lflag field, clear the ICANON (and perhaps ECHO) bits. Also, set c_cc[VMIN] to 1 and c_cc[VTIME] to 0.
In a pinch, under Unix, use system (see question 19.27) to invoke the stty command to set terminal driver modes (as in the preceding three items).
Under MS-DOS, use getch or getche, or the corresponding BIOS interrupts.
Under VMS, try the Screen Management (SMG$) routines, or curses, or issue low-level $QIO's with the IO$_READVBLK function code (and perhaps IO$M_NOECHO, and others) to ask for one character at a time. (It's also possible to set character-at-a-time or ``pass through'' modes in the VMS terminal driver.)
Under other operating systems, you're on your own.
(As an aside, note that simply using setbuf or setvbuf to set stdin to unbuffered will not generally serve to allow character-at-a-time input.)

If you change terminal modes, save a copy the initial state and be sure to restore it no matter how your program terminates.

If you're trying to write a portable program, a good approach is to define your own suite of three functions to (1) set the terminal driver or input system into character-at-a-time mode (if necessary), (2) get characters, and (3) return the terminal driver to its initial state when the program is finished. (Ideally, such a set of functions might be part of the C Standard, some day.)

As an example, here is a tiny test program which prints the decimal values of the next ten characters as they are typed, without waiting for RETURN. It is written in terms of three functions, as described, and is followed by implementations of the three functions for curses, classic Unix, System V Unix, and MS-DOS. (The on-line archives associated with this list contain a more complete set of functions.)

#include <stdio.h>

main()
{
  int i;
  if(tty_break() != 0)
    return 1;
  for(i = 0; i < 10; i++)
    printf(" = %d\n", tty_getchar());
  tty_fix();
  return 0;
}
This implementation of the three functions is for curses:

#include <curses.h>

int tty_break()
{
  initscr();
  cbreak();
  return 0;
}

int tty_getchar()
{
  return getch();
}

int tty_fix()
{
  endwin();
  return 0;
}
Here is the code for ``classic'' (V7, BSD) Unix:

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
The code for System V Unix is similar:

#include <stdio.h>
#include <termio.h>

static struct termio savemodes;
static int havemodes = 0;

int tty_break()
{
  struct termio modmodes;
  if(ioctl(fileno(stdin), TCGETA, &savemodes) < 0)
    return -1;
  havemodes = 1;
  modmodes = savemodes;
  modmodes.c_lflag &= ~ICANON;
  modmodes.c_cc[VMIN] = 1;
  modmodes.c_cc[VTIME] = 0;
  return ioctl(fileno(stdin), TCSETAW, &modmodes);
}

int tty_getchar()
{
  return getchar();
}

int tty_fix()
{
  if(!havemodes)
    return 0;
  return ioctl(fileno(stdin), TCSETAW, &savemodes);
}
Finally, here is an implementation for MS-DOS:

int tty_break() { return 0; }

int tty_getchar()
{
  return getche();
}

int tty_fix() { return 0; }
Turning off echo is left as an exercise for the reader.

For detailed information on terminal (keyboard and screen) I/O programming, see an FAQ list, book, or documentation set specific to your operating system. (Note that there can be many more details to take care of, e.g. special characters to disable as well as more mode bits to toggle, than were mentioned above.)

See also question 19.2.

Additional links: more solutions

References: PCS Sec. 10 pp. 128-9, Sec. 10.1 pp. 130-1 
POSIX Sec. 7 