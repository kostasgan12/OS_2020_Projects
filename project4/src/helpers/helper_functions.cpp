#include "../header_files/helper_functions.h"

bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

void list(char *name)
{ 
    DIR *dp;
    struct dirent *dir; char *newname;

    if ((dp=opendir(name))== NULL ) { 
        perror("opendir"); 
        return;
    }

    while ((dir = readdir(dp)) != NULL ) {
        if (dir->d_ino == 0 ) continue;
        newname=(char *)malloc(strlen(name)+strlen(dir->d_name)+2); 
        strcpy(newname ,name);
        cout<<"newname after copying name:\t"<<newname<<endl;
        strcat(newname ,"/");
        cout<<"newname after copying /\t"<<newname<<endl;
        strcat(newname,dir->d_name);
        cout<<"newname after idr->d_name\t"<<newname<<endl;
        printout(newname);
        free(newname); 
        newname=NULL;
    }

    closedir(dp); 
}

void travelDir(char *name)
{ 
    DIR *dp;
    struct dirent *dir; char *newPathName;
    struct stat statbuf;
    char actualpath [PATH_MAX+1];
    char *pathPtr;
    
    cout<<"#############################################"<<endl;
    if ((dp=opendir(name))== NULL ) { 
        perror("opendir"); 

        return;
    }else{
        while ((dir = readdir(dp)) != NULL ) {
            // if(name[strlen(name)-1] == "." ){
            // if((strcmp(name, "..") != 0) && strcmp(name, ".") != 0){
            if (dir->d_ino == 0 ){
                continue;
            }else{
                if((strcmp(dir->d_name, "..") != 0) && strcmp(dir->d_name, ".") != 0){
                    newPathName=(char *)malloc(strlen(name)+strlen(dir->d_name)+2); 
                    strcpy(newPathName ,name);
                    strcat(newPathName ,"/");
                    strcat(newPathName,dir->d_name);

                    cout<<"newPathName\t"<<newPathName<<endl;
                    

                    pathPtr = realpath(newPathName, actualpath);
                    cout<<"pathPtr:\t"<<pathPtr<<endl;
                    
                    if(stat(pathPtr, &statbuf) == -1){
                        perror("Failed to get file status");
                        return;
                    }

                    if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
                        printf("This is a directory\n");
                        travelDir(newPathName);
                    }

                    
                    // printout(pathPtr);
                    free(newPathName); 
                    newPathName=NULL;
                }
            }
        }

        closedir(dp); 
    }
    cout<<"#############################################"<<endl;
    return;
}



void printout(char *name){
    struct stat mybuf;

    stat(name, &mybuf);

    printf("Time/Date : %s",ctime(&mybuf.st_atime)); 
    printf("---------------------------------\n"); 
    printf("entity name: %s\n",name);
    printf("accessed : %s", ctime(&mybuf.st_atime)+4);
    printf("modified : %s", ctime(&mybuf.st_mtime));
}