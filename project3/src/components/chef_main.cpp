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

    sem_t *sp; 
    int retval; 
    int id, err;

    id = shmget(IPC_PRIVATE, SEGMENTSIZE, SEGMENTPERM); /* Make shared memory segment */
    if (id ==  -1) {
        perror("Creation");
    }else{
        printf("Allocated %d\n", id);
    }

    /* Attach the segment. */
    sp = (sem_t *) shmat(id,(void*) 0, 0);
    if ( sp == (void *) -1) {
        perror("Attachment."); 
        exit(2);
    }

     /* Initialize the semaphore. */
    retval = sem_init(sp,1,2); if (retval != 0) {
        perror("Couldn’t initialize."); 
        exit(3);
    }

    retval = sem_trywait(sp);
    printf("Did trywait. Returned %d >\n", retval); getchar();

    retval = sem_trywait(sp);
    printf("Did trywait. Returned %d >\n", retval); getchar();

    retval = sem_trywait(sp);
    printf("Did trywait. Returned %d >\n", retval); getchar();

    sem_destroy(sp);

    /* Remove segment. */
    err = shmctl(id, IPC_RMID , 0);
    if (err == -1) {
        perror("Removal.");
    } else{
        printf("Removed. %d\n",err);
    }
    return 0;
}