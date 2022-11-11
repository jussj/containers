#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include "utils.hpp"

namespace ft {

	template <class InputIt1, class InputIt2>
	bool lexicographical_compare (	InputIt1 first1, 
									InputIt1 last1,
									InputIt2 first2, 
									InputIt2 last2	) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}
}	/* namespace ft */

#endif	/* ALGORITHM_HPP */
