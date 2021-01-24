#include "../header_files/chef_helper_functions.h"

bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

char findSaladMaker(int veg1, int veg2){
    switch (veg1)
    {
        case 1:
            if(veg2 == 2){
                return 'o';
            }else{
                return 'p';
            }
        case 2:
            if (veg2 == 1)
            {
                return 'o';
            }
            else
            {
                return 't';
            }
        case 3:
            if (veg2 == 1)
            {
                return 'p';
            }
            else
            {
                return 't';
            }
        default:
            break;
    }
    return 0;
}

string findPickedVeg(int veg1, int veg2)
{
    string pickedVegArray[2];
    pickedVegArray[0] = "0";
    pickedVegArray[1] = "0"; 
    int pos;

    if(veg1 == 1)
    {
        pickedVegArray[0] = "tomato";
    }
    else if( veg1 == 2)
    {
        pickedVegArray[0] = "pepper";
    }
    else
    {
        pickedVegArray[0] = "onion";
    }

    if (veg2 == 1)
    {
        pickedVegArray[1] = "tomato";
    }
    else if (veg2 == 2)
    {
        pickedVegArray[1] = "pepper";
    }
    else
    {
        pickedVegArray[1] = "onion";
    }

    return *pickedVegArray;
}

string getCurrentTime(time_t setTime, timeval setMilSec)
{
    struct tm *ptm;
    ptm = gmtime(&setTime);

    int start_hour = (ptm->tm_hour + 2) % 24;
    int start_min = ptm->tm_min;
    int start_sec = (ptm->tm_sec) % 60;
    long start_mil_sec = setMilSec.tv_usec % 100;
    // if(start_mil_sec > 59){
    //     start_mil_sec = start_mil_sec % 60;
    //     ++start_sec;
    //     cout<<"helo"<<endl;
    // }

    string stringTime = "";
    stringTime += to_string(start_hour) + ":" + to_string(start_min) + ":" + to_string(start_sec) + ":" + to_string(start_mil_sec);

    return stringTime;
}
