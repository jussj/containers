#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include "tools.hpp"

namespace ft {

	template <class InputIt1, class InputIt2>
	bool
	lexicographical_compare(InputIt1 first1, 
							InputIt1 last1,
							InputIt2 first2, 
							InputIt2 last2) {
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
	
	template <class InputIt1, class InputIt2, class Compare>
	bool 
	lexicographical_compare(InputIt1 first1,
							InputIt1 last1,
                            InputIt2 first2,
							InputIt2 last2,
							Compare comp) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template <class InputIt1, class InputIt2>
	bool
	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	
	template <class InputIt1, class InputIt2, class Compare>
	bool
	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, Compare comp) {
		while (first1 != last1) {
			if (comp(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
}	/* namespace ft */

#endif	/* ALGORITHM_HPP */
