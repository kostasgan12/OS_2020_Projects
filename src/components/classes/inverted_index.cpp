
#include "../../header_files/inverted_index.h"

InvertedIndexEntry::InvertedIndexEntry(int yearPassed)
    : 
        year(yearPassed),
        studentLocationP(NULL),
        nextInvIndexEntry(NULL)
    {}

InvertedIndexEntry::InvertedIndexEntry(int yearPassed, StudentHashTableEntry *studentPassed)
    : year(yearPassed),
        studentLocationP(studentPassed),
        nextInvIndexEntry(NULL)
{}


InvertedIndex::InvertedIndex()
{
    invertedIndex = new InvertedIndexEntry *[invertedTableSize];
    for (int i = 0; i < invertedTableSize; i++)
    {
        ;
        int _yearToBePassed = i + invertedStartYear;
        invertedIndex[i] = new InvertedIndexEntry(_yearToBePassed);
    }
}

void InvertedIndex::InsertStudentReference(int yearToBeInserted, StudentHashTableEntry *student)
{
    int yearPositionInIndexTable = yearToBeInserted - invertedStartYear;

    InvertedIndexEntry *p = NULL; //initialize p with NULL
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    //currentEntry when initialized, should point at an empty Entry, 
    //That only contains our Header Year, so we check if a next Entry Exists, 
    //which would mean there is a student entered.

    // currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry->nextInvIndexEntry == NULL)
    //table for this year hasnt got any student records 
    {
        currentEntry->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
        // cout << "student entered and currentEntry->nextInvIndexEntry is:\t" << currentEntry->nextInvIndexEntry->studentLocationP->studentData.getStudentLastName() << endl;
    }
    else
    //table for this year already has student records
    {
        // p = currentEntry;
        // currentEntry = currentEntry->nextInvIndexEntry;
        // while (currentEntry != NULL)
        // {
        //     p = currentEntry;
        //     currentEntry = currentEntry->nextInvIndexEntry;
        // }

        // p->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
        
        while (currentEntry != NULL)
        {
            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;
        }

        p->nextInvIndexEntry = new InvertedIndexEntry(yearToBeInserted, student);
    }

    // delete p;
}

void InvertedIndex::DeleteStudentReference(int entryYear, string id)
{
    int yearPositionInIndexTable = entryYear - invertedStartYear;

    InvertedIndexEntry *p = NULL;
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    bool flag = false;

    cout << "\n########################################################################\n"
         << endl;


    currentEntry = currentEntry->nextInvIndexEntry; //first item of invertedindx contains only the year, student items start from the second
    if (currentEntry != NULL) //check if first entry of this position in the hashtable is null, if not then we can search for the item, if its there
    {
        while (currentEntry != NULL)
        {
            // p = currentEntry;
            // currentEntry = currentEntry->nextInvIndexEntry;

            cout << "comparing " << currentEntry->studentLocationP->studentData.getStudentId() << " with given id: " << id << endl;

            if (currentEntry->studentLocationP->studentData.getStudentId() == id)
            {
                flag = true;
                cout << "student found" << endl;
                break;
            }

            p = currentEntry;
            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    else
    {
        cout << "No Student found with id " << id << endl;
        return;
    }

    if (flag)
    {
        p->nextInvIndexEntry = currentEntry->nextInvIndexEntry;
        // p->nextInvIndexEntry = currentEntry;
        cout << "Student with id:\t" << id << "\t Successfully Removed Reference From Our Inverted Index Table" << endl;
    }
    else
    {
        cout << "No Student found with id " << id << endl;
    }
    delete currentEntry;
    cout << "\n########################################################################\n"
         << endl;
}

void InvertedIndex::FindActiveUsersInAcademicYear(int academicYear)
{
    int entryYearRetrieved = invertedEndYear - academicYear +1;
    int yearPositionInIndexTable = entryYearRetrieved - invertedStartYear;
    int counter = 0;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"<< endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            counter++;
            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    cout << counter << " Students Were Found Active In Their:\t" << academicYear<<"\tAcademic Year" << endl;
}

void InvertedIndex::FindNBestStudentsOfYear(int num, int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;
    int isArrayFilledCounter = 0;

    float bestNGPA[num];

    for (int i = 0; i < num; i++)
    {
        bestNGPA[i]=-1;
    }
    
    float tmpGPA = 0;
    bool flag=false;
    int innerStarterVal=0;
    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"<< endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        float minGPA = 10;
        int whileCounter =0;
        int isArrayFilledCounter = 0;
        bool foundDuplicate;
        while (currentEntry != NULL)
        {
            //looping over every item in given year
            tmpGPA = currentEntry->studentLocationP->studentData.getStudentLessonAverage();
            foundDuplicate = false;
            if (isArrayFilledCounter < num)
            {
                if (tmpGPA < minGPA)
                {
                    minGPA = tmpGPA;
                }

                //need to check if value already exists in bestNGPA array
                for (int l = 0; l < isArrayFilledCounter; l++)
                {
                    if (bestNGPA[l] == tmpGPA)
                    {
                        foundDuplicate = true;
                    }
                }

                if(!foundDuplicate){
                    bestNGPA[isArrayFilledCounter] = tmpGPA;
                }
            }

            if (isArrayFilledCounter >= num)
            {   
                for (int i = 0; i < num; i++)   //looping over bestGPA array sized num
                {
                    if (tmpGPA > minGPA && bestNGPA[i] == minGPA)
                    {
                        bestNGPA[i] = tmpGPA;

                        //looking for new minGPA
                        minGPA = bestNGPA[0];   //set it as the first students GPA nad start seaching from the second
                        for (int j = 1; j < num; j++)
                        {
                            if(bestNGPA[j]<minGPA){
                                minGPA = bestNGPA[j];
                            }
                        }
                        break;
                    }
                }
            }

            isArrayFilledCounter++;
            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }


    cout<<"Top\t"<<num<<"\tGPAs Students For Year\t"<<yearRequested<<"\n"<<endl;

    float  __gpa;
    for (int i = 0; i < num; i++)
    {
        __gpa = 0;

        if (bestNGPA[i] != -1){

            cout<<"Students With GPA Equal To:\t" << bestNGPA[i] <<"\n\n";

            currentEntry = invertedIndex[yearPositionInIndexTable]->nextInvIndexEntry;

            while (currentEntry != NULL)
            {
                __gpa = currentEntry->studentLocationP->studentData.getStudentLessonAverage();
                
                if (__gpa == bestNGPA[i]){
                    cout << "Student Details\nID->\t" << currentEntry->studentLocationP->studentData.getStudentId();
                    cout << "\nName->\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << " ";
                    cout << currentEntry->studentLocationP->studentData.getStudentFirstName() << "\n";
                    cout << "ZipCode->\t" << currentEntry->studentLocationP->studentData.getStudentZipCode()<<"\n"<< endl;
                }
                currentEntry = currentEntry->nextInvIndexEntry;
            }
            cout<<"\n";
        }
    }
}

void InvertedIndex::FindAverageGPAOfYear(int yearRequested){
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];
    
    float gpaSum = 0;
    int studentCounter = 0;
    float gpaAverage=0;

    cout
        << "\n########################################################################\n"
        << endl;

    if (currentEntry->nextInvIndexEntry != NULL)
    {
        currentEntry = currentEntry->nextInvIndexEntry;

        while (currentEntry != NULL){
            gpaSum += currentEntry->studentLocationP->studentData.getStudentLessonAverage();
            studentCounter++;
            currentEntry = currentEntry->nextInvIndexEntry;
        }

        gpaAverage = gpaSum / studentCounter;

        cout<<"Average GPA For Year: "<<yearRequested<<" is: "<<gpaAverage<<endl;
    }else{
        cout << "Year: " << yearRequested << " Hasnt Got Any Active Students. So GPA Average is 0."<< endl;
    }
    cout
        << "\n########################################################################\n"
        << endl;
}

void InvertedIndex::MinGPAStudentOfYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    float minGPA = 10;
    float tmpGPA;

    // InvertedIndexEntry *minStudent;

    cout
        << "\n########################################################################\n"
        << endl;

    if (currentEntry->nextInvIndexEntry != NULL)
    {
        currentEntry = currentEntry->nextInvIndexEntry;

        while (currentEntry != NULL)
        {
            tmpGPA = currentEntry->studentLocationP->studentData.getStudentLessonAverage();

            if(tmpGPA < minGPA){
                // minStudent = currentEntry;
                minGPA = tmpGPA;
            }

            currentEntry = currentEntry->nextInvIndexEntry;
        }

        cout << "Min GPA For Year: " << yearRequested << " is: " << minGPA<< "\n" << endl;

        currentEntry = invertedIndex[yearPositionInIndexTable]->nextInvIndexEntry;

        while (currentEntry != NULL)
        {
            tmpGPA = currentEntry->studentLocationP->studentData.getStudentLessonAverage();

            if (tmpGPA  == minGPA)
            {
                cout << "Student Details:\n\nID->\t" << currentEntry->studentLocationP->studentData.getStudentId();
                cout << "\nName->\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << " ";
                cout << currentEntry->studentLocationP->studentData.getStudentFirstName() << "\n";
                cout << "ZipCode->\t" << currentEntry->studentLocationP->studentData.getStudentZipCode() << "\n\n"
                     << endl;
            }
            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    else
    {
        cout << "Year: " << yearRequested << " Hasnt Got Any Active Students" << endl;
    }
    cout
        << "\n########################################################################\n"
        << endl;
    delete currentEntry;
}

void InvertedIndex::FindNMostPopularZipCode(int rank){

    cout << "studentSum:\t"<< studentSum << endl;

    int isArrayFilledCounter = 0;

    // string popularZipCodePerYear[invertedTableSize];

    // for (int i = 0; i < invertedTableSize; i++)
    // {
    //     popularZipCodePerYear[i] = "null";
    // }

    InvertedIndexEntry *currentEntry;

    ZipCodeEntry zipCodeArray[studentSum];

    for (int j = 0; j < studentSum; j++)
    {
        zipCodeArray[j].zipCode="null";
        zipCodeArray[j].zipCodeCount=0;
    }

    string tmpZipCode;

        for (int i = 0; i < invertedTableSize; i++)
    {
        //we want to loop for every year!
        currentEntry = invertedIndex[i];
        cout << "\n########################################################################\n"
             << endl;
        cout << "Searching for year ->\t" << currentEntry->year << endl;
        cout << "\n########################################################################\n"
             << endl;

        currentEntry = currentEntry->nextInvIndexEntry;
        if (currentEntry != NULL)
        {
            //check if this year is empty of students

            int whileCounter = 0;
            int isArrayFilledCounter = 0;
            bool foundDuplicate;
            while (currentEntry != NULL)
            {
                //looping over every student in i year

                tmpZipCode = currentEntry->studentLocationP->studentData.getStudentZipCode();

                cout << "this students zipcode is\t"<<tmpZipCode<<endl;

                //check if zipcode already exists in zipCodeArray
                foundDuplicate=false;
                for (int k = 0; k < studentSum; k++)
                {
                    if (zipCodeArray[k].zipCode == tmpZipCode)
                    {
                        cout<<"zipcode: "<<tmpZipCode<<" already exists, we increase counter"<<endl;
                        zipCodeArray[k].zipCodeCount++;
                        foundDuplicate =true;
                    }
                }

                //else if the zipcode doesnt alredy exist we must add
                if(!foundDuplicate){
                    while(zipCodeArray[whileCounter].zipCodeCount != 0){
                        whileCounter++;
                    }
                    cout<<"found first available slot at position: "<<whileCounter<<endl;
                    zipCodeArray[whileCounter].zipCode = tmpZipCode;
                    zipCodeArray[whileCounter].zipCodeCount++;
                }

                isArrayFilledCounter++;
                currentEntry = currentEntry->nextInvIndexEntry;
            }
        }
    }

    int arrayIndex = 0;
    while (zipCodeArray[arrayIndex].zipCodeCount != 0)
    {
        cout << "Zip Code: " << zipCodeArray[arrayIndex].zipCode << " Was Found: " << zipCodeArray[arrayIndex].zipCodeCount << " Times." << endl;
        arrayIndex++;
    }

    // cout << "Top\t" << rank << "\tGPAs Students For Year\t" << yearRequested << "\n"
    //      << endl;

    // float __gpa;
    // for (int i = 0; i < rank; i++)
    // {
    //     __gpa = 0;

    //     if (bestNGPA[i] != -1)
    //     {

    //         cout << "Students With GPA Equal To:\t" << bestNGPA[i] << "\n\n";

    //         currentEntry = invertedIndex[0]->nextInvIndexEntry;

    //         while (currentEntry != NULL)
    //         {
    //             __gpa = currentEntry->studentLocationP->studentData.getStudentLessonAverage();

    //             if (__gpa == bestNGPA[i])
    //             {
    //                 cout << "Student Details\nID->\t" << currentEntry->studentLocationP->studentData.getStudentId();
    //                 cout << "\nName->\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << " ";
    //                 cout << currentEntry->studentLocationP->studentData.getStudentFirstName() << "\n";
    //                 cout << "ZipCode->\t" << currentEntry->studentLocationP->studentData.getStudentZipCode() << "\n"
    //                      << endl;
    //             }
    //             currentEntry = currentEntry->nextInvIndexEntry;
    //         }
    //         cout << "\n";
    //     }
    // }

}

void InvertedIndex::CountStudentsPerYear()
{
    int counter;
    InvertedIndexEntry *currentEntry;

    int yearSearching = 0;
    
    for (int i = 0; i < invertedTableSize; i++ )    //loop every year
    {
        counter = 0;
            cout
        << "\n########################################################################\n"
        << endl;

        yearSearching = i + invertedStartYear;

        currentEntry = invertedIndex[i];

        currentEntry = currentEntry->nextInvIndexEntry;     //initialize with second item in inverted index because the first always contains the yaer

        if (currentEntry != NULL)
        {
            while (currentEntry != NULL)
            {
                counter++;
                currentEntry = currentEntry->nextInvIndexEntry;
            }
            cout << yearSearching << ":\t" << counter << "\tStudents Were Found." << endl;
        }
        else
        {
            cout << yearSearching << ":\t" << "\tNo Students Were Found." << endl;
        }
    }
}

void InvertedIndex::ShowAllStudentsInYear(int yearRequested)
{
    int yearPositionInIndexTable = yearRequested - invertedStartYear;

    InvertedIndexEntry *currentEntry = invertedIndex[yearPositionInIndexTable];

    cout << "\n########################################################################\n"
         << endl;

    currentEntry = currentEntry->nextInvIndexEntry;
    if (currentEntry != NULL)
    {
        while (currentEntry != NULL)
        {
            cout << "found student with id:\t" << currentEntry->studentLocationP->studentData.getStudentId();
            cout << "\tand name:\t" << currentEntry->studentLocationP->studentData.getStudentLastName() << "\t";
            cout << currentEntry->studentLocationP->studentData.getStudentFirstName()<<endl;

            currentEntry = currentEntry->nextInvIndexEntry;
        }
    }
    else
    {
        cout << "No Students Were Found With Entry Year:\t" << yearRequested << endl;
    }
}

InvertedIndex::~InvertedIndex(){
    delete[] invertedIndex;
};