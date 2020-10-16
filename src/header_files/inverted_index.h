#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "main.h"
#include "student_class.h"
#include "hash_table.h"
#include "../helpers/helper_functions.h"

struct InvertedIndexEntry
{
    // Student  studentLocationP;
    int year;
    StudentHashTableEntry *studentLocationP; //we want to store a pointer to a student, actually we want to store the student record location
    InvertedIndexEntry *nextInvIndexEntry;
    InvertedIndexEntry *p;

    // InvertedIndexEntry(Student *studentPassed);
    InvertedIndexEntry(int yearPassed);
    InvertedIndexEntry(int yearPassed, StudentHashTableEntry *studentPassed);

    int getIndexYear() { return year; }
    StudentHashTableEntry *getStudentLocationP() { return studentLocationP; }
};

class InvertedIndex
{
private:
public:
    InvertedIndexEntry **invertedIndex;

    InvertedIndex();
    ~InvertedIndex();

    void InsertStudentReference(int yearToBeInserted, StudentHashTableEntry *student);
    void DeleteStudentReference(string id);
    void ShowAllStudentsInYear(int yearRequested);
    void CountStudentsInYear(int yearRequested);
};

#endif