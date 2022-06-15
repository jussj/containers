/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:41:46 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/15 10:54:12 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>
# define NAMESPACE std

namespace ft {

	template <class T, class Container = NAMESPACE::vector<T> >
	class stack {
		public:
// MEMBER FUNCTIONS
		explicit stack (const container_type & ctnr = container_type());
									// constructor
		bool 			empty() const;
		size_type		size() const;
		value_type&		top();
		const value_type&	top() const;

// MEMBER TYPES
			typedef T 		value_type;
			typedef Container	container_type;		//container_type >> vector by default
			typedef size_t		size_type;		// size _t is default

	};

#endif
