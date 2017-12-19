#include <iomanip>
#include <string>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
#include <condition_variable>

class simplex
{
public:
	simplex();
	simplex(std::ifstream);
	~simplex();
	bool is_negative();
	void print();
	void compute();
	double show();
private:
	double **simplex_core;
	int rows;
	int columns;
};
