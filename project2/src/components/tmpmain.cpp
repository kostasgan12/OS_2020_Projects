#include "../header_files/main.h"

int lowestNumToCheck = 0;
int upperNumToCheck = 0;
int numOfChildren = 0;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

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
            //check whether we previous argument to i, was Not a valide flag
            if(!strcmp(argv[i-1], "-l") && !strcmp(argv[i-1], "-u") && !strcmp(argv[i-1], "-w")  ){
                cout << "########### Unrecognised Flag ###########\n"<< endl;
            }
            //initially check whether i argument is a valid numeric
            else if (!isNumeric(argv[i])){
                string msg = "";
                if(strcmp(argv[i-1], "-l") == 0){
                    cout << "\n\tLowest Value\tIs Not Numeric:\t '"<< argv[i] <<"'"<< endl;
                    cout << "\tEnter Valid Lowest Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "\tWRONG!\tEnter Valid Lowest Value: ";
                        cin >> temp;
                    }
                    lowestNumToCheck = stoi(temp);
                }else if(strcmp(argv[i-1], "-u") == 0){
                    cout << "\n\tUpper Value\tIs Not Numeric:\t '"<< argv[i] <<"'"<< endl;
                    cout << "\tEnter Valid Upper Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "\tWRONG!\tEnter Valid Upper Value: ";
                        cin >> temp;
                    }
                    upperNumToCheck = stoi(temp);
                }else if(strcmp(argv[i-1], "-w") == 0){
                    cout << "\n\tNumber Of Children Value\tIs Not Numeric:\t '"<< argv[i] <<"'"<< endl;
                    cout << "\tEnter Valid Number Of Children Value: ";
                    string temp;
                    cin >> temp;
                    while ( !isNumeric(temp) ) {
                        cout << "\tWRONG!\tEnter Valid Number Of Children Value: ";
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

    if (lowestNumToCheck > upperNumToCheck){
        int swapTemp = lowestNumToCheck;
        lowestNumToCheck = upperNumToCheck;
        upperNumToCheck = swapTemp;

        cout << "\n\tSwapped Lowest & Upper Value Because, Lowest Was Greater\n"<<endl;
        cout << "\tLowest: " << lowestNumToCheck << "\t&\tUpper: " << upperNumToCheck << "\n"<< endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////


    int** childrenRangeValues = new int*[numOfChildren];
    for(int i = 0; i < numOfChildren; ++i)
        childrenRangeValues[i] = new int[2];

    calculateChildrenAllocation(childrenRangeValues, numOfChildren, lowestNumToCheck, upperNumToCheck);

    for (int i = 0; i < numOfChildren; i++)
    {
        cout << "\tIN MAIN\tchildrenRangeValues["<<i<<"] is:[" << childrenRangeValues[i][0]<< ","<<childrenRangeValues[i][1]<<"]"<<endl;
    }

    // int totalGrandchildren = pow(numOfChildren, 2.0);

    // int** grandchildrenRangeValues = new int*[totalGrandchildren];   //total of leaf nodes in our tree are numOfChildren ^ 2
    // for(int i = 0; i < totalGrandchildren; ++i){
    //     grandchildrenRangeValues[i] = new int[2];
    // }

    // for(int i = 0; i < numOfChildren; i++){
    //     cout << "\tallocating grandchildren for range:\t is:[" << childrenRangeValues[i][0]<< ","<<childrenRangeValues[i][1]<<"]"<<endl;
    //     calculateGrandchildrenAllocation(grandchildrenRangeValues, totalGrandchildren, childrenRangeValues[i][0], childrenRangeValues[i][1]);
    // }

    // for (int i = 0; i < totalGrandchildren; i++)
    // {
    //     cout << "\tIN MAIN\tgrandchildrenRangeValues["<<i<<"] is:[" << grandchildrenRangeValues[i][0]<< ","<<grandchildrenRangeValues[i][1]<<"]"<<endl;
    // }




    for (int i = 0; i < numOfChildren; i++) // loop to create numOfChildren number of children for  level 1
    {
        //forking root into numOfChildren children processes
        pid_t pid = fork();
        if (pid < 0){
            cout << "Root Fork Failed!"<<endl;
            return 1;
        }

        if (pid == 0)   //children
        {
            cout << "\tChild -- > pid = " << getpid() << " and ppid = " << getppid() << "\n"
                << endl;
            // for (int y = 0; y < numOfChildren; y++) //loop to create numOfChildren number of grandchildren for  level 2
            // {
            //     //forking children into numOfChildren grandchildren processes
            //     pid_t child_pid = fork();
            //     if (child_pid < 0)
            //     {
            //         cout << "Child Fork Failed!" << endl;
            //         return 1;
            //     }
            //     if (child_pid == 0) //grandchildren
            //     {
            //         cout << "\tGrandchild -- > pid = " << getpid() << " and ppid = " << getppid() << "\n"
            //              << endl;
            //         exit(0);
            //     }
            // }

            // const char *argv[] = { "ls", "-a", nullptr };
            // myExecvp(argv[0], argv);

            string programName = "ls";
            string arg1 = "-lh";
            string arg2 = "/home";
            
            execlp(programName, programName, arg1, arg2, NULL);

            exit(0);
        }
    }

    // for (int i = 0; i < numOfChildren * numOfChildren; i++) // loop will run numOfChildren*numOfChildren times
    for (int i = 0; i < numOfChildren ; i++) // loop will run numOfChildren times
    wait(NULL);

    return 0;
}