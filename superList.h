#ifndef _superList_
#define _superList_
#include <memory>
#include <optional>

template <typename eltType>
class Node
{
    public:
        Node();
        std::shared_ptr<Node<eltType>> last = nullptr;
        std::shared_ptr<Node<eltType>> next = nullptr;
        std::optional<eltType> data;
        void erase();
};

template <typename eltType>
Node<eltType>::Node() : data(std::nullopt) {}

template <typename eltType>
void Node<eltType>::erase() {data.reset();}

/*****************************************************************************************/

template <typename eltType>
class superList
{
    public:
        std::shared_ptr<Node> front = nullptr;
        std::shared_ptr<Node> back = nullptr;
    
    private:
        int nodeCount = 1;

};

#endif