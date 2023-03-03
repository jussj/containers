#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "algorithm.hpp"

namespace ft {

	// PAIR STRUCT

	template <class T1, class T2>
	struct pair {	
		
		// ATTRIBUTES
		
		typedef	T1 first_type;
		typedef T2 second_type;
	
		T1 first;
		T2 second;

		// CTOR
		
		pair()
			: first(), second()	{}
		
		pair(const T1& x, const T2& y) 
			: first(x), second(y) {}
		
		template<class U1, class U2>
		pair(const pair<U1, U2>& p)
			: first(p.first), second(p.second) {}

		// OPERATOR
		
		pair&	operator=(const pair& src) {
			if (&src == this)
				return *this;
			this->first	= src.first;
			this->second = src.second;
			return *this;
		}

	};

	// NON-MEMBER OPERATORS
	
	template<class T1, class T2>
	bool
	operator==(const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return x.first == y.first
				&& x.second == y.second;
	}

	template<class T1, class T2>
	bool
	operator!=(const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return !(x == y);
	}

	template<class T1, class T2>
	bool
	operator<(	const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return x.first < y.first || (!(y.first < x.first)
				&& x.second < y.second);	
	}

	template<class T1, class T2>
	bool
	operator>(	const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return y < x;
	}	
	
	template<class T1, class T2>
	bool
	operator<=(const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return !(y < x);
	}

	template<class T1, class T2>
	bool
	operator>=(const pair<T1,T2>& x,
				const pair<T1,T2>& y) {
		return !(x < y);
	}

	// MAKE PAIR

	template <class T1, class T2>
	pair<T1,T2>	
	make_pair (T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}

}	/* namespace ft */

#endif	/* UTILITY_HPP */
