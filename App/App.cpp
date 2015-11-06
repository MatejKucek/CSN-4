// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <deque>

#include <windows.h>

using namespace std;

class Node {

public:
	string name;
	deque<string> vertices;

	void addVertice(string verticeName) {
		vertices.push_back(verticeName);
	}

	Node() {}
	Node(string name) {
		this->name = name;
	}
};

class Graph {

public:
	deque<Node> nodes;

	int findNode(string nodeName) {

		for (int i = 0;i < nodes.size();i++) {
			if (nodes[i].name == nodeName) {
				return i;
			}
		}
		nodes.push_back(nodeName);
		return nodes.size() - 1;
	}

	void addNode(string nodeName) {
		nodes.emplace_back(nodeName);
	}

	void addNode(Node node) {
		nodes.push_back(node);
	}
	
	void addVertice(string nodeName, string targetNode) {
		
		int i = findNode(nodeName);
		nodes[i].addVertice(targetNode);
	}
};

class Language {

public:
	string name;
	int nodes;
	int vertices;
	Graph data;

};

deque<Language*> loadData() {
	string languages[] = { "Arabic","basque","Catalan","Chinese","Czech","English","Greek","Hungarian","Italian","Turkish" };
	int languagesAmount = 10;
	string languagePostFix = "_syntactic_dependency_network.txt";
	deque<Language*> lang;

	for (int i = 0;i < languagesAmount;i++) {
		//this is just for faster testing
		//for (int i = 0;i < 1;i++) {
		//ifstream f("data/Czech" + languagePostFix);
		ifstream f("data/" + languages[i] + languagePostFix);

		lang.push_back(new Language());
		
		lang[i]->name = languages[i];

		string a, b;
		f >> lang[i]->nodes;
		f >> lang[i]->vertices;

		string previousNode = "";
		Node *node = new Node();
		int duplicates = 0;
		cout << i+1 << " processing " << lang[i]->name << endl;

		while (f >> a) {
			f >> b;
			
			if (previousNode != a) {

				if (previousNode != "") {
					lang[i]->data.addNode(*node);
				}
				previousNode = a;
				delete(node);
				node = new Node(a);
			}
			if (b != a) {
				node->addVertice(b);
			}
			else {
				duplicates++;
			}
		}
		lang[i]->data.addNode(*node);

		f.close();
		cout << "duplicates found: " << duplicates << endl;
	}

	return lang;
}

int main()
{
	deque<Language*> languages = loadData();

	getchar();

    return 0;
}

