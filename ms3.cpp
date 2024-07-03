#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Station.h"
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Utilities.h"
#include "LineManager.h"

using namespace std;
using namespace sdds;

// Function prototypes
template<typename T>
static void loadFromFile(const char* filename, vector<T>& theCollection);

template<typename T>
static void loadFromFile(const char* filename, vector<T*>& theCollection);

int main(int argc, char** argv) {
    cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        cout << " " << argv[i];
    cout << endl << endl;

    if (argc != 5) {
        cerr << "ERROR: Incorrect number of arguments\n";
        return 1;
    }

    vector<Workstation*> theStations;
    vector<CustomerOrder> theOrders;

    try {
        // Load stations from files with different delimiters
        Utilities::setDelimiter(',');
        loadFromFile(argv[1], theStations);
        Utilities::setDelimiter('|');
        loadFromFile(argv[2], theStations);

        // Display summary of stations
        cout << "========================================" << endl;
        cout << "=         Stations (summary)           =" << endl;
        cout << "========================================" << endl;
        for (const auto* station : theStations)
            station->display(cout, false);
        cout << endl << endl;

        // Display full details of stations
        cout << "========================================" << endl;
        cout << "=          Stations (full)             =" << endl;
        cout << "========================================" << endl;
        for (const auto* station : theStations)
            station->display(cout, true);
        cout << endl << endl;

        // Manual validation of station functionality
        cout << "========================================" << endl;
        cout << "=          Manual Validation           =" << endl;
        cout << "========================================" << endl;
        cout << "getItemName(): " << theStations[0]->getItemName() << endl;
        cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << endl;
        cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << endl;
        cout << "getQuantity(): " << theStations[0]->getQuantity() << endl;
        theStations[0]->updateQuantity();
        cout << "getQuantity(): " << theStations[0]->getQuantity() << endl;
        cout << endl << endl;

        // Load customer orders
        loadFromFile<CustomerOrder>(argv[3], theOrders);

        // Display loaded orders
        cout << "========================================" << endl;
        cout << "=                Orders                =" << endl;
        cout << "========================================" << endl;
        for (auto& order : theOrders) {
            order.display(std::cout);
            g_pending.push_back(std::move(order));
        }
        cout << endl << endl;

        // Display stations setup from file
        cout << "========================================" << endl;
        cout << "=       Display Stations (loaded)      =" << endl;
        cout << "========================================" << endl;
        LineManager lm(argv[4], theStations);
        lm.display(cout);
        cout << endl << endl;

        // Display ordered stations after reordering
        cout << "========================================" << endl;
        cout << "=      Display Stations (ordered)      =" << endl;
        cout << "========================================" << endl;
        lm.reorderStations();
        lm.display(cout);
        cout << endl << endl;

        // Simulate filling orders on the assembly line
        cout << "========================================" << endl;
        cout << "=           Filling Orders             =" << endl;
        cout << "========================================" << endl;
        while (!lm.run(cout)); // Run the assembly line until all orders processed
        cout << endl << endl;
    }
    catch (const string& msg) {
        cerr << msg << '\n';
        return 2;
    }

    // Display completed orders
    cout << "========================================" << endl;
    cout << "=      Processed Orders (complete)     =" << endl;
    cout << "========================================" << endl;
    for (const auto& o : g_completed)
        o.display(cout);
    cout << endl << endl;

    // Display incomplete orders
    cout << "========================================" << endl;
    cout << "=     Processed Orders (incomplete)    =" << endl;
    cout << "========================================" << endl;
    for (const auto& o : g_incomplete)
        o.display(cout);
    cout << endl << endl;

    // Display full inventory status of stations
    cout << "========================================" << endl;
    cout << "=          Inventory (full)            =" << endl;
    cout << "========================================" << endl;
    for (const auto* theItem : theStations)
        theItem->display(cout, true);
    cout << endl;

    // Cleanup dynamically allocated stations
    for (auto station : theStations)
        delete station;

    return 0;
}

// Function to load objects from file into a vector of objects
template<typename T>
static void loadFromFile(const char* filename, vector<T>& theCollection) {
    if (!filename) {
        throw string("ERROR: No filename provided.");
    }
    ifstream file(filename);
    if (!file) {
        throw string("Unable to open [") + filename + "] file.";
    }

    string record;
    while (std::getline(file, record)) {
        T elem(record);
        theCollection.push_back(std::move(elem));
    }

    file.close();
}

// Function to load pointers to objects from file into a vector of pointers
template<typename T>
static void loadFromFile(const char* filename, vector<T*>& theCollection) {
    if (!filename) {
        throw string("ERROR: No filename provided.");
    }
    ifstream file(filename);
    if (!file) {
        throw string("Unable to open [") + filename + "] file.";
    }

    string record;
    while (std::getline(file, record)) {
        theCollection.push_back(new T(record));
    }

    file.close();
}
