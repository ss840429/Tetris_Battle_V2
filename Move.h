#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

class GameBoard;
class Block;

void LoadToBuffer( GameBoard& , Block ) ;

void MoveBlock( GameBoard& gb , int x , int y , int desx , int desy ) ;
bool MoveDown( GameBoard&   ) ;
void MoveRight( GameBoard&  ) ;
void MoveLeft( GameBoard& ) ;
void AllDown( GameBoard& ) ;
void Rotate( GameBoard& ) ;
void Showpect( GameBoard& gb ) ;
void RemShape( GameBoard& gb ) ;

#endif // MOVE_H_INCLUDED
