#include <simplex.hpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("compute", "[compute]") {
	simplex init(std::ifstream("f1.txt"));
	double hold;
	init.compute();
	hold = init.show();
	REQUIRE(hold == [16.5714]);
}
