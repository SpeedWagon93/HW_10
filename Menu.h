#pragma once


#include <iostream>
#include <string>
#include <ncurses.h>

using namespace std;



	int ChooseMenu(int n, string* variants)
	{
    //setlocale(LC_ALL, "ru_RU.UTF8");
    initscr(); 
    clear(); 
    curs_set(0);
    noecho(); 
    cbreak(); 
    keypad(stdscr, TRUE); 
    start_color(); 
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK); 

    int active_menu = 0;

    while (true) 
    {
        //clear();

        int max_y; 
		int max_x;
        getmaxyx(stdscr, max_y, max_x); 

        int menu_start_x = (max_x - variants[0].length()) / 2; 

        for (int i = 0; i < n; i++) 
        {
            if (i == active_menu) 
            {
                attron(COLOR_PAIR(1) | A_BOLD);
            }
            mvprintw(max_y / 2 + i, menu_start_x, variants[i].c_str()); 
            attroff(COLOR_PAIR(1)); 
            attron(COLOR_PAIR(2) | A_BOLD);
        }

        refresh();

        int ch = getch();
        switch (ch) {
           case 27: // ESC
                clear();
                endwin(); 
                exit;
                return 0; 
            case KEY_UP: // Стрелка вверх
                if (active_menu > 0) 
                {
                    active_menu--;
                }else if (active_menu == 0)
                {
                    active_menu = n - 1;
                }
                break;
            case KEY_DOWN: // Стрелка вниз
                if (active_menu < n - 1) 
                {
                    active_menu++;
                }else if (active_menu == n-1)
                {
                    active_menu = 0;
                }
                break;
			case '\n': //enter
            clear();
			refresh();
			return active_menu;
        }
    }
}