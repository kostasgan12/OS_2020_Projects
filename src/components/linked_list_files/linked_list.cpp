#include "../../header_files/linked_list.h"

linkedList::linkedList()
{
    head = NULL;
    tail = NULL;
}

void linkedList::insert_end(int value)
{
    node *temp = new node;
    temp->data = value;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

void linkedList::insert_start(int value)
{
    node *temp = new node;
    temp->data = value;
    temp->next = head;
    head = temp;
}

void linkedList::insert_position(int pos, int value)
{
    node *previous = new node;
    node *current = new node;
    node *temp = new node;
    current = head;
    for (int i = 1; i < pos; i++)
    {
        previous = current;
        current = current->next;
    }
    temp->data = value;
    previous->next = temp;
    temp->next = current;
}

void linkedList::delete_head()
{
    node *temp = new node;
    temp = head;
    head = head->next;
    delete temp;
}

void linkedList::delete_tail()
{
    node *current = new node;
    node *previous = new node;
    current = head;
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }
    tail = previous;
    previous->next = NULL;
    delete current;
}

void linkedList::delete_position(int pos)
{
    node *current = new node;
    node *previous = new node;
    current = head;
    for (int i = 1; i < pos; i++)
    {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
}

void linkedList::display()
  {
    node *temp=new node;
    temp=head;
    while(temp!=NULL)
    {
      cout<<temp->data<<"\t";
      temp=temp->next;
    }
  } 