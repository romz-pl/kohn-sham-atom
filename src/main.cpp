//
// Main file for RAtom application
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//


#include "ratom.h"

void Intro(FILE* out);

int main(int argc, char* argv[])
{
    Intro(stdout);

    if(argc != 2)
    {
        printf("Usage: ratom name\n\n");
        return 1;
    }


    try
    {
        RAtom ratom( argv[ 1 ]);
        ratom.Run( );
        printf("\n\n********** CALCULATIONS FINISHED SUCCESSFULLY! **********\n\n\n");
        return 0;
    }
    catch( std::exception& e )
    {
        printf("\n\nERROR! %s\n\n\n", e.what());
        return 1;
    }
    catch( ... )
    {
        printf( "Unexpected error!\n\n" );
        return 1;
    }

}

void Intro(FILE* out)
{
    fprintf(out,
        "===============================================================================\n"
        " RRRR   AAA  TTTTT  OOO   M   M      Zbigniew Romanowski             \n"
        " R   R A   A  TTT  O   O  MM MM                                      \n"
        " RRRR  AAAAA   T   O   O  M M M      romz@wp.pl                      \n"
        " R  R  A   A   T   O   O  M   M                                      \n"
        " R   R A   A   T    OOO   M   M      https://sourceforge.net/p/ratom \n"
        "===============================================================================\n\n\n");
}

