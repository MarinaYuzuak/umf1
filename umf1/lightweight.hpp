#pragma once
#include <iostream>
#include <vector>

template <typename T>
void print(std::vector<T> _vec) {
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << _vec[i] << ' ';
	std::cout << std::endl;
}