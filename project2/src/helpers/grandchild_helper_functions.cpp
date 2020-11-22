#include "../header_files/grandchild_helper_functions.h"

#define YES true 
#define NO false

bool isPrime_1(int n){ 
    int i;
    if (n==1) return(NO); 
    for (i=2 ; i<n ; i++)
        if ( n % i == 0) return(NO); 
    return(YES);
}

bool isPrime_2(int n){
    int i=0, limitup=0;
    limitup = (int)(sqrt((float)n));
    if (n==1) return(NO);
    for (i=2 ; i <= limitup ; i++)
        if ( n % i == 0) return(NO); 
    return(YES);
}