#include "helper.h"
#include "dynamic.h"

#include <iostream>

int main()
{
	std::cout << nh::sqr(5.0f) << std::endl;
	nh::point p1( 1.0f, 2.0f);
	nh::point p2( 5.0f, 6.0f);
	nh::point p3 = p1 + p2;

	std::cout << p3.x << ", " << p3.y << std::endl;

	system("pause");
}