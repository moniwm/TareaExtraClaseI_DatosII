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
     * This method initialize the graph according to the number of vertexes the user inputs when creating the graph.
     */
    void initializeGraph(){

        std::string name = "A";
        Vertex*newVertex = new Vertex(name);
        this->vertices->insertElement(newVertex);

        name = "B";
        Vertex*newVertex2 = new Vertex(name);
        this->vertices->insertElement(newVertex2);

        addEdge("A", 5, "B");
        addEdge("B", 5, "A");

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


    Graph(){
        this->vertices = new LinkedList<Vertex>();
        this->edges = new LinkedList<Edge>();
        this->initializeGraph();
        this->numberVertices = this->vertices->getSize();
    }
    ~Graph(){
        delete this->vertices;
        delete this->edges;
        delete this;
    }

    LinkedList<Vertex> *getVertices(){
        return this->vertices;
    }

    std::string printVertices(){
        std::string vertices = "";
        NodeLL<Vertex> *ptr = this->vertices->getFirst();
        while(ptr != nullptr){
            std::string vertexName = ptr->getData()->getValue();
            vertices = vertices+vertexName;
            std::cout << " " << vertexName;
            ptr = ptr->getNext();
        }
        std::cout<<"\n";
        delete ptr;

        return vertices;

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


   std::string addVertex(std::string inputValue){


        if(this->containsVertex(inputValue)){
            return "The vertex already exists in the graph!";
        }
       Vertex *newVertex = new Vertex(inputValue);
       this->vertices->insertElement(newVertex);
       return "The vertex has been succesfully added!";


    }

    void deleteVertex(std::string vertexName){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();

        while(ptr != nullptr){
            if(ptr->getData()->getValue() == vertexName){
                this->vertices->remove(ptr->getData());
                deleteEdge(vertexName);
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

    /**
     * This method is used to make sure that every vertex has a connection to it and from it.
     */

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
                startVertex->deleteDestinyNode();
                endVertex->deleteIncomingNode();
                return;
            }

            ptrEdge = ptrEdge->getNext();
        }

        std::cout << "There was no edge found with the given values! \n";
        delete startVertex;
        delete endVertex;

    }

    bool doesEdgeExist(std::string start, std::string end){

        NodeLL<Edge> *ptrEdge = this->edges->getFirst();
        while(ptrEdge != nullptr){
            std::string startTemp = ptrEdge->getData()->getStartVertex()->getValue();
            std::string endTemp = ptrEdge->getData()->getEndNodes()->getValue();
            if(startTemp.compare(start)==0 && endTemp.compare(end)==0){
                return true;
            }

            ptrEdge = ptrEdge->getNext();
        }

        return false;
    }

    void deleteEdge(std::string vertexName){
        NodeLL<Edge> *ptrEdge = this->edges->getFirst();

        while(ptrEdge != nullptr){
            std::string startTemp = ptrEdge->getData()->getStartVertex()->getValue();
            std::string endTemp = ptrEdge->getData()->getEndNodes()->getValue();

            if(startTemp == vertexName) {
                ptrEdge->getData()->getEndNodes()->deleteIncomingNode();
                this->edges->remove(ptrEdge->getData());
            }
            else if(endTemp == vertexName){
                ptrEdge->getData()->getStartVertex()->deleteDestinyNode();
                this->edges->remove(ptrEdge->getData());
            }

            ptrEdge = ptrEdge->getNext();
        }
        checkVertexConnections();
    }



    Edge *getEdge(std::string start, std::string end){

        NodeLL<Edge> *ptrEdge = this->edges->getFirst();
        while(ptrEdge != nullptr){
            std::string startTemp = ptrEdge->getData()->getStartVertex()->getValue();
            std::string endTemp = ptrEdge->getData()->getEndNodes()->getValue();
            if(startTemp.compare(start)==0 && endTemp.compare(end)==0){
                return ptrEdge->getData();
            }
            ptrEdge = ptrEdge->getNext();
        }
        return nullptr;
    }

    /**
     * This method creates an adjacency matrix with the graph vertices and then it creates a new matrix
     * with the shortest path between each pair of vertices.
     *
     */

    void floydWarshall(){

        numberVertices = this->vertices->getSize();
        int adjMatrix[numberVertices][numberVertices];
        int infinite = 999999;

        /**
         * This part of the method creates the adjacency matrix.
         */
        std::string start;
        std::string end;
        NodeLL<Vertex> *rowPtr = this->vertices->getFirst();
        NodeLL<Vertex> *columnPtr;

        for(int i = 0; i < numberVertices; i++){
            start = rowPtr->getData()->getValue();
            columnPtr = this->vertices->getFirst();

            for(int j = 0; j < numberVertices; j++){
                end = columnPtr->getData()->getValue();
                if (start == end){
                    adjMatrix[i][j] = 0;
                }
                else{
                    if(doesEdgeExist(start, end)){
                        adjMatrix[i][j] = this->getEdge(start, end)->getCost();
                    }
                    else{
                        adjMatrix[i][j] = infinite;
                    }
                }

                columnPtr = columnPtr->getNext();
            }

            rowPtr = rowPtr->getNext();
        }

        /**
         * This part implements the Floyd Warshall algorithm to modify the adjacency matrix
         * in order to obtain a matrix with the cheapest cost from one vertex to another.
         */

        int newDistance;

        for(int k = 0; k < numberVertices; k++){
            for(int i = 0; i < numberVertices; i++){
                for(int j = 0; j < numberVertices; j++){
                    newDistance = adjMatrix[i][k] + adjMatrix[k][j];
                    if(newDistance < adjMatrix[i][j]){
                        adjMatrix[i][j] = newDistance;
                    }
                }
            }
        }

    }



};



