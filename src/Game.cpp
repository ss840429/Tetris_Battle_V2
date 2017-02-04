#include "../include/CmdMethod.h"
#include "../include/Block.h"
#include "../include/Loc.h"
#include "../include/Game.h"
#include "../include/Move.h"
#include "../include/Audio.h"
#include <stdlib.h>
#include <algorithm>
#include <time.h>

void ShowBoard( GameBoard& gb ) ;
void ShowNextBlock( Block ) ;
void ShowHoldBlock( Block ) ;
void ShowScore( int total_score , int total_line , int combo ) ;
void ShowForm() ;
void EraseLine( GameBoard& gb, int& score, int& line, int& combo ) ;
bool GameOver( GameBoard& gb );


constexpr int level_time = 1000 ;                           /* ms -> speed */
constexpr int max_level_time = 150 ;
constexpr int Lscore[5] = { 0, 20, 100, 250, 500 } ;     /* Value of erasing each line */
Mode mode = Single ;

void Game(Mode M)
{
    srand(time(0));
    PMode( M ) ;

    CleanScreen() ;
    GameBoard gb ;

    Block Cur, Next, Hold ;
    Cur.GainBlock(), Next.GainBlock();
    initAudio();

    int score = 0, line = 0, combo = 0 ;
    int timecounter = 0;
    bool next, changable = true ;

    ShowForm() ;
    LoadToBuffer( gb , Cur ) ;
    playMusic();

    do{
        ShowNextBlock( Next ) ;
        ShowHoldBlock( Hold ) ;
        ShowScore( score, line, combo ) ;
        Showpect( gb );
        ShowBoard( gb ) ;

        timecounter = clock() ;
        next = false ;

        do{
            int interact = GetKeyboardInput() ;   /* User input */

            if( interact == Down || (clock()-timecounter)*1000 >= std::max( level_time - line*4 , max_level_time )*CLOCKS_PER_SEC )
            {
                timecounter = clock() ;   /* reset time for next count */
                next = !MoveDown( gb ) ;
                if( next ) Delay(100) ;
                ShowBoard( gb ) ;
            }
            if( interact == Left ) MoveLeft( gb ) ;
            if( interact == Right ) MoveRight( gb ) ;
            if( interact == Space ){
                AllDown( gb ) ;
                next = true ;
            }
            if( interact == Up )  Rotate( gb ) ;
            if( interact == C && changable )
            {
                RemShape(gb) ;
                if( Hold.GetType() == None ){  /* Fisrt Hold */
                    Hold = Cur ;
                    Cur = Next , Next.GainBlock() ;
                    LoadToBuffer( gb, Cur ) ;
                }
                else{
                    std::swap( Hold, Cur ) ;
                    changable = false ;
                    LoadToBuffer( gb, Cur ) ;
                }
                break;
            }


            if( interact != 0 ){               // Refresh
                Showpect( gb );
                ShowBoard( gb ) ;
            }

        }while(!next);

        if( next )
        {
            playSound() ;
            EraseLine( gb, score, line, combo ) ;
            Cur = Next , Next.GainBlock() ;
            changable = true ;
            LoadToBuffer( gb, Cur ) ;
        }

    }while (!GameOver(gb)) ;


}


void ShowForm()
{
    GoToXY( Form_X+6, Form_Y-1 ) ;
    ColorText( " Y  O  U  R  " , Yellow ) ;
    if( mode == Multi )
    {
        GoToXY( Form_X2+7, Form_Y2-1 ) ;
        ColorText( " R I V A L" , Yellow ) ;
    }
    for( int i = 0 ; i < SIZE_X -2 ; ++i ) /* Main Form */
    {
        GoToXY( Form_X, Form_Y + i ) ;
        for( int j = 0 ; j < SIZE_Y + 2 ; ++j  )
            if( i == 0 || i == SIZE_X-3 || j == 0 || j == SIZE_Y+1 )
                DrawBlock(White) ;
            else
                cout << "  " ;

        if( mode == Multi )
        {
            GoToXY( Form_X2, Form_Y2 + i ) ;
            for( int j = 0 ; j < SIZE_Y + 2 ; ++j )
                if( i == 0 || i == SIZE_X-3 || j == 0 || j == SIZE_Y+1 )
                    DrawBlock(White) ;
                else
                    cout << "  " ;
        }
    }
    for( int i = 0 ; i < 7 ; ++i )
    {
        GoToXY( Next_X, Next_Y+i ) ;    /* Next Form */
        if( !i )
        {
            ColorText( " N  E  X  T  " , Yellow ) ;
        }
        else if( i == 1 || i == 6 )
        {
            for( int j = 0 ; j < 6 ; ++j )
                DrawBlock( White ) ;
        }
        else
        {
            DrawBlock( White ) ;
            cout << "        "  ;
            DrawBlock( White ) ;
        }

        GoToXY( Hold_X, Hold_Y+i ) ;    /* Hold Form */
        if( !i )
        {
            ColorText( " H  O  L  D  " , Yellow ) ;
        }
        else if( i == 1 || i == 6 )
        {
            for( int j = 0 ; j < 6 ; ++j )
                DrawBlock( White ) ;
        }
        else
        {
            DrawBlock( White ) ;
            cout << "        " ;
            DrawBlock( White ) ;
        }
    }
}
void ShowBoard( GameBoard& gb )
{
    gb.Print( Form_X+2, Form_Y+1 );
    GoToXY( 0, 0 ) ;
}
void ShowScore( int score , int line , int combo )
{
    GoToXY( Score_X, Score_Y ) ;
    cout << "Score : " << score ;
    GoToXY( Score_X, Score_Y+2 ) ;
    cout << "Cleared : " << line ;
    GoToXY( Score_X, Score_Y+4 ) ;
    cout << "Combo : " << combo ;
}
void ShowNextBlock( Block next )
{
    for( int i = 0 ; i < 4 ; ++i  )
    {
        GoToXY( Next_X+2 , Next_Y+2+i ) ;
        for( int j = 0 ; j < 4 ; ++j )
            if( Bricks[next.GetAtt().shape][i*4+j] )
                next.Print() ;
            else
                cout <<  "  "  ;
    }
}
void ShowHoldBlock( Block hold )
{
    if( hold.GetType() == Shape )
    {
        for( int i = 0 ; i < 4 ; ++i )
        {
            GoToXY( Hold_X+2 , Hold_Y+2+i ) ;
            for( int j = 0 ; j < 4 ; ++j  )
                if( Bricks[hold.GetAtt().shape][i*4+j] )
                    hold.Print() ;
                else
                    cout << "  " ;
        }
    }
}

void EraseLine( GameBoard& gb, int& score, int& line, int& combo )
{
    int add = 0 ;
    int i , j ;   /* For loop */

    for( i = SIZE_X-1 ; i > 3 ; --i )
    {
        int check = 0 ;
        for( j = 0 ; j < SIZE_Y ; ++j )
        {
            if( gb.GetBlock(i,j).GetType() == Lock ) check ++ ;
        }

        if( check == SIZE_Y )
        {
            add += 1;

            for( j = i ; j > 4 ; --j )
            {
                for( int k = 0 ; k < SIZE_Y  ; ++k )
                    MoveBlock( gb, j-1, k, j, k ) ;
            }
            i += 1 ;
        }
    }

    score += Lscore[add]*(1+combo) ;
    line += add ;
    if( add == 0 ) combo = 0 ;
    else combo += 1 ;
}
bool GameOver( GameBoard& board )
{
    for( int i = 0 ; i < SIZE_Y ; ++i )
        if( board.GetBlock(3,i).GetType() == Lock )
            return true ;

    return false ;
}

void PMode( Mode M )
{
    if( M == Single ){
        Form_X = S_Form_X ;
        Form_Y = S_Form_Y ;
        Next_X = S_Next_X ;
        Next_Y = S_Next_Y ;
        Hold_X = S_Hold_X ;
        Hold_Y = S_Hold_Y ;
        Score_X = S_Score_X ;
        Score_Y = S_Score_Y ;
        Pause_X = S_Pause_X ;
        Pause_Y = S_Pause_Y ;
        mode = Single ;
    }
    else{
        Form_X = M_Form_X ;
        Form_Y = M_Form_Y ;
        Next_X = M_Next_X ;
        Next_Y = M_Next_Y ;
        Hold_X = M_Hold_X ;
        Hold_Y = M_Hold_Y ;
        Score_X = M_Score_X ;
        Score_Y = M_Score_Y ;
        Pause_X = M_Pause_X ;
        Pause_Y = M_Pause_Y ;
        mode = Multi ;
    }
}

