/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:22:36 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/04 13:25:49 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF
# define ENABLE_IF

template <bool Cond, class T = void>
struct enable_if {};

template <true, T> 
struct enable_if {
	typedef T	type;
};

#endif	/* ENABLE_IF */
