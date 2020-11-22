#include "../header_files/grandchild_main.h"

int lowestValue;
int upperValue;
int numOfValues;

// #define WRITE readPipeFD[1]
// #define READ readPipeFD[0]

#define MSGSIZE 65
// int MSGSIZE;

#define fifo "child_grandchild_fifo"
// char const *fifo = "child_grandchild_fifo";

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    // cout << "in Grandchild process!!!! with pid:\t"<<getpid()<<endl;

    lowestValue = stoi(argv[1]);
    upperValue = stoi(argv[2]);
    numOfValues = upperValue - lowestValue + 1;
    // MSGSIZE = numOfValues;
        //////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////
    int *primesFound = new int[numOfValues];
    for (int i = 0; i < numOfValues; ++i)
        primesFound[i] = 0 ;    //initiallizing with 0

    bool isPrime;
    for(int i = lowestValue; i <= upperValue; i++){
        isPrime = isPrime_1(i);
        if(isPrime > 0) {
            addToPrimeArray(primesFound, i);
        }
    }

    int primeCounter = 0;
    while (primesFound[primeCounter] != 0)
    {
        // cout << "primesFound[" << primeCounter << "] is:\t" << primesFound[primeCounter] << endl;
        primeCounter++;
    }

    char const *ourNumAsChar ;

    char array1[MSGSIZE+1];
    strncpy(array1, "primes ", sizeof("primes "));

    string primeToAppend; 
    primeCounter = 0;
    while (primesFound[primeCounter] != 0){
        primeToAppend = to_string(primesFound[primeCounter]);
        ourNumAsChar = primeToAppend.c_str();
        if (primeCounter != 0){
            strncat(array1, " ", (sizeof(array1) - strlen(", ") - 1));
        }
        strncat(array1, ourNumAsChar, (sizeof(array1) - strlen(ourNumAsChar) - 1));
        primeCounter++;
    }
    cout << array1 << endl;


    // int readPipeFD[2], writePipeFD[2];;
    // string writeMessage[20] = "Hi";
    // string readMessage[20];

    // if (pipe(readPipeFD) == -1)
    // {
    //     cout<<"Pipe Failed"<<endl;;
    //     return 1;
    // }

    // if (pipe(writePipeFD) == -1)
    // {
    //     cout<<"Pipe Failed"<<endl;;
    //     return 1;
    // }



    int fd, i, nwrite;
    char msgbuf[MSGSIZE + 1];

    if ((fd = open(fifo, O_CREAT | O_WRONLY )) < 0)
    {
        cout<<"File Open Error"<<endl;
    }

    write(fd, array1, MSGSIZE + 1);
    // write(fd, " ti les ", MSGSIZE + 1);
    close(fd);
    // unlink(fifo);
    exit(0);

    return 0;
}