/**
 *
 * @author Monica Waterhouse Montoya
 * @since 09/21/2020
 * @version 1.0
 *
 * @brief code to create a directed Graph
 *
 */

#include <iostream>

template <typename T>

struct Node{
public:
    T value;
    Node *nextNode;
};

template <typename T>

class List{
public:
    Node<T> *first;

    List(){
        first = new Node<T>;
    }

    void addFirst(T value){
        this->first->value = value;
        this->first->nextNode = nullptr;
    }

    void printNodeValue(){
        std::cout << "This is the value: "<< first->value << " This is the address: " << this->first << " This is the next node: " << first->nextNode;
    }
};

int main(){

    List<int> lista;
    lista.addFirst(8);
    lista.printNodeValue();
};



