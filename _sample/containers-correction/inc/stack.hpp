#ifndef STACK_HPP
# define STACK_HPP

# include <stdexcept>
# include <vector>
# include "vector.hpp"

namespace ft {

	// FT WORD
	template <class T, class Container = ft::vector<T> >
	class stack {

		public:

		// MEMBER TYPES

			typedef Container							container_type;
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::reference		reference;

		// CTOR

			explicit stack(const Container& container = Container())
				: c(container)	{}
			
			~stack()			{}
		
		// MEMBER FUNCTIONS

			bool
			empty() const {
				if (c.size() == 0)
					return true;
				return false;
			}
			size_type
			size() const {
				return c.size();
			}
			value_type &
			top() {
				if (this->empty()) 
					throw EmptyStack();
				return c.back();
			}
			const value_type &
			top() const {
				if (this->empty()) 
					throw EmptyStack();
				return c.back();
			}
			void
			push(const value_type& val) {
				c.push_back(val);
			}
			void
			pop() {
				if (this->empty()) 
					throw EmptyStack();
				c.pop_back();
			}

		// EXCEPTION

			class EmptyStack : public std::exception {
				public:
					virtual const char* what() const throw() { 
						return "stack is empty";
					}
			};

		protected:

			Container		c;

		public:
		
		// NON-MEMBER FRIENDS OPERATOR OVERLOADS

			friend bool
			operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
				return x.c == y.c;
			}
			friend bool
			operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
				return !(x == y);
			}
			friend bool
			operator>(const stack<T, Container>& x, const stack<T, Container>& y) {
				return y < x;
			}
			friend bool
			operator<(const stack<T, Container>& x, const stack<T, Container>& y) {
				return x.c < y.c;	
			}
			friend bool
			operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
				return !(x < y);
			}
			friend bool
			operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
				return !(y < x);
			}
	};	/* class stack */

}	/* namespace ft */

#endif	/* STACK_HPP */
