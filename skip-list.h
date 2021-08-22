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
        node* prev;
        node* next;
        node* down;
        node* up;
    };
    bool diff_comp(T lhs, T rhs) {
        return abs(lhs - head->datum) > abs(rhs - head->datum);
    }
    node* head = nullptr;
    node* current;
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

    void insert_between(const T& newDatum, node* n) {
        node* toInsert = new node;
        toInsert->prev = n;
        toInsert->next = n->next;
        toInsert->datum = newDatum;

        n->next = toInsert;
        toInsert->next->prev = toInsert;
    }

    public:

    void insert(const T& newDatum) {
        if (head == nullptr)
        {
            head = new node;
            head->datum = newDatum;
            current = head;
            numNodes++;
            return;
        }
        if (find(newDatum))
        {
            return;
        }
        
        numNodes++;
        insert_helper(newDatum);
    }

    void insert_helper(const T& newDatum) {
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
            insert_helper(newDatum);
        }
        
        else if (diff_comp(newDatum,current->datum)) // operator is wrong, make custom comparator that compares using abs newDatum
        {
            current = current->next;
            insert_helper(newDatum);
        }
        else {
            // insert in between two nodes
            insert_between(newDatum,current);
        }
    }

    void erase(const T& newDatum) {
        if (head == nullptr)
        {
            return;
        }
        
        if (!find(newDatum))
        {
            return;
        }
        numNodes--;
        erase();
        
    }

    void erase_helper() {
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
            erase_helper();
        }
        else {
            delete current;
            current = nullptr;
        }
    }

    bool find(const T& newDatum) {
        while (newDatum != current->datum)
        {
            if (diff_comp(newDatum,current->datum))
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