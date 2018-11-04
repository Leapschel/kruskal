
// Created by leap on 10/24/18.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;


struct Edge {
  int v1;
  int v2;
  long weight;
};

// get root of component + setting parent of all its elements directly to root
long getParent(long* UF, long v){
    if (UF[v] != v){
      UF[v] = getParent(UF, UF[v]);
    }
    return UF[v];
}


bool connected (long* UF, long v1, long v2){
    return getParent(UF, v1) == getParent(UF, v2);
}

// sort edges according to weight
bool sortcol (const Edge& v1, const Edge& v2){
    return v1.weight < v2.weight;
}

void Union (long v, long w, long* UF, long* balance){
    if (balance[w] > balance[v]){
     UF[v]=w;
     balance[w] +=1;
    }

    else {
     UF[w]= v;
     balance[v] +=1;
   }
}

long mst(vector<Edge>* graph, int& e, int& sizeV){
// Kruskals algorithm

    // 1. sort edges - according to weight
    sort(graph -> begin(), graph -> end(), sortcol);

    long* parents = new long[sizeV];
    long* balance = new long[sizeV];

    for (int i = 0; i < sizeV ; ++i){
      parents[i] = i;
      balance[i] = 0;
    }

    // 2. add edges to MST
    long weight = 0;
    for (int v = 0; v != e; ++v){

    long a = graph -> at(v).v1;
    long b = graph -> at(v).v2;

    // 3. union unconnected components
    if (!connected(parents, a, b)){
        weight += graph -> at(v).weight;
        Union(parents[a], parents[b], parents, balance);
      }
    }

    delete[] parents;
    return weight;
}


vector<string> split(const string& s, char delimiter){

    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter)){
      tokens.push_back(token);
    }
    return tokens;
}


vector<Edge>* readIn(string filename, int& n, int& numV){

    vector<Edge>* graph = new vector<Edge> (n);

    ifstream myfile(filename);
    char character = myfile.get();
    int count = 0;

    int from;
    int to;
    long weight;

    while (!myfile.eof()){

      from   = 0;
      to     = 0;
      weight = 0;

      while (48 <= character && character <= 57 ){ from = (from *10) + (character-48); character = myfile.get();} //skip the space}
      character = myfile.get();

      while (48 <= character && character <= 57 ){ to = (to *10) + (character-48); character = myfile.get();} //skip the space}
      character = myfile.get();

      while (48 <= character && character <= 57 ){ weight = (weight *10) + (character-48); character = myfile.get();} //skip the space}
      character = myfile.get();

      graph -> at(count).v2     = to;
      graph -> at(count).weight = weight;
      graph -> at(count).v1     = from;

      if( from > numV )  numV = from;
      if(   to > numV )  numV = to;

      count++;
      }

      numV++;
      myfile.close();

      return graph;
}

int main(int argc, char** args){

      int n = atoi(args[1]);
      int numV;

      vector<Edge>* graph = readIn(args[2], n, numV);

      long minWeight = mst(graph, n, numV);

      delete graph;

      // printing out MST - minimum weight value to connect all vertices
      cout << minWeight << endl;
}
