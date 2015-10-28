#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "CmdMethod.h"
#include "Color.h"
#include <iostream>
using namespace std;

enum BTYPE { None , Shape , Lock , Spect } ;

const int SIZE_X = 10 ;
const int SIZE_Y = 24 ;  // 20+4( board+buffer )
const int Prob_Trap = 2 ; // x of 100%


const bool bricks[9][16] =  {
                            {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},      // Square
                            {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},      // Line
                            {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},      // _|-
                            {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},      // -|_
                            {0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0},      // reverse L
                            {0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},      // L
                            {0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},      // T
                            {1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1},      // Trap 1
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}      // Trap 2
                            ;

struct Attribute{
	int shape ;
	int color ;
} ;

class Block{
    friend ostream & operator << (ostream &os, const Block& block ) ;

	public:
		void Init(){
			att_.shape = -1 ;
			att_.color = White ;
			type_ = None ;
			isSpinNode_ = false ;
		}
		void SetNode(){
			isSpinNode_ = true ;
		}
		void SetType( BTYPE type ){
			type_ = type ;
		}
		void SetAtt( Attribute att ){
			att_ = att ;
		}
		void GainBlock() ;

		const Attribute& GetAtt() const{
            return att_ ;
        }
        const BTYPE& GetType() const{
        	return type_ ;
        }

	private:
		Attribute att_ ;
		BTYPE type_ ;
		bool isSpinNode_ ;

};



class GameBoard{

	public:
		GameBoard() ;
		GameBoard( int sizeX , int sizeY ) ;
		~GameBoard() ;

		void Init() ;
		Block& GetBlock( int locX , int locY ){
			if( IsValid( locX , locY ) )
				return gameBoard_[locX+locY*SIZE_X] ;
			else
				return gameBoard_[0] ;
		}


		bool IsEmpty() const ;
		void Print( int PointX , int PointY ) const ;
		bool IsValid( int locX , int locY ) const{
			return ( 0<=locX+locY*SIZE_X && locX+locY*SIZE_X<SIZE_X*SIZE_Y ) ;
		}
	private:
		Block* gameBoard_ ;
		int sizeX_ , sizeY_ ;

} ;


#endif // BLOCK_H_INCLUDED
