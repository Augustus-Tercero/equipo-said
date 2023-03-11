#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <dirent.h>

using namespace std;

template <typename T> vector<list<T>> readFile(const string & path) {
    vector<list<T>> adjlist;
    string line;
    string element;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "cant't open file" << endl;
        exit(1);
    }
    while (getline(file,line)) {
        line = line.substr(2);
        stringstream ss(line);
        list<T> aux;
        T vertex;
        while (ss >> vertex) {
            aux.push_back(vertex);
        }
        adjlist.push_back(aux);
    }
    return adjlist;
}

template <typename T> void printList(vector<list<T>> list) {
    for (int i = 0; i < list.size(); i++) {
        cout << i << ": ";
        for (auto j : list[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

template <typename T> vector<vector<int>> list2matrix(vector<list<T>> list) {
    int n = list.size();
    vector<vector<int>> adjmatrix(n, vector<int>(n,0));
    for (int i = 0; i < n; i++) {
        for (auto j : list[i]) {
            adjmatrix[i][j] = 1;
        }
    }

    return adjmatrix;
}

bool isDirected(vector<vector<int>> adjmatrix) {
    vector<int> diagonal;
    int n = adjmatrix.size();
    for (int i = 0; i < n; i++) {
        diagonal.push_back(adjmatrix[i][i]);
    }
    if (equal(diagonal.begin() + 1, diagonal.end(), diagonal.begin()))
        return false;
    else
        return true;
}

bool isComplete(vector<vector<int>> adjmatrix) {
    int edges = 0;
    int n = adjmatrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {// skip
            edges++;
        }
    }
    if (edges == (n*(n-1))/2)
        return true;
    else
        return false;
}

// bool isBipartite(vector<vector<int>> adjmatrix) {
    // int n = adjmatrix.size();
    // vector<vector<int>> unique_rows;
    // for (int i = 0; i < n; i++) {
        // if (find(unique_rows.begin(), unique_rows.end(), adjmatrix[i]) == unique_rows.end()) {
//
        // }
    // }
//
    // return true;
// }

bool isMulti(vector<vector<int>> adjmatrix) {
    int n = adjmatrix.size();
    vector<int> diagonal;
    for (int i = 0; i < n; i++) {
        diagonal.push_back(adjmatrix[i][i]);
    }
    for (int i : diagonal) {
        if (diagonal[i] > 0) {
            return true;
        }
        // else if ()
    }
}

void deepSearch(int node, vector<list<int>> adjlist, vector<bool>& visited, vector<int>& path, int length) {
    visited[node] = true;
    path.push_back(node);
    if (path.size() == length) {
        cout << "Walk: ";
        for (auto i : path) {
            cout << i << " ";
        }
        cout << endl;
        path.pop_back();
        visited[node] = false;
        return;
    }
    for (auto adj : adjlist[node]) {
        if (!visited[adj]) {
            deepSearch(adj, adjlist, visited, path, length);
        }
    }
    path.pop_back();
    visited[node] = false;
}

void findWalks(vector<list<int>> adjlist, int length) {
    vector<bool> visited(adjlist.size(), false);
    vector<int> path;
    for (int i = 0; i < adjlist.size(); i++) {
        deepSearch(i, adjlist, visited, path, length);
    }
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
        cin >> option;
        closedir(dir);
        return paths[option]->d_name;
    }
    else {
        cout << "Not found" << endl;
        exit(1);
    }
}

void menu() {
    string path = "../";
    cout << "Select a graph: " << endl;
    string filename = selectfile(path);
    vector<list<int>> adjlist;
    vector<vector<int>> adjmatrix;
    int option;
    path += filename;
    adjlist = readFile<int>(path);
    adjmatrix = list2matrix(adjlist);
    cout << "Adjacency list of the selected graph: " << endl;
    printList(adjlist);
    cout << "Graph type: ";
    if (isDirected(adjmatrix))
        cout << "directed, ";
    if (isComplete(adjmatrix))
        cout << "complete";
    if (!isMulti(adjmatrix))
        cout << "simple";
    cout << "Select path type: " << endl << "1) walk" << endl << "option: ";
    cin >> option;
    if (option == 1) {
        int length = 0;
        cout << "Enter a length: ";
        cin >> length;
        findWalks(adjlist, length);
    }
    return;
}

int main() {
    menu();
}