
#include "../../header_files/inverted_index.h"

InvertedIndexEntry::InvertedIndexEntry(int yearPassed)
    : 
        year(yearPassed),
        studentLocationP(NULL),
        nextInvIndexEntry(NULL)
    {}

InvertedIndexEntry::InvertedIndexEntry(int yearPassed, StudentHashTableEntry *studentPassed)
    : year(yearPassed),
        studentLocationP(studentPassed),
        nextInvIndexEntry(NULL)
{
        cout << "studentLocationP is ==>:\t" << studentLocationP << endl;
}


InvertedIndex::InvertedIndex()
{
    invertedIndex = new InvertedIndexEntry *[invertedTableSize];
    for (int i = 0; i < invertedTableSize; i++)
    {
        ;
        int _yearToBePassed = i + invertedStartYear;
        invertedIndex[i] = new InvertedIndexEntry(_yearToBePassed);
    }
}

void InvertedIndex::InsertStudentReference(int yearToBeInserted, StudentHashTableEntry *student)
{
    int yearPositionInIndexTable = yearToBeInserted - invertedStartYear;

    InvertedIndexEntry *p = NULL; //initialize p with NULL
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    //currentEntry when initialized, should point at an empty Entry, 
    //That only contains our Header Year, so we check if a next Entry Exists, 
    //which would mean there is a student entered.

    if (currentEntry->nextInvIndexEntry == NULL)   
    //table for this year hasnt got any student records 
    {
        cout<<"first element for year:\t"<<yearToBeInserted<<endl;
        currentEntry->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
        // cout << "student entered and currentEntry->nextInvIndexEntry is:\t" << currentEntry->nextInvIndexEntry->studentLocationP->studentData.getStudentLastName() << endl;
    }
    else
    //table for this year already has student records
    {
        p = currentEntry;
        currentEntry = currentEntry->nextInvIndexEntry;
        while (currentEntry != NULL)
        {
            cout << "space at:\t" << currentEntry->studentLocationP <<"\toccupied by:\t";
            cout << currentEntry->studentLocationP->studentData.getStudentLastName() << endl;
            
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;
        }

        p->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
    }
}

void InvertedIndex::DeleteStudentReference(int entryYear, string id)
{
    int yearPositionInIndexTable = entryYear - invertedStartYear;

    InvertedIndexEntry *p = NULL;
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    bool flag = false;

    cout << "\n########################################################################\n"
         << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL) //check if first entry of this position in the hashtable is null, if not then we can search for the item, if its there
    {
        while (currentEntry != NULL)
        {
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;


            if (currentEntry->studentLocationP->studentData.getStudentId() == id)
            {
                flag = true;
                break;
            }
        }
    }
    else
    {
        cout << "No Student found with id " << id << endl;
        return;
    }

    if (flag)
    {
        p->nextInvIndexEntry = currentEntry->nextInvIndexEntry;
        cout << "Student with id:\t" << id << "\t Successfully Removed Reference From Our Inverted Index Table" << endl;
    }
    else
    {
        cout << "No Student found with id " << id << endl;
    }
    delete currentEntry;
    cout << "\n########################################################################\n"
         << endl;
}

void InvertedIndex::FindActiveUsersInAcademicYear(int academicYear)
{
    int entryYearRetrieved = invertedEndYear - academicYear +1;
    int yearPositionInIndexTable = entryYearRetrieved - invertedStartYear;
    int counter = 0;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"<< endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            counter++;
            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    cout << counter << " Students Were Found Active In Their:\t" << academicYear<<"\tAcademic Year" << endl;
}

void InvertedIndex::FindNBestStudentsOfYear(int num, int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;
    int isArrayFilledCounter = 0;

    float bestNGPA[num];

    for (int i = 0; i < num; i++)
    {
        bestNGPA[i]=-1;
    }
    
    float tmpGPA = 0;
    bool flag=false;
    int innerStarterVal=0;
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"<< endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        // while (currentEntry != NULL)
        // {
        //     //looping over every item in given year

        //     // isArrayFilledCounter++;
        //     tmpGPA = currentEntry->studentLocationP->studentData.getStudentLessonAverage();
            
        //     for (int i = 0; i < num; i++)
        //     {
        //         //for every item in the given year, we now loop over every item in our bestGPA array
                
        //         if (tmpGPA > bestNGPA[i] && bestNGPA[i + 1] != -1)
        //         {
        //             cout << "in first if " << "\ttmpGPA is:\t" << tmpGPA << endl;
        //             flag = false;

        //             if(num - isArrayFilledCounter >=0){
        //                 innerStarterVal = num - isArrayFilledCounter;
        //             }
        //             for (int j = innerStarterVal; j < num; j++)
        //             {
        //                 cout << "Searching if "
        //                      << "\ttmpGPA:\t" << tmpGPA << "\t is a bigger GPA Than:\t" << bestNGPA[j] << endl;
        //                 if (bestNGPA[j] == tmpGPA){
        //                     flag = true;
        //                 }
        //             }
        //             // for (int j = 0; j <num; j++)
        //             // {
        //             //     //looping to see if we find duplicate GPA value. If so we flag it so that we dont save it again.
        //             //     cout << "Searching for an EQUAL GPA TO:\t" << tmpGPA << "\tbestNGPA["<<i<<"] is:\t" << bestNGPA[j] << "\n"
        //             //          << endl;
        //             //     if (bestNGPA[j] == tmpGPA)
        //             //     {
        //             //         flag = true;
        //             //     }
        //             // }
        //             if(!flag){
        //                 bestNGPA[i] = tmpGPA;
        //                 cout << "bestNGPA["<<i<<"]\t set to:\t" << bestNGPA[i] << endl;
        //             }
        //             break;
        //         }

        //         cout << "\ttmpGPA is:\t" << tmpGPA << "\tbestNGPA[" << i << "] is:\t" << bestNGPA[i] << endl;
        //     }
        //     isArrayFilledCounter++;
        //     currentEntry = currentEntry->nextInvIndexEntry;
        //     cout << "\n########################################################################\n" << endl;
        // }

        float minGPA = 10;
        int whileCounter =0;
        int isArrayFilledCounter = 0;
        while (currentEntry != NULL)
        {
            //looping over every item in given year

            // isArrayFilledCounter++;
            tmpGPA = currentEntry->studentLocationP->studentData.getStudentLessonAverage();
            // isArrayFilledCounter = 0;

            // whileCounter =0;
            cout << "isArrayFilledCounter is:\t" << isArrayFilledCounter << endl;

            if (isArrayFilledCounter < num)
            {
                if (tmpGPA < minGPA)
                {
                    minGPA = tmpGPA;
                }
                bestNGPA[isArrayFilledCounter] = tmpGPA;
                // isArrayFilledCounter++;
            }

            // while (whileCounter < num)
            // {
            //     if(tmpGPA < minGPA )
            //     {
            //         minGPA = tmpGPA;
            //         cout << "minGPA set as:\t" << tmpGPA << endl;
            //     }
            //     bestNGPA[whileCounter] = tmpGPA;

            //     cout << "bestNGPA[" << whileCounter << "] set as:\t" << tmpGPA << endl;
            //     whileCounter++;
            // }
            // isArrayFilledCounter= whileCounter;

            if (isArrayFilledCounter >= num)
            {
                cout<<"BestGPA Array is full, so now we check if any other tmpGPA is bigger than one of our current values\n"<<endl;
                
                for (int i = 0; i < num; i++)   //loopinh over bestGPA array sized num
                {
                    cout << "tmpGPA is:\t" << tmpGPA << "\tMIN is:\t" << minGPA<<"\n" << endl;
                    if (tmpGPA > minGPA && bestNGPA[i] == minGPA)
                    {
                        bestNGPA[i] = tmpGPA;
                        cout << "bestNGPA[" << i << "] set as:\t" << bestNGPA[i]<<"\n" << endl;

                        minGPA = bestNGPA[0];
                        for (int j = 1; j < num; j++)
                        {
                            if(bestNGPA[j]<minGPA){
                                cout<<"in min searchhhhhh bestNGPA["<<j<<"] is\t"<<bestNGPA[j]<<endl;
                                minGPA = tmpGPA;
                            }
                        }
                        cout << "\nminGPA set as:\t" << minGPA << endl;

                        break;
                    }
                }
            }

            cout << "\n\nbestNGPA[0] set as:\t" << bestNGPA[0] << endl;
            cout << "bestNGPA[1] set as:\t" << bestNGPA[1] << endl;
            cout << "bestNGPA[2] set as:\t" << bestNGPA[2] << endl;

            isArrayFilledCounter++;
            currentEntry = currentEntry->nextInvIndexEntry;
            cout << "\n########################################################################\n"
                 << endl;
        }
    }


    cout<<"best\t"<<num<<"\tGPAs,for year\t"<<yearRequested<<endl;

    float  __gpa;
    for (int i = 0; i < num; i++)
    {
        __gpa = 0;

        cout << bestNGPA[i] <<"\t";
        if (bestNGPA[i] != 0){

            currentEntry = invertedIndex[yearPositionInIndexTable]->nextInvIndexEntry;

            while (currentEntry != NULL)
            {
                __gpa = currentEntry->studentLocationP->studentData.getStudentLessonAverage();
                
                if (__gpa == bestNGPA[i]){
                    cout << currentEntry->studentLocationP->studentData.getStudentLastName() << "\t";
                }
                currentEntry = currentEntry->nextInvIndexEntry;
            }
            cout<<"\n";
        }
    }
}

void InvertedIndex::CountStudentsPerYear()
{
    int counter;
    InvertedIndexEntry *currentEntry;

    int yearSearching = 0;
    
    for (int i = 0; i < invertedTableSize; i++)
    {
        counter = 0;
            cout
        << "\n########################################################################\n"
        << endl;

        yearSearching = i + invertedStartYear;

        currentEntry = invertedIndex[i];

        currentEntry = currentEntry->nextInvIndexEntry;

        if (currentEntry != NULL)
        {
            while (currentEntry != NULL)
            {
                counter++;
                currentEntry = currentEntry->nextInvIndexEntry;
            }
            cout << yearSearching << ":\t" << counter << "\tStudents Were Found." << endl;
        }
        else
        {
            cout << yearSearching << ":\t" << "\tNo Students Were Found." << endl;
        }
    }
}

void InvertedIndex::ShowAllStudentsInYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"
         << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            cout << "found student with id:\t" << currentEntry->studentLocationP->studentData.getStudentId();
            cout << "\tand name:\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << "\t";
            cout << currentEntry->studentLocationP->studentData.getStudentFirstName()<<endl;

            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    else
    {
        cout << "No Students Were Found With Entry Year:\t" << yearRequested << endl;
    }
}

InvertedIndex::~InvertedIndex(){
    delete[] invertedIndex;
};