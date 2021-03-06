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
    std::string adjacencyMatrix;


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

        numberVertices = this->vertices->getSize();
        std::string vertices = std::to_string(numberVertices);
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

    std::string deleteVertex(std::string vertexName){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();

        while(ptr != nullptr){
            if(ptr->getData()->getValue() == vertexName){
                this->vertices->remove(ptr->getData());
                this->deleteEdge(vertexName);
                return "The vertex was successfully deleted!";
            }
            ptr = ptr->getNext();
        }

        return "Done";
    }

    std::string addEdge(std::string start, int cost, std::string end){

        Vertex *startVertex = this->getVertex(start);
        Vertex*endVertex = this->getVertex(end);

        if(doesEdgeExist(start, end)){
            return "The edge requested already exist!";
        }

        Edge *newEdge = new Edge(startVertex, endVertex, cost);
        startVertex->addDestinyNode();
        endVertex->addIncomingNode();

        this->edges->insertElement(newEdge);
        return "The edge was successfully added!";

    }

    /**
     * This method is used to make sure that every vertex has a connection to it and from it.
     */

    bool missingVertexConnections(){
        NodeLL<Vertex> *ptr = this->vertices->getFirst();

        while(ptr!= nullptr){
            Vertex *ptrVertex = ptr->getData();
            std::string vertexName;


            if(ptrVertex->getLeadNodes()==0 || ptrVertex->getReachedNodes()==0){
                return true;
            }

            ptr = ptr->getNext();
        }
        return false;
    }

    /**
     * This method deletes a specific edge and the adjacent nodes for given vertexes
     * @param start the start vertex
     * @param end the end vertex
     */
    std::string deleteEdge(std::string start, std::string end){
        Vertex *startVertex = this->getVertex(start);
        Vertex *endVertex = this->getVertex(end);

        NodeLL<Edge> *ptrEdge = this->edges->getFirst();
        while(ptrEdge != nullptr){
            std::string startTemp = ptrEdge->getData()->getStartVertex()->getValue();
            std::string endTemp = ptrEdge->getData()->getEndNodes()->getValue();
            if(startTemp.compare(start)==0 && endTemp.compare(end)==0){
                this->edges->remove(ptrEdge->getData());
                startVertex->deleteDestinyNode();
                endVertex->deleteIncomingNode();
                return "The edge was successfully deleted !";
            }

            ptrEdge = ptrEdge->getNext();
        }

        return "There was no edge found with the given values! ";

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

    std::string getAdjacencyMatrix(){
        numberVertices = this->vertices->getSize();
        int adjMatrix[numberVertices][numberVertices];
        int infinite = 999999;
        adjacencyMatrix = this->printVertices();

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
                    adjacencyMatrix = adjacencyMatrix+"0";
                }
                else{
                    if(doesEdgeExist(start, end)){
                        int edgeCost = this->getEdge(start, end)->getCost();
                        adjMatrix[i][j] = edgeCost;
                        adjacencyMatrix = adjacencyMatrix + std::to_string(edgeCost);
                    }
                    else{
                        adjMatrix[i][j] = infinite;
                        adjacencyMatrix = adjacencyMatrix + "-";
                    }
                }

                columnPtr = columnPtr->getNext();
            }

            rowPtr = rowPtr->getNext();
        }

        return this->adjacencyMatrix;
    }

    std::string floydWarshall(std::string startVertex, std::string endVertex){

        std::string vertexValues;
        vertexValues = this->printVertices();

        if(missingVertexConnections()){
            return "Verify that all the vertices lead and can be reached by at least one other vertex!";
        }

        char charStart[startVertex.size()+1];
        startVertex.copy(charStart, startVertex.size());

        char charEnd[endVertex.size()+1];
        endVertex.copy(charEnd, endVertex.size());

        numberVertices = this->vertices->getSize();
        int adjMatrix[numberVertices][numberVertices];
        int infinite = 999999;
        std::string shortestPath = startVertex;
        int intStart;
        int intEnd;
        int shortestInt = 0;

        char charVertices[vertexValues.size()+1];
        vertexValues.copy(charVertices, vertexValues.size());

        for (int i = 0; i < vertexValues.size(); i++){
            if (charStart[0] == charVertices[i]){
                intStart = i;
            }
            else if(charEnd[0] == charVertices[i]){
                intEnd = i;
            }
        }

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

                        if(i == intStart && j == intEnd){
                            shortestPath = shortestPath + vertexValues[k];
                            shortestInt = adjMatrix[i][j];
                        }

                    }
                }
            }
        }

        shortestPath = shortestPath + endVertex;
        std::string costStr = std::to_string(shortestInt);

        std::string message = "The shortest path is ";

        for (int i = 0; i  < shortestPath.size(); i ++){
            if(i!=shortestPath.size()-1){
                message = message + shortestPath[i] + "->";
            }
            else{
                message = message + costStr;
            }

        }

        message = "with a cost of: " + costStr;

        return message;

    }



};



