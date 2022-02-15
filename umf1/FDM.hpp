#pragma once
#include "lightweight.hpp"

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>

using std::experimental::filesystem::path;

struct Params {
	size_t count_int;	/// Количество интервалов
	double koef_part;	/// Коэффициент разбиения
};

enum class Axes {
	X,
	Y
};

struct Bound1
{
	Axes axes;
	size_t begin;
	size_t end;
	double u_g;
};

struct Bound2
{
	Axes axes;
	size_t begin;
	size_t end;
	double theta;
};

struct Bound3
{
	Axes axes;
	size_t begin;
	size_t end;
	double u_b;
	double beta;
	double u_s3;
};

class FDM
{

public:
	FDM(const path& _path) {

		bool _is = readFile(_path);

		if (_is == false) {
			std::cerr << "file not open..." << std::endl;
			std::exit(3);
		}

		print(x_coord);
		print(y_coord);
	}

private:
	size_t size_x, size_y;
	std::vector<double> x_coord, y_coord;
	std::vector<Params> x_params, y_params;

	std::vector<Bound1> bound1;
	std::vector<Bound2> bound2;
	std::vector<Bound3> bound3;

	bool readFile(const path& );	
};

bool FDM::readFile(const path& _path) {

	std::ifstream fin(_path / "x_coord.txt");
	if (fin.is_open()) {
		
		fin >> size_x;
		x_coord.resize(size_x);

		for (size_t i = 0; i < size_x; i++)
			fin >> x_coord[i];

		fin.close();
	}
	else
		return false;

	fin.open(_path / "y_coord.txt");
	if (fin.is_open()) {
		
		fin >> size_y;
		y_coord.resize(size_y);

		for (size_t i = 0; i < size_y; i++)
			fin >> y_coord[i];

		fin.close();
	}
	else
		return false;

	fin.open(_path / "x_params_grid.txt");
	if (fin.is_open()) {

		x_params.resize(size_x - 1);

		for (size_t i = 0; i < x_params.size(); i++)
			fin >> x_params[i].count_int 
				>> x_params[i].koef_part;

		fin.close();
	}
	else
		return false;

	fin.open(_path / "y_params_grid.txt");
	if (fin.is_open()) {

		x_params.resize(size_y - 1);

		for (size_t i = 0; i < y_params.size(); i++)
			fin >> y_params[i].count_int
			    >> y_params[i].koef_part;

		fin.close();
	}
	else
		return false;

	fin.open(_path / "x_bounds.txt");

	if (fin.is_open()) {

		size_t n;
		fin >> n;

		for (size_t i = 0; i < n; i++) {
			size_t bound;
			fin >> bound;

			switch (bound)
			{
			case 1: 
				Bound1 b_1;
				fin >> b_1.begin >> b_1.end >> b_1.u_g;
				b_1.axes = Axes::X;

				bound1.push_back(b_1);
			case 2:
				Bound2 b_2;
				fin >> b_2.begin >> b_2.end >> b_2.theta;
				b_2.axes = Axes::X;

				bound2.push_back(b_2);
			case 3:
				Bound3 b_3;
				fin >> b_3.begin >> b_3.end >> b_3.u_b >> b_3.beta >> b_3.u_s3;
				b_3.axes = Axes::X;

				bound3.push_back(b_3);
			default:
				std::cerr << "no exist type boundary" << std::endl;
				break;
			}
		}
	}



	return true;
}