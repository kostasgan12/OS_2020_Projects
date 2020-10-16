
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
    if (currentEntry->nextInvIndexEntry == NULL)    
    {
        cout<<"student location TO BE INSERTED:\t"<<student<<endl;
        currentEntry->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
    }
    else
    {   
        while (currentEntry->nextInvIndexEntry != NULL){
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;

            cout << "space at:\t" << currentEntry->studentLocationP <<"\tocupied by:\t";
            cout << currentEntry->studentLocationP->studentData.getStudentLastName() << endl;
            
        }
    }
}

InvertedIndex::~InvertedIndex(){
    delete[] invertedIndex;
};