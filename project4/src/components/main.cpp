#include "../header_files/main.h"

int verbose = 0;
int verifyDeleted = 0;
int considerLinks = 0;

int main(int argc, char *argv[])
{

    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    string optionFlag;

    for (int i = 0; i < argc; i++)
    {
        optionFlag = argv[i];
        if (optionFlag == "-v")
        { //verbose option, if it exist then we print program procedure info
            verbose = 1;
        }
        else if (optionFlag== "-d")
        {   //deleted option, if it exist then,
            //we should make sure deleted files in A get deleted in B
            verifyDeleted = 1;
        }
        else if (optionFlag == "-l")
        {   //consider links option, if it exist then,
            //our program should consider possible links
            considerLinks = 1;
        }
    }
    
    if (verbose)
    {
        cout << "\tVerbose Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerbose Mode: OFF"<< endl;
    }

    if (verifyDeleted)
    {
        verifyDeleted = 1;
        cout << "\tVerify Deletion Mode: ON"<< endl;
    }
    else
    {
        cout << "\tVerify Deletion Mode: OFF"<< endl;
    }

    if (considerLinks)
    {
        considerLinks = 1;
        cout << "\tConsider Links Mode: ON\n"<< endl;
    }
    else
    {
        cout << "\tConsider Links Mode: OFF\n"<< endl;
    }

    char source_dir_name[256]; 
    char dest_dir_name[256];
    // string source_dir_name, dest_dir_name;

    if((verbose + verifyDeleted + considerLinks == 0 )&& argc > 2){
        strcpy(source_dir_name, argv[1]);
        strcpy(dest_dir_name, argv[2]);
        // source_dir_name = argv[1];
        // dest_dir_name = argv[2];
    }else if((verbose + verifyDeleted + considerLinks == 1) && argc > 3){
        strcpy(source_dir_name, argv[2]);
        strcpy(dest_dir_name, argv[3]);
        // source_dir_name = argv[2];
        // dest_dir_name = argv[3];
    }else if((verbose + verifyDeleted + considerLinks == 2 )&& argc > 4){
        strcpy(source_dir_name, argv[3]);
        strcpy(dest_dir_name, argv[4]);
        // source_dir_name = argv[3];
        // dest_dir_name = argv[4];
    }else if((verbose + verifyDeleted + considerLinks == 3 )&& argc == 6){
        strcpy(source_dir_name, argv[4]);
        strcpy(dest_dir_name, argv[5]);
        // source_dir_name = argv[4];
        // dest_dir_name = argv[5];
    }else{
        cout<<"ERROR PARSING PATHS"<<endl;
        exit(-1);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    DIR *source_directory_pointer;
    struct dirent *direntp;
    struct stat statbuf;
    char *newPathName;
    char actualpath [PATH_MAX+1];
    char *pathPtr;

    // cout<<"source_dir_name:\t"<<source_dir_name<<endl;
    // if(stat(source_dir_name, &statbuf) == -1){
    //     perror("Failed to get source_dir_name file status");
    //     return -1;
    // }
    // if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
    //     printf("source_dir_name is a directory\n");
    // }

    if ( ( source_directory_pointer = opendir ( source_dir_name ) ) == NULL ) {
        fprintf ( stderr , "cannot open %s \n" , source_dir_name ) ;
    }

    while ( ( direntp = readdir ( source_directory_pointer ) ) != NULL ){
        if((strcmp(direntp->d_name, "..") != 0) && strcmp(direntp->d_name, ".") != 0){
            
            printf ("\ninode %d of the entry %s\n" ,  ( int ) direntp->d_ino , direntp->d_name );
            newPathName=(char *)malloc(strlen(source_dir_name)+strlen(direntp->d_name)+3); 
            strcpy(newPathName, source_dir_name);
            strcat(newPathName, "/");
            strcat(newPathName,direntp->d_name);

            pathPtr = realpath(newPathName, actualpath);
            cout<<"pathPtr:\t"<<pathPtr<<endl;
                    

            if(stat(pathPtr, &statbuf) == -1){
                perror("Failed to get file status");
                free(newPathName); 
                newPathName=NULL;
                continue;
            }
            
            if ((statbuf.st_mode & S_IFMT) == S_IFREG ){
                printf("This is a regular file\n");
            }

            if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
                printf("This is a directory\n");
                travelDir(pathPtr);
            }

            free(newPathName); 
            newPathName=NULL;
        }
    }

    if(closedir(source_directory_pointer) == -1){
        fprintf ( stderr , "cannot close %s \n" , source_dir_name ) ;
    }

    return 0;
}