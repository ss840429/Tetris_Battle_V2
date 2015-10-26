#include "Block.h"
#include <iostream>
using namespace std ;

int main()
{
    Block g ;
    g.SetType(Spect) ;
    g.SetAtt( (Attribute){2,2} );
    cout << g <<g<<g<<g<<endl<<g<<g;
    return 0 ;
}
