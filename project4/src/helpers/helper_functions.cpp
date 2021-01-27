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

void travelDir(char *name, char *targetFolder)
{ 
    DIR *dp;
    struct dirent *dir; 
    char *newPathName;
    char *innerTargetPath;
    struct stat statbuf;
    char actualpath [PATH_MAX+1];
    char *pathPtr;

    if ((dp=opendir(name))== NULL ) { 
        perror("opendir"); 

        return;
    }else{
        while ((dir = readdir(dp)) != NULL ) {
            if (dir->d_ino == 0 ){
                continue;
            }else{
                if((strcmp(dir->d_name, "..") != 0) && strcmp(dir->d_name, ".") != 0){
                    newPathName=(char *)malloc(strlen(name)+strlen(dir->d_name)+2); 
                    strcpy(newPathName ,name);
                    strcat(newPathName ,"/");
                    strcat(newPathName,dir->d_name);
                    
                    pathPtr = realpath(newPathName, actualpath);
                    // cout<<"pathPtr:\t"<<pathPtr<<endl;
                    
                    if(stat(pathPtr, &statbuf) == -1){
                        perror("Failed to get file status");
                        return;
                    }

                    // cout<<"targetFolder:\t"<<targetFolder<<endl;
                    // cout<<"dir->d_name:\t"<<dir->d_name<<endl;
                    innerTargetPath=(char *)malloc(strlen(targetFolder)+strlen(name)+3); 
                    strcpy(innerTargetPath, targetFolder);
                    strcat(innerTargetPath, "/");
                    strcat(innerTargetPath, dir->d_name);

                    if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
                        // printf("This is a directory\n");
                        
                        cout<<"pathPtr for travelling...:\t"<<newPathName<<endl;
                        travelDir(newPathName, innerTargetPath);
                        
                        // copyFile(name, targetFolder);

                    }

                    if ((statbuf.st_mode & S_IFMT) == S_IFREG ){
                        // printf("This is a regular file\n");
                        copyFile(name, targetFolder);
                    }
                    
                    free(innerTargetPath); 
                    innerTargetPath=NULL;
                    // printout(pathPtr);
                    free(newPathName); 
                    newPathName=NULL;
                }
            }
        }

        closedir(dp); 
    }
    return;
}

void copyFile(char *fileName, char *targetDirectory){
    DIR *dp;
    struct dirent *dir; char *newname;
    
    struct stat statbuf;
    char actualpath [PATH_MAX+1];
    char *targetPathPointer;

    targetPathPointer = realpath(targetDirectory, actualpath);

    char oldPath[100];
    char newPath[100];

    cout<<"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    //set current path so we can change back
    getcwd(oldPath, 100);

    // if ((dp=opendir(name))== NULL ) { 
    //     perror("opendir"); 
    //     return;
    // }

    // cout<<"targetDirectory:\t"<<targetDirectory<<endl;

    if(stat(targetPathPointer, &statbuf) == -1){
        // cout<<"making new folder at: \t"<<targetDirectory<<endl;

        mkdir(targetDirectory, 0700);
    }

    //change to destination folder
    // if(chdir(targetPathPointer)){
    //     perror("changing dir");
    // }else{
    //     printf("path after\t%s\n", getcwd(newPath, 100)); 

    //     //change back to source folder
    // }
    chdir(targetPathPointer);
    // printf("path after\t%s\n", getcwd(newPath, 100)); 
    chdir(oldPath);

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