#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "main.h"
#include "student_class.h"

class StudentHashTable
{
private:
public:
    Student **studentHashTable;

    StudentHashTable();

    ~StudentHashTable();

    int HashFunc(int key);

    void insert_student(Student student);
};

#endif