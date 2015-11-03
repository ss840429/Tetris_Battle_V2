
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "CmdMethod.h"
using namespace std ;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

HANDLE ScreenOut  = GetStdHandle(STD_OUTPUT_HANDLE) ;    // Standard Output -> Screen
#endif // _WIN32


void GoToXY( int x , int y )
{
#ifdef _WIN32
    COORD dot = { x , y } ;
    SetConsoleCursorPosition( ScreenOut , dot );
#endif // _WIN32

#ifdef __linux__
    printf("%c[%d;%df",0x1B,y,x);
#endif // __linux__
}

int GetKeyboardInput()
{
#ifdef _WIN32
    if ( kbhit( ) ) /* kbhit() -> if have input */
    {
        return (int)getch() ;
    }
    return 0 ;
#endif // _WIN32
}

void SetColor( int front , int back )
{
#ifdef _WIN32
    SetConsoleTextAttribute(ScreenOut,front+back);
#endif // _WIN32

#ifdef __linux__
    printf("\033[%d;%dm",front,back) ;
#endif // __linux__
}

void SetColor( int color )
{
#ifdef _WIN32
    SetConsoleTextAttribute(ScreenOut,color);
    if( color > 100 ) // background
        SetConsoleTextAttribute(ScreenOut,color+White);
#endif // _WIN32

#ifdef __linux__
    if( color < 40 )
        printf("\033[%d;%dm",color,49) ;
    else
        printf("\033[%d;%dm",White,color) ;
#endif // __linux__
}

void HighlightText( char t[] )
{
    SetColor( Black , Yellow ) ;
    cout << t ;
    SetColor(White) ;
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

void CleanScreen()
{
#ifdef _WIN32
    system( "cls" ) ;
#endif // _WIN32
#ifdef __linux__
    cout << "\033[2J" ;
#endif // __linux__
}


// For linux no conio.h

#ifdef __linux__

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}

#endif // __linux__


