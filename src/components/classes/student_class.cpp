#include "../../header_files/student_class.h"

// Student::Student(string __studentId, string __studentLastName, string __student_Name,
//             int __zipcode, int __studentEntryYear, float __lessonsAverage) 
//                 : 
//                 studentID(__studentId), 
//                 studentLastName(__studentLastName), 
//                 studentFirstName(__student_Name), 
//                 studentZipCode(__zipcode), 
//                 studentEntryYear(__studentEntryYear), 
//                 studentLessonAverage(__lessonsAverage)
//                 {};

Student::Student(){};

// Student::Student(){}

void Student::SetStudent(string __studentId, string __studentLastName, string __student_Name,
                         int __zipcode, int __studentEntryYear, float __lessonsAverage)
{
    cout<<"in set student"<<endl;

    studentID = __studentId;
    studentLastName = __studentLastName;
    studentFirstName = __student_Name;
    studentZipCode = __zipcode;
    studentEntryYear = __studentEntryYear;
    studentLessonAverage = __lessonsAverage;

    cout << "in set student after its done" << endl;
    // this->studentID = __studentId;
    // this->studentLastName = __studentLastName;
    // this->studentFirstName = __student_Name;
    // this->studentZipCode = __zipcode;
    // this->studentEntryYear = __studentEntryYear;
    // this->studentLessonAverage = __lessonsAverage;
}

Student::~Student()
{
    // cout<<"Deleting Student"<<endl;
}