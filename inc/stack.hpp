/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:41:46 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/20 18:44:50 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>
# define NAMESPACE std

namespace ft {

	template <class T, class Container = NAMESPACE::vector<T> >
	class Stack {

		public:

		// CONSTRUCTOR
			Stack();								//empty stack
			explicit Stack (const container_type & cont = container_type());	//stack init with copied cont elements
			~Stack();

		// MEMBER FUNCTIONS
			bool 			empty() const {
				if (c.size() == 0)
					return (true);
				return (false);
			}
			size_type		size() const {
				return (c.size());
			}
			value_type &		top() {
				if (this->empty()) 
					throw EmptyStack();
				return (c.back());
			}
			const value_type &	top() const {
				if (this->empty()) 
					throw EmptyStack();
				return (c.back());
			}
			void			push(const value_type & val) {
				c.push_back(value_type);
			}
			void			pop() {
				if (this->empty()) 
					throw EmptyStack();
				c.pop_back();
			}

		// EXCEPTIONS
			class EmptyStack : public std::exception() {
				public:
					virtual const char * what() const throw() 
						return "stack is empty";
			};

		// MEMBER TYPES
			typedef Container				container_type;		//container_type >> vector by default
			//typedef T 					value_type;
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type		size_type;		// size _t is default
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::reference		reference

		protected:
			Container		c;

	};

#endif
