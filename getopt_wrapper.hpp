#include <getopt.h>
#include <string>


/**
 * @see getopt_long_only documentation
 * @param argc program arguments number
 * @param argv program arguments array
 * @param task string to write "task" option argument
 */
inline void getopt_wrapper(int argc, char** argv, 
		std::string& task, float& rMin, float& rMax) {
	task = "";
	rMin = rMax = 0;
	
	while (true) {
	// through all options
		static struct option long_options[] = {
			{"task",    required_argument, 0, 't'},
			{"rmin",    required_argument, 0, 'l'},
			{"rmax",    required_argument, 0, 'g'},
			{0, 0, 0, 0}
		};
		
		int option_index = 0;
		int c = getopt_long_only(argc, argv, "t:l:g:", long_options, &option_index);
		if (c == -1) { break; } // end of the options
		
		switch (c) {
			case 't':
				task = optarg;
				break;
			
			case 'l':
				rMin = std::stof(optarg);
				break;
			
			case 'g':
				rMax = std::stof(optarg);
				break;
			
			default:
				break;
		}
	}
}
