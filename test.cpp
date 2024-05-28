#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>
#include "superList.h"

int main()
{
    //! Test 1
    std::cout << "\n\nTest 1:\t";
    superList<int> list1(3);
    for(int i=0; i<list1.size(); ++i)
        {std::cout << list1[i]->data.value() << " ";}

    //! Test 2
    std::cout << "\nTest 2:\t";
    superList<int> list2({1,2,3});
    for(int i=0; i<list2.size(); ++i)
        {std::cout << list2[i]->data.value() << " ";}

    //! Test 3
    std::cout << "\nTest 3:\t";
    superList<int> list3;
    std::cout << list3[0]->data.value() << " ";

    //! Test 4
    std::cout << "\nTest 4:\t";
    superList<std::string> list4(5);
    for(int i=0; i<list4.size(); ++i)
        {std::cout << list4[i]->data.value() << " ";}

    //! Test 5
    std::cout << "\nTest 5:\t";
    superList<std::string> list5({"hello", "meatball", "spongecake", "stringExample"});
    for(int i=0; i<list5.size(); ++i)
        {std::cout << list5[i]->data.value() << " ";}
    
    //! Test 6
    std::cout << "\nTest 6:\t";
    std::cout << list5;

    //! Test 7
    std::cout << "\nTest 7:\t";
    list3.insertBulk({14,15,6465,654,654,456,456});
    std::cout << list3;

    //! Test 8
    std::cout << "\nTest 8:\t";
    for(int i=0; i<list4.size(); ++i)
        {list4[i]->data = "Hello";}
    std::cout << list4;

    std::cout << "\n\n\n";
    return 0;
}

/*
    ! Size is default <1> if nothing is specified upon creation
        ? superList *list = new myList()            --> myList.size() == 1
        ? superList *list = new myList(1)           --> myList.size() == 1
    ! Defining contents of list upon creation makes list immutable
        ? superList<int> list(<contents>);          --> entirely immutable
        ? superList<int> list(<size>);              --> size immutable
        ? superList<int> list;                      --> entirely mutable
    ! Indexed doubly linked list
        * superList<int> list({1,2,3});
            ? cout << list[1]->data.value();        --> 2
            ? cout << list[1]->next->data.value();  --> 3
            ? cout << list[1]->last->data.value();  --> 1
            ? cout << list[0]->last->data.value();  --> Null
            ? cout << list[2]->next->data.value();  --> Null
            ? cout << list[4]->data.value();        --> Error. Reference to out of bounds index
    ! Print entire list using cout
        * superList<int> list({1,2,3});
            ? cout << list;                         --> [1,2,3]
    ! Head and rear pointer
    !   <front> and <back> point to a node object that will output its contents if cout is called on it
        * superList<int> list({1,2,3});
            ? cout << list->front()->data.value();  --> 1
            ? cout << list->back()->data.value();   --> 3
            ? cout << list->front().value();        --> 1
            ? cout << list->back().value();         --> 3
    ! Ordered and unordered insertion options both push and push_back style as well as bulk and indexed entry
        * superList<int> list;
            ? list.insertBulk(1,3,5);               --> [1,3,5]
            ? list.insertOrdered(4);                --> [1,3,4,5]
            ? list.insertFront(7);                  --> [7,1,3,4,5]
            ? list.insertRear(2);                   --> [7,1,3,4,5,2]
            ? list[1] = 4;                          --> [1,4,3,4,5,2]
        * superList<int> list(5);
            ? list.insertRear(6);                   --> Error. Cannot alter immutable superList object
    ! Deletion is typical linked list deletion plus ability to directly alter Node values using [].
    !   There will be no calls directly to Node object for changing values as to preserve immutability
        * superList<int> list;
            ? list.insertBulk(1,3,5,7,9);           --> [1,3,5,7,9]
            ? list.removeFront();                   --> [3,5,7,9]
            ? list.removeBack();                    --> [3,5,7]
            ? list.remove(1);                       --> [3,7]
            ? list.remove();                        --> Error. Not given an index
            ? list.remove(8);                       --> Error. Attempting to erase out of bounds index
            ? list.clear();                         --> []
    ! Assignment operator can be used to overwrite values in the superList object, but only if the list is mutable
        * superList<int> list({1,2,3});
            ? list[1] = 5;                          --> Error. Attempting to alter immutable superList object
            ? list.clear();                         --> Error. Attempting to alter immutable superList object
            ? list.remove(1);                       --> Error. Attempting to alter immutable superList object
        * superList<int> list;
        * list.insertBulk({1,2,3});
            ? list[2] = 5;                          --> [1,2,5]
            ? list.clear();                         --> []
            ? list.remove(1)                        --> [1,5]
*/