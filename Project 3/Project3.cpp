#include <iostream>
#include <string>
#include "verticies.h"

using namespace std;


int main() {

	int verticies, edges, k , start , end ;

	cin >> verticies;
	cin >> edges;

	cout << "implementing graph\n\n";

	Verticies* arr = new Verticies[verticies]; // dynamic array to represent graph
	

	for (int i = 0; i < verticies; i++) {//initialize each of the verticies 
		arr[i].number = i;
		arr[i].next = nullptr;
		arr[i].marked = false;
	}


	int startPos, endPos;
	for (int i = 0; i < edges; i++) {
		cin >> startPos;
		cin >> endPos;
		arr->linkVert(startPos, endPos, arr);
	}

	cin >> k;//read in the number of queries
	string s1; // will be used to read in queries

	while (k > 0) {
		cin >> s1;

		if (s1 == "degree-distribution") {
			arr->distribution(arr, verticies);
		}
		else if (s1 == "components"){
			arr->components(arr, verticies);
		}
		else if (s1 == "diameter") {
			cout << "The diameter of the graph is " << arr->diameter(arr, verticies) << endl;
		}
		else if (s1 == "shortest-path") {
			cin >> startPos;
			cin >> endPos;
			arr->shortestPath(arr, startPos, endPos, verticies);
		}
		else if (s1 == "spanning-tree") {
			cout << "spanning tree is \n";
			arr->spaning_tree(arr, verticies);
		}
		k--;
		cout << "----------------------------------------------------------------------------\n\n";

	}

	return 0;
}


