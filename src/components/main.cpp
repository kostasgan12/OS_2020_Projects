#include "../header_files/main.h"

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    // if (argc != 5)
    // {
    //     cout << "########## ERROR WITH PARSED PARAMETERS ########## " << endl;
    //     return 0;
    // }

    // if (strcmp(argv[1], "-i") != 0)
    // {
    //     cout << "########## ERROR WITH PARSING input file ##########" << endl;
    //     return 0;
    // }

    // if (strcmp(argv[3], "-c") != 0)
    // {
    //     cout << "########## ERROR WITH PARSING config file ##########" << endl;
    //     return 0;
    // }

    string inputFile, configFile;

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-i")
        {                                                                           //then we know that inputFile is next
            cout << "Loading Input File..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "inputfile")
            {
                inputFile = argv[i+1];
                cout << "########### Successfully Loaded Input File ###########" << endl;
            }
            else
            {
                if(argc <= i+1){
                    cout << "########### Expected Input File Not Given ###########" << endl;
                }
                else if (string(argv[i + 1]) != "inputfile"){
                    if (string(argv[i + 1]) == "-c"){
                        cout << "########### Expected Input File Not Given ###########" << endl;
                    }
                    else
                    {
                        cout << "########### Wrong Input File Given ###########" << endl;
                    }
                }else
                {
                    cout << "########### Unknown Error With Input File ###########" << endl;
                }
            }
        }
        else if (string(argv[i]) == "-c")
        {                                                                           //then we know that configFile is next
            cout << "Loading Config..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "configfile")
            {
                inputFile = argv[i+1];
                cout << "########### Successfully Loaded Config File ###########" << endl;
            }
            else
            {
                if (argc <= i + 1)
                {
                    cout << "########### Expected Config File Not Given ###########" << endl;
                }
                else if (string(argv[i + 1]) != "configfile")
                {
                    cout << "########### Wrong Config File Given ###########" << endl;
                }
                else
                {
                    cout << "########### Unknown Error With Config File ###########" << endl;
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
}