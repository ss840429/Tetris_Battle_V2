
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "CmdMethod.h"
using namespace std ;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

HANDLE ScreenOut  = GetStdHandle(STD_OUTPUT_HANDLE) ;    // Standard Output -> Screen
#endif


void GoToXY( int x , int y )
{
#ifdef _WIN32
    COORD dot = { x , y } ;
    SetConsoleCursorPosition( ScreenOut , dot );
#endif

#ifdef __linux__
    printf("%c[%d;%df",0x1B,y,x);
#endif
}

void SetColor( int front , int back )
{
#ifdef _WIN32
    SetConsoleTextAttribute(ScreenOut,front+back);
#endif

#ifdef __linux__
    printf("\033[%d;%dm",front,back) ;
#endif
}

void SetColor( int color )
{
#ifdef _WIN32
    SetConsoleTextAttribute(ScreenOut,color);
    if( color > 100 ) // background
        SetConsoleTextAttribute(ScreenOut,color+White);
#endif

#ifdef __linux__
    printf("\033[%dm",color) ;
#endif
}


void DrawSpect( ostream& os ){
    os << "¡¼" ;
}
void DrawBlock( ostream& os , int color ){
    SetColor(color) ;
    os << "¢i" ;
    SetColor(White) ;
}
void DrawSpace( ostream& os ){
    cout << "  " ;
}

int Random( int ln , int un )
{
    return rand()%(un-ln+1) + ln ;
}


