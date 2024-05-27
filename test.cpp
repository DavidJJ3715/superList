#include <iostream>
#include <string>
#include <memory>
#include "superList.h"

int main()
{
    superList<int> myList(3);
    for(int i=0; i<myList.size(); ++i)
        {std::cout << " " << myList[i]->data.value();}

    std::cout << std::endl;
    superList<int> list2({1,2,3});
    for(int i=0; i<list2.size(); ++i)
        {std::cout << " " << list2[i]->data.value();}
    return 0;
}

/*
    ! Size is default <1> if nothing is specified upon creation
        ? superList *myList = new myList()  --> myList.size() == 1
        ? superList *myList = new myList(1) --> myList.size() == 1
    ! Defining contents of list upon creation makes list immutable
        ? superList *myList = new myList(<contents>); == entirely immutable
        ? superList *myList = new myList(<size>); == size immutable
        ? superList *myList = new myList(); == entirely mutable
    ! Indexed doubly linked list
        * superList *myList = new myList({1,2,3});
            ? cout << temp[1];              --> 2
            ? cout << temp[1]->next;        --> 3
            ? cout << temp[1]->last;        --> 1
            ? cout << temp[0]->last;        --> Null
            ? cout << temp[2]->next;        --> Null
            ? cout << temp[4];              --> Error. Reference to out of bounds index
    ! Print entire list using cout
        * superList *myList = new myList({1,2,3});
            ? cout << myList;               --> [1,2,3]
    ! Head and rear pointer
    !   <front> and <back> point to a node object that will output its contents if cout is called on it
        * superList *myList = new myList({1,2,3});
            ? cout << myList->front()->data;--> 1
            ? cout << myList->back()->data; --> 3
            ? cout << myList->front();      --> 1
            ? cout << myList->back();       --> 3
    ! Ordered and unordered insertion options both push and push_back style as well as bulk and indexed entry
        * superList *myList = new myList();
            ? myList.insertBulk(1,3,5);     --> [1,3,5]
            ? myList.insertOrdered(4);      --> [1,3,4,5]
            ? myList.insertFront(7);        --> [7,1,3,4,5]
            ? myList.insertRear(2);         --> [7,1,3,4,5,2]
            ? myList[1] = 4;                --> [1,4,3,4,5,2]
        * superList *myList = new myList({1,3,5})
        * superList *myList = new myList(5)
            ? myList.insertRear(6);         --> Error. Cannot alter immutable superList object
    ! Deletion is typical linked list deletion plus ability to directly alter Node values using [].
    !   Changes done directly to Node object will have no affect on the superList object
        * superList *myList = new myList()
            ? myList.insertBulk(1,3,5,7,9); --> [1,3,5,7,9]
            ? myList.removeFront();         --> [3,5,7,9]
            ? myList.removeBack();          --> [3,5,7]
            ? myList.remove(1);             --> [3,7]
            ? myList[1].erase();            --> [3,Null] *Note that Node object still exists, but has a Null value*
            ? myList[2].erase();            --> Error. Reference to out of bounds index
            ? myList.remove();              --> Error. Not given an index
            ? myList.remove(8);             --> Error. Attempting to erase out of bounds index
            ? myList.clear();               --> [Null]
*/