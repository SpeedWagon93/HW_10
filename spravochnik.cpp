#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char Name[20];
    long Tel;
};

void Read(char *filename)
{
    int count = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person users[count];
    size_t read = fread(users, sizeof(users[0]), count, fp);
    count = read;
    printf("read %d elements\n", count);
    if(read > 0)
    {
        for(int i = 0; i < count; i++)
        {
            printf("Name: %s \t Tel: %ld\n", users[i].Name, users[i].Tel);
        }
    }
    fclose(fp);
}

void Write(char *filename)
{
    char* Name = new char[20];
    long tel;
    scanf("%s", Name);
    scanf("%*[^\n]");
    scanf("%ld", &tel);


    int countOfReadUsers = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person usersRead[countOfReadUsers];
    size_t read = fread(usersRead, sizeof(usersRead[0]), countOfReadUsers, fp);
    countOfReadUsers = read;
    fclose(fp);

    struct Person* usersWrite = new struct Person[countOfReadUsers +1];
    for(int i = 0; i < countOfReadUsers; i++)
    {
        usersWrite[i] = usersRead[i];
        printf("Name: %s \t Tel: %ld\n", usersWrite[i].Name, usersWrite[i].Tel);
    }
    strcpy(usersWrite[countOfReadUsers].Name, Name);
    usersWrite[countOfReadUsers].Tel = tel;
    printf("Name: %s \t Tel: %ld\n", usersWrite[countOfReadUsers].Name, usersWrite[countOfReadUsers].Tel);
    
    fp = fopen(filename, "w");

    size_t write = fwrite(usersWrite, sizeof(usersWrite[0]), countOfReadUsers+1, fp);
    countOfReadUsers = write;
    fclose(fp);
    
}

void Search(char *filename)
{
    char* foundName = new char[20];
    printf("Введите имя абонента, номер которого хотите найти: ");
    scanf("%s", foundName);
    int count = 1000;
    FILE *fp = fopen(filename, "r");
    struct Person users[count];
    size_t read = fread(users, sizeof(users[0]), count, fp);
    count = read;
    if(read > 0)
    {
        for(int i = 0; i < count; i++)
        {
            if(strcmp(users[i].Name, foundName) == 0)
            {
                printf("Name: %s \t Tel: %ld\n", users[i].Name, users[i].Tel);
            }
        }
    }
    fclose(fp);
}


int recFunc(int* action, char *filename, void (*operations[3])(char*))
{
    

    printf("Прочитать - 0\tЗаписать - 1\tНайти - 2\tВыйти - 3\nВведите число: ");
    scanf("%d", &*action);
    if (*action == 3)
    {
        exit;
    }else if(*action == 0 || *action == 1 || *action == 2)
    {
        operations[*action](filename);
        recFunc(action, filename, operations);
    }else
    {
        printf("Вы ввели невалидное значение, начнём заново...\n");
        recFunc(action, filename, operations);
    }
}

int main(void)
{
    int action;
    char * filename = "people.bin";
    void (*operations[3])(char*) = {Read, Write, Search};
    int length = sizeof(operations)/sizeof(operations[0]);
    recFunc(&action, filename, operations);
}