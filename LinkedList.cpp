/**
 * @brief This code contains the data structures and algortithms that are neccesary to create a graph to which a Floyd-Marshall
 * algorithm will be applied to.
 *
 * @author Mónica Waterhouse.
 * @version 1.0
 * @since 09/20/2020
 *
*/

#include <iostream>

template <typename T>
class NodeLL{

    T data;
    NodeLL<T> *nextNode;

public:
    NodeLL(T data){
        this->data = data;

    }

    ~NodeLL(){
        delete nextNode;
        delete this;
    }

    T getData(){
        return this->data;
    }

    NodeLL<T> *getNext(){
        return this->nextNode;
    }

    void setNext(NodeLL<T> *element){
        this->nextNode = element;
    }

};

template <typename T>

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

    void insertElement(T data){
        NodeLL<T> *newNode = new NodeLL<T>(data);
        NodeLL<T> *tempPtr = this->head;

        newNode->setNext(nullptr);

        if(this->head == nullptr){
            this->head = newNode;
            return;
        }

        while(tempPtr->getNext() != nullptr){
            tempPtr = tempPtr->getNext();
        }

        tempPtr->setNext(newNode);
        return;
    }

    void printList()
    {
        NodeLL<T> *node = this->head;
        while (node != NULL)
        {
            std::cout <<" "<<node->getData();
            node = node->getNext();
        }
    }
};

int main(){
    LinkedList<std::string> *list = new LinkedList<std::string>();
    list->insertElement("Hola");
    list->insertElement("soy");
    list->insertElement("Moni");
    list->printList();
    return 0;
}

