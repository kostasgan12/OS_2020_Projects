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
    
    // travelDir(source_dir_name, dest_dir_name);


    DIR *source_directory_pointer, *target_dp;
    struct dirent *direntp, *target_dir;
    struct stat statbuf;
    char *newSourcePath;
    char *newTargetPath;
    char actualpath [PATH_MAX+1];
    char *pathPtr;

    char oldPath[100];
    char newPath[100];

    char *srcFileName, *targetFileName;

    struct stat sourceFileStatBuff;
    struct stat targetFileStatBuff;

    if ( ( source_directory_pointer = opendir ( source_dir_name ) ) == NULL ) {
        fprintf ( stderr , "cannot open %s \n" , source_dir_name ) ;
    }

    //in given source directory
    //loop every item in here, directories and other types
    while ( ( direntp = readdir ( source_directory_pointer ) ) != NULL ){
        if((strcmp(direntp->d_name, "..") != 0) && strcmp(direntp->d_name, ".") != 0){
            
            // printf ("\n\ninode %d of the entry %s\n" ,  ( int ) direntp->d_ino , direntp->d_name );
            
            //set path from source_dir to source_dir/item
            newSourcePath=(char *)malloc(strlen(source_dir_name)+strlen(direntp->d_name)+3); 
            strcpy(newSourcePath, source_dir_name);
            strcat(newSourcePath, "/");
            strcat(newSourcePath,direntp->d_name);

            //set path for target folder
            newTargetPath=(char *)malloc(strlen(dest_dir_name)+strlen(direntp->d_name)+3); 
            strcpy(newTargetPath, dest_dir_name);
            strcat(newTargetPath, "/");
            strcat(newTargetPath,direntp->d_name); 

            //get absolute path
            pathPtr = realpath(newSourcePath, actualpath);   

            //get status
            if(stat(pathPtr, &statbuf) == -1){
                perror("Failed to get file status");
                free(newSourcePath); 
                newSourcePath=NULL;
                continue;
            }
            
            //check whether item is normal file
            if ((statbuf.st_mode & S_IFMT) == S_IFREG ){
                copyFile(direntp->d_name, source_dir_name, dest_dir_name);
            }

            //check whether item is a directory
            if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
                if(doesPathExist(newSourcePath, newTargetPath)){
                    cout<<"path:"<<newTargetPath<< " exists!"<<endl;
                }else{
                    cout<<"path:"<<newTargetPath<< " does NOT exist!"<<endl;
                    mkdir(newTargetPath, 0700);
                }
                //first we check the contents of the folder
                travelDir(pathPtr, newTargetPath);
            }

            free(newSourcePath); 
            newSourcePath=NULL;
            free(newTargetPath); 
            newTargetPath=NULL;
        }
    }

    if(closedir(source_directory_pointer) == -1){
        fprintf ( stderr , "cannot close %s \n" , source_dir_name ) ;
    }

    int found = 0;
    //open target directory
    if ((target_dp=opendir(dest_dir_name))== NULL ) { 
        perror("target opendir"); 

        return -1;
    }else{
        //for every item in target dir we want to check if it exists in source dir
        while ((target_dir = readdir(target_dp)) != NULL ) {
            //if deleted, continue
            if (target_dir->d_ino == 0 ){
                printf("\n\n\ndeleted\n");
                continue;
            }else{
                //skip .. and . entities
                if((strcmp(target_dir->d_name, "..") != 0) && strcmp(target_dir->d_name, ".") != 0){
                    cout<<"looking for:\t"<<target_dir->d_name<<"\t in:\t"<<dest_dir_name<<endl;
                    found = 0;

                    //open source directory
                    if ((source_directory_pointer=opendir(source_dir_name))== NULL ) { 
                        perror("source seccond opendir"); 
                        closedir(target_dp); 
                        return -1;
                    }else{
                        //loop source dir
                        while ((direntp = readdir(source_directory_pointer)) != NULL ) {
                            //if deleted, continue
                            if (direntp->d_ino == 0 ){
                                printf("deleted\n");
                                continue;
                            }else{
                                //skip .. and . entities
                                if((strcmp(direntp->d_name, "..") != 0) && strcmp(direntp->d_name, ".") != 0){
                                    //check if it exists in source folder
                                    if(stat(source_dir_name, &sourceFileStatBuff) == 0){
                                        if(strcmp(target_dir->d_name, direntp->d_name) == 0){
                                            // cout<<"entry: "<<target_dir->d_name<<" exists -->:\t"<<dir->d_name<<endl;
                                            //NOW WE FOUND A DELETED ONE WE MUST DELETE IT FROM TARGET DIR
                                            found++;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        if(found == 0){
                            cout<<"couldnt find entry:\t"<<target_dir->d_name<<endl;
                        }

                        closedir(source_directory_pointer); 
                    }
                }
            }
        }

        closedir(target_dp); 
    }

    return 0;
}