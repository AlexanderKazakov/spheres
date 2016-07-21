#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <iomanip>
#include <sstream>
#include <vector>


class StringUtils {
public:
	
	/**
	 * Split the string into vector of strings by given delimiter symbol.
	 * Several repeating delimiters handled as one.
	 */
	static std::vector<std::string> split(const std::string s, const char delimiter) {
		
		std::vector<std::string> ans;
		
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delimiter)) {
			if (item != "") { //< prevent empty strings if delimiter is repeating
				ans.push_back(item);
			}
		}
		
		return ans;
	}
	
	
	/**
	 * Create line of items from the given container.
	 * Items will be split by the given separator.
	 */
	template<typename TContainer>
	static std::string joinToLine(const TContainer& container, const char delimiter) {
		
		std::string ans = "";
		
		for (const auto& item : container) {
			std::string itemStr = std::to_string(item);
			ans += itemStr + delimiter;
		}
		
		if (ans.size() != 0) { // remove delimiter at the end
			ans.pop_back();
		}
		
		return ans;
	}
	
	
};


#endif // STRINGUTILS_HPP
