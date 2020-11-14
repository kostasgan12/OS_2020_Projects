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
    string studentZipCode;
    int studentEntryYear;
    float studentLessonAverage;

public:
    // Student(string __studentId, string __studentLastName, string __student_Name,
    //         int __zipcode, int __studentEntryYear, float __lessonsAverage);
    Student();
    ~Student();

    void SetStudent(string __studentId, string __studentLastName, string __student_Name,
            string __zipcode, int __studentEntryYear, float __lessonsAverage);

    string getStudentId() { return studentID; }
    string getStudentLastName() { return studentLastName; }
    string getStudentFirstName() { return studentFirstName; }
    string getStudentZipCode() { return studentZipCode; }
    int getStudentEntryYear() { return studentEntryYear; }
    float getStudentLessonAverage() { return studentLessonAverage; }
};

#endif
