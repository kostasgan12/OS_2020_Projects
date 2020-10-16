
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

        cout << "invertedIndex[" << i << "]->year is:\t" << invertedIndex[i]->getIndexYear() << endl;
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

    // while (currentEntry != NULL)
    // {
    //     if(currentEntry->studentLocationP == NULL && currentEntry->nextInvIndexEntry == NULL){
    //         cout << "This Is Empty Header File for year:\t" << currentEntry->year << endl;
    //     }else{
    //         cout << "space at:\t" << currentEntry->studentLocationP << "\tocupied by:\t";
    //         cout << currentEntry->studentLocationP->studentData.getStudentLastName() << endl;
    //     }
    //     p = currentEntry;
    //     currentEntry = currentEntry->nextInvIndexEntry;
    // }


    // if (currentEntry == NULL)
    // {
    //     cout << " After While currentEntry is NULL" << endl;
    //     currentEntry = new InvertedIndexEntry(yearToBeInserted, student);
    // }else{
    //     cout << " After While currentEntry **NOT** NULL" << endl;
    // }

    if (currentEntry->nextInvIndexEntry == NULL)    
    {
        currentEntry->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
        cout << "student entered and currentEntry->nextInvIndexEntry is:\t" << currentEntry->nextInvIndexEntry->studentLocationP->studentData.getStudentLastName() << endl;
    }
    else
    {   
        while (currentEntry->nextInvIndexEntry != NULL){
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;

            cout << "space at:\t" << currentEntry->studentLocationP <<"\tocupied by:\t";
            cout << currentEntry->studentLocationP->studentData.getStudentLastName() << endl;
            
        }
        currentEntry = new InvertedIndexEntry(yearToBeInserted, student);
        cout << "student entered and currentEntry is:\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << endl;
    }
}

void InvertedIndex::ShowAllStudentsInYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "########################################################################" << endl;
    cout << "Searching for Student in year:\t"<< yearRequested << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            cout << "found student with id:\t" << currentEntry->studentLocationP->studentData.getStudentId();
            cout << "\tand name:\t" << currentEntry->studentLocationP->studentData.getStudentLastName() <<"\t";
            cout << currentEntry->studentLocationP->studentData.getStudentFirstName();
            cout << "\tat location ===>\t" << currentEntry << endl;

            currentEntry = currentEntry->nextInvIndexEntry;
            cout << "currentEntry before while end loop:\t" << currentEntry<<endl;
        }
    }else{
        cout << "currentEntry->nextInvIndexEntry is NULL"<<endl;
    }
}


InvertedIndex::~InvertedIndex(){
    delete[] invertedIndex;
};