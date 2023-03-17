#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <iostream>
# include <sstream>
# include "type_traits.hpp"
# include "vector_iterator.hpp"
# include "utility.hpp"

namespace ft {

	template<class T>
	std::string
	to_str(T n) {
		std::stringstream stream;

		stream << n;
		std::string str = stream.str();
		return str;
	}

	template<class It>
	size_t
	distance(It first, It last) {
		size_t dis = 0;

		for (;first != last; ++first)
			++dis;
		return dis;
	}
	
	template<class Pair, class T>
	struct first_of {
		const T&
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
		const T&
		operator()(const T& v) const {
			return v;
		}	
	};

}	/* namespace ft */

#endif	/* TOOLS_HPP */
