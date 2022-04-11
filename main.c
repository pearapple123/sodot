#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <panel.h>

void screen_init(void) {
    SCREEN *screen = newterm("xterm-16color", stdout, stdin);
    if (screen == NULL) {
        fputs("Could not initialise term for ncurses", stderr);
        exit(EXIT_FAILURE);
    }

    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

WINDOW *create_newwin(int lines, int cols) {
    WINDOW *win;

    win = newwin(lines, cols, 0 , 0);
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}

int main(void) {
    int x, y;
    int ch;

    screen_init();

    x = 0;
    y = 0;

    move(y, x);

    while((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_LEFT:
                if (x > 0) move(y, --x);
                break;
            case KEY_RIGHT:
                if (x < COLS-1) move(y, ++x);
                break;
            case KEY_UP:
                if (y > 0) move(--y, x);
                break;
            case KEY_DOWN:
                if (y < LINES-1) move(++y, x);
                break;
            case KEY_HOME:
                move(y, (x = 0)); break;
            case KEY_END:
                move(y, (x = COLS-1)); break;
            case KEY_NPAGE:
                move((y = LINES-1), x); break;
            case KEY_PPAGE:
                move((y = 0), x); break;
            // backspace
            case 127:
                if (x > 0) {
                    move(y, --x); delch(); break;
                } else if (x == 0 && y == 0) {
                    break;
                } else {
                    move(--y, (x = COLS-1)); break;
                }
            case KEY_DC:
                delch(); break;
            // Return key
            case 10:
                addch('\n'); move(++y, (x = 0));
                break;
            default:
                addch(ch);
                if (x < COLS-1) {
                    move(y, ++x);
                } else {
                    move(++y, (x = 0));
                }
        }
    }

    endwin();
    return 0;
}
