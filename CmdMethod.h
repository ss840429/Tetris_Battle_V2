#ifndef WINCMD_H_INCLUDED
#define WINCMD_H_INCLUDED

#include <iostream>
using namespace std;

#ifdef __linux__
	enum Key { Enter = 10 , Up = 65, Down = 66, Left = 68 , Right = 67 , Space = 32 , C = 99 , Pause = 112 , ESC = 27 } ;
    enum Color{  Black = 30 ,  Red = 31 ,  Green = 32 ,  Blue = 34 ,  Yellow = 33 ,  Purple = 35 ,  Cyan = 36 ,  White = 37 };
    enum Bolor{ BBlack = 40 , BRed = 41 , BGreen = 42 , BBlue = 44 , BYellow = 43 , BPurple = 45 , BCyan = 46 , BWhite = 47 };
#endif

#ifdef _WIN32
	enum Key { Enter = 13 , Up = 72 , Down = 80 , Left = 75 , Right = 77 , Space = 32 , C = 99 , Pause = 112 , ESC = 27 } ;
    enum Color{ Black = 0 , Red =  12 ,  Green =  10 ,  Blue =   9 ,  Yellow =  14 ,  Purple = 13 ,  Cyan = 11 ,  White = 07 };
    enum Bolor{ BRed = 192 , BGreen = 160 , BBlue = 144 , BYellow = 224 , BPurple = 208 , BCyan = 176 , BWhite = 240 };
#endif




void GoToXY( int x , int y ) ;
int GetKeyboardInput() ;

void SetColor( int front , int back ) ;
void SetColor( int color ) ;
void HighLightText( char t[] ) ;
void ColorText( char t[] , int color ) ;

void DrawSpect( ) ;
void DrawBlock( int color ) ;
void DrawSpace( ) ;

int Random( int ln , int un ) ;
void CleanScreen() ;
#ifdef __linux__

#endif // __linux__

#endif // WINCMD_H_INCLUDED
