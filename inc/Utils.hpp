#ifndef UTILS_HPP
# define UTILS_HPP

# include "type_traits/enable_if.hpp"
# include "type_traits/is_integral.hpp"
# include "VectorIterator.hpp"
# include "Vector.hpp"

namespace ft {
	std::string	long_to_str(size_t n) {
		std::stringstream	stream;

		stream << n;
		std::string 		str = stream.str();
		return str;
	}

	// protect against not random access it?
	template<class It>
	//typename It::difference_type
	size_t	distance(It first, It last) {
				//typename ft::enable_if<!ft::is_integral<It>::value >::type* = NULL
				//) {
		size_t	dis = 0;
		//typename It::difference_type dis = 0;

		while (first != last) {
			++first;
			++dis;
		}
		return dis;
		//return last - first;
	}
}

#endif	/* UTILS_HPP */
