#include "../../header_files/hash_table.h"

StudentHashTable::StudentHashTable()
{
    studentHashTable = new Student *[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
        studentHashTable[i] = NULL;
}

int StudentHashTable::HashFunc(int key)
{
    return key % hashTableSize;
}

void StudentHashTable::insert_student(Student student)
{
    int hash_v = HashFunc(k);
    Student *p = NULL;
    Student *en = studentHashTable[hash_v];
    while (en != NULL)
    {
        p = en;
        en = en->n;
    }
    if (en == NULL)
    {
        en = new Student(student);
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
        en->student = student;
    }
}

StudentHashTable::~StudentHashTable()
{
    delete[] studentHashTable;
}