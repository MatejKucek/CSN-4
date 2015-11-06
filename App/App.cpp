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

int main()
{
	string languages[] = { "Arabic","basque","Catalan","Chinese","Czech","English","Greek","Hungarian","Italian","Turkish" };
	int languagesAmount = 10;
	string languagePostFix = "_syntactic_dependency_network.txt";
	Language* lang = new Language[10];

	//for (int i = 0;i < languagesAmount;i++) {
	for (int i = 0;i < 1;i++) {

		//ifstream f("data/"+languages[i] + languagePostFix);
		ifstream f("data/Czech" + languagePostFix);
		string line;
		
		lang[i].name = languages[i];
			
		string a,b;
		f >> lang[i].nodes;
		f >> lang[i].vertices;

		string previousNode = "";
		Node *node=new Node();
		int index = 0;
		cout << i << " processing " << lang[i].name << endl;

		while (f >> a) {
			f >> b;
			index++;
			if (index % 10000 == 0)cout << index << " out of " << lang[i].vertices << endl;

			if (previousNode != a) {

				if (previousNode != "") {
					lang[i].data.addNode(*node);
				}
				previousNode = a;
				delete(node);
				node = new Node(a);
			}
			node->addVertice(b);
		}
		lang[i].data.addNode(*node);

		f.close();
	}

	getchar();

    return 0;
}

