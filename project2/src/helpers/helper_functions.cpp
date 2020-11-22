#include "../header_files/helper_functions.h"

bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

void calculateChildrenAllocation(int **  valuesRangeArray, int arraySize, int lowestValue, int upperValue){

    // cout << "lowestValue is:\t" << lowestValue << "\tupperValue is:\t" << upperValue<< endl;

    int rangeSize = upperValue - lowestValue + 1;
    int individualRangeSize = rangeSize / numOfChildren;
    // cout << "rangeSize is:\t" << rangeSize << endl;
    // cout << "individualRangeSize is:\t" << individualRangeSize << endl;

    int tmpLowest = lowestValue;
    int tmpUpper = upperValue;

    if (individualRangeSize < 1)
    {
        cout << "rangeSize / numOfChildren is:\t" << individualRangeSize << " so each child will get either 1 or 0 values to check." << endl;
    }
    // else
    // {
    //     cout << "individualRangeSize is:\t" << individualRangeSize << endl;
    // }

    int remainder = 0;

    if (rangeSize % numOfChildren == 0)
    {
        // cout << "rangeSize: " << rangeSize << " can be divided equally." << endl;
        for (int i = 0; i < numOfChildren; i++)
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
        remainder = rangeSize % numOfChildren;
        cout << "remainder is: " << remainder << endl;
        for (int i = 0; i < numOfChildren; i++)
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


void calculateGrandchildrenAllocation(int **  valuesRangeArray, int arraySize, int lowestValue, int upperValue){

    // cout << "lowestValue is:\t" << lowestValue << "\tupperValue is:\t" << upperValue<< endl;

    int rangeSize = upperValue - lowestValue + 1;
    int individualRangeSize = rangeSize / numOfChildren;
    // cout << "rangeSize is:\t" << rangeSize << endl;

    int tmpLowest = lowestValue;
    int tmpUpper = upperValue;

    if (individualRangeSize < 1)
    {
        cout << "rangeSize / numOfChildren is:\t" << individualRangeSize << " so each child will get either 1 or 0 values to check." << endl;
    }
    // else
    // {
    //     cout << "individualRangeSize is:\t" << individualRangeSize << endl;
    // }

    // int remainder = 0;

    // if (rangeSize % numOfChildren == 0)
    // {
    //     // cout << "rangeSize: " << rangeSize << " can be divided equally." << endl;
    //     for (int i = 0; i < numOfChildren; i++)
    //     {
    //         valuesRangeArray[i][0] = tmpLowest;
    //         valuesRangeArray[i][1] = tmpLowest + individualRangeSize - 1;
    //         cout << "MIN value to check is:\t" << tmpLowest << endl;
    //         cout << "MAX value to check is:\t" << tmpLowest + individualRangeSize - 1 << endl;
    //         tmpLowest = tmpLowest + individualRangeSize;
    //     }
    // }
    // else
    // {
    //     remainder = rangeSize % numOfChildren;
    //     cout << "remainder is: " << remainder << endl;
    //     for (int i = 0; i < numOfChildren; i++)
    //     {
    //         if (remainder > 0)
    //         {
    //             valuesRangeArray[i][0] = tmpLowest;
    //             valuesRangeArray[i][1] = tmpLowest + individualRangeSize;
    //             cout << "remainder is:\t" << remainder << endl;
    //             remainder--;

                
    //             cout << "MIN value to check is:\t" << valuesRangeArray[i][0] << endl;
    //             cout << "MAX value to check is:\t" << valuesRangeArray[i][1] << endl;
    //             tmpLowest = tmpLowest + individualRangeSize + 1;
    //         }
    //         else
    //         {
    //             valuesRangeArray[i][0] = individualRangeSize;

    //             valuesRangeArray[i][0] = tmpLowest;
    //             valuesRangeArray[i][1] = tmpLowest + individualRangeSize - 1;

    //             cout << "MIN value to check is:\t" << valuesRangeArray[i][0] << endl;
    //             cout << "MAX value to check is:\t" << valuesRangeArray[i][1] << endl;
    //             tmpLowest = tmpLowest + individualRangeSize;
    //         }
    //     }
    // }
}


// template <size_t N>
// int myExecvp(const char* file, const char* const (&argv)[N])
// {
//   assert((N > 0) && (argv[N - 1] == nullptr));

//   return execvp(file, const_cast<char* const*>(argv));
// }

// int myExecvp(const char *file, const char *const argv[])
// {
//     size_t argc = 0;
//     size_t len = 0;

//     /* measure the inputs */
//     for (auto *p = argv;  *p;  ++p) {
//         ++argc;
//         len += strlen(*p) + 1;
//     }
//     /* allocate copies */
//     auto const arg_string = make_unique<char[]>(len);
//     auto const args = make_unique<char*[]>(argc+1);
//     /* copy the inputs */
//     len = 0;                    // re-use for position in arg_string
//     for (auto i = 0u;  i < argc;  ++i) {
//         len += strlen(args[i] = strcpy(&arg_string[len], argv[i]))
//             + 1; /* advance to one AFTER the nul */
//     }
//     args[argc] = nullptr;
//     return execvp(file, args.get());
// }

