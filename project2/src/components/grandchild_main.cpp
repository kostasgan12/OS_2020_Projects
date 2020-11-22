#include "../header_files/grandchild_main.h"

int lowestValue;
int upperValue;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    cout << "in Grandchild process!!!! with pid:\t"<<getpid()<<endl;

    lowestValue = stoi(argv[1]);
    upperValue = stoi(argv[2]);

    // cout<<"\t lowestValue in GRAND CHILD program:\t"<<lowestValue<<endl;
    // cout<<"\t upperValue in GRAND CHILD program:\t"<<upperValue<<endl;

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    bool isPrime;
    for(int i = lowestValue; i <= upperValue; i++){
        isPrime = isPrime_1(i);
        if(isPrime > 0) {
            cout<<"\t"<<i<<"\tis prime!!!"<<endl;
        }
    }
    return 0;
}