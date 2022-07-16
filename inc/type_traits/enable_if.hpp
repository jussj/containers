/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:22:36 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/16 17:30:36 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF
# define ENABLE_IF

namespace ft {

	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T> 
	struct enable_if<true, T> {
		typedef T	type;
	};	/* template class struct enable if */

}	/* namespace ft */

#endif	/* ENABLE_IF */
