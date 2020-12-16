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

    int id, err;

    /* Make shared memory segment */
    id = shmget(IPC_PRIVATE, SEGMENTSIZE, SEGMENTPERM);
    if (id == -1)
    {
        perror("Creation");
    }
    else
    {
        printf("Allocated %d\n", id);
    }


    sem_t *tomato_sp;
    sem_t *pepper_sp;
    sem_t *onion_sp;

    int tomato_retval;
    int pepper_retval;
    int onion_retval;

    /* Attach tomato_sp the segment. */
    tomato_sp = (sem_t *) shmat(id,(void*) 0, 0);
    if ( tomato_sp == (void *) -1) {
        perror("Attachment."); 
        exit(2);
    }

    /* Initialize tomato_sp the semaphore. */
    tomato_retval = sem_init(tomato_sp,1,2); 
    if (tomato_retval != 0) {
        perror("Couldn’t initialize."); 
        exit(3);
    }

    /* Attach pepper_sp the segment. */
    pepper_sp = (sem_t *)shmat(id,(void*) sizeof(sem_t), 0);
    if (pepper_sp == (void *)-1)
    {
        perror("Attachment.");
        exit(2);
    }

    /* Initialize pepper_sp the semaphore. */
    pepper_retval = sem_init(pepper_sp, 1, 2);
    if (pepper_retval != 0)
    {
        perror("Couldn’t initialize.");
        exit(3);
    }

    /* Attach onion_sp the segment. */
    onion_sp = (sem_t *)shmat(id, (void *) (2*sizeof(sem_t)), 0);
    if (onion_sp == (void *)-1)
    {
        perror("Attachment.");
        exit(2);
    }

    /* Initialize onion_sp the semaphore. */
    onion_retval = sem_init(onion_sp, 1, 2);
    if (onion_retval != 0)
    {
        perror("Couldn’t initialize.");
        exit(3);
    }

    tomato_retval = sem_trywait(tomato_sp);
    printf(" Did trywait . Returned % d >\n ", tomato_retval);
    getchar();

    tomato_retval = sem_trywait(tomato_sp);
    printf(" Did trywait . Returned % d >\n ", tomato_retval);
    getchar();

    tomato_retval = sem_trywait(tomato_sp);
    printf(" Did trywait . Returned % d >\n ", tomato_retval);
    getchar();

    sem_destroy(tomato_sp);
    sem_destroy(pepper_sp);
    sem_destroy(onion_sp);

    /* Remove segment. */
    err = shmctl(id, IPC_RMID , 0);
    if (err == -1) {
        perror("Removal.");
    } else{
        printf("Removed. %d\n",err);
    }
    return 0;
}