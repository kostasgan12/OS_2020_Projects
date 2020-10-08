#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
};

class linkedList
{
    private : node *head, *tail;

    public:
        linkedList();

        void insert_end(int value);
        void insert_start(int value);
        void insert_position(int pos, int value);
        
        void delete_head();
        void delete_tail();
        void delete_position(int pos);
        
        void display();
};

#endif