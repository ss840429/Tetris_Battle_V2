#ifndef WINCMD_H_INCLUDED
#define WINCMD_H_INCLUDED

#include <iostream>
using namespace std;

#ifdef __linux__
    enum Color{  Red = 31 ,  Green = 32 ,  Blue = 33 ,  Yellow = 34 ,  Purple = 35 ,  Cyan = 36 ,  White = 37 };
    enum Bolor{ BRed = 10 , BGreen = 10 , BBlue = 10 , BYellow = 10 , BPurple = 10 , BCyan = 10 , BWhite = 10 };
#endif

#ifdef _WIN32
    enum Color{ Black = 0 , Red =  12 ,  Green =  10 ,  Blue =   9 ,  Yellow =  14 ,  Purple = 13 ,  Cyan = 11 ,  White = 07 };
    enum Bolor{ BRed = 192 , BGreen = 160 , BBlue = 144 , BYellow = 224 , BPurple = 208 , BCyan = 176 , BWhite = 240 };
#endif

void GoToXY( int x , int y ) ;

void SetColor( int front , int back ) ;
void SetColor( int color ) ;

void DrawSpect( ostream& os ) ;
void DrawBlock( ostream& os , int color ) ;
void DrawSpace( ostream& os ) ;

int Random( int ln , int un ) ;


#endif // WINCMD_H_INCLUDED
