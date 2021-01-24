#include "../header_files/main.h"

int verbose = 0;
int verifyDeleted = 0;
int considerLinks = 0;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    if (argc > 1 && string(argv[1]) == "-v")
    { //verbose option, if it exist then we print program procedure info
        verbose = 1;
        cout << "\tVerbose Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerbose Mode: OFF"<< endl;
    }

    if (argc > 2 && string(argv[2]) == "-d")
    {   //deleted option, if it exist then,
        //we should make sure deleted files in A get deleted in B
        verifyDeleted = 1;
         cout << "\tVerify Deletion Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerify Deletion Mode: OFF"<< endl;
    }

    if (argc > 3 && string(argv[3]) == "-l")
    {   //consider links option, if it exist then,
        //our program should consider possible links
        considerLinks = 1;
        cout << "\tConsider Links Mode: ON"<< endl;
    }
    else
    {
        cout << "\tConsider Links Mode: OFF"<< endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    

    return 0;
}