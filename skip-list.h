#ifndef SKIP_H
#define SKIP_H

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
class skip_list {
    vector<vector<T>> items;
    public:

    skip_list() {
        items.resize(16);
        for (size_t i = 0; i < items.size(); i++)
        {
            size_t length = pow(2,i);
            items[i].resize(length);
        }
        
    }

    void insert(const T& datum) {
        for (size_t row = 0; row < items.size(); row++)
        {
            for (size_t col = 0; col < items[row].size(); col++)
            {
                if (datum > )
                {
                    
                }
                
            }
            
        }
        
    }

    void erase(const T& datum) {

    }

    T& find(const T& datum) {

    }
};

#endif