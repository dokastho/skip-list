#ifndef SKIP_H
#define SKIP_H

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
class skip_list {
    struct node {
        T datum;
        int* prev;
        int* next;
        int* down;
        int* up;
    };
    node* head = nullptr;
    node* current = head;
    int numRows = 0,numNodes = 0;

    void copy_row(node* end) {
        node* newEnd = new node;
        while (end)
        {
            end->down = newEnd;
            newEnd->up = end;
            newEnd->datum = end->datum;

            newEnd->next = new node;
            newEnd->next->prev = newEnd;

            newEnd = newEnd->next;
            end = end->next;
        }
        newEnd = nullptr; // cut off final entry;
    }

    void build_up(node* n) {
        if (rand() % 2 == 0)
        {
            node* newDown = n;
            T newDatum = n->datum;
            n = n->prev;
            while (!n->up)
            {
                n = n->prev;
            }
            insert_between(newDatum,n);
            n->down = newDown;
            n->newDown->up = n;
        }
        
    }

    void insert_between(T& newDatum, node* n) {
        node* toInsert = new node;
        toInsert->prev = n;
        toInsert->next = n->next;
        toInsert->datum = newDatum;

        n->next = toInsert;
        toInsert->next->prev = toInsert;
    }

    public:

    void insert_helper(const T& newDatum) {
        if (find(newDatum))
        {
            return;
        }
        numNodes++;
        insert(newDatum,current);
    }

    void insert(const T& newDatum) {
        if (current->next == nullptr)
        {
            //insert the node to the right if bottom row has space
            if (numNodes != pow(2,numRows + 1) - 1)
            {
                insert_between(newDatum,current);
            }
            
            else if (current->down == nullptr)
            {
                node* end = head;
                while (end->down)
                {
                    end = end->down;
                }
                copy_row(end);
            }
            
            current = current->down;
            insert(newDatum);
        }
        
        else if (abs(newDatum) > abs(current->datum)) // operator is wrong, make custom comparator that compares using abs newDatum
        {
            current = current->next;
            insert(newDatum);
        }
        else {
            // insert in between two nodes
            insert_between(current);
        }
    }

    void erase_helper(const T& newDatum) {
        if (!find(newDatum))
        {
            return;
        }
        numNodes--;
        erase();
        
    }

    void erase() {
        current->prev->next = current->next;
        if (current->next)
        {
            current->next->prev = current->prev;
        }
        if (current->up)
        {
            current = current->up;
            delete current->down;
            current->down = nullptr;
            erase();
        }
        else {
            delete current;
            current = nullptr;
        }
    }

    bool find(const T& newDatum) {
        while (newDatum != current->datum)
        {
            if (abs(newDatum) > abs(current->datum))
            {
                if (current->next)
                {
                    current = current->next;
                }
                else if (current->down)
                {
                    current = current->down;
                }
            }
            else {
                return false;
            }
        }
        
        return true;
    }

    size_t size() {
        return numNodes;
    }
};

#endif