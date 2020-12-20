#include "../header_files/chef_main.h"

int numOfSlds = 0;
int manTime = 0;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-n")
        { //then we know that Number Of Salads is next
            if (i + 1 < argc && isNumeric(argv[i + 1]))
            {
                numOfSlds = stoi(argv[i + 1]);
                cout << "numOfSlds Is:\t" << numOfSlds << endl;
            }
        }
        else if (string(argv[i]) == "-m")
        { //then we know that Chef Resting Time (manTime) is next
            if (i + 1 < argc && isNumeric(argv[i + 1]))
            {
                manTime = stoi(argv[i + 1]);
                cout << "manTime Is:\t" << manTime << endl;
            }
        }
        else
        {
            //check whether the previous argument to i, was Not a valid flag
            if (!strcmp(argv[i - 1], "-n") && !strcmp(argv[i - 1], "-m"))
            {
                cout << "########### Unrecognised Flag ###########\n"
                     << endl;
            }
            else if (!isNumeric(argv[i])) //initially check whether i argument is a valid numeric
            {
                string msg = "";
                if (strcmp(argv[i - 1], "-n") == 0)
                {
                    cout << "\n\tnumOfSlds\tIs Not Numeric:\t '" << argv[i] << "'" << endl;
                    cout << "\tEnter Valid numOfSlds: ";
                    string temp;
                    cin >> temp;
                    while (!isNumeric(temp))
                    {
                        cout << "\tWRONG!\tEnter Valid numOfSlds: ";
                        cin >> temp;
                    }
                    numOfSlds = stoi(temp);
                }
                else if (strcmp(argv[i - 1], "-m") == 0)
                {
                    cout << "\n\tmanTime\tIs Not Numeric:\t '" << argv[i] << "'" << endl;
                    cout << "\tEnter Valid manTime: ";
                    string temp;
                    cin >> temp;
                    while (!isNumeric(temp))
                    {
                        cout << "\tWRONG!\tEnter Valid manTime: ";
                        cin >> temp;
                    }
                    manTime = stoi(temp);
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
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
    FILE *combinedLogFile;
    string combinedFileName = "combinedLogFile.log";
    FILE *chefLogFile;
    string chefFileName  = "chefLogFile.log";

    combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (combinedLogFile == NULL)
        cout << "Error Creating Log File" << endl;

    fprintf(combinedLogFile, "\t######################################################\n\tInitialized Combined Log File For Program Work Flow...\n\t######################################################\n\n");
    fclose(combinedLogFile);


    int id, err;

    /* Make shared memory segment */
    id = shmget(IPC_PRIVATE, SEGMENTSIZE, 0666 | IPC_CREAT | IPC_EXCL);
    if (id == -1)
    {
        perror("Creation");
    }
    else
    {
        printf("Allocated %d\n", id);
    }

    salad_table_buffer_t *salad_table_buffer;

    salad_table_buffer = (salad_table_buffer_t *)shmat(id, (void *)0, 0);
    if (salad_table_buffer == (void *)-1)
    {
        perror("Attachment.");
        exit(2);
    }

    sem_init(&salad_table_buffer->occupied, 1, 0);
    sem_init(&salad_table_buffer->empty, 1, numOfSlds);
    sem_init(&salad_table_buffer->chef_muting, 1, 1);
    sem_init(&salad_table_buffer->saladmaker_1_muting, 1, 0);
    sem_init(&salad_table_buffer->saladmaker_2_muting, 1, 0);
    sem_init(&salad_table_buffer->saladmaker_3_muting, 1, 0);
    salad_table_buffer->next_in = salad_table_buffer->next_out = 5;
    
    int i=1;
    int random_vegetable_1, random_vegetable_2;
    int which_saladmaker;
    int chefMute;
    int isEmpty;
    sem_getvalue(&salad_table_buffer->empty, &isEmpty);

    string pickedVegArray[2];

    time_t currentTimeMain;
    struct timeval currentTimeMilliseconds;
    string currentTimeString;

    while (isEmpty)
    {
        sem_getvalue(&salad_table_buffer->empty, &isEmpty);
        cout<<"how many salads left??\t:"<<isEmpty<<endl;

        sem_wait(&salad_table_buffer->empty);
        sem_wait(&salad_table_buffer->chef_muting);

        //////////////////////////////////////////////////////////////////////////
        /////////////////////// B U S I N E S S  L O G I C ///////////////////////
        //////////////////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////
        /////// S E L E C T  V E G E T A B L E S ///////
        ////////////////////////////////////////////////
        random_vegetable_1 = rand() % 3 + 1;
        random_vegetable_2 = rand() % 3 + 1;
        while (random_vegetable_2 == random_vegetable_1)
        {
            random_vegetable_2 = rand() % 3 + 1;
        }
        if (random_vegetable_1 == 1)
        {
            pickedVegArray[0] = "tomato";
        }
        else if (random_vegetable_1 == 2)
        {
            pickedVegArray[0] = "pepper";
        }
        else
        {
            pickedVegArray[0] = "onion";
        }

        if (random_vegetable_2 == 1)
        {
            pickedVegArray[1] = "tomato";
        }
        else if (random_vegetable_2 == 2)
        {
            pickedVegArray[1] = "pepper";
        }
        else
        {
            pickedVegArray[1] = "onion";
        }

        combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
        time(&currentTimeMain);
        gettimeofday(&currentTimeMilliseconds, NULL);
        currentTimeString = getCurrentTime(currentTimeMain, currentTimeMilliseconds);
        fprintf(combinedLogFile, "\t[%s]\t[1]\t[Chef]\t[Selecting ingredients: [%s][%s]]\n", currentTimeString.c_str(), pickedVegArray[0].c_str(), pickedVegArray[1].c_str());
        fclose(combinedLogFile);
        which_saladmaker = findSaladMaker(random_vegetable_1, random_vegetable_2);
        ////////////////////////////////////////////////

        salad_table_buffer->offered_vegetable[salad_table_buffer->next_in] = which_saladmaker;
        salad_table_buffer->next_in++;
        salad_table_buffer->next_in %= BFSIZE;       //check whether it exceeds BFSIZE

        switch (which_saladmaker)
        {
            case 't':
                cout << "looking for a tomato..." << endl;
                sem_post(&salad_table_buffer->occupied);
                combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
                time(&currentTimeMain);
                gettimeofday(&currentTimeMilliseconds, NULL);
                currentTimeString = getCurrentTime(currentTimeMain, currentTimeMilliseconds);
                fprintf(combinedLogFile, "\t[%s]\t[1]\t[Chef]\t[Notify saladmaker: [1]]\n",currentTimeString.c_str());
                fclose(combinedLogFile);
                sem_post(&salad_table_buffer->saladmaker_1_muting);
                break;
            case 'p':
                cout << "looking for a pepper..." << endl;
                sem_post(&salad_table_buffer->occupied);
                combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
                time(&currentTimeMain);
                gettimeofday(&currentTimeMilliseconds, NULL);
                currentTimeString = getCurrentTime(currentTimeMain, currentTimeMilliseconds);
                fprintf(combinedLogFile, "\t[%s]\t[1]\t[Chef]\t[Notify saladmaker: [2]]\n",currentTimeString.c_str());
                fclose(combinedLogFile);
                sem_post(&salad_table_buffer->saladmaker_2_muting);
                break;
            case 'o':
                cout << "looking for an onion..." << endl;
                sem_post(&salad_table_buffer->occupied);
                combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
                time(&currentTimeMain);
                gettimeofday(&currentTimeMilliseconds, NULL);
                currentTimeString = getCurrentTime(currentTimeMain, currentTimeMilliseconds);
                fprintf(combinedLogFile, "\t[%s]\t[1]\t[Chef]\t[Notify saladmaker: [3]]\n",currentTimeString.c_str());
                fclose(combinedLogFile);
                sem_post(&salad_table_buffer->saladmaker_3_muting);
                break;
            default:
                cout << "in default switch block" << endl;
                break;
        }
        
        combinedLogFile = fopen(combinedFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
        time(&currentTimeMain);
        gettimeofday(&currentTimeMilliseconds, NULL);
        currentTimeString = getCurrentTime(currentTimeMain, currentTimeMilliseconds);
        fprintf(combinedLogFile, "\t[%s]\t[1]\t[Chef]\t[Man Time For Resting]\n",currentTimeString.c_str());
        fclose(combinedLogFile);
        sleep(manTime);
        
        sem_getvalue(&salad_table_buffer->empty, &isEmpty);
        // i++;
    }
    

    sem_destroy(&salad_table_buffer->occupied);
    sem_destroy(&salad_table_buffer->empty);
    sem_destroy(&salad_table_buffer->chef_muting);
    sem_destroy(&salad_table_buffer->saladmaker_1_muting);
    sem_destroy(&salad_table_buffer->saladmaker_2_muting);
    sem_destroy(&salad_table_buffer->saladmaker_3_muting);


    /* Remove segment. */
    err = shmctl(id, IPC_RMID , 0);
    if (err == -1) {
        perror("Removal.");
    } else{
        printf("Removed. %d\n",err);
    }

    

    chefLogFile = fopen(chefFileName.c_str(), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (chefLogFile == NULL)
        cout << "Error Creating Log File" << endl;

    fprintf(chefLogFile, "\t##################################################\n\tInitialized Log File For Chef's Work Flow...\n\t##################################################\n");
    
    
    fclose(chefLogFile);

    return 0;
}