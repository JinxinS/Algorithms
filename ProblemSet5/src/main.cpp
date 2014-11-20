//============================================================================
// Name        : ProblemSet5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string.h>
#include <unordered_map>
#include <sstream>

class Node{
	int id;
	std::unordered_map<Node*,int> neighbor;
	public:
	Node():
		id(){}

	void setid(int i){ id = i;}
	int getid() const { return id;}
	void addNeighbor(Node* v, int d){
		neighbor.insert(std::make_pair(v,d));
	}

	void printNode(){
		for(auto it = neighbor.begin();it !=neighbor.end();++it ){
			printf("Node %d -> distance %d \n",it->first->getid(),it->second);
		}
	}
};


using namespace std;

int main() {
	FILE* fp;
	fp = fopen("./dijkstraData.txt","r");
	if(fp == NULL) exit(EXIT_FAILURE);
	ssize_t read;
	size_t len = 0;
	char* line= NULL;
	int num_of_lines = 0;
	while((read = getline(&line,&len,fp)) != -1){
		++num_of_lines;
	}
	Node* v = new Node[num_of_lines];

	rewind(fp);

	int *array = (int*)malloc(sizeof(int)*num_of_lines);
	int i = 0;
	while((read = getline(&line,&len,fp)) != -1){
		std::string s(line);
		istringstream iss(s);

		v[i].setid(i+1);
		string sub;
		iss >> sub;  			//skip the current node
		int node,distance;
		do
		{
			iss >> sub;
			char * pch;
			pch = strtok ((char*)sub.c_str(),",");
			node = atoi(pch);
			pch = strtok (NULL, ",");		  
			if(pch != NULL){
				distance = atoi(pch);
				v[i].addNeighbor(v+node-1,distance);
			}
		} while (iss);
		i++;
	}


//	for(int i = 0; i< num_of_lines; ++i)
//	{
//		printf("v[%d] %d \n",i,v[i].getid());
//		v[i].printNode();
//	}
	delete []v;
	return 0;
}
