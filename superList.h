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
};

template <typename eltType>
Node<eltType>::Node() : data(std::nullopt) {}

template <typename eltType>
Node<eltType>::Node(const eltType& value) : data(value) {}

/*****************************************************************************************/

template <typename eltType>
class superList
{
    public:
        superList();
        explicit superList(int);
        explicit superList(std::initializer_list<eltType>);

        int size() const;
        Node<eltType> front();
        Node<eltType> back();

        std::shared_ptr<Node<eltType>> operator[](int) const;
        
        void insertRear(const eltType&);
        void insertFront(const eltType&);
        void insertOrdered(const eltType&);
        void insertBulk(const std::initializer_list<eltType>&);

    private:
        bool sizeImmutable = false, dataImmutable = false;
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
    sizeImmutable = true;
}

template <typename eltType>
superList<eltType>::superList(std::initializer_list<eltType> list)
{
    insertBulk(list);
    sizeImmutable = true, dataImmutable = true;
}

template <typename eltType>
void superList<eltType>::insertRear(const eltType& value)
{
    if(!sizeImmutable)
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
    else {throw std::logic_error("Error. Cannot alter immutable superList object");}
}

template <typename eltType>
void superList<eltType>::insertFront(const eltType& value)
{
    if(!sizeImmutable)
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
    else {throw std::logic_error("Error. Cannot alter immutable superList object");}
}

template <typename eltType>
void superList<eltType>::insertOrdered(const eltType& value)
{

}

template <typename eltType>
void superList<eltType>::insertBulk(const std::initializer_list<eltType>& list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
        {insertRear(*it);}
}

template <typename eltType>
int superList<eltType>::size() const
    {return nodeCount;}

template <typename eltType>
Node<eltType> superList<eltType>::front() 
    {return begin->get();}

template <typename eltType>
Node<eltType> superList<eltType>::back() 
    {return end->get();}

template <typename eltType>
std::shared_ptr<Node<eltType>> superList<eltType>::operator[](int index) const
{
    if(index < 0 || index > nodeCount-1)
        {throw std::out_of_range("Error. Reference to out of bounds index");}

    auto current = begin;
    for(int i=0; i != index; ++i)
        {current = current->next;}
    return current;
}

/**************************************************************************************/

template <typename eltType>
std::ostream& operator<<(std::ostream& os, const std::optional<eltType>& opt)
{
    if(opt.has_value())
        {os << opt.value();}
    else
        {os << "nullopt";}
    return os;
}

template <typename eltType>
std::ostream& operator<<(std::ostream& os, const superList<eltType>& list)
{
    for(int i=0; i<list.size(); ++i)
        {os << list[i]->data.value() << " ";}
    return os;
}

#endif