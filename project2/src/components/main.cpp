#include "../header_files/main.h"

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    int lowestNumToCheck = 0;
    int upperNumToCheck = 0;
    int numOfChildren = 0;

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-l")
        { //then we know that lowerValue is next
            if( i+1<argc && isNumeric(argv[i+1]) ){
                lowestNumToCheck = stoi(argv[i+1]);
                // cout << "Lowest Value Is:\t"<<argv[i+1] << endl;
            }
        }
        else if (string(argv[i]) == "-u")
        { //then we know that upperValue is next
            if( i+1<argc && isNumeric(argv[i+1]) ){
                upperNumToCheck = stoi(argv[i+1]);
            }
        }
        else if (string(argv[i]) == "-w")
        { //then we know that NumOfChildren is next
            if( i+1<argc && isNumeric(argv[i+1]) ){
                numOfChildren = stoi(argv[i+1]);
            }
        }
        else
        {   
            if(!strcmp(argv[i-1], "-l") && !strcmp(argv[i-1], "-u") && !strcmp(argv[i-1], "-w")  ){
                cout << "########### Unrecognised Flag ###########\n"<< endl;
            }
            else if (!isNumeric(argv[i])){
                string msg = "";
                if(strcmp(argv[i-1], "-l") == 0){
                    cout << "###########\tLowest Value\tIs Not Numeric:\t '"<< argv[i] <<"' ###########\n"<< endl;
                    cout << "###########\tEnter Valid Lowest Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "###########\tWRONG!\tEnter Valid Lowest Value: ";
                        cin >> temp;
                    }
                    lowestNumToCheck = stoi(temp);
                }else if(strcmp(argv[i-1], "-u") == 0){
                    cout << "###########\tUpper Value\tIs Not Numeric:\t '"<< argv[i] <<"' ###########\n"<< endl;
                    cout << "###########\tEnter Valid Upper Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "###########\tWRONG!\tEnter Valid Upper Value: ";
                        cin >> temp;
                    }
                    upperNumToCheck = stoi(temp);
                }else if(strcmp(argv[i-1], "-w") == 0){
                    cout << "###########\tNumber Of Children Value\tIs Not Numeric:\t '"<< argv[i] <<"' ###########\n"<< endl;
                    cout << "###########\tEnter Valid Number Of Children Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "###########\tWRONG!\tEnter Valid Number Of Children Value: ";
                        cin >> temp;
                    }
                    numOfChildren = stoi(temp);
                }else{
                    continue;
                }
            }
            else{
                continue;
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    return 0;
}