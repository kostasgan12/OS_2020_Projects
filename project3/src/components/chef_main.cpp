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

    salad_table_buffer_t *salad_table_buffer;

    salad_table_buffer = (salad_table_buffer_t *)shmat(id, (void *)0, 0);
    if (salad_table_buffer == (void *)-1)
    {
        perror("Attachment.");
        exit(2);
    }
    else
    {
        printf("table buffer attached ok!\n");
    }


    sem_init(&salad_table_buffer->occupied, 0, 0);
    sem_init(&salad_table_buffer->empty, 0, BFSIZE);
    sem_init(&salad_table_buffer->chef_muting, 0, 1);
    sem_init(&salad_table_buffer->saladmaker_1_muting, 0, 1);
    sem_init(&salad_table_buffer->saladmaker_2_Muting, 0, 1);
    sem_init(&salad_table_buffer->saladmaker_3_Muting, 0, 1);
    salad_table_buffer->next_in = salad_table_buffer->next_out = 0;
    
    int i=1;
    int random_vegetable_1, random_vegetable_2;
    int which_saladmaker;
    while (i <= numOfSlds)
    {
        sem_wait(&salad_table_buffer->empty);
        sem_wait(&salad_table_buffer->chef_muting);

        random_vegetable_1 = rand() % 3 + 1;
        random_vegetable_2 = rand() % 3 + 1;
        while (random_vegetable_2 == random_vegetable_1)
        {
            random_vegetable_2 = rand() % 3 + 1;
        }
        
        which_saladmaker = findSaladMaker(random_vegetable_1, random_vegetable_2);

        salad_table_buffer->offered_vegetable[salad_table_buffer->next_in] = which_saladmaker;
        salad_table_buffer->next_in++;
        salad_table_buffer->next_in %= BFSIZE;

        
        switch (which_saladmaker)
        {
        case 't':
            cout<<"in tomato switch block"<<endl;
            break;
        case 'p':
            cout << "in pepper switch block" << endl;
            break;
        case 'o':
            cout << "in onion switch block" << endl;
            break;
        default:
            cout << "in default switch block" << endl;
            break;
        }

        sem_post(&salad_table_buffer->chef_muting);
        sem_post(&salad_table_buffer->occupied);
        i++;
    }

    sem_destroy(&salad_table_buffer->occupied);
    sem_destroy(&salad_table_buffer->empty);
    sem_destroy(&salad_table_buffer->chef_muting);
    sem_destroy(&salad_table_buffer->saladmaker_1_muting);
    sem_destroy(&salad_table_buffer->saladmaker_2_Muting);
    sem_destroy(&salad_table_buffer->saladmaker_3_Muting);

    // sem_t *sp;

    // int retval;

    // /* Attach sp the segment. */
    // printf("semaphore addressfor tomato:\t%lu\n", 0);
    // sp = (sem_t *)shmat(id, (void *)0, 0);
    // if ( sp == (void *) -1) {
    //     perror("Attachment."); 
    //     exit(2);
    // }else{
    //     printf("tomato allocated ok!\n");
    // }

    // /* Initialize sp the semaphore. */
    // retval = sem_init(sp, 1, 2);
    // if (retval != 0)
    // {
    //     perror("Couldn’t initialize."); 
    //     exit(3);
    // }

    // retval = sem_trywait(sp);
    // printf(" Did trywait . Returned % d >\n ", retval);
    // getchar();

    // sem_destroy(sp);

    /* Remove segment. */
    err = shmctl(id, IPC_RMID , 0);
    if (err == -1) {
        perror("Removal.");
    } else{
        printf("Removed. %d\n",err);
    }
    return 0;
}