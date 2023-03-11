//
// Created by suipiss on 2/24/23.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

template <typename T> struct hhmap {
    map<T, map<T,T>> hashmap;
};

template<typename T> vector<vector<T>> adjacencyMatrix(const string & path) {
    vector<vector<T>> data;
    string line;
    T item;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "No se puede abrir el archivo" << endl;
        exit(1);
    }
    // T line;
    while (getline(file,line)) {
        stringstream ss(line); // convierte a string el contenido del archivo
        vector<T> row; // RESETEAR EL VECTOR XDDDDDDDDDDDDDDDD SEMEOLVIDO
        while (ss >> item) {
            row.push_back(item);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}

vector<string> split(string str) {
    vector<string> vec;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ',')) {
        vec.push_back(element);
    }
    for (int i = 1; i < vec.size(); i++) {
        vec[i].erase(0,1);
    }
    return vec;
}

template <typename T> map<T, map<T,T>> adjMap(const string & path) {
    map<T,map<T,T>> adjMap;
    string line;
    ifstream file(path);
    if (!file.is_open()){
        cout << "Not found" << endl;
        exit(1);
    }
    while (getline(file, line)) {
        T vertex;
        map<T,T> adjList;
        vertex = line[0];
        size_t pos = line.find_first_of(" ");
        string list = line.substr(pos + 1);
        pos = 0;
        vector<T> elements = split(list);
        
    }
}

// template <typename T> map<T,map<T,T>> adjacencyMap(const string & path) {
map<char,map<char,string>> adjacencyMap(const string & path) {
    map<char,map<char,string>> adjMap;
    string line;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "BRUH" << endl;
        exit(1);
    }
    // int vrtAmount = 0;
    // file >> vrtAmount;
    // getline(file, line); // skip 1st
    while (getline(file,line)) {
        char vertex;
        map<char, string> adjList;
        vertex = line[0];
        size_t pos = line.find_first_of(" ");
        string list = line.substr(pos + 1);
        pos = 0;
        if ((pos = list.find(",")) == string::npos) { // vertex per row = 1
            char adj = list[0];
            string arist = list.substr(3,3);
            adjList[adj] = arist;
        } else { // vertex per row >= 2
            vector<string> elements = split(list);
            for (int i = 0; i < elements.size(); i++) {
                char adj = elements[i][0];
                string arist = elements[i].substr(3,3);
                adjList[adj] = arist;
            }
            // adjMap[vertex] = adjList; // perdona oh todo poderoso por los pecados cometidos en estos dos bucles while.
            // while ((pos = list.find_first_of(",", pos)) != string::npos) {
                // string half = list.substr(0, pos);
                // char adj = half[0];
                // string arist = list.substr(3, 3);
                // adjList[adj] = arist;
                // size_t pos2 = list.find_last_of("{");
                // while (pos2 != string::npos) {
                    // char adj2 = list[pos2 - 2];
                    // string arist2 = list.substr(pos2 + 1, 3);
                    // adjList[adj2] = arist2;
                    // pos2 = half.find_last_of(" ", pos2 - 1);
                // }
                // pos++;
            // }
        }
        adjMap[vertex] = adjList;
    }
    return adjMap;
}

vector<vector<int>> map2matrix(map<char,map<char,string>> adjMap) {
    int n = adjMap.size();
    int i = 0; // iterador 1
    vector<vector<int>> matrix(n, vector<int>(n,-1));
    for (const auto &element : adjMap) {
        char vertex = element.first;
        map<char,string> adjList = element.second;
        for (const auto & arist : adjList) {
            char adj = arist.first;
            int j = 0; // iterador 2
            for (const auto & index : adjMap) {
                if (index.first == adj) {
                    break;
                }
                j++;
            }
            matrix[i][j] = 1;
        }
        i++;
    }
    return matrix;
}

bool isBiporite(vector<vector<int>> matrix) {
    stack <vector<int>> stack;
    vector<int> row;
    for (int i = 0; i < matrix.size(); i++) {
        row = matrix[i];
        if (!(row == stack.top()))
            stack.push(row);
    }
    if (stack.size() >= 2)
        return false;
    else
        return true;
}


int isRegularK(vector<vector<int>> matrix) {
    vector<int> deg(matrix.size(),0);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[i][j] == 1)
                deg[i]++;
        }
    }
    if (equal(deg.begin() + 1, deg.end(), deg.begin()))
        return deg[0];
    else
        return 0;
}

bool isSimple(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i+1; j < matrix.size(); j++) {
            if (matrix[i][j] == 1 && matrix[j][i] == 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const string path = "/home/suipiss/CLionProjects/actividad-practica-2-Augustus-Tercero/map.txt";
    const string path2 = "/home/suipiss/CLionProjects/actividad-practica-2-Augustus-Tercero/map2.txt";
    map<char,map<char,string>> test; // templates innecesarias?
    vector<vector<int>> matrix;
    test = adjacencyMap(path2);
    matrix = map2matrix(test);
    cout << "Es un grafo: ";
    if (isRegularK(matrix) != 0)
        cout << "regular";
    if (isSimple(matrix))
        cout << ", simple";
    // if (isBiporite(matrix))
        // cout << "bipartito";
    return 0;
}
