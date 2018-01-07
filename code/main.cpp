#include <iostream>
#include <cstdlib>
#include "Graph.hpp"
#include "MapPrinter.hpp"
using namespace std;

void mainPage() {
    system("cls");
    cout << "|***************************************************|" << endl;
    cout << "|                 SYSU Guide System                 |" << endl;
    cout << "|***************************************************|" << endl;
    cout << "|                                                   |" << endl;
    cout << "|  1)Attractions View     2)Check for Attraction    |" << endl;
    cout << "|  3)Walking Guide        4)Driving Guide           |" << endl;
    cout << "|  q)Quit                                           |" << endl;
    cout << "|                                                   |" << endl;
    cout << "|***************************************************|" << endl;
    cout << endl;
    cout << "Please input your option:";
}

int main() {
	cout << "Loading data, please wait for a few seconds..." << endl;
    Graph guideMap;
    string opt, name, start, end, q, ans;
    mainPage();
    while (cin >> opt && (opt != "q" && opt != "Q")) {
        if (opt == "1") {
            system("cls");
			cout << "--------------------------MAP--------------------------" << endl;
            cout << getGraph() << endl;
			cout << "--------------------------MAP--------------------------" << endl;
            cout << "Attractions View:" << endl;
            cout << guideMap.allInfo();
            cout << "(Input q or Q to quit)" << endl;
            while (cin >> q && (q != "q" && q != "Q")) {}
        } else if (opt == "2") {
            system("cls");
			cout << "--------------------------MAP--------------------------" << endl;
			cout << getGraph() << endl;
			cout << "--------------------------MAP--------------------------" << endl;
            cout << "Attraction Detail:" << endl;
            cout << "Please input the attraction's name:";
            cin >> name;
            Node temp = guideMap.getInfo(name);
			if (temp.id == -1) {
				cout << name << " does not exist!" << endl;
			} else {
				cout << temp.name << endl;
				cout << temp.introduction << endl;
			}
			cout << "(Input q or Q to quit)" << endl;
            while (cin >> q && (q != "q" && q != "Q")) {}
        } else if (opt == "3") {
            system("cls");
			cout << "--------------------------MAP--------------------------" << endl;
			cout << getGraph() << endl;
			cout << "--------------------------MAP--------------------------" << endl;
            cout << "Walking Guide:" << endl;
            cout << "Please input the start attracion:";
            cin >> start;
            cout << "Please input the end attracion:";
            cin >> end;
            ans = guideMap.getWalkingPath(start, end);
            if (ans == "Empty") {
                cout << "Invalid place information is provided." << endl;
            } else if (ans == "Stupid") {
				cout << "You can't get there by walking!" << endl;
			} else {
                cout << "From " << start << " to " << end << ":" << endl;
                cout << ans << endl;
            }
            cout << "(Input q or Q to quit)" << endl;
            while (cin >> q && (q != "q" && q != "Q")) {}
        } else if (opt == "4") {
            system("cls");
			cout << "--------------------------MAP--------------------------" << endl;
			cout << getGraph() << endl;
			cout << "--------------------------MAP--------------------------" << endl;
            cout << "Driving Guide:" << endl;
            cout << "Please input the start attracion:";
            cin >> start;
            cout << "Please input the end attracion:";
            cin >> end;
            ans = guideMap.getDrivingPath(start, end);
            if (ans == "Empty") {
                cout << "Invalid place information is provided." << endl;
			} else if (ans == "Stupid") {
				cout << "You can't get there by driving!" << endl;
			} else {
                cout << "From " << start << " to " << end << ":" << endl;
                cout << ans << endl;
            }
            cout << "(Input q or Q to quit)" << endl;
            while (cin >> q && (q != "q" && q != "Q")) {}
        } else {
			system("cls");
			cout << "ERROR: " << endl;
            cout << "Wrong option is inputted!" << endl;
            cout << "(Input q or Q to quit)" << endl;
            while (cin >> q && (q != "q" && q != "Q")) {}
        }
        mainPage();
    }
}