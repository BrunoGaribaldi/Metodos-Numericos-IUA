#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	ofstream archivo("Data.txt");
	int a = 9,b=3;
	archivo<<a<<"\t"<<b<<endl;
	archivo<<a<<"\t"<<b<<endl;
	return 0;
}

