#include "helper_functions.h"

int transform_id(string id)
{
    int formatted_key;
    string buffer;

    for (char &c : id)
    {
        if(isdigit(c)){
            buffer += c;
        }
    }

    formatted_key = stoi(buffer);

    return formatted_key;
}

// void sortArray(int givenArray[]){
//     int arraySize = 0;
//     while (givenArray[arraySize] != NULL)
//     {
//         arraySize++;
//     }

//     int i, j, min, temp;
//     for (i = 0; i < arraySize - 1; i++)
//     {
//         min = i;
//         for (j = i + 1; j < n; j++)
//             if (givenArray[j] < givenArray[min])
//                 min = j;
//         temp = givenArray[i];
//         givenArray[i] = givenArray[min];
//         givenArray[min] = temp;
//     }
// }