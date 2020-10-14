#include "../../header_files/hash_table.h"

// StudentHashTableEntry::StudentHashTableEntry(Student* studentPassed)
// {
//     this->key = stoi(studentPassed->getStudentId());
//     this->studentValue = *studentPassed;
//     this->n = NULL;
// }
StudentHashTableEntry::StudentHashTableEntry(Student *studentPassed)
    :   
        key(transform_id(studentPassed->getStudentId())),
        studentValue(* studentPassed),
        n(NULL)
        {}

int StudentHashTable::HashFunc(string id)
{
    int key = transform_id(id);
    // int key = stol(id);

    return key % hashTableSize;
}

StudentHashTable::StudentHashTable()
{
    studentHashTable = new StudentHashTableEntry *[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
        studentHashTable[i] = NULL;
}


void StudentHashTable::insert_student(Student * student)
{
    int hash_v = HashFunc(student->getStudentId());

    StudentHashTableEntry* p = NULL;
    StudentHashTableEntry* en = studentHashTable[hash_v];

    while (en != NULL)                                                  //searching chained list at hashtable position given by hash function until empty
    {
        p = en;
        en = en->n;
    }
    if (en == NULL)
    {
        en = new StudentHashTableEntry(student);
        if (p == NULL)
        {
            studentHashTable[hash_v] = en;
        }
        else
        {
            p->n = en;
        }
    }
    else
    {
        en->studentValue = *student;
    }
}

StudentHashTable::~StudentHashTable()
{
    delete[] studentHashTable;
}