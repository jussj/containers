/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:07:18 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/24 19:07:28 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TPP
# define VECTOR_TPP

// ACCESS

template <class T, class Alloc = std::allocator<T> >
vector<T>::reference 	vector<T>::operator[](size_type n) {
	// if container is empty? 
	// if n is fucked up?
	return _begin + n;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::const_reference vector<T>::operator[](size_type n) const {
	// if container is empty? 
	// if n is fucked up?
	return _begin + n;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::reference 	vector<T>::front() {
	return _begin;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::const_reference vector<T>::front() const {
	return _begin;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::reference 	vector<T>::back() {
	return _end;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::const_reference vector<T>::back() const {
	return _end;
}

// CAPACITY

template <class T, class Alloc = std::allocator<T> >
vector<T>::size_type	vector<T>::size() const {
	// if container empty? ret 0
	return _begin - _end;
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::size_type	vector<T>::max_size() const {
	return _allocator.max_size();
}

template <class T, class Alloc = std::allocator<T> >
vector<T>::size_type 	vector<T>::capacity() const {
	return _capacity - _end;
}

template <class T, class Alloc = std::allocator<T> >
bool 	vector<T>::empty() const {
	if (size())
		return false;
	return true;
}

#endif
