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