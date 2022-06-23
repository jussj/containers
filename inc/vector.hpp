/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/23 16:07:28 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# define NAMESPACE std

namespace ft {
	template <class T, class Allocator = allocator<T> >
	class vector {
		public:
		
		// TYPES
			typedef						iterator;
			typedef						const_iterator;
			typedef						size_type;
			typedef						difference_type;
			typedef	T					value_type;
			typedef Allocator				allocator_type;
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer		pointer;
			typedef typename Allocator::const_pointer	const_pointer
			typedef NAMESPACE::reverse_iterator<iterator>		reverse_iterator;
			typedef NAMESPACE::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CTOR/CPY/DTOR
			explicit vector(const Allocator& = Allocator());
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
			vector(const vector<T,Allocator>& x);
			
			~vector();
			
			template <class InputIterator>
			void 			assign(InputIterator first, InputIterator last);
			void			assign(size_type n, const T& u);
			allocator_type		get_allocator() const;
			
			vector<T,Allocator>&	operator=(const vector<T,Allocator>& x);

		// ITERATORS
			iterator		begin();
			const_iterator 		begin() const;
			iterator 		end();
			const_iterator		end() const;
			reverse_iterator 	rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator 	rend();
			const_reverse_iterator	rend() const;

		// CAPACITY
			size_type		size() const;
			size_type		max_size() const;
			void 			resize(size_type sz, T c = T());
			size_type 		capacity() const;
			bool 			empty() const;
			void 			reserve(size_type n);
		
		// ACCESS
			reference 		operator[](size_type n);
			const_reference 	operator[](size_type n) const;
			const_reference 	at(size_type n) const;
			reference 		at(size_type n);
			reference 		front();
			const_reference 	front() const;
			reference 		back();
			const_reference 	back() const;
		
		// MODIFIERS
			void 			push_back(const T& x);
			void 			pop_back();
			iterator 		insert(iterator position, const T& x);
			void 			insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void 			insert(iterator position, InputIterator first, InputIterator last);
			iterator 		erase(iterator position);
			iterator 		erase(iterator first, iterator last);
			void 			swap(vector<T,Allocator>&);
			void 			clear();
	};

	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

// specialized algorithms??? need to implement THAT?
//template <class T, class Allocator>
//void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

#endif
