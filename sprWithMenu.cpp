#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

using namespace std;

//setlocale(0, "RUS");

struct Person
{
    char Name[20];
    long Tel;
};

void Write(char *filename)
{
    char* Name = new char[20];
    long tel;
    attron(COLOR_PAIR(3));
    printw("Enter the name: ");
    attroff(COLOR_PAIR(3));
    curs_set(1);
    echo();
    attron(COLOR_PAIR(2));
    scanw("%s", Name);
    attroff(COLOR_PAIR(2));
    //scanw("%*[^\n]");
    attron(COLOR_PAIR(3));
    printw("Enter phone number: ");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(2));
    scanw("%ld", &tel);
    attroff(COLOR_PAIR(2));


    int countOfReadUsers = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person usersRead[countOfReadUsers];
    size_t read = fread(usersRead, sizeof(usersRead[0]), countOfReadUsers, fp);
    countOfReadUsers = read;
    fclose(fp);
    struct Person* usersWrite = new struct Person[countOfReadUsers +1];
    if(read > 0)
    {
        for(int i = 0; i < countOfReadUsers; i++)
        {
            usersWrite[i] = usersRead[i];
        }
        strcpy(usersWrite[countOfReadUsers].Name, Name);
        usersWrite[countOfReadUsers].Tel = tel;    
        fp = fopen(filename, "w");
        size_t write = fwrite(usersWrite, sizeof(usersWrite[0]), countOfReadUsers+1, fp);
        countOfReadUsers = write;
        //printf("%d\n", countOfReadUsers);
        fclose(fp);
    }else
    {
        strcpy(usersWrite[countOfReadUsers].Name, Name);
        usersWrite[countOfReadUsers].Tel = tel;
        fp = fopen(filename, "w");

        size_t write = fwrite(usersWrite, sizeof(usersWrite[0]), countOfReadUsers+1, fp);
        countOfReadUsers = write;
        //printf("%d\n", countOfReadUsers);
        fclose(fp);
    }
    curs_set(0);
    attron(COLOR_PAIR(3));
    printw("New entry made\n");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("To go to the menu press ENTER\n");

}

void Read(char *filename)
{
    int count = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person users[count];
    size_t read = fread(users, sizeof(users[0]), count, fp);
    count = read;

    if(read > 0)
    {
        attron(COLOR_PAIR(2));
        for(int i = 0; i < count; i++)
        {
            printw("Name: %s\t Tel: %ld\n", users[i].Name, users[i].Tel);
            refresh();
        } 
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("To go to the menu press ENTER\n");
    }
    else
    {
        attron(COLOR_PAIR(1));
        printw("The abonents list is empty. To create an entry press ENTER\n");
        attroff(COLOR_PAIR(1));
        int CH;
        while(CH != '\n')
        {
            CH = getch();
        }
        Write(filename);
    }
    fclose(fp);
}



void Search(char *filename)
{
    char* foundName = new char[20];
    //printw("Введите имя абонента, номер которого хотите найти: ");
    attron(COLOR_PAIR(3));
    printw("Enter the name of the abonent whose number you want to find: ");
    attroff(COLOR_PAIR(3));
    curs_set(1);
    echo();
    refresh();
    attron(COLOR_PAIR(2));
    scanw("%s", foundName);
    //printf("%s\n", foundName);
    int count = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person users[count];
    size_t read = fread(users, sizeof(users[0]), count, fp);
    count = read;
    int countOfFound = 0;
    //printf("%s\n", users[4].Name);
    if(read > 0)
    {
        for(int i = 0; i < count; i++)
        {
            if(strcmp(users[i].Name, foundName) == 0)
            {
                printw("Name: %s \t Tel: %ld\n", users[i].Name, users[i].Tel);
                refresh();
                countOfFound++;
            }
        }
        if(countOfFound == 0)
        {
            attron(COLOR_PAIR(3));
            printw("No entries found\n");
            attroff(COLOR_PAIR(3));
        }
    }
    attroff(COLOR_PAIR(2));
    fclose(fp);
    curs_set(0);
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("To go to the menu press ENTER\n");
    attroff(COLOR_PAIR(1));
}


int recFunc( char *filename, void (*operations[3])(char*))
{
    int CH;
    string menu[]{"Read abonents", "Write abonent", "Search abonent", "Exit"};
    //string menu[]{"Read", "Write", "Search", "Выход"};
    switch(ChooseMenu(4, menu))
    {
        
        case 0:
        {
            operations[0](filename);
            while(CH != '\n')
            {
                CH = getch();
            }
            recFunc(filename, operations);
            break;
        }
        case 1:
         {
            operations[1](filename);
            while(CH != '\n')
            {
                CH = getch();
            }
            recFunc(filename, operations);
            break;
        }
        case 2:
        {
            operations[2](filename);
            while(CH != '\n')
            {
                CH = getch();
            }
            recFunc(filename, operations);
            break;
        }
        
        case 3:
        clear();
        endwin(); 
        exit;
        break;
    }
    
}

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF8");
    int action;
    char * filename = "people.bin";
    void (*operations[3])(char*) = {Read, Write, Search};
    int length = sizeof(operations)/sizeof(operations[0]);
    recFunc(filename, operations);
}