/**
 * @brief This code contains the structure for a Linked List using generics.
 *
 * @author Mónica Waterhouse.
 * @version 1.0
 * @since 09/20/2020
 *
*/

#include <iostream>

template <typename T> /// template is used to add flexibility to the class and methods so we can work with different data types.

/**
 * The NodeLL class represents each node of a linked list.
 * @tparam T The data type that will be stored in the node
 */
class NodeLL{

    T *data;
    NodeLL<T> *nextNode;

public:
    NodeLL(T *data){
        this->data = data;

    }

    ~NodeLL(){
        delete nextNode;
        delete this;
    }

    /**
     *
     * @return returns the data stored in the node
     */

    T *getData(){
        return this->data;
    }

    /**
     *
     * @return returns a pointer to the adjacent node
     */

    NodeLL<T> *getNext(){
        return this->nextNode;
    }

    void setNext(NodeLL<T> *element){
        this->nextNode = element;
    }

};

template <typename T>

/**
 * This class contains the structure to create a basic Linked List
 * @tparam T allows to create linked lists with different data types
 */
class LinkedList{

    NodeLL<T> *head;
    int size;

public:

    LinkedList(){
        this->head = nullptr;
        this->size = 0;
    }
    ~LinkedList(){
        delete this;
    }

    /**
     *
     * @param data the data value that will be stored in a node at the end of the list
     */
    void insertElement(T *data){
        NodeLL<T> *newNode = new NodeLL<T>(data);
        NodeLL<T> *tempPtr = this->head;

        newNode->setNext(nullptr);

        if(this->head == nullptr){
            this->head = newNode;
            this->size++;
            return;
        }

        while(tempPtr->getNext() != nullptr){
            tempPtr = tempPtr->getNext();
        }

        tempPtr->setNext(newNode);
        this->size++;
        return;
    }

    /**
     *
     * @param data the value of the data the user wants to look for
     * @return true if the data exists in the list, otherwise it return false
     */
    bool contains(T data){
        NodeLL<T> *tempPtr = head;
        while(tempPtr != nullptr){
            if(tempPtr->getData().compare(data) == 0){
                return true;
            }
            tempPtr = tempPtr->getNext();
        }
        return false;
    }

    NodeLL<T> *getFirst(){
        return this->head;
    }

    /**
     *
     * @param data the value of the data that the user wants to eliminate and
     */
    void remove(T *data){

        NodeLL<T> *currentPtr = this->head;
        NodeLL<T> *nextPtr = currentPtr->getNext();

        if(head->getData()==data){
            this->head = head->getNext();
            this->size--;
            return;
        }

        while (nextPtr != nullptr){

            if(nextPtr->getData() == data) {
                currentPtr->setNext(nextPtr->getNext());
                this->size--;
                return;
            }

            currentPtr = currentPtr->getNext();
            nextPtr = currentPtr->getNext();
        }

    }

    void printList()
    {
        NodeLL<T> *node = this->head;
        while (node != NULL)
        {
            std::cout <<" "<<node->getData();
            node = node->getNext();
        }
        delete node;
    }

    int getSize(){
        return this->size;
    }
};

