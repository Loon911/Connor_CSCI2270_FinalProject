#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    int ID;
    std::string name;
    int district;
    bool visited;
    int distance;
    vertex *parent;
    std::vector<adjVertex> adj;
    std::string store;
};

struct queueVertex{
    int distance;
    std::vector<vertex *> path;
};
class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void initializeCities(std::string fileName);
        void initializeStores(std::string fileName);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistricts();
        void BFTraversalLabel(std::string startingCity, int distID);
        void shortestCityPath(std::string startingCity,std::string endingCity);
        void shortestStorePath(std::string startingCity,std::string endingCity);
        vertex * findVertex(std::string name);
        void printVertices();
        void deleteCity(std::string name);
        void setStore(std::string storeName, std::string linkedName);

    protected:
    private:
        std::vector<std::string> split(std::string text, std::string separator);
        std::vector<vertex> vertices;

};

#endif // GRAPH_H
