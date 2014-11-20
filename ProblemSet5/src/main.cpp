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
#include <set>
#include <limits.h>
class Node{
	int id;
	bool isVisited;
	public:

	int shortestpath;
	std::unordered_map<Node*,int> neighbor;
	Node():
		id(),
		isVisited(false),
		shortestpath(INT_MAX),
		neighbor()
	{}

	void setid(int i){ id = i;}
	int getid() const { return id;}
	void addNeighbor(Node* v, int d){
		neighbor.insert(std::make_pair(v,d));
	}

	void updateDistance(int d){
		this->shortestpath = d;
	}	

	void printNode(){
		for(auto it = neighbor.begin();it !=neighbor.end();++it ){
			printf("Node %d -> distance %d \n",it->first->getid(),it->second);
		}
	}
	
};

void dijkstra(Node* n,std::set<Node*>& nSet){
	if(n->getid() == 1){
		n->shortestpath = 0;
	}

	while(!nSet.empty()){
		Node* mindst = *(nSet.begin());
		for(auto it = nSet.begin();it!=nSet.end();++it){
			Node * n = *it;
			if( (mindst->shortestpath) > (n->shortestpath) ) mindst = n;		
		}
		nSet.erase(mindst);

		for(auto it = (mindst->neighbor).begin();it!=(mindst->neighbor).end();++it){
			Node* adj_node  = it->first;
			int weight = it->second;
			int distance =mindst->shortestpath + weight;
		        if(distance < adj_node->shortestpath)
				adj_node->shortestpath = distance;	
		}
	}

}
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
	std::set<Node*> nSet;
	int *array = (int*)malloc(sizeof(int)*num_of_lines);
	int i = 0;
	while((read = getline(&line,&len,fp)) != -1){
		std::string s(line);
		istringstream iss(s);

		v[i].setid(i+1);
		nSet.insert(v+i);
		string sub;
		iss >> sub;  			//skip the current node
		int node,weight;
		do
		{
			iss >> sub;
			char * pch;
			pch = strtok ((char*)sub.c_str(),",");
			node = atoi(pch);
			pch = strtok (NULL, ",");		  
			if(pch != NULL){
				weight = atoi(pch);
				v[i].addNeighbor(v+node-1,weight);
			}
		} while (iss);
		i++;
	}

	
	dijkstra(&v[0],nSet);
		for(int i = 0; i< num_of_lines; ++i)
		{
			printf("v[%d] %d \n",i+1,v[i].shortestpath);
		
		}
	delete []v;
	return 0;
}
