#include "../header_files/saladmaker_helper_functions.h"

bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

string convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
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
