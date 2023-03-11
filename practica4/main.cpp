#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <SFML/Graphics.hpp>

using namespace std;

// template <typename T>list<vector<T>> readFile(const string & path) {
list<vector<int>> readFile(const string & path) {
    list<vector<int>> adjlist;
    string line;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "cant't open file" << endl;
        exit(1);
    }
    while (getline(file,line)) {
        stringstream ss(line);
        vector<int> edges;
        int edge;
        ss >>  edge; // skip vertex
        while (ss >> edge) {
            edges.push_back(edge);
        }
        adjlist.push_back(edges);
    }
    return adjlist;
}

bool isTxt(const string & name) {
    string extension = name.substr(name.find_last_of(".") + 1);
    if (extension == "txt") {
        if (name == "CMakeLists.txt")
            return false;
        return true;
    }
    else
        return false;

}

string selectfile(const string & directory) {
    DIR * dir;
    struct dirent * dirent;
    vector<struct dirent *> paths;
    int option;
    if ((dir = opendir(directory.c_str())) != NULL) {
        int i = 0;
        while ((dirent = readdir(dir)) != NULL) {
            string name(dirent->d_name);
            if (isTxt(name)) {
                cout << i << ": " << name << endl;
                paths.push_back(dirent);
                i++;
            }
        }
        // cin >> option;
        option = 0;
        closedir(dir);
        return paths[option]->d_name;
    }
    else {
        cout << "Not found" << endl;
        exit(1);
    }
}

vector<vector<int>> list2matrix(list<vector<int>> adjlist) {
    int n = adjlist.size();
    vector<vector<int>> matrix(n,vector<int>(n,0));
    int k = 0;
    for (auto const& i : adjlist) {
        for (auto const& j : i) {
            matrix[k][j] = 1;
        }
        k++;
    }
    return matrix;
}

bool isEulerian(vector<vector<int>> adjmatrix) {
    int n = adjmatrix.size();
    vector<int> deg(adjmatrix.size(),0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjmatrix[i][j] == 1)
                deg[i]++;
        }
    }
    int j = 0;
    for (auto i : deg) {
        if ((i%2) == 0 )
            j++;
    }
    // if (j == n)
        // return true;
    // else
        // return false;
    return (j == n);
}

void printAdjList(list<vector<int>> adjlist) {
    int k = 0;
    for (auto const & i : adjlist) {
        cout << k << ": ";
        for (auto const & j : i) {
            cout << j << " ";
        }
        k++;
        cout << endl;
    }
    return;
}

void drawGraph(list<vector<int>> adjlist) {
    sf::RenderWindow window(sf::VideoMode(800,600), "Graph");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
    return;
}

int main() {
    string path = "../";
    cout << "Select a file: " << endl;
    string filename = selectfile(path);
    list<vector<int>> adjlist;
    int option;
    path += filename;
    adjlist = readFile(path); // Seleccionar archivo

    printAdjList(adjlist); // Se imprime la lista
    cout << endl;

    vector<vector<int>> adjmatrix;
    adjmatrix = list2matrix(adjlist);
    if (isEulerian(adjmatrix))
        drawGraph(adjlist);
    return 0;
}