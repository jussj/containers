#ifndef UTILS_HPP
# define UTILS_HPP

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
	//typename std::iterator_traits<It>::difference_type
	typename It::difference_type
	distance(It first, It last) {
		typename It::difference_type dis = 0;
		while (first != last) {
			++first;
			++dis;
		}
		return dis;
		//return last - first;
	}
}

#endif	/* UTILS_HPP */
