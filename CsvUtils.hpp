#ifndef CSVUTILS_HPP
#define CSVUTILS_HPP

#include <vector>
#include <fstream>

#include "config.hpp"
#include "StringUtils.hpp"


/**
 * Class to read and write csv files
 */
class CsvUtils {
public:
	static const char delimiter = ';';
	
	typedef std::vector<real>    Line;
	typedef std::vector<Line>    Table;
	
	
	/**
	 * Read from csv file, which columns separated with delimiter.
	 * The file supposed to contain real values only.
	 * Head of the table (names of columns with delimiters) must be present,
	 * but the values from it are currently ignored.
	 */
	static Table readFromFile(const std::string fileName) {
		
		std::ifstream input;		
		input.open(fileName, std::ios::in);
		assert(input.is_open());
		
		Table table;
		readLines(input, table);
		
		assert(!input.bad());
		input.close();
		
		return table;
	}
	
	
	/**
	 * Write the table to csv file, which columns separated with delimiter.
	 * The file supposed to contain real values only.
	 */
	static void writeToFile(const std::string fileName, const Table& table) {
		std::ofstream output;
		output.open(fileName, std::ios::out);
		assert(output.is_open());
		
		writeLines(output, table);
		
		assert(output.good());
		output.close();
	}
	
	
private:
	
	static size_t estimateNumberOfColumns(std::ifstream& input) {
		std::string headOfTable;
		std::getline(input, headOfTable);
		return StringUtils::split(headOfTable, delimiter).size();
	}
	
	
	static void readLines(std::ifstream& input, Table& table) {
		const size_t numberOfColumns = estimateNumberOfColumns(input);
		
		while ( !input.eof() ) {
			std::string lineStr;
			std::getline(input, lineStr);
			if (lineStr == "") { break; }
			
			const auto items = StringUtils::split(lineStr, delimiter);
			assert(items.size() == numberOfColumns);
			
			Line line;
			for (const auto& item : items) {
				real value = std::stof(item);
				line.push_back(value);
			}
			table.push_back(line);			
		}
	}
	
	
	static void writeLines(std::ofstream& output, const Table& table) {
		for (const auto& line : table) {
			output << StringUtils::joinToLine(line, delimiter) << std::endl;
		}
		output << std::endl;
	}
	
	
};



#endif // CSVUTILS_HPP