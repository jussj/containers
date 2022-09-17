#ifndef UTILS_HPP
# define UTILS_HPP

# include "type_traits/enable_if.hpp"
# include "type_traits/is_integral.hpp"
# include "vectorIterator.hpp"
# include "vector.hpp"

namespace ft {
	std::string	long_to_str(size_t n) {
		std::stringstream	stream;

		stream << n;
		std::string 		str = stream.str();
		return str;
	}

	// protect against not random access it?
	template<class It>
	size_t	distance(It first, It last) {
		size_t	dis = 0;

		while (first != last) {
			++first;
			++dis;
		}
		return dis;
	}
}

#endif	/* UTILS_HPP */
