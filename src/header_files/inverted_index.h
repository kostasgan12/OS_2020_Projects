#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "main.h"
#include "student_class.h"
#include "hash_table.h"
#include "../helpers/helper_functions.h"

struct StudentHashTableEntry;

struct InvertedIndexEntry
{
    int year;
    StudentHashTableEntry *studentLocationP; //we want to store a pointer to a student, actually we want to store the student record location
    InvertedIndexEntry *nextInvIndexEntry;
    InvertedIndexEntry *p;

    // InvertedIndexEntry(Student *studentPassed);
    InvertedIndexEntry(int yearPassed);
    InvertedIndexEntry(int yearPassed, StudentHashTableEntry *studentPassed);
};

class InvertedIndex
{
private:
public:
    InvertedIndexEntry **invertedIndex;

    InvertedIndex();
    ~InvertedIndex();

    void InsertStudentReference(int yearToBeInserted, StudentHashTableEntry *student);
    void DeleteStudentReference(int entryYear, string id);
    void ShowAllStudentsInYear(int yearRequested);
    void FindActiveUsersInAcademicYear(int academicYear);
    void FindNBestStudentsOfYear(int num, int yearRequested);
    void CountStudentsPerYear();
};

#endif