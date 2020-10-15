#include "../../header_files/hash_table.h"

StudentHashTableEntry::StudentHashTableEntry(Student *studentPassed)
    :   
        key(transform_id(studentPassed->getStudentId())),
        studentData( studentPassed),
        n(NULL)
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

    if (studentHashTable[hash_v] != NULL){
        cout << "in studentHashTable[" << hash_v << "] where the first student is ====> " << studentHashTable[hash_v]->studentData->getStudentLastName() << endl;
    }
    while (en != NULL)                                                  //searching chained list at hashtable position given by hash function until we find available entry space
    {
        p = en;                                                         //p is assigned en value of chained list
        en = en->n;                                                     // en is assinged next value of chained list

        cout << "in studentHashTable[" << hash_v << "] p is ====> " << p->studentData->getStudentLastName() << endl;
    }
    
    if (en == NULL)                                                     // if en == NULL, which means that
    {
        en = new StudentHashTableEntry(student);                        // we assign en with a new entry
        // cout<<"en->key is "<<en->key<<endl;
        // cout << "en->studentData->getStudentLastName is " << en->studentData->getStudentLastName() << endl;
        
        if (p == NULL)                                                  // p is null when our chained list at position hash_v is empty
        {
            studentHashTable[hash_v] = en;                              //so we assign the first item in that list with our en value 
            if (studentHashTable[hash_v] != NULL){
                cout << "first student in studentHashTable["<<hash_v<<"] is ====> " << studentHashTable[hash_v]->studentData->getStudentLastName() << endl;
            }
        }
        else
        {
            cout << "p->studentData->getStudentLastName is ====> " << p->studentData->getStudentLastName() << endl;
            p->n = en;                                                  //else if the list isnt empty, we assign our value to the next element of the last one that is represented by p
        }
    }
    else
    {
        // en->studentData = *student;
        cout<<"in en else condition en should not be NULL, it is ==> "<<en<<endl;
        en->studentData = student;
    }
}

void StudentHashTable::LookUpStudent(string id)
{
    cout << "########################################################################" << endl;
    cout << "id given to LookUpStudent : "<< id << endl;

    int key = transform_id(id);
    cout << "key transformed from id in LookUpStudent : " << key << endl;

    int hash_v = HashFunc(id);

    cout << "hash_v in for id: "<<id<<"LookUpStudent : " << hash_v << endl;
    bool flag = false;

    StudentHashTableEntry *en = studentHashTable[hash_v];
    cout << "########################################################################" << endl;
    if (en != NULL)
    {
        while (en != NULL)
        {
            if (en->key == key)
            {
                flag = true;
            }
            if (flag)
            {
                cout << "Element found at key " << key << ": ";
                cout << en->studentData->getStudentId() << endl;
            }
            // cout << en->studentData->getStudentLastName() << endl;
            en = en->n;
        }
    }
    if (!flag)
        cout << "No Element found at key " << key << endl;
    cout << "########################################################################" << endl;
}

void StudentHashTable::ShowAllStudents(){
    for (int i = 0; i < hashTableSize; i++)
    {
        if(studentHashTable[i]!= NULL){
            cout << "########################################################################" << endl;
            cout<<"for index: "<<i<< " we have students. Lets See Them"<<endl;
            StudentHashTableEntry *en = studentHashTable[i];
            while(en != NULL){
                cout << "found student with id:\t"<<en->studentData->getStudentId();
                cout << "\tand name:\t" << en->studentData->getStudentLastName()<< "\t" << en->studentData->getStudentFirstName() << endl;
                en = en->n;
            }
        }
    }
}

StudentHashTable::~StudentHashTable()
{
    delete[] studentHashTable;
}