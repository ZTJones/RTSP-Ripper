#include "Bug.h"

#include <iostream>

Bug::Bug(int age_i) {
	std::cout << "Hello world" << std::endl;
	Bug::age = age_i;
}

void Bug::showAge() {
	std::cout << Bug::age << std::endl;
}

void Bug::chirp() {
	std::cout << "CHIRP!" << std::endl;
}