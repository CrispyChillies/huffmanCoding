#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

vector<int> encoding(string s1);
void decoding(vector<int> op, string outputFile);

void writeBinaryToFile(const vector<int> &data, const string &filename);
vector<int> readBinaryFromFile(const string &filename);

string readFile(string inputFile);
bool checkInput(string inputFile, string outputFile);
