#include "WinCmd.h"
#include "Color.h"
#include "Block.h"
#include <iostream>
using namespace std;

void Block::GainBlock()
{
    this->SetType( Shape ) ;

    int color = Random(0,5) ;
    if( Random(1,100) <= Prob_Trap )
    	this->SetAtt( (Attribute){Random(7,8),color} ) ;	// Trap
    else
    	this->SetAtt( (Attribute){Random(0,6),color} ) ;	// Basic
}

ostream& operator <<( ostream& os , const Block& block ) {
    if( block.type_ == Spect )
        DrawSpect( os ) ;
    else if( block.type_ != None )
        DrawBlock( os , block.att_.color ) ;
    else
        DrawSpace( os ) ;
    return os ;
}

GameBoard::GameBoard(){
	sizeX_ = SIZE_X , sizeY_ = SIZE_Y ;

	gameBoard_ = new Block[SIZE_X*SIZE_Y] ;
	if( gameBoard_ == NULL )
		sizeX_ = 0 , sizeY_ = 0 ;
}
GameBoard::GameBoard( int sizeX , int sizeY ) {
	sizeX_ = sizeX , sizeY_ = sizeY ;

	gameBoard_ = new Block[sizeX*sizeY] ;
	if( gameBoard_ == NULL )
		sizeX_ = 0 , sizeY_ = 0 ;
}
GameBoard::~GameBoard() {
	delete [] gameBoard_ ;
}

void GameBoard::Init() {
	for( int i = 0 ; i < SIZE_X*SIZE_Y ; i ++ )
        gameBoard_[i].Init() ;
}
bool GameBoard::IsEmpty() const{
	for( int i = 0 ; i < SIZE_X*SIZE_Y ; i ++ )
		if(  gameBoard_[i].GetType() == Shape ||  gameBoard_[i].GetType() == Lock )
			return false ;

	return true ;
}
void GameBoard::Print( int PointX , int PointY ) const{
	for( int i = 4 ; i < SIZE_Y; i ++ )
    {
        GoToXY( PointX , PointY+i-4 ) ;
        for( int j = 0 ; j < SIZE_X ; j ++ )
         	cout << gameBoard_[j+i*SIZE_X] ;
    }
}



