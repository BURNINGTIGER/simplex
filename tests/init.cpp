#include <simplex.hpp>
#include <catch.hpp>
#include <iostream>
#include <fstream>
#include <math.h>

SCENARIO("compute", "[compute]") {
	std::ofstream fout("f2.txt");
	fout << "5" << std::endl;
	fout << "5" << std::endl;
	fout << "0" << std::endl;
	fout << "0 0 1 2 3" << std::endl;
	fout << "4 4 2 1 1" << std::endl;
	fout << "5 3 1 4 0" << std::endl;
	fout << "6 6 0 0.5  1" << std::endl;
	fout << "0 0 -8 -6 -2" ;
	fout.close();
	simplex init(std::ifstream("f2.txt"));
	double hold;
	init.compute();
	hold = init.show();
	hold = floor(hold);
	REQUIRE(hold == 16);
}
