#include "../../header_files/hash_table.h"

StudentHashTableEntry::StudentHashTableEntry(Student *studentPassed)
    :   
        key(transform_id(studentPassed->getStudentId())),
        // studentData( studentPassed),
        studentData(* studentPassed),
        nextSt(NULL)
        {}

int StudentHashTable::HashFunc(string id)
{
    int key = transform_id(id);

    return key % hashTableSize;
}

StudentHashTable::StudentHashTable()
{
    studentHashTable = new StudentHashTableEntry *[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
        studentHashTable[i] = NULL;
}


void StudentHashTable::InsertStudent(Student * student)
{
    int hash_v = HashFunc(student->getStudentId());

    StudentHashTableEntry* p = NULL;                                    //initialize p with NULL
    StudentHashTableEntry* en = studentHashTable[hash_v];               //initialize en with the first object contained in the list at position hash_v of our hashtable, it either contains an object or NULL as initialized
    
    cout << "########################################################################" << endl;
    cout << "Student we want to insert is :\t" << student->getStudentLastName() << endl;

    while (en != NULL)                                                  //searching chained list at hashtable position given by hash function until we find available entry space
    {
        p = en;                                                         //p is assigned en value of chained list
        en = en->nextSt;                                                // en is assinged next value of chained list
    
        cout << "++ Looping Over Chained List Items ++ p is ====> " << p->studentData.getStudentLastName() << endl;
    }
    
    if (en == NULL)                                                     // if en == NULL, which means that
    {
        en = new StudentHashTableEntry(student);                        // we assign en with a new entry
       
        if (p == NULL)                                                  // p is null when our chained list at position hash_v is empty
        {
            studentHashTable[hash_v] = en;                              //so we assign the first item in that list with our en value 
        }
        else
        {
            p->nextSt = en;                                                  //else if the list isnt empty, we assign our value to the next element of the last one that is represented by p
        }
    }
    else
    {
        cout<<"in en else condition en should not be NULL, it is ==> "<<en<<endl;
        en->studentData = * student;
    }
    cout << "########################################################################" << endl;
}

void StudentHashTable::LookUpStudent(string id)
{
    int key = transform_id(id);
    int hash_v = HashFunc(id);
    bool flag = false;

    StudentHashTableEntry *en = studentHashTable[hash_v];
    cout << "\n########################################################################\n" << endl;
    if (en != NULL)
    {
        while (en != NULL)
        {
            if (en->key == key)
            {
                flag = true;
                cout << "Student Found With Details:\n\n";
                cout << "ID-> \t\t" << en->studentData.getStudentId()
                     << "\nSurname->\t" << en->studentData.getStudentLastName()
                     << "\nName->\t\t" << en->studentData.getStudentFirstName()
                     << "\nZipCode->\t" << en->studentData.getStudentZipCode()
                     << "\nEntry Year->\t" << en->studentData.getsStudentEntryYear()
                     << "\nGPA->\t\t" << en->studentData.getStudentLessonAverage() << endl;
            }
            en = en->nextSt;
        }
    }
    if (!flag)
        cout << "No Element found at key " << key << endl;
    cout << "\n########################################################################\n" << endl;
}

//TODO Delete needs refactoring

void StudentHashTable::DeleteStudent(string id)
{
    int key = transform_id(id);
    int hash_v = HashFunc(id);
    StudentHashTableEntry *en = studentHashTable[hash_v];
    StudentHashTableEntry *p = NULL;
    if (en == NULL || en->key != key)
    {
        cout << "No Element found at key " << key << endl;
        return;
    }
    while (en->nextSt != NULL)
    {
        p = en;
        en = en->nextSt;
    }
    if (p != NULL)
    {
        p->nextSt = en->nextSt;
    }
    delete en;
    cout << "Element Deleted" << endl;
}

void StudentHashTable::ShowAllStudents(){
    for (int i = 0; i < hashTableSize; i++)
    {
        if(studentHashTable[i]!= NULL){
            cout << "########################################################################" << endl;
            cout<<"for index: "<<i<< " we have students. Lets See Them"<<endl;
            StudentHashTableEntry *en = studentHashTable[i];
            while(en != NULL){
                cout << "found student with id:\t"<<en->studentData.getStudentId();
                cout << "\tand name:\t" << en->studentData.getStudentLastName()<< "\t" << en->studentData.getStudentFirstName() << endl;
                // cout << "found student with id:\t"<<en->studentData->getStudentId();
                // cout << "\tand name:\t" << en->studentData->getStudentLastName()<< "\t" << en->studentData->getStudentFirstName() << endl;
                en = en->nextSt;
            }
        }
    }
}

StudentHashTable::~StudentHashTable()
{
    delete[] studentHashTable;
}