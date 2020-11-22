#include "../header_files/main.h"

int lowestNumToCheck = 0;
int upperNumToCheck = 0;
int numOfChildren = 0;

#define root_child_fifo "root_child_fifo"

#define MSGSIZE 65

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    int fdChildParent;
    mknod(root_child_fifo, S_IFIFO | 0640, 0);

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

    string childLowestArg, childUpperArg;
    string numOfChildrenArg = to_string(numOfChildren);

    for (int i = 0; i < numOfChildren; i++) // loop to create numOfChildren number of children for  level 1
    {
        //forking root into numOfChildren children processes
        pid_t pid = fork();
        if (pid < 0){
            cout << "Root Fork Failed!"<<endl;
            return 1;
        }

        if ((fdChildParent = open(root_child_fifo, O_RDONLY | O_NDELAY)) < 0)
        {
            perror("root fifo open problem");
            exit(3);
        }

        if (pid == 0)   //children
        {
            childLowestArg = to_string(childrenRangeValues[i][0]);    //copy lowest value for argument purposes
            childUpperArg = to_string(childrenRangeValues[i][1]); //copy upper value for argument purposes
            childrenRangeValues[i][0] = 0;  //make them 0 for signaling purposes
            childrenRangeValues[i][1] = 0;  //make them 0 for signaling purposes
            
            char const * programName = "./child_program";  
            char const * arg1 = numOfChildrenArg.c_str();
            char const * arg2 = childLowestArg.c_str();
            char const * arg3 = childUpperArg.c_str();

            execlp(programName, programName, arg1, arg2, arg3, NULL);
            exit(0);
        }
        wait(NULL);
    }

    char childMessageBuffer[MSGSIZE + 1];

    string stringConvertedPrimeArray[numOfChildren];
    
    int k = 0;
    int rootPrimesCounter = 0;
    while (k < numOfChildren)
    {
        read(fdChildParent, childMessageBuffer, MSGSIZE + 1);

        stringConvertedPrimeArray[k] = convertToString(childMessageBuffer, strlen(childMessageBuffer));

        // REMINDER FIRST VALUE OF PIPE ARRAY IS THE TOTAL PRIMES THAT LEAF NODE HAS FOUND
        rootPrimesCounter = rootPrimesCounter + extractNumOfPrimes(stringConvertedPrimeArray[k]);

        k++;
    }
    close(fdChildParent);


    int intConvertedPrimeArray[rootPrimesCounter];

    k = 0;
    int arrayIndex;
    int intArrayIndex = 0;
    while (k < numOfChildren)
    {
        arrayIndex = 0;
        while (stringConvertedPrimeArray[k][arrayIndex] != ' ')
        {
            arrayIndex++;
        }

        string s = "";
        for (int i = 0; i < extractNumOfPrimes(stringConvertedPrimeArray[k]); i++)
        {
            s = "";
            arrayIndex++;
            while (stringConvertedPrimeArray[k][arrayIndex] != ' ')
            {
                s = s + stringConvertedPrimeArray[k][arrayIndex];
                // s.push_back(stringConvertedPrimeArray[k][arrayIndex]);
                arrayIndex++;
            }
            s.push_back('\0');
            intConvertedPrimeArray[intArrayIndex] = stoi(s);
            intArrayIndex++;
        }
        k++;
    }

    cout << "For The Given Range: [" << lowestNumToCheck << "," << upperNumToCheck << "]:\t" << rootPrimesCounter << " Primes Were Found."<< endl;

    int l = 0;
    while (l < rootPrimesCounter)
    {
        cout << intConvertedPrimeArray[l]<<endl;
        l++;
    }



    return 0;
}