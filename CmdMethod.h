#ifndef WINCMD_H_INCLUDED
#define WINCMD_H_INCLUDED

#include "Color.h"
#include <iostream>
using namespace std;

void GoToXY( int x , int y ) ;

void DrawSpect( ostream& os ) ;
void DrawBlock( ostream& os , int color ) ;
void DrawSpace( ostream& os ) ;

int Random( int ln , int un ) ;


#endif // WINCMD_H_INCLUDED
