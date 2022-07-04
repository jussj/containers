/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:19:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/04 13:42:40 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL
# define IS_INTEGRAL

# include <type_traits>

template <class T> 
struct is_integral : public integral_constant {};

#endif	/* IS_INTEGRAL */
