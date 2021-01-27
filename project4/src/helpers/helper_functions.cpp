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

void travelDir(char *currentDir, char *targetFolder)
{ 
    DIR *dp, *target_dp;
    struct dirent *dir, *target_dir;
    char *newSourcePath;
    char *newTargetPath;
    char *deletionFile;
    struct stat statbuf;
    char actualpath [PATH_MAX+1];
    char *pathPtr;

    char *srcFileName, *targetFileName;

    struct stat sourceFileStatBuff;
    struct stat targetFileStatBuff;

    //open current directory
    if ((dp=opendir(currentDir))== NULL ) { 
        perror("opendir"); 

        return;
    }else{
        //read every item in directory
        while ((dir = readdir(dp)) != NULL ) {
            //if deleted, continue
            if (dir->d_ino == 0 ){
                printf("deleted\n");
                continue;
            }else{
                //skip .. and . entities
                if((strcmp(dir->d_name, "..") != 0) && strcmp(dir->d_name, ".") != 0){
                    totalEntitiesInHierarchy++;
                    //change path to item path. e.g. source_dir -> source_dir/item1
                    newSourcePath=(char *)malloc(strlen(currentDir)+strlen(dir->d_name)+2); 
                    strcpy(newSourcePath ,currentDir);
                    strcat(newSourcePath ,"/");
                    strcat(newSourcePath,dir->d_name);
                    
                    //get absolute path
                    pathPtr = realpath(newSourcePath, actualpath);
                    
                    //get item stat
                    if(stat(pathPtr, &statbuf) == -1){
                        perror("Failed to get file status");
                        free(newSourcePath); 
                        newSourcePath=NULL;
                        return;
                    }

                    //set target folder path, according tou our depth. e.g. source_dir/item1 -> dest_dir/item1
                    newTargetPath=(char *)malloc(strlen(targetFolder)+strlen(currentDir)+3); 
                    strcpy(newTargetPath, targetFolder);
                    strcat(newTargetPath, "/");
                    strcat(newTargetPath, dir->d_name);

                    //if normal file
                    if ((statbuf.st_mode & S_IFMT) == S_IFREG ){
                        // if(ctime(&statbuf.st_mtime))
                        copyFile(dir->d_name, currentDir, targetFolder);
                    }

                    //if current item is a directory
                    if ((statbuf.st_mode & S_IFMT) == S_IFDIR ){
                        //we want to carry on searching in this new directory
                        //new directory has currentDir -> newSourcePath e.g. source_dir/item1
                        //and target folder -> dest_dir/item1

                        //check if this path exists in target before travelling further down
                        if(doesPathExist(newSourcePath, newTargetPath) == 0)
                        {
                            if(verbose){
                                cout<<"path for :\t"<<dir->d_name<<"\tdoesn't exist, so we create one."<<endl;
                            }
                            mkdir(newTargetPath, 0700);
                            totalEntitiesCopied++;
                        }
                        travelDir(newSourcePath, newTargetPath);
                    }
                    
                    free(newTargetPath); 
                    newTargetPath=NULL;
                    // printout(pathPtr);
                    free(newSourcePath); 
                    newSourcePath=NULL;
                }
            }
        }

        closedir(dp); 
    }

    int found = 0;
    //open target directory
    if ((target_dp=opendir(targetFolder))== NULL ) { 
        perror("target opendir"); 

        return;
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
                    // cout<<"looking for:\t"<<target_dir->d_name<<"\t in:\t"<<targetFolder<<endl;
                    found = 0;

                    //open source directory
                    if ((dp=opendir(currentDir))== NULL ) { 
                        perror("source seccond opendir"); 
                        closedir(target_dp); 
                        return;
                    }else{
                        //loop source dir
                        while ((dir = readdir(dp)) != NULL ) {
                            //if deleted, continue
                            if (dir->d_ino == 0 ){
                                printf("deleted\n");
                                continue;
                            }else{
                                //skip .. and . entities
                                if((strcmp(dir->d_name, "..") != 0) && strcmp(dir->d_name, ".") != 0){
                                    //check if it exists in source folder
                                    if(stat(currentDir, &sourceFileStatBuff) == 0){
                                        if(strcmp(target_dir->d_name, dir->d_name) == 0){
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
                            
                            deletionFile=(char *)malloc(strlen(targetFolder)+strlen(target_dir->d_name)+3); 
                            strcpy(deletionFile, targetFolder);
                            strcat(deletionFile, "/");
                            strcat(deletionFile,target_dir->d_name);
                
                            if(remove(deletionFile)){
                                perror("deletion error");
                            }

                            free(deletionFile); 
                            deletionFile=NULL;
                        }

                        closedir(dp); 
                    }
                }
            }
        }

        closedir(target_dp); 
    }
    return;
}

void copyFile(char *fileName, char *sourceDirectory, char *targetDirectory){
    char ch;
    FILE *source_file_ptr, *target_file_ptr;
    char *srcFileName, *targetFileName;
    char buffer[512];
    size_t bytes;
    struct stat sourceFileStatBuff;
    struct stat targetFileStatBuff;

    srcFileName=(char *)malloc(strlen(sourceDirectory)+strlen(fileName)+3);
    targetFileName=(char *)malloc(strlen(targetDirectory)+strlen(fileName)+3);

    strcpy(srcFileName, sourceDirectory);
    strcat(srcFileName, "/");
    strcat(srcFileName, fileName);

    strcpy(targetFileName, targetDirectory);
    strcat(targetFileName, "/");
    strcat(targetFileName, fileName);

    if(stat(srcFileName, &sourceFileStatBuff) == -1){
        printf("Cannot get stat\n");
        free(srcFileName);
        free(targetFileName);
        exit(0);
    }
    //get item stat
    if(stat(targetFileName, &targetFileStatBuff) == 0){
        //compare times
        if(sourceFileStatBuff.st_mtime <= targetFileStatBuff.st_mtime){
            if(verbose){
                cout<<"file :\t"<<fileName<<"\t,has not been modified, so we do not overwrite it."<<endl;
            }
            free(srcFileName);
            free(targetFileName);
            return;
        }
    }
    if(verbose){
        cout<<"file :\t"<<fileName<<"\t,has  been modified, so we will overwrite it."<<endl;
    }

    // Open one file for reading
    source_file_ptr = fopen(srcFileName, "r");
    if (source_file_ptr == NULL){
        printf("Cannot open file %s \n", srcFileName);
        free(srcFileName);
        free(targetFileName);
        exit(0);
    }

    // Open another file for writing
    target_file_ptr = fopen(targetFileName, "w+");
    if (target_file_ptr == NULL){
        printf("Cannot open file %s \n", targetFileName);
        free(srcFileName);
        free(targetFileName);
        exit(0);
    }

    while ((bytes = fread(buffer, 1, 512, source_file_ptr)) != 0) {
        if(fwrite(buffer, 1, bytes, target_file_ptr) != bytes) {
            fclose(source_file_ptr);
            fclose(target_file_ptr);
            free(srcFileName);
            free(targetFileName);
            
            return;
        }
        totalBytesCopied += sizeof(bytes);
    }

    totalEntitiesCopied++;

    fclose(source_file_ptr);
    fclose(target_file_ptr);
    free(srcFileName);
    free(targetFileName);
    
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

int doesPathExist(char *source_path, char *dest_path){
    struct stat statbuf;

    if(stat(dest_path, &statbuf) == -1){
        //path doesnt exist
        return 0;
    }
    return 1;
}

int doesEntryExist(char* fileName, char *inLocation){
    struct stat statbuf;

    if(stat(inLocation, &statbuf) == -1){
        //path doesnt exist
        return 0;
    }
    return 1;
}