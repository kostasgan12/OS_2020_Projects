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
    // Student* studentData;
    Student studentData;
    int key;
    StudentHashTableEntry *nextSt;
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

    void InsertStudent(Student* student);
    void LookUpStudent(string id);
    void DeleteStudent(string id);
    void ShowAllStudents();
};

#endif