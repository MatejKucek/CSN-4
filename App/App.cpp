// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
#include <set>

#include <windows.h>

using namespace std;

class Node {

public:
	set<int> vertices;
};

class Language {

public:
	string name;
	int amountOfNodes;
	int amountOfVertices;
	vector<Node> nodes;
};

deque<Language*> loadData() {
	string languages[] = { "Arabic","Basque","Catalan","Chinese","Czech","English","Greek","Hungarian","Italian","Turkish" };
	int languagesAmount = 10;
	string languagePostFix = "_syntactic_dependency_network.txt";
	deque<Language*> lang;

	//for (int i = 0;i < languagesAmount;i++) {

	//this is just for faster testing
	for (int i = 0;i < 1;i++) {


		ifstream f("data/" + languages[i] + languagePostFix);
		lang.push_back(new Language());
		lang[i]->name = languages[i];

		string a, b;
		f >> lang[i]->amountOfNodes;
		f >> lang[i]->amountOfVertices;
		lang[i]->nodes.resize(lang[i]->amountOfNodes);

		int duplicates = 0;
		unordered_map<string, int> map;
		int index = 0;

		cout << i + 1 << " processing " << lang[i]->name << endl;

		while (f >> a) {
			f >> b;

			if (a == b) {
				duplicates++;
				continue;
			}

			int ia, ib;

			unordered_map<string, int>::const_iterator it=map.find(a);
			if (it != map.end()) {
				ia = it->second;
			}
			else {
				ia = index;
				map[a] = index++;
			}

			it = map.find(b);
			if (it != map.end()) {
				ib = it->second;
			}
			else {
				ib = index;
				map[b] = index++;
			}
				
			lang[i]->nodes[ia].vertices.insert(ib);
		}

		f.close();
		cout << "duplicates found: " << duplicates << endl;
	}

	return lang;
}

void printTable1(deque<Language*> languages) {
	
	cout << "Language\tN\tE\t(k)\tRo\n";

	for (deque<Language*>::iterator i = languages.begin();i != languages.end();i++) {
		double N = (double)(*i)->amountOfVertices;
		double E = (double)(*i)->amountOfNodes;

		cout << (*i)->name << "\t";
		cout << N << "\t";
		cout << E << "\t";
		cout << E / N << "\t";
		cout << 2 * E / (N*(N + 1))<<endl;
	}
}

int main()
{
	
	deque<Language*> languages = loadData();

	printTable1(languages);

	getchar();
    return 0;
}

