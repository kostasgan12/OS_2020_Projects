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

    switch (veg1)
    {
    case 1:
        if (veg2 == 2)
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "onion";
            break;
        }
        else
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "pepper";
            break;
        }
    case 2:
        if (veg2 == 1)
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "onion";
        }
        else
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "tomato";
        }
    case 3:
        if (veg2 == 1)
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "pepper";
        }
        else
        {
            if (pickedVegArray[0] == "0")
            {
                pos = 0;
            }
            else
            {
                pos = 1;
            }
            pickedVegArray[pos] = "tomato";
        }
    default:
        break;
    }
    return *pickedVegArray;
}
