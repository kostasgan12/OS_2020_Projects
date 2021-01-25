#include "../header_files/main.h"

int verbose = 0;
int verifyDeleted = 0;
int considerLinks = 0;

int main(int argc, char *argv[])
{

    DIR *source_directory_pointer;
    DIR *destination_directory_pointer;
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    string optionFlag;

    for (int i = 0; i < argc; i++)
    {
        optionFlag = argv[i];
        if (optionFlag == "-v")
        { //verbose option, if it exist then we print program procedure info
            verbose = 1;
        }
        else if (optionFlag== "-d")
        {   //deleted option, if it exist then,
            //we should make sure deleted files in A get deleted in B
            verifyDeleted = 1;
        }
        else if (optionFlag == "-l")
        {   //consider links option, if it exist then,
            //our program should consider possible links
            considerLinks = 1;
        }
    }
    
    if (verbose)
    {
        cout << "\tVerbose Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerbose Mode: OFF"<< endl;
    }

    if (verifyDeleted)
    {
        verifyDeleted = 1;
        cout << "\tVerify Deletion Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerify Deletion Mode: OFF"<< endl;
    }

    if (considerLinks)
    {
        considerLinks = 1;
        cout << "\tConsider Links Mode: ON"<< endl;
    }
    else
    {
        cout << "\tConsider Links Mode: OFF"<< endl;
    }

    
    string source_dir_name, dest_dir_name;

    if((verbose + verifyDeleted + considerLinks == 0 )&& argc > 2){
        cout<<"hereee"<<endl;
        source_dir_name = argv[1];
        dest_dir_name = argv[2];
    }else if((verbose + verifyDeleted + considerLinks == 1) && argc > 3){
        source_dir_name = argv[2];
        dest_dir_name = argv[3];
    }else if((verbose + verifyDeleted + considerLinks == 2 )&& argc > 4){
        source_dir_name = argv[3];
        dest_dir_name = argv[4];
    }else if((verbose + verifyDeleted + considerLinks == 3 )&& argc == 6){
        source_dir_name = argv[4];
        dest_dir_name = argv[5];
    }else{
        cout<<"ERROR PARSING PATHS"<<endl;
        exit(-1);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    

    return 0;
}