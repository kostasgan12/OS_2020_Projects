#include "../header_files/saladmaker_main.h"

int lowerTimeValue = 0;
int upperTimeValue = 0;
int sharedMemoryId = 0;
string missingVegetable;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-t1")
        { //then we know that lowerTimeValue is next
            if (i + 1 < argc && isNumeric(argv[i + 1]))
            {
                lowerTimeValue = stoi(argv[i + 1]);
            }
        }
        else if (string(argv[i]) == "-t2")
        { //then we know that upperTimeValue is next
            if (i + 1 < argc && isNumeric(argv[i + 1]))
            {
                upperTimeValue = stoi(argv[i + 1]);
            }
        }
        else if (string(argv[i]) == "-s")
        { //then we know that shared memory sharedMemoryId flag is next
            if (i + 1 < argc && isNumeric(argv[i + 1]))
            {
                sharedMemoryId = stoi(argv[i + 1]);
            }
        }
        else if (string(argv[i]) == "-v")
        { //then we know that missing vegetable is next
            if (i + 1 < argc && argv[i + 1])
            {
                missingVegetable = argv[i + 1];
            }
        }
        else
        {
            //check whether the previous argument to i, was Not a valid flag
            if (!strcmp(argv[i - 1], "-t1") && !strcmp(argv[i - 1], "-t2") && !strcmp(argv[i - 1], "-s"))
            {
                cout << "########### Unrecognised Flag ###########\n"
                     << endl;
            }
            else if (!isNumeric(argv[i])) //initially check whether i argument is a valid numeric
            {
                string msg = "";
                if (strcmp(argv[i - 1], "-t1") == 0)
                {
                    cout << "\n\tlowerTimeValue\tIs Not Numeric:\t '" << argv[i] << "'" << endl;
                    cout << "\tEnter Valid lowerTimeValue: ";
                    string temp;
                    cin >> temp;
                    while (!isNumeric(temp))
                    {
                        cout << "\tWRONG!\tEnter Valid lowerTimeValue: ";
                        cin >> temp;
                    }
                    lowerTimeValue = stoi(temp);
                }
                else if (strcmp(argv[i - 1], "-t2") == 0)
                {
                    cout << "\n\tupperTimeValue\tIs Not Numeric:\t '" << argv[i] << "'" << endl;
                    cout << "\tEnter Valid upperTimeValue: ";
                    string temp;
                    cin >> temp;
                    while (!isNumeric(temp))
                    {
                        cout << "\tWRONG!\tEnter Valid upperTimeValue: ";
                        cin >> temp;
                    }
                    upperTimeValue = stoi(temp);
                }
                else if (strcmp(argv[i - 1], "-s") == 0)
                {
                    cout << "\n\tsharedMemoryId\tIs Not Numeric:\t '" << argv[i] << "'" << endl;
                    cout << "\tEnter Valid sharedMemoryId: ";
                    string temp;
                    cin >> temp;
                    while (!isNumeric(temp))
                    {
                        cout << "\tWRONG!\tEnter Valid sharedMemoryId: ";
                        cin >> temp;
                    }
                    sharedMemoryId = stoi(temp);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }

    string temp;
    if (lowerTimeValue == 0)
    {
        cout << "\n\tlowerTimeValue\tIs:\t" << lowerTimeValue << endl;
        cout << "\tEnter Valid lowerTimeValue ( > 0): ";
        temp = "";
        cin >> temp;
        while (!isNumeric(temp))
        {
            cout << "\tWRONG!\tEnter Valid lowerTimeValue: ";
            cin >> temp;
        }
        lowerTimeValue = stoi(temp);
    }
    // cout << "\n\tlowerTimeValue\tIs:\t" << lowerTimeValue << endl;

    if (upperTimeValue == 0)
    {
        cout << "\n\tupperTimeValue\tIs:\t" << upperTimeValue << endl;
        cout << "\tEnter Valid upperTimeValue ( > 0): ";
        temp = "";
        cin >> temp;
        while (!isNumeric(temp))
        {
            cout << "\tWRONG!\tEnter Valid upperTimeValue: ";
            cin >> temp;
        }
        upperTimeValue = stoi(temp);
    }

    // cout << "\n\tupperTimeValue\tIs:\t" << upperTimeValue << endl;

    if (sharedMemoryId == 0)
    {
        cout << "\n\t!!ERROR!!\tsharedMemoryId\tIs:\t" << sharedMemoryId << endl;
        exit(-1);
    }

    // cout << "\n\tsharedMemoryId\tIs:\t" << sharedMemoryId << endl;
    cout << "\n\tmissing Vegetable\tIs:\t" << missingVegetable << endl;
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////// L O G  F I L E  H A N D L E R S ///////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////


    FILE *logFile;
    string fileName; 
    int processId;

    FILE *combinedLogFile;
    string combinedFileName = "combinedLogFile.log";
    

    if (strcmp(missingVegetable.c_str(), "tomato") == 0)
    {
        fileName = "tomatoLogFile.log";
        processId = 2;
    }
    else if (strcmp(missingVegetable.c_str(), "pepper") == 0)
    {
        fileName = "pepperLogFile.log";
        processId = 3;
    }
    else if (strcmp(missingVegetable.c_str(), "onion") == 0)
    {
        fileName = "onionLogFile.log";
        processId = 4;
    }
    else
    {
        cout << "Error Creating Vegetable" << endl;
    }

    logFile = fopen(fileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (logFile == NULL) cout<<"Error Creating Log File"<<endl;

    fprintf(logFile, "\t##################################################\n\tInitialized Log File For %s Work Flow...\n\t##################################################\n\n", missingVegetable.c_str());
    fclose(logFile);
    //////////////////////////////////////////////////////////////////////////////////////

    char item;
    salad_table_buffer_t *salad_table_buffer;
    int retval; 
    int err;
    
    salad_table_buffer = (salad_table_buffer_t *)shmat(sharedMemoryId, (void *)0, 0);
    if (salad_table_buffer == (void *)-1)
    {
        perror("Attachment.");
        exit(2);
    }

    //////////////////////////////////////////////////////////////////////////
    ////////////////// S E M A P H O R E S  H A N D L E R S //////////////////
    //////////////////////////////////////////////////////////////////////////

    int workDurationTime = (rand() % (upperTimeValue - lowerTimeValue + 1)) + lowerTimeValue;
    cout << "workDurationTime:\t" << workDurationTime << endl;

    int isEmpty;
    sem_getvalue(&salad_table_buffer->empty, &isEmpty);

    int occupied;

    int runningFlag = true;
    while (isEmpty)
    {
        if(isEmpty == 0){
            cout<<"our table is empty so we exit while loop!"<<endl;
            break;
        }

        cout << "how many salads left??\t:" << isEmpty << endl;

        // logFile = fopen(fileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
        // if (logFile == NULL)
        //     cout << "Error Creating Log File" << endl;

        // combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
        // if (combinedLogFile == NULL)
        //     cout << "Error Creating Log File" << endl;

        if (strcmp(missingVegetable.c_str(), "tomato") == 0)
        {
            cout << "waiting for tomato call" << endl;
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);
            sem_wait(&salad_table_buffer->saladmaker_1_muting);
            
            sem_getvalue(&salad_table_buffer->occupied, &occupied);
            cout << "occupied\t:" << occupied << endl;

            sem_wait(&salad_table_buffer->occupied);
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);
            sem_post(&salad_table_buffer->chef_muting);
        }
        else if (strcmp(missingVegetable.c_str(), "pepper") == 0)
        {
            cout << "waiting for pepper call" << endl;
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);

            sem_wait(&salad_table_buffer->saladmaker_2_muting);
            
            sem_getvalue(&salad_table_buffer->occupied, &occupied);
            cout << "occupied\t:" << occupied << endl;

            sem_wait(&salad_table_buffer->occupied);
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);
            sem_post(&salad_table_buffer->chef_muting);
        }
        else if (strcmp(missingVegetable.c_str(), "onion") == 0)
        {
            cout << "waiting for onion call" << endl;
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Waiting For Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);
            sem_wait(&salad_table_buffer->saladmaker_3_muting);
            
            sem_getvalue(&salad_table_buffer->occupied, &occupied);
            cout << "occupied\t:" << occupied << endl;

            sem_wait(&salad_table_buffer->occupied);
            logFile = fopen(fileName.c_str(), "a+");
            combinedLogFile = fopen(combinedFileName.c_str(), "a+");
            fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Get Ingredient: %s]\n", processId, processId - 1, missingVegetable.c_str());
            fclose(logFile);
            fclose(combinedLogFile);
            sem_post(&salad_table_buffer->chef_muting);
        }
        else
        {
            cout<<"unknown Vegetable"<<endl;
            sem_post(&salad_table_buffer->chef_muting);
            break;
        }

        //////////////////////////////////////////////////////////////////////////
        /////////////////////// B U S I N E S S  L O G I C ///////////////////////
        //////////////////////////////////////////////////////////////////////////
        logFile = fopen(fileName.c_str(), "a+");
        combinedLogFile = fopen(combinedFileName.c_str(), "a+");
        fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Started Making Salad...]\n", processId, processId - 1);
        fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Started Making Salad...]\n", processId, processId - 1);
        fclose(logFile);
        fclose(combinedLogFile);
        
        sleep(workDurationTime);

        logFile = fopen(fileName.c_str(), "a+");
        combinedLogFile = fopen(combinedFileName.c_str(), "a+");
        fprintf(logFile, "\t[%d]\t[SaladMaker %d]\t[Finished Making Salad!]\n", processId, processId - 1);
        fprintf(combinedLogFile, "\t[%d]\t[SaladMaker %d]\t[Finished Making Salad!]\n", processId, processId - 1);
        fclose(logFile);
        fclose(combinedLogFile);
        //////////////////////////////////////////////////////////////////////////

        // sem_post(&salad_table_buffer->chef_muting);
        // sem_post(&salad_table_buffer->empty);
        sem_getvalue(&salad_table_buffer->empty, &isEmpty);
    }
    
    cout<<"out of that loop"<<endl;
    /* Remove segment . */
    err = shmdt((void *)salad_table_buffer);
    if (err == -1)
        perror(" Detachment . ");

    // fclose(logFile);
    return 0;
}