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
    void addAdjNode(T *adjNode){
        adjacentNodes->insertElement(adjNode);
    }
    LinkedList<T> *getAdjNodes(){
        return this->adjacentNodes;
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

    std::string getValue(){
        return this->adjNode->getValue();
    }
};

class Graph{

    LinkedList<Vertex<AdjacentNodes> > *vertexes;
    int numberVertexes;

public:
    Graph(int numberVertexes){
        this->vertexes = new LinkedList<Vertex<AdjacentNodes> >();
        this->numberVertexes = numberVertexes;
    }
    ~Graph(){
        delete this->vertexes;
        delete this;
    }

    void createGraph(){
        Vertex<AdjacentNodes> *v1 = new Vertex<AdjacentNodes>("A");
        Vertex<AdjacentNodes> *v2 = new Vertex<AdjacentNodes>("B");
        Vertex<AdjacentNodes> *v3 = new Vertex<AdjacentNodes>("C");

        this->vertexes->insertElement(v1);
        this->vertexes->insertElement(v2);
        this->vertexes->insertElement(v3);
    }

    void addAdjacency(int cost, Vertex<AdjacentNodes> *node){
        AdjacentNodes *adjNode = new AdjacentNodes(this->vertexes->getFirst()->getNext()->getData(), cost);
        this->vertexes->getFirst()->getData()->addAdjNode(adjNode);

    }

    void printFirst(){
        std::cout<< vertexes->getFirst()->getData()->getValue() <<"\n";
        std::cout<< "This is the adjacent node for v1: " << vertexes->getFirst()->getData()->getAdjNodes()->getFirst()->getData()->getValue();
        std::cout<< "This is the cost: " << vertexes->getFirst()->getData()->getAdjNodes()->getFirst()->getData()->getCost();
    }

    LinkedList<Vertex<AdjacentNodes> > *getVertexes(){
        return this->vertexes;
    }

};

int main(){

    Graph *graph = new Graph(7);
    graph->createGraph();
    graph->addAdjacency(10, graph->getVertexes()->getFirst()->getNext()->getData());
    graph->printFirst();


    return 0;
}


