#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct node
{
    int data;
    node *next;
};

class LinkedList
{
    private : node *head, *tail;

    public:
        LinkedList();
        ~LinkedList();

        void insert_end(int value);
        void insert_start(int value);
        void insert_position(int pos, int value);
        
        void delete_head();
        void delete_tail();
        void delete_position(int pos);
        
        void display();
};

#endif