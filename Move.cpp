#include "Move.h"
#include "Block.h"

const char node[9][2] = { {1,1} , {1,2} , {1,1} , {1,2} , {2,3} , {2,0} , {2,1} , {1,1} , {1,1}} ;

void LoadToBuffer( GameBoard& gb, Block b )
{
    for( int i = 0 ; i < 4*4 ; i ++ )
    {
        if( Bricks[b.GetAtt().shape][i] )
        {
            gb.GetBlock( i/4, (SIZE_Y/2-2) + i%4 ).SetType(Shape);
            gb.GetBlock( i/4, (SIZE_Y/2-2) + i%4 ).SetAtt(b.GetAtt());
        }
        else
            gb.GetBlock( i/4, (SIZE_Y/2-2) + i%4 ).Init();
    }

    gb.GetBlock( node[b.GetAtt().shape][0] , node[b.GetAtt().shape][1]+SIZE_Y/2-2 ).SetNode() ;

    while( MoveDown( gb ) )
    {
        bool k = false ;

        for( int i = 0 ; i < SIZE_Y ; i ++ )
           if( gb.GetBlock(4,i).GetType() == Shape )
                k = true ;

        if(k) break;
    }

}

bool Movable( GameBoard& gb, int x, int y )
{
    for( int i = 0 ; i < SIZE_X ; ++i )
        for( int j = 0 ; j < SIZE_Y ; ++j )
            if( gb.GetBlock(i,j).GetType() == Shape &&
                    ( !gb.IsValid(i+x,j+y) || gb.GetBlock(i+x,j+y).GetType() == Lock ) )
                        return false ;
    return true ;
}
void MoveBlock( GameBoard& gb, int x, int y, int desx, int desy )
{
    if(  !( gb.IsValid( x, y ) && gb.IsValid( desx, desy ) )  ) return ;

    gb.GetBlock( desx, desy ) = gb.GetBlock( x , y ) ;
    gb.GetBlock( x, y ).Init() ;
}
bool MoveDown( GameBoard& gb )
{
    if(Movable(gb, 1, 0))
    {
        for( int i = SIZE_X - 2 ; i >= 0 ; --i )
            for( int j = 0 ; j < SIZE_Y ; ++j  )
                if( gb.GetBlock(i,j).GetType() == Shape )
                    MoveBlock( gb, i, j, i+1, j ) ;

        return true;
    }
    else        /* Lock Block */
    {
        for( int i = 0 ; i < SIZE_X ; ++i )
            for( int j = 0 ; j < SIZE_Y ; ++j )
                if( gb.GetBlock(i,j).GetType() == Shape )
                    gb.GetBlock(i,j).SetType(Lock);
        return false;
    }
}
void MoveRight( GameBoard& gb )
{
    if( Movable( gb, 0, 1 ) )
    {
        for( int i = 0 ; i < SIZE_X ; ++i )
            for( int j = SIZE_Y - 2  ; j >= 0 ; --j )
                if( gb.GetBlock(i,j).GetType() == Shape )
                    MoveBlock( gb, i, j, i, j+1 ) ;
    }
}
void MoveLeft( GameBoard& gb )
{
    if( Movable( gb, 0, -1 ) )
    {
        for( int i = 0 ; i < SIZE_X ; ++i )
            for( int j = 1  ; j < SIZE_Y ; ++j )
                if( gb.GetBlock(i,j).GetType() == Shape )
                    MoveBlock( gb, i, j, i, j-1 ) ;
    }
}
void AllDown( GameBoard& gb )
{
    while( MoveDown(gb) );
}
bool AttemptToRotate( GameBoard& gb, GameBoard& tmp, int x, int y )
{
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 5 ; j ++ )
            if( tmp.GetBlock(i,j).GetType() == Shape && ( !gb.IsValid(x-2+i,y-2+j) || gb.GetBlock(x-2+i,y-2+j).GetType() == Lock ))
                return false ;

    RemShape(gb) ;

    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 5 ; j ++ )
            if( !gb.IsValid(x-2+i,y-2+j) ) continue ;
            else if( tmp.GetBlock(i,j).GetType() == Shape )
                gb.GetBlock(x-2+i,y-2+j) = tmp.GetBlock(i,j) ;

    return true ;
}
void Rotate( GameBoard& gb )
{
    GameBoard tmp(5,5);
    int midx, midy ;

    for( int i = 0 ; i < SIZE_X ; ++i )
        for( int j = 0  ; j < SIZE_Y ; ++j )
            if( gb.GetBlock(i,j).GetType() == Shape && (gb.GetBlock(i,j).GetAtt().shape == 0 || gb.GetBlock(i,j).GetAtt().shape > 6 ))
                return ;
            else if( gb.GetBlock(i,j).IsNode() && gb.GetBlock(i,j).GetType() == Shape )
                midx = i, midy = j ;

    for( int i = 0 ; i < 5 ; ++i )         /* Produce Graph */
        for( int j = 0 ; j < 5 ; ++j )
            if( gb.IsValid(midx-2+i,midy-2+j) && gb.GetBlock(midx-2+i,midy-2+j).GetType() == Shape )
                tmp.GetBlock(j,4-i) = gb.GetBlock(midx-2+i,midy-2+j) ;

    for( int i = 0 ; i < 3 ; ++i )
        if( AttemptToRotate(gb, tmp, midx, midy+i) || AttemptToRotate(gb, tmp, midx, midy-i) ) return ;

    AttemptToRotate(gb, tmp, midx+1, midy-1 );      // T spin
}
void Showpect( GameBoard& gb )
{
    int k = 0 ;
    GameBoard tmpgb(gb) ;
    while( Movable(tmpgb, 1, 0) && k++ < 20 ) MoveDown(tmpgb);

    for( int i = 0 ; i < SIZE_X ; ++i )
        for( int j = 0  ; j < SIZE_Y ; ++j )
            if( gb.GetBlock(i,j).GetType() == None && tmpgb.GetBlock(i,j).GetType() == Shape )
                gb.GetBlock(i,j).SetType(Spect);
            else if( gb.GetBlock(i,j).GetType() == Spect && tmpgb.GetBlock(i,j).GetType() != Shape )
                gb.GetBlock(i,j).Init() ;
}
void RemShape( GameBoard& gb )
{
    for( int i = 0 ; i < SIZE_X ; ++i )
        for( int j = 0 ; j < SIZE_Y ; ++j )
            if( gb.GetBlock(i,j).GetType() != Lock )
                gb.GetBlock(i,j).Init() ;
}
