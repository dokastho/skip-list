#ifndef SKIP_H
#define SKIP_H

#include <vector>
#include <iostream>
#include <math.h>
#include <limits>

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
    node* head;
    int numRows,numNodes;

    void copy_row(node* end) {
        node* newEnd = new node;
        while (end)
        {
            end->down = newEnd;
            newEnd->up = end;
            newEnd->datum = end->datum;

            if (end->next)
            {
                newEnd->next = new node;
                newEnd->next->prev = newEnd;
            }

            newEnd = newEnd->next;
            end = end->next;
        }
        newEnd = nullptr; // cut off final entry;
    }

    void build_up(node* n) {
        if (rand() % 2 == 0)
        {
            node* upper = n->prev;
            T newDatum = n->datum;
            while (!upper->up)
            {
                if (upper->prev)
                {
                    upper = upper->prev;
                }
                else
                {
                    return;
                }
            }
            upper = upper->up;
            insert_between(newDatum,upper);
            n->up = upper->next;
            upper->next->down = n;
        }
        
    }

    void insert_between(const T& newDatum, node* n) {
        node* toInsert = new node;
        toInsert->prev = n;
        toInsert->next = n->next;
        toInsert->datum = newDatum;

        n->next = toInsert;
        if (toInsert->next)
        {
            toInsert->next->prev = toInsert;
        }
        
        build_up(toInsert);
    }

    public:

    skip_list() {
        node* dummy = new node;
        T small = T(-1 * INFINITY);
        dummy->datum = small;
        head = dummy;
        numNodes = 0;
        numRows = 0;
    }

    void insert(const T& newDatum) {
        node* at = find(newDatum);
        if (at->datum == newDatum)
        {
            return;
        }
        // insert using the current location from find
        else {
            if (numNodes == (pow(2,numRows + 1) - 1))
            {
                numRows++;
                // move node to end of row
                node* end = at;
                while (end->prev)
                {
                    end = end->prev;
                }
                
                copy_row(end);
                at = at->down;
            }
            
            insert_between(newDatum, at);
        }
        numNodes++;
        return;
    }

    void erase(const T& newDatum) {
        node* at = find(newDatum);
        if (at->datum != newDatum)
        {
            return;
        }

        numNodes--;
        // delete down
        while (at)
        {
            if (at->up)
            {
                delete at->up;
            }
            
            // delete the node
            if (at->prev)
            {
                at->prev->next = at->next;
            }
            if (at->next)
            {
                at->next->prev = at->prev;
            }
            at = at->down;
        }
    }

    node* find(const T& newDatum) {
        node* readHead = head;
        while (newDatum != readHead->datum)
        {
            if (readHead->next)
            {
                if (newDatum >= readHead->next->datum)
                {
                    readHead = readHead->next;
                    continue;
                }
                else if (readHead->down)
                {
                    readHead = readHead->down;
                    continue;
                }
                else {
                    break;
                }
            }
            else {
                if (readHead->down)
                {
                    readHead = readHead->down;
                    continue;
                }
                else {
                    break;
                }
            }
        }
        
        return readHead;
    }

    size_t size() {
        return numNodes;
    }
};

#endif