#include "getopt_wrapper.hpp"
#include "CsvUtils.hpp"
#include "Separator.hpp"


int main(int argc, char *argv[]) {
	std::string taskFileName;
	real rMin, rMax;
	getopt_wrapper(argc, argv, taskFileName, rMin, rMax);
	assert(taskFileName != "");
	assert(rMin > 0);
	assert(rMax >= rMin);
	static const int Dimensionality = 3;
	
	const auto task = CsvUtils::readFromFile(taskFileName);
	Separator<Dimensionality> separator(task, rMin, rMax);
	const auto result = separator.separate();
	print("Number of points after separation: ", result.size()); // TODO replace
	assert(result.size() == task.size());
	CsvUtils::writeToFile(taskFileName + "_result.csv", result);
	
	return 0;
}


