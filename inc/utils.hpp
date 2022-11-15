#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sstream>
# include "type_traits.hpp"
# include "vector_iterator.hpp"
# include "utility.hpp"

namespace ft {

	std::string
	long_to_str(size_t n) {
		std::stringstream	stream;

		stream << n;
		std::string 		str = stream.str();
		return str;
	}

	// protect against not random access it?
	template<class It>
	size_t
	distance(It first, It last) {
		size_t	dis = 0;

		while (first != last) {
			++first;
			++dis;
		}
		return dis;
	}

	template<class Pair, class T>
	struct first_of {
		T&
		operator()(const Pair& p) const {
			return p.first; 
		}
	};

	template<class T>
	struct return_value {
		T&
		operator()(T& v) const {
			return v;
		}	
	};

}	/* namespace ft */

#endif	/* UTILS_HPP */
