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

void sortArray(float * givenArray){
    int arraySize = 0;
    while (givenArray[arraySize] != -1)
    {
        arraySize++;
    }

    int i, j, min;
    float temp;
    for (i = 0; i < arraySize - 1; i++)
    {
        min = i;
        for (j = i + 1; j < arraySize; j++)
            if (givenArray[j] < givenArray[min])
                min = j;
        temp = givenArray[i];
        givenArray[i] = givenArray[min];
        givenArray[min] = temp;
    }
}