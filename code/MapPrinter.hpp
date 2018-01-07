#ifndef MAP_PRINTER_H
#define MAP_PRINTER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static string __graph;

static string& getGraph() {
  if (__graph == "") {
    fstream file("graph.data");
    getline(file, __graph, (char)-1);
  }
  return __graph;
}

#endif