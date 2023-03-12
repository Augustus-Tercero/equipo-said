#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <set>
#include <unistd.h>

using namespace std;

typedef pair<float,float> position;

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

position getPos(int min, int max) {
    position pos;
    pos.first = rand() % max + min;
    pos.second = rand() % max - min;
    return pos;
}

sf::RectangleShape makeLine(vector<sf::CircleShape> vertices, int x, int y) {
    sf::Vector2f dist = vertices[x].getPosition() - vertices[y].getPosition();
    sf::RectangleShape line(sf::Vector2f(sqrt(dist.x*dist.x + dist.y*dist.y), 1.f));
    line.setPosition(vertices[y].getPosition());
    line.setRotation(atan2(dist.y, dist.x) * 180 / 3.1416f);
    return line;
}

void drawGraph(list<vector<int>> adjlist, vector<int> & path) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // xd
    int n = adjlist.size();
    sf::RenderWindow window(sf::VideoMode(800,600), "Graph",sf::Style::Default, settings);
    vector<sf::CircleShape> vertices(n);
    vector<sf::RectangleShape > lines;
    vector<sf::Text> names(n);
    vector<sf::Text> path_text(path.size());
    sf::Font font;
    font.loadFromFile("/home/suipiss/roboto.ttf");
    int k = 0;

    for (auto const & i : adjlist){
    // for (int i = 0; i < n; i++) { // Crear vértices y darles una posición
        vertices[k] = sf::CircleShape(10.f);
        vertices[k].setPosition(rand() % (window.getSize().x - 100) + 50, rand() % (window.getSize().y - 100) + 50);
        vertices[k].setFillColor(sf::Color::White);

        names[k].setFont(font);
        names[k].setString(to_string(i[k]));
        names[k].setCharacterSize(10);
        names[k].setStyle(sf::Text::Bold);
        names[k].setFillColor(sf::Color::Red);
        names[k].setPosition(vertices[k].getPosition());

        k++;
    }

    k = 0;
    for (auto const & i : adjlist) { // Crear líneas entre cada vértice
        lines.push_back(makeLine(vertices, k,i[k]));
        k++;
    }
    for (int i = 0; i < path.size(); i++) {
        path_text[i].setFont(font);
        path_text[i].setString(to_string(path[i]));
        path_text[i].setCharacterSize(10);
        path_text[i].setStyle(sf::Text::Bold);
        path_text[i].setFillColor(sf::Color::Red);
        path_text[i].setPosition(100+(i-1)*50,50);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < n; i++) {
            window.draw(vertices[i]);
            window.draw(names[i]);
            window.draw(lines[i]);
        }
        for (int i = 0; i < path_text.size(); i++) {
            window.draw(path_text[i]);
        }
        window.display();
    }
    return;
}


void printPath(vector<vector<int>>& adjlist, int vertex, set<pair<int, int>>& visited, vector<int> & path) {
    cout << vertex << " ";
    path.push_back(vertex);
    for (int other : adjlist[vertex]) {
        if (visited.count(make_pair(vertex, other)) == 0) {
            visited.insert(make_pair(vertex, other));
            visited.insert(make_pair(other, vertex));
            printPath(adjlist, other, visited, path);
        }
    }
}

vector<int> traverse(vector<vector<int>>& adjlist) {
    vector<int> path;
    set<pair<int, int>> visited;
    printPath(adjlist, 0, visited,path);
    return path;
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
    vector<vector<int>> test(adjlist.begin(),adjlist.end()); // oops
    vector<int> path_e;
    adjmatrix = list2matrix(adjlist);
    if (isEulerian(adjmatrix)) {
        path_e = traverse(test);
    }
    drawGraph(adjlist, path_e);
    return 0;
}