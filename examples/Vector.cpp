#include <vector>
#include <iostream>
using namespace std;

#include "cods/Vector.h"
CODS_USING_NAMESPACE

int main(int argc, char **argv) {
  // First constructor.
  {
    Vector<int, 3> vec;

    cout << "===" << endl << "First constructor" << endl << "===" << endl << endl;

    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Appending 10" << endl;
    vec.append(10);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Prepending 9, 8" << endl;
    vec.prepend(9);
    vec.prepend(8);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Inserting 3 at 1" << endl;
    vec.insert(1, 3);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Shrink to fit" << endl;
    vec.shrinkToFit();
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Clearing" << endl;
    vec.clear();
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    cout << endl << "Appending 20, 30, 30, 50" << endl;
    vec.append(20);
    vec.append(30);
    vec.append(30);
    vec.append(50);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    int pos = 2;
    cout << endl << "Value at position = " << pos << " is: " << vec[pos] << endl;

    cout << endl << "Removing 30" << endl;
    vec.remove(30);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();

    pos = 1;
    cout << endl << "Remove at position = " << pos << endl;
    vec.removeAt(pos);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();
  }

  // Second constructor.
  {
    cout << endl << "===" << endl << "Second constructor" << endl << "===" << endl << endl;

    Vector<int> vec(3, 9);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();
  }

  // Third constructor.
  {
    cout << endl << "===" << endl << "Third constructor" << endl << "===" << endl << endl;

    auto *arr = new int[3] {2, 4, 8};
    Vector<int> vec(3, arr);
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();
    delete[] arr;
  }

  // Fourth constructor.
  {
    cout << endl << "===" << endl << "Fourth constructor" << endl << "===" << endl << endl;

    std::vector<int> svec{1, 2, 3};

    Vector<int, 5> vec(svec.begin(), svec.end());
    cout << "Vector: capacity: " << vec.capacity()
         << ", size: " << vec.size() << endl;
    vec.print();
  }

  return 0;
}
