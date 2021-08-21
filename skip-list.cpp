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
    
    return 0;
}