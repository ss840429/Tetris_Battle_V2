#include "CmdMethod.h"
#include "Block.h"
#include <iostream>
using namespace std;

void Block::GainBlock()
{
    this->Init() ;
    this->SetType( Shape ) ;

    int pick[] = { Red , Green , Blue , Yellow , Purple , Cyan } ;
    int color = pick[Random(0,5)] ;

    if( Random(1,100) <= Prob_Trap )
    	this->SetAtt( (Attribute){Random(7,8),color} ) ;	// Trap
    else
    	this->SetAtt( (Attribute){Random(0,6),color} ) ;	// Basic
}

const void Block::Print() const {
    if( type_ == Spect )
        DrawSpect( ) ;
    else if( type_ != None )
        DrawBlock( att_.color ) ;
    else
        DrawSpace() ;
}

GameBoard::GameBoard( int X , int Y ) {
    int i = -1 ;
	try{
        gameBoard_ = new Block*[X] ;
        for( i = 0 ; i < X ; ++i  )
            gameBoard_[i] = new Block[Y] ;
        sizeX_ = X , sizeY_ = Y ;
        this->Init();
	}
	catch( bad_alloc e ){
        cerr << e.what() ;
        if( i != -1 ){
            for( int j = 0 ; j < i ; ++j ){
                delete[] gameBoard_[j] ;
            }
            delete[] gameBoard_ ;
        }
        sizeX_ = 0 , sizeY_ = 0 ;
	}
}
GameBoard::GameBoard( const GameBoard& gb ): GameBoard(gb.sizeX_, gb.sizeY_)
{
    for( int i = 0 ; i < gb.sizeX_ ; ++i )
        for( int j = 0 ; j < gb.sizeY_ ; ++j )
            this->gameBoard_[i][j] = gb.gameBoard_[i][j];
}

GameBoard::~GameBoard() {
    for( int i = 0 ; i < sizeX_ ; ++i ){
        delete[] gameBoard_[i] ;
    }
	delete[] gameBoard_ ;
}

void GameBoard::Init() {
	for( int i = 0 ; i < sizeX_ ; ++i )
        for( int j = 0 ; j < sizeY_ ; ++j )
            gameBoard_[i][j].Init() ;
}

bool GameBoard::IsEmpty() const{
	for( int i = 0 ; i < sizeX_ ; ++i )
        for( int j = 0 ; i < sizeY_ ; ++j )
            if(  gameBoard_[i][j].GetType() == Shape ||  gameBoard_[i][j].GetType() == Lock )
                return false ;
	return true ;
}
void GameBoard::Print( int PointX , int PointY ) const{
	for( int i = 4 ; i < sizeX_; ++i )
    {
        GoToXY( PointX , PointY+i-4 ) ;
        for( int j = 0 ; j < sizeY_ ; ++j )
         	gameBoard_[i][j].Print() ;
    }
}



