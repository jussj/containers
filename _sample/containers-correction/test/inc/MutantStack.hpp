/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:33:13 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/03 14:00:20 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <iterator>

template<typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack() {}
		~MutantStack() {}
		MutantStack(MutantStack const & src) { *this = src; }

		typedef typename std::stack<T>::container_type::iterator	iterator;

		iterator		begin() { return this->c.begin(); }
		iterator		end() { return this->c.end(); }

};

#endif
