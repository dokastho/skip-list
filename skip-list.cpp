#include "skip-list.h"

int main() {
    skip_list<int> sl;
    sl.insert(1);
    for (int i = 0; i < 10; i++)
    {
        sl.insert(2 * i);
    }

    cout << "Test 1\n";
    if (sl.size() == 11)
    {
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed Insertion Test\n";
        cout << "Actual: " << sl.size() << "\n";
        cout << "Expected: 11\n";
    }
    
    cout << "Test 2\n";
    if (sl.find(1)->datum == 1)
    {
        cout << "Passed\n";
    }
    else {
        cout << "Item 1 wasn't found\n";
    }

    cout << "Test 3\n";
    if (sl.find(0)->datum == 0)
    {
        cout << "Passed\n";
    }
    else {
        cout << "Item 0 wasn't found\n";
    }

    cout << "Test 4\n";
    sl.erase(1);
    if (sl.find(1)->datum != 1)
    {
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed Deletion Test\n";
    }

    cout << "Test 5\n";
    if (sl.size() == 10)
    {
        cout << "Passed\n";
    }
    else {
        cout << "Failed Insertion Test\n";
        cout << "Actual: " << sl.size() << "\n";
        cout << "Expected: 10\n";
    }
    
    return 0;
}