/**
 * This code contains the structure to create a directed graph
 * @author Monica Waterhouse Montoya
 * @version 1.0
 * @since 09/21/2020
 *
 */

#include <iostream>
#include "LinkedList.h"


/**
 * This class represents the vertex of the graph
 * @tparam T
 */

class Vertex{
    std::string value;
    int lead;
    int reached;

public:
    Vertex(std::string value){
        this->value = value;
        lead = 0;
        reached = 0;
    }
    ~Vertex(){
        delete this;
    }


    std::string getValue(){
        return this->value;
    }

    int getLeadNodes(){
        return this->lead;
    }

    int getReachedNodes(){
        return this->reached;
    }
    void addDestinyNode(){
        this->lead++;
    }
    void addIncomingNode(){
        this->reached++;
    }
    void deleteDestinyNode(){
        this->lead--;
    }
    void deleteIncomingNode(){
        this->reached--;
    }

};

/**
 * This class represents the edges of the graph
 */

class Edge{
    Vertex *start;
    Vertex *end;
    int cost;

public:
    Edge(Vertex *start, Vertex *end, int cost){
        this->start = start;
        this->end = end;
        this->cost = cost;
    }
    ~Edge(){
        delete start;
        delete end;
        delete this;
    }
    void modifyCost(int newCost){
        this->cost = newCost;
    }

    Vertex *getStartVertex(){
        return this->start;
    }

    Vertex*getEndNodes(){
        return this->end;
    }

    int getCost(){
        return this->cost;
    }
};

/**
 * This class represents a weighted graph
 */

class Graph{

    LinkedList<Vertex> *vertices;
    LinkedList<Edge> *edges;
    int numberVertices;

    /**
     * This method set the initial graph
     * @param i rhe amount of vertices that the graph will initially have.
     * @return the name of the variable just created.
     */

    std::string setVertices(int i){
        std::string inputValue;
        std::cout << "Name of vertex: " << i << " : ";
        std::cin >> inputValue;
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        while(ptr != nullptr){
            std::string name = ptr->getData()->getValue();
            if(inputValue.compare(name)== 0){
                std::cout << "The vertex '" << name << "' already exists! \n Try again! \n";
                return this->setVertices(i);
            }
            ptr = ptr->getNext();
        }
        return inputValue;
    }

    /**
     * This method initialize the graph according to the number of vertexes the user inputs when creating the graph.
     */
    void initializeGraph(){

        for (int i = 1; i <= numberVertices; i++){
            std::string name = this->setVertices(i);
            Vertex*newVertex = new Vertex(name);
            this->vertices->insertElement(newVertex);

        }

        std::cout << "Add the edges \n";
       this->checkVertexConnections();



    }

    /**
     * This method is used to return a vertex from the vertex list when given a value
     * @param value the value of the vertex the user wants to update
     * @return the vertex requested
     */
    Vertex* getVertex(std::string value){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        while(ptr != nullptr){
            std::string name = ptr->getData()->getValue();
            if(value.compare(name)== 0){
                return ptr->getData();
            }
            ptr = ptr->getNext();
        }
        std::cout<< "The vertex you are trying to reach doesn't exist in the graph! \n";
        return nullptr;
    }

public:


    Graph(int numberVertices){
        this->vertices = new LinkedList<Vertex>();
        this->edges = new LinkedList<Edge>();
        this->numberVertices = numberVertices;
        this->initializeGraph();
    }
    ~Graph(){
        delete this->vertices;
        delete this->edges;
        delete this;
    }

    LinkedList<Vertex> *getVertices(){
        return this->vertices;
    }

    void printVertices(){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        while(ptr != nullptr){
            std::cout << " " << ptr->getData()->getValue();
            ptr = ptr->getNext();
        }
        std::cout<<"\n";
        delete ptr;

    }

    bool containsVertex(std::string vertexName){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        while(ptr != nullptr){
            std::string name = ptr->getData()->getValue();
            if(vertexName.compare(name)== 0) {
                return true;
            }
            ptr = ptr->getNext();
        }
        return false;
    }


   void addVertex(){
        std::string inputValue;
        std::cout << "Name of the new vertex: ";
        std::cin >> inputValue;
        if(containsVertex(inputValue)){
            std::cout << "The vertex '" << inputValue << "' already exists! \n Try again! \n";
            this->addVertex();
        }
        else{
            Vertex *newVertex = new Vertex(inputValue);
            this->vertices->insertElement(newVertex);
        }

    }

    void deleteVertex(std::string vertexName){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();

        while(ptr != nullptr){
            if(ptr->getData()->getValue() == vertexName){
                this->vertices->remove(ptr->getData());
                return;
            }
            ptr = ptr->getNext();
        }
        std::cout <<"The vertex '"<< vertexName << "' doesn't belong to the graph \n";
    }

    void addEdge(std::string start, int cost, std::string end){
        Vertex *startVertex = this->getVertex(start);
        Vertex*endVertex = this->getVertex(end);

        Edge *newEdge = new Edge(startVertex, endVertex, cost);
        this->edges->insertElement(newEdge);

    }

    void checkVertexConnections(){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        Vertex *ptrV;

        while(ptr!= nullptr){
            Vertex *ptrVertex = ptr->getData();
            std::string vertexName;
            int cost;


            if(ptrVertex->getLeadNodes()==0){
                std::cout <<"The vertex '" << ptrVertex->getValue() << "' doesn't lead to another vertex. \n";
                std::cout <<"Add edge \n From " << ptrVertex->getValue() << "\n";
                std::cout << "To: ";
                std::cin >> vertexName;
                std::cout << "With a cost of: ";
                std::cin >>cost;

                this->addEdge(ptrVertex->getValue(), cost, vertexName);
                ptrV = this->getVertex(vertexName);
                ptrV->addIncomingNode();
                ptrVertex->addDestinyNode();
            }

            if(ptrVertex->getReachedNodes()==0){
                std::cout <<"The vertex '" << ptrVertex->getValue() << "' can't be reached. \n";
                std::cout <<"Add edge \n To " << ptrVertex->getValue() << "\n";
                std::cout << "From: ";
                std::cin >> vertexName;
                std::cout << "With a cost of: ";
                std::cin >>cost;

                this->addEdge(vertexName, cost, ptrVertex->getValue());
                ptrV = this->getVertex(vertexName);
                ptrV->addDestinyNode();
                ptrVertex->addIncomingNode();
            }

            ptr = ptr->getNext();
        }
    }

    /**
     * This method deletes a specific edge and the adjacent nodes for given vertexes
     * @param start the start vertex
     * @param end the end vertex
     */
    void deleteEdge(std::string start, std::string end){
        Vertex *startVertex = this->getVertex(start);
        Vertex *endVertex = this->getVertex(end);

        NodeLL<Edge> *ptrEdge = this->edges->getFirst();
        while(ptrEdge != nullptr){
            std::string startTemp = ptrEdge->getData()->getStartVertex()->getValue();
            std::string endTemp = ptrEdge->getData()->getEndNodes()->getValue();
            if(startTemp.compare(start)==0 && endTemp.compare(end)==0){
                edges->remove(ptrEdge->getData());
                return;
            }

            ptrEdge = ptrEdge->getNext();
        }

        std::cout << "There was no edge found with the given values! \n";
        delete startVertex;
        delete endVertex;

    }

    LinkedList<Edge> *getEdges(){
        return this->edges;
    }

};

int main(){

    Graph *graph = new Graph(4);
    graph->printVertices();

    graph->addVertex();
    graph->printVertices();

    std::string nameDelete;
    std::cout << "Which vertex do you want to delete?: ";
    std::cin>> nameDelete;
    std::cout<<"\n";
    graph->deleteVertex(nameDelete);
    graph->printVertices();


    return 0;
}


