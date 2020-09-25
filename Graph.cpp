/**
 * This code contains the structure to create a directed graph
 * @author Monica Waterhouse Montoya
 * @version 1.0
 * @since 09/21/2020
 *
 */

#include <iostream>
#include "LinkedList.h"

template <typename T>
class Vertex{
    std::string value;
    LinkedList<T> *adjacentNodes;

public:
    Vertex(std::string value){
        this->value = value;
        adjacentNodes = new LinkedList<T>();
    }
    ~Vertex(){
        delete adjacentNodes;
        delete this;
    }
    std::string getValue(){
        return this->value;
    }
};

class AdjacentNodes{
    Vertex<AdjacentNodes> *adjNode;
    int cost;

public:
    AdjacentNodes(Vertex<AdjacentNodes> *adjacentNode, int cost){
        this->adjNode = adjacentNode;
        this->cost = cost;
    }
    ~AdjacentNodes(){
        delete this->adjNode;
        delete this;
    }

    int getCost(){
        return this->cost;
    }

    std::string returnValue(){
        return adjNode->getValue();
    }
};

int main(){

    LinkedList<Vertex<AdjacentNodes> > *vertexes = new LinkedList<Vertex<AdjacentNodes> >();
    Vertex<AdjacentNodes> *v1 = new Vertex<AdjacentNodes>("Hola");
    Vertex<AdjacentNodes> *v2 = new Vertex<AdjacentNodes>("soy");
    Vertex<AdjacentNodes> *v3 = new Vertex<AdjacentNodes>("Moni");

    vertexes->insertElement(v1);
    vertexes->insertElement(v2);
    vertexes->insertElement(v3);

    std::cout << vertexes->getFirst()->getNext()->getData()->getValue();

    return 0;
}


