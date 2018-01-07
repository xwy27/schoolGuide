#include "Graph.hpp"
#include "mypath.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

Node error(-1);

Graph::Graph()
{
    edge_driving.resize(MAX);
    edge_walking.resize(MAX);
    for (int i = 0; i < MAX; i++)
    {
        edge_driving[i].resize(MAX);
        edge_walking[i].resize(MAX);
        for (int j = 0; j < MAX; j++)
        {
            if (i == j) {
                edge_driving[i][j] = 0;
                edge_walking[i][j] = 0;
            }
            else {
                edge_driving[i][j] = 9999999;
                edge_walking[i][j] = 9999999;
            }
        }
    }

    char line[1024];
    ifstream filein("path.data", ios::in);
    string x, y, z, m;
    int count = 0;
	char rubbish;

    while (filein.getline(line, sizeof(line))) {
        stringstream ss(line);
        ss >> x;
        if (x == "*") {
            count++;
            continue;
        }
        if (count == 1) {
            ss >> y >> z >> m;
            int id;
            stringstream xx(y);
            xx >> id;
            x = x.substr(0, x.length() - 1);
            z = z.substr(0, z.length() - 1);
            m = m.substr(0, m.length() - 1);
            attractions.push_back(Node(id, x, z, m));
        }
        if (count == 2) {
            ss >> y >> z;
            stringstream xx;
            xx << x << " " << y << " " << z;
            int temp1 = 0, temp2 = 0, temp3 = 0;
            xx >> temp1 >> temp2 >> temp3;
            edge_walking[temp1][temp2] = temp3;
            edge_walking[temp2][temp1] = temp3;
        }
        if (count == 3) {
            ss >> y >> z;
            stringstream xx;
			xx << x << " " << y << " " << z;
            int temp1 = 0, temp2 = 0, temp3 = 0;
            xx >> temp1 >> temp2 >> temp3;
            edge_driving[temp1][temp2] = temp3;
            edge_driving[temp2][temp1] = temp3;
        }
    }
    filein.clear();
    filein.close();
	
	for (int i = 0; i < attractions.size(); ++i) {
		for (int j = 0; j < attractions.size(); ++j) {
			A[i][j].setDetail(edge_walking[i][j], i, j);
		}
	}
	for (int k = 0; k < attractions.size(); ++k) {
		for (int i = 0; i < attractions.size(); ++i) {
			for (int j = 0; j < attractions.size(); ++j) {
				if (A[i][j] > (A[i][k] + A[k][j])) {
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}

	for (int i = 0; i < attractions.size(); ++i) {
		for (int j = 0; j < attractions.size(); ++j) {
			B[i][j].setDetail(edge_driving[i][j], i, j);
		}
	}
	for (int k = 0; k < attractions.size(); ++k) {
		for (int i = 0; i < attractions.size(); ++i) {
			for (int j = 0; j < attractions.size(); ++j) {
				if (B[i][j] >(B[i][k] + B[k][j])) {
					B[i][j] = B[i][k] + B[k][j];
				}
			}
		}
	}
}
//Check if the attraction is in the graph
bool Graph::check(string _name) {
    for (auto it : attractions) {
        if (it.name == _name)
            return true;
        else
            continue;
    }
    return false;
}
//Get info of certain attraction
Node &Graph::getInfo(string _name) {
    if (check(_name)) {
        vector<Node>::iterator it = attractions.begin();
        while (it != attractions.end()) {
            if ((*it).name == _name)
                return (*it);
			++it;
        }
    }
    return error;
}
//Get all attractions
string Graph::getNodeName(int index) {
	return attractions[index].name;
}

string Graph::allInfo() //名称和介绍之间用的是'/'， 景点与景点之间用的是 '\'
{
    string allattr;
    for (auto it : attractions) {
        allattr += it.name;
		for (int i = it.name.length(); i < 13; ++i) {
			allattr += " ";
		}
        allattr += '-';
        allattr += it.info;
        allattr += '\n';
    }
    return allattr;
}

//Get the shortest walking path from start to end
string Graph::getWalkingPath(string startName, string endName)
{  
	if (!(check(startName) && check(endName)))
        return "Empty";
    else {
		int start = getInfo(startName).id, end = getInfo(endName).id;
        Path mindis = A[start][end];
		if (mindis.getLength() >= 9999999)
			return "Stupid";
        stringstream ss;
		int size = mindis.getNodes().size();
		auto iter = mindis.getNodes().begin();
		int index1, index2;
		for (int i = 1; i < size; ++i)  {
			index1 = *iter;
			index2 = *(++iter);
			ss << getNodeName(index1) << "--" << (double)A[index1][index2].getLength() / 60 << "min"
				<< "-->" << getNodeName(index2) << "\n";
		}     
        string str;
		getline(ss, str, (char)-1);
        return str;
    }
}
//Get the shortest driving path from start to end
string Graph::getDrivingPath(string startName, string endName)
{
	if (!(check(startName) && check(endName)))
		return "Empty";
	else {
		int start = getInfo(startName).id, end = getInfo(endName).id;
		Path mindis = B[start][end];
		if (mindis.getLength() >= 9999999)
			return "Stupid";
		stringstream ss;
		int size = mindis.getNodes().size();
		auto iter = mindis.getNodes().begin();
		int index1, index2;
		for (int i = 1; i < size; ++i) {
			index1 = *iter;
			index2 = *(++iter);
			ss << getNodeName(index1) << "--" << (double)B[index1][index2].getLength() / 60 / driving_speed << "min"
				<< "-->" << getNodeName(index2) << "\n";
		}
		string str;
		getline(ss, str, (char)-1);
		return str;
	}
}
