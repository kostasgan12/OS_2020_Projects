#include "../header_files/main.h"

int hashTableSize;

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

    string inputFile, configFile;

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-i")
        {                                                                           //then we know that inputFile is next
            cout << "Loading Input File..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "inputfile")
            {
                inputFile = argv[i+1];
                cout << "########### Successfully Loaded Input File ###########" << endl;
            }
            else
            {
                if(argc <= i+1){
                    cout << "########### Expected Input File Not Given ###########" << endl;
                }
                else if (string(argv[i + 1]) != "inputfile"){
                    if (string(argv[i + 1]) == "-c"){
                        cout << "########### Expected Input File Not Given ###########" << endl;
                    }
                    else
                    {
                        cout << "########### Wrong Input File Given ###########" << endl;
                    }
                }else
                {
                    cout << "########### Unknown Error With Input File ###########" << endl;
                }
            }
        }
        else if (string(argv[i]) == "-c")
        {                                                                           //then we know that configFile is next
            cout << "Loading Config..." << endl;
            if (argc > i+1 && string(argv[i+1]) == "configfile")
            {
                configFile = argv[i+1];
                cout << "########### Successfully Loaded Config File ###########" << endl;
            }
            else
            {
                if (argc <= i + 1)
                {
                    cout << "########### Expected Config File Not Given ###########" << endl;
                }
                else if (string(argv[i + 1]) != "configfile")
                {
                    cout << "########### Wrong Config File Given ###########" << endl;
                }
                else
                {
                    cout << "########### Unknown Error With Config File ###########" << endl;
                }
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

    infile.open(configFile); //opening input file to count number of students in file
    while (infile >> __htsizeFlag >> hashTableSize)
    {
        if (__htsizeFlag == "-hts"){
            cout<<"hash table size is =====> "<<hashTableSize<<endl;
        }
    }
    infile.close();
    //////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////// I N P U T  F I L E /////////////////////////////////

    int __zipcode, __studentEntryYear;
    string __studentId, __studentLastName, __student_Name;
    float __lessonsAverage;
    int studentSum = 0;

    int counter = 0;

    infile.open(inputFile);                                                                     //opening input file to count number of students in file
    while (getline(infile, buffer))
    {
        if (buffer.length() != 0)
        {                                                                                       //check if empty line
            ++studentSum;
        }
        else
        {
            cout << "in break" << endl;
            break;
        }
    }
    infile.close();

    StudentHashTable tempHashTable;

    string studentsIdArray[studentSum];                                                         // array used for checking for student duplicates
    // Student * newStudent = NULL;

    infile.open(inputFile);
    while (infile >> __studentId >> __studentLastName >> __student_Name >> __zipcode >> __studentEntryYear >> __lessonsAverage)
    {
        int found;
        if (counter > 0)
        {
            found = 0;
            for (int i = 0; i < counter; i++)                                                   //we scan our studentIdArray for possible duplicates
            {
                if (studentsIdArray[i] == __studentId)
                {
                    found++;
                    break;
                }
            }
        }

        if (found > 0)
        {
            cout << "Duplicate Student Found With ID: " << __studentId << " And Was Dismissed." << endl;
            continue;
        }
        else
        {
            // newStudent = new Student(__studentId, __studentLastName, __student_Name, __zipcode, __studentEntryYear, __lessonsAverage);
            Student newStudent(__studentId, __studentLastName, __student_Name, __zipcode, __studentEntryYear, __lessonsAverage);
            cout << "newStudent id is +++++> " << newStudent.getStudentId() << endl;
            // here we need to implement adding the student to our hashtable

            studentsIdArray[counter] = __studentId;
            ++counter;
        }
    }

    infile.close(); //closing text file

    //////////////////////////////////////////////////////////////////////////////////////
}