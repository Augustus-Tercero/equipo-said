Es una estructura de datos compuesta por varios nodos, tiene un principio y un final; cada nodo contiene dos datos, el valor del nodo y un enlace que apunta en dirección al siguiente puntero.
![[Pasted image 20230220143913.png]]
# Implementación
Para implementar una lista enlazada hay 3 maneras:
1. Como una estructura de datos
2. Como una clase
3. Como librería
## Implementación de una estructura de datos
``` c++
struct node {
	int data;
		struct node * next;
};
```
## Implementación de clase
``` c++
class Node{
public:
	int data;
	Node * next;
	Node() { // Constructor de la clase
		data = 0;
		next = NULL;
	}
	Node(int data) { // Constructor con parámetro
		this->data = data;
		this->next = NULL;
	}
};
class Linkedlist() {
	Node * head;
public:
	Linkedlist() {
		head = NULL;
	}
	void insertNode();
	void printList();
	void deleteNode();
}
```
## Implementación de la librería "list"
``` c++
#include <iostream>
#include <list>
#include <string>

using namespace std;

template <typename T> void showlist(list<T> list) {
	int n = list.size();
	for (auto const & i : list) {
		cout << i << endl;
	}
}

int main() {
	string item;
	list<int> shopping;
	for (int i = 0; i < 5; i++) {
        cout << "Enter item: ";
		cin >> item;
		shopping.push_back(item);
	}
	return 0;
}
```