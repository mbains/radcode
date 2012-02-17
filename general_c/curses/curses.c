#include <time.h>
#include <curses.h>

int current_getch;
int doloop = 1;
static WINDOW *mainwnd;
static WINDOW *screen;
WINDOW *my_win;

int now_sec, now_min, now_hour, now_day, now_wday, now_month, now_year;
time_t now;
struct tm *now_tm;
	
void screen_init(void) {
   mainwnd = initscr();
   noecho();
   cbreak();
   nodelay(mainwnd, TRUE);
   refresh(); // 1)
   wrefresh(mainwnd);
   screen = newwin(13, 27, 1, 1);
   box(screen, ACS_VLINE, ACS_HLINE);
}

static void update_display(void) {
   curs_set(0);
   mvwprintw(screen,1,1,"-------- HEADER --------");
   mvwprintw(screen,3,6,"TIME: %d:%d:%d", now_hour, now_min, now_sec);
   mvwprintw(screen,5,6,"DATE: %d-%d-%d", now_day, now_month, now_year);
   mvwprintw(screen,7,6,"PRESS q TO END");
   mvwprintw(screen,10,1,"-------- FOOTER --------");
   wrefresh(screen);
   refresh();
}

void screen_end(void) {
   endwin();
}

void maketime(void) {
	// Get the current date/time
	now = time (NULL);
	now_tm = localtime (&now);
   now_sec = now_tm->tm_sec;
	now_min = now_tm->tm_min;
	now_hour = now_tm->tm_hour;
	now_day = now_tm->tm_mday;
	now_wday = now_tm->tm_wday;
	now_month = now_tm->tm_mon + 1;
	now_year = now_tm->tm_year + 1900;
}

int main(void) {
   screen_init();
   while (doloop) {
      current_getch = getch();
      if (current_getch == 113) {
         doloop = 0;
      }
      maketime();
      update_display();
      sleep(1);
   }
   screen_end();
   printf("TEST ENDS\n");
   return 0;
}

