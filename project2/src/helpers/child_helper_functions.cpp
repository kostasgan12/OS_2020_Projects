#include "../header_files/child_helper_functions.h"


bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

void calculateChildrenAllocation(int **  valuesRangeArray, int numOfGrandchilds, int lowestValue, int upperValue){

    // cout << "lowestValue is:\t" << lowestValue << "\tupperValue is:\t" << upperValue<< endl;

    int rangeSize = upperValue - lowestValue + 1;
    int individualRangeSize = rangeSize / numOfGrandchilds;
    // cout << "rangeSize is:\t" << rangeSize << endl;
    // cout << "individualRangeSize is:\t" << individualRangeSize << endl;

    int tmpLowest = lowestValue;
    int tmpUpper = upperValue;

    // if (individualRangeSize < 1)
    // {
    //     cout << "rangeSize / numOfGrandchilds is:\t" << individualRangeSize << " so each child will get either 1 or 0 values to check." << endl;
    // }
    // else
    // {
    //     cout << "individualRangeSize is:\t" << individualRangeSize << endl;
    // }

    int remainder = 0;

    if (rangeSize % numOfGrandchilds == 0)
    {
        // cout << "rangeSize: " << rangeSize << " can be divided equally." << endl;
        for (int i = 0; i < numOfGrandchilds; i++)
        {
            valuesRangeArray[i][0] = tmpLowest;
            valuesRangeArray[i][1] = tmpLowest + individualRangeSize - 1;
            // cout << "MIN value to check is:\t" << tmpLowest << endl;
            // cout << "MAX value to check is:\t" << tmpLowest + individualRangeSize - 1 << endl;
            tmpLowest = tmpLowest + individualRangeSize;
        }
    }
    else
    {
        remainder = rangeSize % numOfGrandchilds;
        // cout << "remainder is: " << remainder << endl;
        for (int i = 0; i < numOfGrandchilds; i++)
        {
            if (remainder > 0)
            {
                valuesRangeArray[i][0] = tmpLowest;
                valuesRangeArray[i][1] = tmpLowest + individualRangeSize;
                // cout << "remainder is:\t" << remainder << endl;
                remainder--;

                
                // cout << "MIN value to check is:\t" << valuesRangeArray[i][0] << endl;
                // cout << "MAX value to check is:\t" << valuesRangeArray[i][1] << endl;
                tmpLowest = tmpLowest + individualRangeSize + 1;
            }
            else
            {
                valuesRangeArray[i][0] = individualRangeSize;

                valuesRangeArray[i][0] = tmpLowest;
                valuesRangeArray[i][1] = tmpLowest + individualRangeSize - 1;

                // cout << "MIN value to check is:\t" << valuesRangeArray[i][0] << endl;
                // cout << "MAX value to check is:\t" << valuesRangeArray[i][1] << endl;
                tmpLowest = tmpLowest + individualRangeSize;
            }
        }
    }
}

string convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

int extractNumOfPrimes(string a) 
{ 
    int i = 0; 
    string s = ""; 

    while(a[i] != ' '){
        s = s + a[i]; 
        i++;
    }

    return stoi(s); 
} 