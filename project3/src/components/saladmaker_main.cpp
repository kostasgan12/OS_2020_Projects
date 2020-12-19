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

    // int jj ;
    // sem_getvalue(&salad_table_buffer->saladmaker_3_muting, &jj);
    // cout << "salad_table_buffer->saladmaker_3_muting:\t" << jj << endl;
    
    // int chefMute;
    // sem_getvalue(&salad_table_buffer->chef_muting, &chefMute);
    // cout << "salad_table_buffer->chef_muting:\t" << chefMute << endl;

    // int occupiedSem;
    // sem_getvalue(&salad_table_buffer->occupied, &occupiedSem);
    // cout << "salad_table_buffer->occupied:\t" << occupiedSem << endl;

    // cout << "salad_table_buffer->next_in:\t" << salad_table_buffer->next_in << endl;

    //////////////////////////////////////////////////////////////////////////
    /////////////////////// B U S I N E S S  L O G I C ///////////////////////
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    ////////////////// S E M A P H O R E S  H A N D L E R S //////////////////
    //////////////////////////////////////////////////////////////////////////

    // sem_wait(&salad_table_buffer->occupied);
    cout<<"passed occupied wait"<<endl;
    sem_wait(&salad_table_buffer->saladmaker_3_muting);
    
    int saladmaker3;
    sem_getvalue(&salad_table_buffer->saladmaker_3_muting, &saladmaker3);

    cout << "passed saladmaker_3_muting wait!!!   saladmaker3:\t" << saladmaker3 << endl;

    item = salad_table_buffer->offered_vegetable[salad_table_buffer->next_out];
    salad_table_buffer->next_out++;
    salad_table_buffer->next_out %= BFSIZE;

    // if (missingVegetable == "tomato")
    // {
        
    // }
    // else if (missingVegetable == "pepper")
    // {
    // }
    // if (missingVegetable == "onion"){

    // }else{

    // }

    sem_post(&salad_table_buffer->chef_muting);

    // sem_post(&salad_table_buffer->empty);
    
    /* Remove segment . */
    err = shmdt((void *)salad_table_buffer);
    if (err == -1)
        perror(" Detachment . ");
    return 0;
}