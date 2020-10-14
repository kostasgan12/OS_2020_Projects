#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "main.h"
#include "student_class.h"
#include "../helpers/helper_functions.h"

struct StudentHashTableEntry
{
    Student studentValue;
    int key;
    StudentHashTableEntry *n;
    StudentHashTableEntry *p;

    StudentHashTableEntry(Student* studentPassed);
};


class StudentHashTable
{
private:
public:
    StudentHashTableEntry **studentHashTable;

    StudentHashTable();

    ~StudentHashTable();

    int HashFunc(string key);

    void insert_student(Student* student);
};

#endif