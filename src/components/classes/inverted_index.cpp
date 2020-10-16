
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
        // cout << "studentLocationP is ==>:\t" << studentLocationP << endl;
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

void InvertedIndex::CountStudentsInYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;
    int counter = 0;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "########################################################################\n" << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            counter++;
            currentEntry = currentEntry->nextInvIndexEntry;
        }
        cout << "\n"<<counter<<" Students Were Found With Entry Year:\t" << yearRequested << endl;
    }else{
        cout << "No Students Were Found With Entry Year:\t"<<yearRequested<<endl;
    }
}

void InvertedIndex::ShowAllStudentsInYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "########################################################################\n"
         << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            cout << "found student with id:\t" << currentEntry->studentLocationP->studentData.getStudentId();
            cout << "\tand name:\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << "\t";
            cout << currentEntry->studentLocationP->studentData.getStudentFirstName();
            cout << "\tat location ===>\t" << currentEntry << endl;

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