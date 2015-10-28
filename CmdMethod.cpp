
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Color.h"
using namespace std ;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif


void GoToXY( int x , int y )
{
    #ifdef _WIN32
        HANDLE Screen_Out  = GetStdHandle(STD_OUTPUT_HANDLE) ;    // Standard Output -> Screen
        COORD dot = { x , y } ;
        SetConsoleCursorPosition( Screen_Out , dot );
    #endif
    #ifdef __linux__
       printf("%c[%d;%df",0x1B,y,x);
    #endif
}

void ColorText( int choose )
{
#ifdef _WIN32
   if( choose == Red ) SetConsoleTextAttribute( Screen_Out , RED ) ;
   else if( choose == Green ) SetConsoleTextAttribute( Screen_Out , GREEN ) ;
   else if( choose == Blue ) SetConsoleTextAttribute( Screen_Out , BLUE ) ;
   else if( choose == Yellow ) SetConsoleTextAttribute( Screen_Out , YELLOW ) ;
   else if( choose == Purple ) SetConsoleTextAttribute( Screen_Out , PURPLE ) ;
   else if( choose == Cyan ) SetConsoleTextAttribute( Screen_Out , CYAN ) ;
   else if( choose == White ) SetConsoleTextAttribute( Screen_Out , WHITE ) ;
   else if( choose == Red+BgOffset ) SetConsoleTextAttribute( Screen_Out , RED_BACK ) ;
   else if( choose == Green+BgOffset ) SetConsoleTextAttribute( Screen_Out , GREEN_BACK ) ;
   else if( choose == Blue+BgOffset ) SetConsoleTextAttribute( Screen_Out , BLUE_BACK ) ;
   else if( choose == Yellow+BgOffset ) SetConsoleTextAttribute( Screen_Out , YELLOW_BACK ) ;
   else if( choose == Purple+BgOffset ) SetConsoleTextAttribute( Screen_Out , PURPLE_BACK ) ;
   else if( choose == Cyan+BgOffset ) SetConsoleTextAttribute( Screen_Out , CYAN_BACK ) ;
   else if( choose == White+BgOffset ) SetConsoleTextAttribute( Screen_Out , WHITE_BACK ) ;
#endif
#ifdef __linux__
   printf("\033[%dm",choose) ;
#endif
}


void DrawSpect( ostream& os ){
    os << "□" ;
}
void DrawBlock( ostream& os , int color ){
    ColorText(color) ;
    os << "■" ;
    ColorText(White) ;

}
void DrawSpace( ostream& os ) {
    cout << "  " ;
}

int Random( int ln , int un )
{
    return rand()%(un-ln+1) + ln ;
}


