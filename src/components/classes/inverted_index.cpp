
#include "../../header_files/inverted_index.h"

InvertedIndexEntry::InvertedIndexEntry(int yearPassed)
    : 
        year(yearPassed),
        studentLocationP(NULL),
        nextInvIndexEntry(NULL)
    {}

InvertedIndexEntry::InvertedIndexEntry(int yearPassed, Student *studentPassed)
    : year(yearPassed),
        studentLocationP(studentPassed),
        nextInvIndexEntry(NULL)
{
    cout << "In InvertedIndexEntry for student construction"<<endl;
    // cout << "studentPassed is ==>:\t" << studentPassed << endl;
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

        cout << "invertedIndex[" << i << "]->year is:\t" << invertedIndex[i]->getIndexYear() << endl;
    }
}

void InvertedIndex::InsertStudentReference(Student *student){
    int yearToBeInserted = student->getStudentEntryYear();
    // cout<<student->getStudentLastName()<<"\tshould be entered at year:\t"<<yearToBeInserted<<endl;
    int yearPositionInIndexTable = student->getStudentEntryYear() - invertedStartYear;
    // cout << "yearToBeInserted is at position:\t" << yearPositionInIndexTable << endl;

    InvertedIndexEntry *p = NULL; //initialize p with NULL
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    if (currentEntry->nextInvIndexEntry == NULL)
    {
        cout<<"first instance of year\t"<<yearToBeInserted<<endl;
        cout<<"student location TO BE INSERTED:\t"<<student<<endl;
        currentEntry->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
    }
    else
    {   
        while (currentEntry->nextInvIndexEntry != NULL){
            // cout << "currentEntry already has student with reference pointer:\t";
            // cout << currentEntry->getStudentLocationP() << endl;
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;

            cout << p->studentLocationP << endl;
        }
    }
}

InvertedIndex::~InvertedIndex(){
    delete[] invertedIndex;
};