#ifndef _superList_
#define _superList_
#include <memory>
#include <optional>

template <typename eltType>
class Node
{
    public:
        Node();
        explicit Node(const eltType&);
        std::shared_ptr<Node<eltType>> last = nullptr;
        std::shared_ptr<Node<eltType>> next = nullptr;
        std::optional<eltType> data;
        void erase();
};

template <typename eltType>
Node<eltType>::Node() : data(std::nullopt) {}

template <typename eltType>
Node<eltType>::Node(const eltType& value) : data(value) {}

template <typename eltType>
void Node<eltType>::erase() {data.reset();}

/*****************************************************************************************/

template <typename eltType>
class superList
{
    public:
        superList();
        explicit superList(int);
        explicit superList(std::initializer_list<eltType>);

        int size();
        Node<eltType> front();
        Node<eltType> back();

        std::shared_ptr<Node<eltType>> operator[](int);
        
        void insertRear(const eltType&);
        void insertFront(const eltType&);
        void insertOrdered(const eltType&);
        void insertBulk(const std::initializer_list<eltType>&);

    private:
        bool expansionAllowed = true;
        int nodeCount = 0;
        std::shared_ptr<Node<eltType>> begin = nullptr;
        std::shared_ptr<Node<eltType>> end = nullptr; 
};

template <typename eltType>
superList<eltType>::superList() 
    {insertRear(eltType());}

template <typename eltType>
superList<eltType>::superList(int size) 
{
    for(int i=0; i<size; ++i)
        {insertRear(eltType());}
    expansionAllowed = false;
}

template <typename eltType>
superList<eltType>::superList(std::initializer_list<eltType> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
        {insertRear(*it);}
    expansionAllowed = false;
}

template <typename eltType>
void superList<eltType>::insertRear(const eltType& value)
{
    if(expansionAllowed)
    {
        auto tempNode = std::make_shared<Node<eltType>>(value);
        if(nodeCount == 0) 
            {begin = end = tempNode;}
        else
        {
            end->next = tempNode;
            tempNode->last = end;
            end = tempNode;
        }
        ++nodeCount;
    }
    else {throw std::out_of_range("Error. Cannot alter immutable superList object");}
}

template <typename eltType>
void superList<eltType>::insertFront(const eltType& value)
{
    if(expansionAllowed)
    {
        auto tempNode = std::make_shared<Node<eltType>>(value);
        if(nodeCount == 0)
            {begin = end = tempNode;}
        else
        {
            begin->last = tempNode;
            tempNode->next = begin;
            begin = tempNode;
        }
        ++nodeCount;
    }
    else {throw std::out_of_range("Error. Cannot alter immutable superList object");}
}

template <typename eltType>
void superList<eltType>::insertOrdered(const eltType& value)
{

}

template <typename eltType>
void superList<eltType>::insertBulk(const std::initializer_list<eltType>& list)
{

}

template <typename eltType>
int superList<eltType>::size() 
    {return nodeCount;}

template <typename eltType>
Node<eltType> superList<eltType>::front() 
    {return begin->get();}

template <typename eltType>
Node<eltType> superList<eltType>::back() 
    {return end->get();}

template <typename eltType>
std::shared_ptr<Node<eltType>> superList<eltType>::operator[](int index)
{
    if(index < 0 || index > nodeCount-1)
        {throw std::out_of_range("Error. Reference to out of bounds index");}

    auto current = begin;
    for(int i=0; i != index; ++i)
        {current = current->next;}
    return current;
}

#endif