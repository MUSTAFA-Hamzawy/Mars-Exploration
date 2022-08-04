//
// Created by Mustafa Hamzawy on 8/3/2022.
//

#ifndef FILE_PRIORITYQUEUE_H
#define FILE_PRIORITYQUEUE_H

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Mission/Mission.h"
using namespace std;

struct Node{
    Mission mission;
    Node* next;
    int pri;
};

class PriorityQueue{

    int size;
    Node* head;
public:
    PriorityQueue(){

        size = 0;
        head = nullptr;
    }

    void push(Mission data, int priority){

        Node* inserted = new Node;
        inserted->mission = data;
        inserted->pri = priority;

        if (head == nullptr || priority > head->pri)
        {
            inserted->next = head;
            head = inserted;
        }else{
            Node* temp = head;
            while (temp->next != nullptr && temp->next->pri <= priority)
            {
                temp = temp->next;
                inserted->next = temp->next;
                temp->next = inserted;
            }
        }
        size++;
    }

    int get_size(){
        return size;
    }

    void pop()
    {
        if (head)
        {
            size--;
            Node *temp  = head;
            head = head->next;
            temp->next = nullptr;
            delete temp;
        }
    }

    Mission front(){

        if (head)
        {
            return head->mission;
        }
    }

    bool empty(){
        return size == 0 ;
    }

};



#endif //FILE_PRIORITYQUEUE_H
