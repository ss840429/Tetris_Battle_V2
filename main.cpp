#include "Block.h"
#include <iostream>
#include "CmdMethod.h"

using namespace std ;

int main()
{
    Block g ;

    g.SetType(Spect) ;

    cout << g << endl ;

    g.SetType(Shape) ;
    g.SetAtt( (Attribute){2,Yellow} );




    for(int i = 0 ; i < 31 ; i ++ )
    {
        cout << g  ;
        g.GainBlock() ;
        if( i%10 == 0 ) cout << endl ;
     }

    cout << endl << endl << endl ;

    SetColor( Yellow , BRed ) ;
    cout << "12345" ;
    SetColor(Cyan) ;
    cout << "12345" ;
    SetColor(BBlue) ;
    cout << "12345" ;
    SetColor(Green) ;

    return 0 ;
}
