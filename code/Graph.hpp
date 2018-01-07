#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include "mypath.hpp"
#define MAX 35
using std::string;
using std::vector;

typedef struct Node {
    int id;
    string name;
    string info;//Information of the attraction
    string introduction;//A simple sentence introduction for attraction
    Node(int _id, string _name = "", string _info = "", string _introduction = "") : 
        id(_id), name(_name), info(_info), introduction(_introduction){};
} Node;



class Graph {
    private:
        vector<Node> attractions; //Attrations
        vector<vector<int> > edge_walking;//Edges for walking
        vector<vector<int> > edge_driving;//Edges for driving
        int driving_speed = 11;
		Path A[MAX][MAX];
		Path B[MAX][MAX];

    public:
    //Read the map from two data files
    Graph();
    ~Graph() = default; //If needed

    //Check if the attraction is in the graph
    bool check(string _name);
    //Get info of certain attraction
    Node& getInfo(string _name);
    //Get all attractions
    string allInfo();
    //Get the shortest walking path from start to end
    string getWalkingPath(string start, string end);
    //Get the shortest driving path from start to end
    string getDrivingPath(string start, string end);
	string Graph::getNodeName(int index);
};

#endif