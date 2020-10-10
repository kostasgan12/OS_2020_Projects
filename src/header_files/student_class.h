#ifndef STUDENTCLASS_H
#define STUDENTCLASS_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Student
{
private:
    string studentID;
    string studentLastName;
    string studentFirstName;
    int studentZipCode;
    int studentEntryYear;
    float studentLessonAverage;

public:
    // Student(string __studentId, string __studentLastName, string __student_Name,
    //         int __zipcode, int __studentEntryYear, float __lessonsAverage) : studentID(__studentId), studentLastName(__studentLastName), studentFirstName(__student_Name), studentZipCode(__zipcode), studentEntryYear(__studentEntryYear), studentLessonAverage(__lessonsAverage) {};

    Student(string __studentId, string __studentLastName, string __student_Name,
            int __zipcode, int __studentEntryYear, float __lessonsAverage);

    ~Student();


    string getStudentId() { return studentID; }
    string getStudentLastName() { return studentLastName; }
    string getStudentFirstName() { return studentFirstName; }
    int getStudentZipCode() { return studentZipCode; }
    int getsStudentEntryYear() { return studentEntryYear; }
    float getStudentLessonAverage() { return studentLessonAverage; }
};

#endif
