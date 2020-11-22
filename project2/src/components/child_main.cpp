#include "../header_files/child_main.h"

int numOfGrandChilds;
int lowestValue;
int upperValue;

#define MSGSIZE 65
#define fifo "child_grandchild_fifo"
#define root_child_fifo "root_child_fifo"

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    int fd, nwrite;

    mknod(fifo, S_IFIFO | 0640, 0);

    numOfGrandChilds = stoi(argv[1]);
    lowestValue = stoi(argv[2]);
    upperValue = stoi(argv[3]);

    int *childPrimeArray = NULL;  // Pointer to int, initialize to nothing.
    

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


        if ((fd = open(fifo, O_RDONLY | O_NDELAY)) < 0)
        {
            perror("fifo open problem");
            exit(3);
        }

        if (pid == 0)   //GRANDchildren
        {
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

    char array1[MSGSIZE + 1];

    string stringConvertedPrimeArray[numOfGrandChilds];

    int k = 0;
    int childPrimesCounter = 0;
    while (k < numOfGrandChilds)
    {
        read(fd, array1, MSGSIZE + 1);

        stringConvertedPrimeArray[k] =  convertToString(array1, strlen(array1));

        // REMINDER FIRST VALUE OF PIPE ARRAY IS THE TOTAL PRIMES THAT LEAF NODE HAS FOUND
        childPrimesCounter = childPrimesCounter + extractNumOfPrimes(stringConvertedPrimeArray[k]);  

        k++;
    }
    close(fd);

    int intConvertedPrimeArray[childPrimesCounter];

    k = 0;
    int arrayIndex;
    int intArrayIndex = 0;
    while (k < numOfGrandChilds)
    {
        arrayIndex = 0;
        while(stringConvertedPrimeArray[k][arrayIndex] != ' '){
            arrayIndex++;
        }

        string s = "";
        for(int i=0; i< extractNumOfPrimes(stringConvertedPrimeArray[k]); i++){
            s = "";
            arrayIndex++;
            while(stringConvertedPrimeArray[k][arrayIndex] != ' '){
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





    char const *childNumOfPrimesAsChar;
    string childNumOfPrimes;

    childNumOfPrimes = to_string(childPrimesCounter);
    childNumOfPrimesAsChar = childNumOfPrimes.c_str();

    char childMessageBuffer[MSGSIZE+1];
    // strncpy(childMessageBuffer, "primes ", sizeof("primes "));
    strncpy(childMessageBuffer, childNumOfPrimesAsChar, sizeof(childNumOfPrimes));


    char const *ourNumAsChar ;
    string primeToAppend; 
    int counter = 0;
    while(counter < childPrimesCounter)
    {
        primeToAppend = to_string(intConvertedPrimeArray[counter]);
        ourNumAsChar = primeToAppend.c_str();
  
        strncat(childMessageBuffer, " ", (sizeof(childMessageBuffer) - strlen(", ") - 1));
        strncat(childMessageBuffer, ourNumAsChar, (sizeof(childMessageBuffer) - strlen(ourNumAsChar) - 1));
        counter++;
    }

    // cout << childMessageBuffer << endl;

    int fdChildParent;

    if ((fdChildParent = open(root_child_fifo, O_CREAT | O_WRONLY)) < 0)
    {
        cout << "File Open Error" << endl;
    }

    write(fdChildParent, childMessageBuffer, MSGSIZE + 1);
    close(fdChildParent);
    exit(0);

    return 0;
}