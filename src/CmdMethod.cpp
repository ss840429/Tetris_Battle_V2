
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../include/CmdMethod.h"
using namespace std ;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

HANDLE ScreenOut  = GetStdHandle(STD_OUTPUT_HANDLE) ;    // Standard Output -> Screen
#endif // _WIN32

#ifdef __linux__
#include <unistd.h>

char getch(void);
int kbhit(void);
#endif


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
  if ( kbhit( ) ) /* kbhit() -> if have input */
  {
      return (int)getch() ;
  }
  return 0 ;
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

void HighlightText( const char t[] )
{
    SetColor( Black , Yellow ) ;
    cout << t ;
    SetColor(White) ;
}
void ColorText( const char t[] , int color )
{
    SetColor( color ) ;
    cout << t ;
    SetColor(White) ;
}

void DrawSpect( ){
    cout << "\u2591" ;
#ifdef __linux__
    cout << "\u2591" ;
#endif // __linux__
}
void DrawBlock( int color ){
    SetColor(color) ;
    cout << "\u2586" ;
#ifdef __linux__
    cout << "\u2586" ;
#endif // __linux__
    SetColor(White) ;
}
void DrawSpace(  ){
    cout << "  " ;
}

int Random( int ln , int un )
{
    return rand()%(un-ln+1) + ln ;

}
void Delay( int ms )
{
#ifdef _WIN32
    Sleep(ms);
#endif // _WIN32
#ifdef __linux__
    usleep(ms);
#endif // __linux__
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

static struct termios old, newwlog;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  newwlog = old; /* make new settings same as old settings */
  newwlog.c_lflag &= ~ICANON; /* disable buffered i/o */
  newwlog.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &newwlog); /* use these new terminal i/o settings now */
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

#endif // __linux__


