#include "../header_files/child_main.h"

int numOfGrandChilds;
int lowestValue;
int upperValue;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    // cout << "in CHILD CHILD CHILD process!!!! with pid:\t"<<getpid()<<endl;

    numOfGrandChilds = stoi(argv[1]);
    lowestValue = stoi(argv[2]);
    upperValue = stoi(argv[3]);

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    int** grandchildsRangeValues = new int*[numOfGrandChilds];
    for(int i = 0; i < numOfGrandChilds; ++i)
        grandchildsRangeValues[i] = new int[2];

    calculateChildrenAllocation(grandchildsRangeValues, numOfGrandChilds, lowestValue, upperValue);

    string grandChildLowestArg, grandChildUpperArg;

    for (int i = 0; i < numOfGrandChilds; i++) // loop to create numOfGrandChilds number of GRANDchildren for  level 2
    {
        //forking root into numOfGrandChilds GRANDchildren processes
        pid_t pid = fork();
        if (pid < 0){
            cout << "Root Fork Failed!"<<endl;
            return 1;
        }

        if (pid == 0)   //GRANDchildren
        {
            cout << "in Grandchild process!!!! with pid:\t"<<getpid()<<endl;

            grandChildLowestArg = to_string(grandchildsRangeValues[i][0]);    //copy lowest value for argument purposes
            grandChildUpperArg = to_string(grandchildsRangeValues[i][1]); //copy upper value for argument purposes
            grandchildsRangeValues[i][0] = 0;  //make them 0 for signaling purposes
            grandchildsRangeValues[i][1] = 0;  //make them 0 for signaling purposes
            
            char const * programName = "./grandchild_program";  
            char const * arg1 = grandChildLowestArg.c_str();
            char const * arg2 = grandChildUpperArg.c_str();

            execlp(programName, programName, arg1, arg2, NULL);
            exit(0);
        }
        wait(NULL);
    }

    
    return 0;
}