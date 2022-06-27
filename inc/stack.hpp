/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:41:46 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/27 13:32:38 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <stdexcept>
# include <vector>
# define VEC_NAMESPACE std

namespace ft {

	template <class T, class Container = VEC_NAMESPACE::vector<T> >
	class stack {

		public:

		// MEMBER TYPES

			typedef Container				container_type;
			//typedef T 					value_type;
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type		size_type;		// size_t is default
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::reference		reference;

		// cpy and dtor??
		// overload for assign elements from one cont to another
		// CTOR

			explicit stack (const container_type& cont = container_type())		// stack init with copy of
				: c(cont) {}							// cont elements or nothing
		
		// MEMBER FUNCTIONS

			bool 			empty() const {
				if (c.size() == 0)
					return true;
				return false;
			}
			size_type		size() const {
				return c.size();
			}
			value_type &		top() {
				if (this->empty()) 
					throw EmptyStack();
				return c.back();
			}
			const value_type &	top() const {
				if (this->empty()) 
					throw EmptyStack();
				return c.back();
			}
			void			push(const value_type& val) {
				c.push_back(val);
			}
			void			pop() {
				if (this->empty()) 
					throw EmptyStack();
				c.pop_back();
			}

		// EXCEPTIONS

			//class EmptyStackException : public std::exception {
			class EmptyStack : public std::exception {
				public:
					virtual const char* what() const throw() { 
						return "stack is empty";
					}
			};

		protected:
			Container		c;
	};

	template <class T, class Cont>
	bool operator==(const stack<T, Cont>& x, const stack<T, Cont>& y) {
		return x == y;	
	}
	template <class T, class Cont>
	bool operator!=(const stack<T, Cont>& x, const stack<T, Cont>& y) {
		return x != y;	
	}
	template <class T, class Cont>
	bool operator> (const stack<T, Cont>& x, const stack<T, Cont>& y) {
		return x > y;	
	}
	template <class T, class Cont>
	bool operator>=(const stack<T, Cont>& x, const stack<T, Cont>& y) {
		return x >= y;	
	}
	template <class T, class Cont>
	bool operator<=(const stack<T, Cont>& x, const stack<T, Cont>& y) {
		return x <= y;	
	}
}

#endif
