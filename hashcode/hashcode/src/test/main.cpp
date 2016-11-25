#include "satellite.hpp"
#include "collection.hpp"
#include <iostream>

int main(){
	std::cout << "Hello World!" << std::endl;
	simulation simu("data/forever_alone.in");
	satellite s1(simu, 47.0, 2.0, 0.5f, 0.5f, 0.5f);
	satellite s2(simu, 47.0, 2.0, 0.5f, 0.5f, 0.5f);
	satellite s3(simu, 47.0, 2.0, 0.5f, 0.5f, 0.5f);
	satellite s4(simu, 47.0, 2.0, 0.5f, 0.5f, 0.5f);
	satellite s5(simu, 47.0, 2.0, 0.5f, 0.5f, 0.5f);

	collection c1(1, 1, 1);
	collection c2(1, 1, 1);
	collection c3(1, 1, 1);

	location l1(47, 47);
	location l2(47, 47);
	location l3(47, 47);
	location l4(47, 47);
	location l5(47, 47);
	
	time_range t1(3600, 3600);

	photograph p1(l1, t1);

	c1.add_photograph(&p1);


}
