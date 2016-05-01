#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

Graph::Graph(){

}

Graph::~Graph(){
    cout << "Goodbye!" << endl;
}

void Graph::assignDistricts(){ //not working
    int districtCounter = 1;
    for(int i = 0; i < vertices.size(); i++){
        vertex *v = &vertices[i];

        int defaultDistrict = -1;

        if(v->district == -1){
            for(int j = 0; j < v->adj.size(); j++){//first check to see if any adjacent vertices have been assigned a district
                if(v->adj[j].v->district != -1){
                    defaultDistrict = v->adj[j].v->district;//if they have set that as default district
                    break;
                }
            }
            if(defaultDistrict == -1){ //if none of the vertices have been assigned then set equal to the district counter and increment
                defaultDistrict = districtCounter;
                districtCounter++;
            }
            v->district = defaultDistrict; // set main vertex to default district
        }else{
            defaultDistrict = v->district; //set default district to main vertex
        }

        for(int j = 0; j < v->adj.size(); j++){
            v->adj[j].v->district = defaultDistrict;
        }

    }

//    for(int i = 0; i < vertices.size(); i++){
//        vertex v = vertices[i];
//        cout << v.name << ":" << v.district << endl;
//    }
}

void Graph::shortestStorePath(string startS, string endS){
    vertex startStore;
    vertex endStore;
    bool startFound = false;
    bool endFound = false;
    for(int i = 0; i < vertices.size(); i++){
        if(startS == vertices[i].name || startS == vertices[i].store){
            startStore = vertices[i];
            startFound = true;
        }

        if(endS == vertices[i].name || endS == vertices[i].store){
            endStore = vertices[i];
            endFound = true;
        }
    }

    if(!startFound || !endFound){
        cout << "One or more of the cities or stores doesn't exist" << endl;
        return;
    }

    if(startStore.district == -1 || endStore.district == -1){
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    if(startStore.district != endStore.district){
        cout << "No safe path between stores" << endl;
        return;
    }

    queueVertex qv;
    startStore.visited = true;

    qv.path.push_back(&startStore);

    while(!qv.path.empty()){
        vertex *n = qv.path.back();

        if(n->name == endStore.name){
            vertex *temp = n;
            vector<vertex*> cities;
            while(temp->parent != NULL){
                cities.push_back(temp);
                temp = temp->parent;
            }
            cout << n->distance << "," << startStore.store + "(" + startStore.name + ")";
            for(int j = cities.size() - 1.0; j >= 0; j--){
                cout << "," << cities[j]->store + "(" + cities[j]->name + ")";
            }
            cout << endl;
            //vertices.clear();
            //initialize(fileName);
            //assignDistricts();
            for(int i = 0; i < vertices.size(); i++){
                vertices[i].visited = false;
            }
            return;
        }

//        n->visited = false;
//        n->parent = NULL;
//        n->distance = 0;
        qv.path.pop_back();
        vector<adjVertex> temp;
        temp.swap(n->adj);
        for(int i = temp.size() - 1.0; i >= 0; i--){
            if(!temp[i].v->visited){
                vertex *t = temp[i].v;
                t->visited = true;
                t->parent = n;
                t->distance = n->distance + 1;
                qv.path.push_back(t);
            }
        }
    }
}

void Graph::shortestCityPath(string startC, string endC){
    vertex startCity;
    vertex endCity;
    bool startFound = false;
    bool endFound = false;
    for(int i = 0; i < vertices.size(); i++){
        if(startC == vertices[i].name){
            startCity = vertices[i];
            startFound = true;
        }

        if(endC == vertices[i].name){
            endCity = vertices[i];
            endFound = true;
        }
    }

    if(!startFound || !endFound){
        cout << "One or more cities doesn't exist" << endl;
        return;
    }

    if(startCity.district == -1 || endCity.district == -1){
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    if(startCity.district != endCity.district){
        cout << "No safe path between cities" << endl;
        return;
    }

    queueVertex qv;
    startCity.visited = true;

    qv.path.push_back(&startCity);

    while(!qv.path.empty()){
        vertex *n = qv.path.back();

        if(n->name == endCity.name){
            vertex *temp = n;
            vector<vertex*> cities;
            while(temp->parent != NULL){
                cities.push_back(temp);
                temp = temp->parent;
            }
            cout << n->distance << "," << startCity.name;
            for(int j = cities.size() - 1.0; j >= 0; j--){
                cout << "," << cities[j]->name;
            }
            cout << endl;
            //vertices.clear();
            //initialize(fileName);
            //assignDistricts();
            for(int i = 0; i < vertices.size(); i++){
                vertices[i].visited = false;
            }
            return;
        }

//        n->visited = false;
//        n->parent = NULL;
//        n->distance = 0;
        qv.path.pop_back();
        vector<adjVertex> temp;
        temp.swap(n->adj);
        for(int i = temp.size() - 1.0; i >= 0; i--){
            if(!temp[i].v->visited){
                vertex *t = temp[i].v;
                t->visited = true;
                t->parent = n;
                t->distance = n->distance + 1;
                qv.path.push_back(t);
            }
        }
    }
}

void Graph::initializeCities(string fileName){
    ifstream inFile;
    inFile.open(fileName.c_str());//read in file
    string line;
    std::vector<std::string> cityNames;
    int lineCount = 0;
    if(inFile.good()){ //error check
        while(getline(inFile,line)){
            if(lineCount == 0){
                cityNames = split(line,",");
                for(int i = 1; i<cityNames.size(); i++){
                    addVertex(cityNames[i]);
                }
            }else{
                std::vector<std::string> cityWeights = split(line,",");
                string city = cityWeights[0];
                for(int i = 1; i < cityWeights.size(); i++){
                    int weight = std::stoi(cityWeights[i]);
                    if(weight != -1){
                        addEdge(city, cityNames[i], weight);
                    }
                }
            }
            lineCount++;
        }
    }
}

void Graph::initializeStores(string fileName){
    ifstream inFile;
    inFile.open(fileName.c_str());//read in file
    string line;

    if(inFile.good()){ //error check
        getline(inFile,line);
        std::vector<std::string> cityStores = split(line,",");
        for(int i = 0; i < vertices.size(); i++){
            vertices[i].store = cityStores[i];
        }
    }
}

void Graph::setStore(string name, string linkedName){
    vertices.back().store = name;
    for(int i = 0; i < vertices.size(); i++){
        if(linkedName == vertices[i].name){
            vertices.back().district = vertices[i].district;
            return;
        }
    }
}

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    //adjVertex av2;
                    //av2.v = &vertices[i];
                    //av2.weight = weight;
                    //vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        v.distance = 0;
        v.parent = NULL;
        vertices.push_back(v);

    }
}

void Graph::deleteCity(string name){
    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(vertices[i].adj[j].v->name == name){
                vertices[i].adj.erase(vertices[i].adj.begin() + j);
            }
        }
    }

    cout <<vertices.size() << endl;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name){
            vertices.erase(vertices.begin() + i);
        }
    }
    cout << vertices.size() << endl;
}

void Graph::printVertices(){
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].district << ":" + vertices[i].name + "(" + vertices[i].store + ")" << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout << vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1){
                cout << "***";
            }
        }
        cout << endl;
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }

}

std::vector<std::string> Graph::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}
