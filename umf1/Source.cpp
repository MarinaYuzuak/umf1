#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING


#include "FDM.hpp"
#include <iostream>
#include <fstream>

std::experimental::filesystem::path dir_to_file = "test-1";

int main(int argc, char* argv[]) {


	FDM fdm(dir_to_file);



	return 0;
}