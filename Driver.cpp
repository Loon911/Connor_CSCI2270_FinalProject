#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]){

    int command = 0;
    string cityFileName = argv[1];//this is the filename for the cities
    string cityStoresFileName = argv[2];//this is the filename for the stores
    string startCity, startStore;
    string endCity, endStore;
    string newCity, linkedCity, newStore;

    Graph g;

    g.initializeCities(cityFileName);//initialize the cities
    g.initializeStores(cityStoresFileName);//assign each store to the city

    g.assignDistricts();


    while(command != 5){

        cout << "======Main Menu======" << endl;
        cout << "1. Print connected cities" << endl;
        cout << "2. Find shortest path to city" << endl;
        cout << "3. Find shortest path to store" << endl;
        cout << "4. Add recovered city to list" << endl;
        cout << "5. Quit" << endl;

        cin >> command;

        switch (command) {
            case 1:
                g.printVertices();//print the list of cities
                break;

            case 2:
                cout << "Enter a starting city:" << endl;
                cin.ignore();
                getline(cin,startCity);
                cout << "Enter an ending city:" << endl;
                getline(cin,endCity);
                g.shortestCityPath(startCity, endCity);

                break;

            case 3:
                cout << "Enter a starting city or store:" << endl;
                cin.ignore();
                getline(cin,startStore);
                cout << "Enter an ending store:" << endl;
                getline(cin,endStore);
                g.shortestStorePath(startStore, endStore);

                break;

            case 4:
                cout << "Enter city name" << endl;
                cin.ignore();
                getline(cin,newCity);
                g.addVertex(newCity);
                cout << "Enter linked city name" << endl;
                getline(cin,linkedCity);
                g.addEdge(newCity,linkedCity,0);
                cout << "Enter store name in City" << endl;
                getline(cin,newStore);
                g.setStore(newStore,linkedCity);//this only updates last vertex in vector;
                break;

        }

    }

    return 0;
}
