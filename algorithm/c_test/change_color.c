#include <windows.h>
#include <conio.h>
#include <stdio.h>
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED);
    printf("hello world\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_GREEN);
    printf("********\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED | FOREGROUND_GREEN);
    return 0;
}
