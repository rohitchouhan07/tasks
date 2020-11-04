#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

/* Function Declaration */

WINDOW *create_newwin(int height, int width, int starty, int startx);

int system (const char * command);

int main(int argc, char *argv[])
{
    WINDOW *task_win;
    int row, col;
    int ch;
    char title[] = "Tasks to accomplish asap!";
    int startx, starty, height, width;
    FILE *fptr;
    char buffer[BUFFER_SIZE];
    int totalRead = 0;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //keypad(task_win, TRUE);
    height = LINES - 5;
    width =  COLS - 2;
    starty = 3;
    startx = 2;
    getmaxyx(stdscr, row, col);
    move(0,(COLS - strlen(title))/2);
    attron(A_BOLD);
    printw("%s", title);
    attroff(A_BOLD);
    mvprintw(row - 1, 0, "Press q to quit ||");
    printw(" Press e to edit");
    refresh();
    task_win = create_newwin(height, width, starty, startx);
    fptr = fopen("tasks.txt", "r");
    while(fgets(buffer, BUFFER_SIZE, fptr) != NULL) 
        {
              /* Total character read count */
              totalRead = strlen(buffer);


              /*
               *          * Trim new line character from last if
               *          exists.
               *                  */
              buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];

               /* Print line read on cosole*/
               waddstr(task_win, buffer);
               wprintw(task_win, "\n");
               wrefresh(task_win); 
        } 
    while(1)
    {
        ch = getch();
        if(ch == 113){
        endwin();
        return 0;
        } 
        
        if(ch == 101)
        {
        system("$EDITOR tasks.txt");
        }
    }       
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
    {
     WINDOW *local_win;
     local_win = newwin(height, width, starty, startx);
   // box(local_win, 0 , 0);      /* 0, 0 gives default characters*/ 
     wrefresh(local_win);        /* Show that box        */
     return local_win;
    }     
