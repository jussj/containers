/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:42:00 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/10 17:23:10 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft {

	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class iter>
	class iterator_traits {
		Iterator::difference_type		difference_type;
		Iterator::value_type			value_type;
		Iterator::pointer				pointer;
		Iterator::reference				reference;
		Iterator::iterator_category		iterator_category;
	};

	template<class T>
	class iterator_traits<T *> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T *							pointer;
		typedef T &							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<class T>
	class iterator_traits<const T *> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T *					pointer;
		typedef const T &					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

}

#endif
