#include "../header_files/main.h"

int hashTableSize;
int invertedStartYear;
int invertedEndYear;
int invertedTableSize;
int studentSum;

int main(int argc, char *argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INITIALIZING PARSED DATA  //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    // if (argc != 5)
    // {
    //     cout << "########## ERROR WITH PARSED PARAMETERS ########## " << endl;
    //     return 0;
    // }

    // if (strcmp(argv[1], "-i") != 0)
    // {
    //     cout << "########## ERROR WITH PARSING input file ##########" << endl;
    //     return 0;
    // }

    // if (strcmp(argv[3], "-c") != 0)
    // {
    //     cout << "########## ERROR WITH PARSING config file ##########" << endl;
    //     return 0;
    // }

    string inputFile="";
    string configFile = "";

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-i")
        {                                                                           //then we know that inputFile is next
            cout << "Loading Input File..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "inputfile")
            {
                inputFile = argv[i+1];
                cout << "########### Successfully Loaded Input File ###########\n" << endl;
            }
            else
            {
                if(argc <= i+1){
                    cout << "########### Expected Input File Not Given ###########\n" << endl;
                }
                else if (string(argv[i + 1]) != "inputfile"){
                    if (string(argv[i + 1]) == "-c"){
                        cout << "########### Expected Input File Not Given ###########\n" << endl;
                    }
                    else
                    {
                        cout << "########### Wrong Input File Given ###########\n" << endl;
                    }
                }else
                {
                    cout << "########### Unknown Error With Input File ###########\n" << endl;
                }
            }
        }
        else if (string(argv[i]) == "-c")
        {                                                                           //then we know that configFile is next
            cout << "Loading Config..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "configfile")
            {
                configFile = argv[i+1];
                cout << "########### Successfully Loaded Config File ###########\n" << endl;
            }
            else
            {
                if (argc <= i + 1)
                {
                    cout << "########### Expected Config File Not Given ###########\n" << endl;
                }
                else if (string(argv[i + 1]) != "configfile")
                {
                    cout << "########### Wrong Config File Given ###########\n" << endl;
                }
                else
                {
                    cout << "########### Unknown Error With Config File ###########\n" << endl;
                }
            }
        }else{
            if(string(argv[i]) != "configfile" && string(argv[i]) != "inputfile"){
                cout << "########### Unrecognised Flag ###########\n" << endl;
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// R E A D I N G  F I L E S ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    string buffer;
    ifstream infile;
    string token;
    /////////////////////////////// C O N F I G  F I L E /////////////////////////////////

    string __htsizeFlag;
    string __invertedStartYearFlag;
    string __invertedEndYearFlag;

    if (configFile != "")
    {
        infile.open(configFile); //opening input file to count number of students in file
        while (infile >> __htsizeFlag >> hashTableSize >> __invertedStartYearFlag >> invertedStartYear >> __invertedEndYearFlag >> invertedEndYear)
        {
            if (__htsizeFlag == "-hts"){
                cout<<"\nHash Table Size Is =====> "<<hashTableSize<<endl;
            }else{

            }
            if (__invertedStartYearFlag == "-startYear")
            {
                cout<<"\nStart Year For Inverted Is =====> "<<invertedStartYear<<endl;
            }
            if (__invertedEndYearFlag == "-endYear")
            {
                cout << "\nEnd Year For Inverted Is =====> " << invertedEndYear << endl;
            }
            if (invertedStartYear > 0 &&
                    invertedEndYear > 0 &&
                invertedStartYear < invertedEndYear)
            {
                invertedTableSize = invertedEndYear - invertedStartYear + 1;
            }
        }
        infile.close();
    }else{
        cout << "Enter Hash Table Size: ";
        cin >> hashTableSize;

        cout << "Enter Program Start Year (ex.2000): ";
        cin >> invertedStartYear;
        
        invertedEndYear = 2020;

        while (invertedStartYear > 2020 || invertedStartYear < 1900)
        {
            cout << "Enter Correct Start Year : ";
            cin >> invertedStartYear;
        }

        invertedTableSize = invertedEndYear - invertedStartYear + 1;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////// I N P U T  F I L E /////////////////////////////////

    int __studentEntryYear;
    string __studentId, __studentLastName, __student_Name, __zipcode;
    float __lessonsAverage;
    int inputFileStudentSum = 0;

    int counter = 0;

    

    infile.open(inputFile);                                                                     //opening input file to count number of students in file
    while (getline(infile, buffer))
    {
        if (buffer.length() != 0)
        {                                                                                       //check if empty line
            ++inputFileStudentSum;
        }
        else
        {
            cout << "in break" << endl;
            break;
        }
    }
    infile.close();


    StudentHashTable *HashTable = new StudentHashTable();
    InvertedIndex * InvertedIndexTable = new InvertedIndex();

    Student *newStudent;
    string studentsIdArray[inputFileStudentSum];                                                 // array used for checking for student duplicates

    StudentHashTableEntry *studentLocation;
    

    infile.open(inputFile);
    bool found;
    while (infile >> __studentId >> __studentLastName >> __student_Name >> __zipcode >> __studentEntryYear >> __lessonsAverage)
    {
        found = false;
        if (counter > 0)
        {
            for (int i = 0; i < counter; i++)                                                   //we scan our studentIdArray for possible duplicates
            {
                if (studentsIdArray[i] == __studentId)
                {
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            cout << "\nDuplicate Student Found With ID:\t" << __studentId << "\t" << __studentLastName << "\t" << __student_Name << "\t"
                 << " And Was Dismissed." << endl;
            continue;
        }
        else
        {
            newStudent = new Student();
            newStudent->SetStudent(__studentId, __studentLastName, __student_Name, __zipcode, __studentEntryYear, __lessonsAverage);
            

            studentLocation = NULL;
            studentLocation = HashTable->InsertStudent(newStudent);

            InvertedIndexTable->InsertStudentReference(__studentEntryYear, studentLocation);

            studentsIdArray[counter] = __studentId;
            ++counter;
        }
    }
    infile.close();                                                                 //closing text file
    //////////////////////////////////////////////////////////////////////////////////////
    
    ////////stuToBe == student to be inserted////////

    int choice;

    int stuToBe_entry_year; 
    float stuToBe_lesson_average;
    string stuToBe_id, stuToBe_last_name, stuToBe_first_name, stuToBe_zip_code;

    int year, numberOfStudents,rank;
    Student *newStudentInsert;

    while (1)
    {
        cout << "\n*************************************************************\n"<< endl;
        cout << "1.\tInsert Student" << endl;
        cout << "2.\tLook Up Student" << endl;
        cout << "3.\tDelete Student" << endl;
        cout << "4.\tSearch Remaining Students In Year" << endl;
        cout << "5.\tFind Top N Students For Given Year" << endl;
        cout << "6.\tCompute Given Years Average" << endl;
        cout << "7.\tFor Given Year Find Student With Worst Average" << endl;
        cout << "8.\tCount Students Per Year" << endl;
        cout << "9.\tFind *rank* Most Popular Zip Code" << endl;
        cout << "10.\tExit" << endl;
        cout << "\n*************************************************************\n"<< endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Student In The Following Format:  studentid lastname firstname zip year gpa  "<<endl;
            cin >> stuToBe_id >> stuToBe_last_name >> stuToBe_first_name >> stuToBe_zip_code >> stuToBe_entry_year >> stuToBe_lesson_average;
            newStudentInsert = new Student();
            newStudentInsert->SetStudent(stuToBe_id, stuToBe_last_name, stuToBe_first_name, stuToBe_zip_code, stuToBe_entry_year, stuToBe_lesson_average);
            HashTable->InsertStudent(newStudentInsert);
            break;
        case 2:
            cout << "Enter The Student's ID: ";
            cin >> stuToBe_id;
            HashTable->LookUpStudent(stuToBe_id);
            break;
        case 3:
            cout << "Enter The Student's ID: ";
            cin >> stuToBe_id;

            year = HashTable->FindStudentEntryYear(stuToBe_id);

            if (year > 0){
                InvertedIndexTable->DeleteStudentReference(year, stuToBe_id);
                HashTable->DeleteStudent(stuToBe_id);
            }else{
                cout << "\n########################################################################\n"
                     << endl;
                cout << "No Student Found With ID:\t"<<stuToBe_id<<"\tTry Again."<<endl;
                cout << "\n########################################################################\n"
                     << endl;
            }
            break;
        case 4:
            cout << "Enter Academic Year: ";
            cin >> year;
            InvertedIndexTable->FindActiveUsersInAcademicYear(year);
            break;
        case 5:
            cout << "Enter N To Search: ";
            cin >> numberOfStudents;
            cout << "Enter Year To Search: ";
            cin >> year;
            InvertedIndexTable->FindNBestStudentsOfYear(numberOfStudents, year);
            break;
        case 6:
            cout << "Enter Year: ";
            cin >> year;
            InvertedIndexTable->FindAverageGPAOfYear(year);
            break;
        case 7:
            cout << "Enter Year: ";
            cin >> year;
            InvertedIndexTable->MinGPAStudentOfYear(year);
            break;
        case 8:
            InvertedIndexTable->CountStudentsPerYear();
            break;
        case 9:
            cout << "Enter rank: ";
            cin >> rank;
            InvertedIndexTable->FindNMostPopularZipCode(rank);
            break;
        case 10:
            if(inputFile!=""){
                delete newStudent;
            }
            delete InvertedIndexTable;
            delete HashTable;
            exit(1);
        default:
            cout << "\nEnter correct option"<<endl;
        }
    }
}