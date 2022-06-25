/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/25 17:38:24 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
		
		// TYPES
			// iterator and const iterator are pointers
			typedef	T*				iterator;
			typedef	const T*			const_iterator;
			
			// right types?	
			typedef	size_t				size_type;
			typedef	ptrdiff_t			difference_type;

			typedef	T				value_type;
			typedef Alloc				allocator_type;
			typedef typename Alloc::reference	reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer		pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			
			// using std reverse_iterator
			typedef std::reverse_iterator<iterator>		reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CTOR/CPY/DTOR
			explicit vector(const Alloc& Allocator = Alloc())
				: _alloc(Allocator), _begin(NULL), _end(NULL), _capacity(NULL) {}

			explicit vector(size_type n, const T& value = T(), 
					const Alloc& Allocator = Alloc()) 
				: _alloc(Allocator) {
				
				this->_begin 	= this->_alloc.allocate(n + 1);
				pointer p 	= this->_begin;
				
				for (size_type s = 0; s < n; s++)
					this->_alloc.construct(p++, value);	
				this->_end	= this->_begin + n;
				this->_capacity = this->_end;
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Alloc& = Alloc());
			vector(const vector<T,Alloc>& x);
			
			~vector();
			
			template <class InputIterator>
			void 			assign(InputIterator first, InputIterator last);
			void			assign(size_type n, const T& u);
			allocator_type		get_Alloc() const;
			
			vector<T,Alloc>&	operator=(const vector<T,Alloc>& x);

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
			size_type		size() const;		//_begin - _end
			size_type		max_size() const;
			void 			resize(size_type sz, T c = T());
			size_type 		capacity() const;	//_capacity - _end
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
			void 		push_back(const T& x);
			void 		pop_back();
			iterator 	insert(iterator position, const T& x);
			void 		insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void 		insert(iterator position, InputIterator first, InputIterator last);
			iterator 	erase(iterator position);
			iterator 	erase(iterator first, iterator last);
			void 		swap(vector<T,Alloc>&);
			void 		clear();

		private:
			allocator_type		_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);

// specialized algorithms??? need to implement THAT?
//template <class T, class Alloc>
//void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}

# include "vector.tpp"

#endif
