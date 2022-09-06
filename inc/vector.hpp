/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/06 17:26:47 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <stdexcept>	// exceptions
# include <sstream>		// stream
# include <iostream>
# include <algorithm>	// equal
# include "vectorIterator.hpp"
# include "utils.hpp"
# include "type_traits/enable_if.hpp"
# include "type_traits/is_integral.hpp"
# include "iterator/reverse_iterator.hpp"
# include "algorithm/equal.hpp"

namespace ft {
	
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:

		// TYPES
			typedef	VectorIterator<T>				iterator;
			typedef	VectorIterator<const T>			const_iterator;
			typedef	size_t							size_type;
			typedef	ptrdiff_t						difference_type;

			typedef	T								value_type;
			typedef Alloc							allocator_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CTOR/CPY/DTOR

			explicit vector(const Alloc& Allocator = Alloc())
				: _alloc(Allocator), _begin(NULL), _end(NULL), _capacity(NULL) {
					this->_begin	= this->_alloc.allocate(0);
					this->_end		= this->_begin;
					this->_capacity = this->_begin;	
				}

			explicit vector(size_type n, const T& value = T(),
					const Alloc& Allocator = Alloc()) 
				: _alloc(Allocator) {
				//why not using reserve
				this->_begin 	= this->_alloc.allocate(n + 1);
				pointer p 		= this->_begin;
				
				for (size_type s = 0; s < n; s++)
					this->_alloc.construct(p++, value);	
				this->_end		= this->_begin + n;
				this->_capacity = this->_end;
			}

			// put it first in overloads?
			template<class InputIt>
			vector(	//typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
					InputIt first,
					InputIt last,
					const Alloc& = Alloc(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
					) {
				this->assign(first, last);
			}
			
			vector(const vector<T,Alloc>& src) {
				this->_begin	= this->_alloc.allocate(src.capacity());
				pointer p		= this->_begin;
				for (size_type s = 0; s < src.size(); s++) {
					this->_alloc.construct(p++, *(src._begin + s));	
				}
				this->_end		= this->_begin + src.size();
				this->_capacity	= this->_begin + src.capacity();
				//use operator=?
			}
			
			~vector() {
				for (size_type s = 0; s < this->size(); s++)
					this->_alloc.destroy(this->_begin + s);
				//this->_alloc.deallocate(this->_begin, this->size());
				this->_alloc.deallocate(this->_begin, this->capacity());
			}
			
			template <class InputIt>
			void 	assign(	InputIt first,
							InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
							) {
				size_type dis	= ft::distance(first, last);
				//iterator it		= first;
				
				// assign on empty vec??
				if (dis > this->capacity())
					this->reserve(dis);	
				this->clear();
				for (; first != last; first++) 
					this->push_back(*first);	
			}

			void	assign(size_type n, const value_type& value) {
				if (n > this->capacity())
					reserve(n);
				// not destroying elements???
				// assign on empty vec??
				// FUNC construct param size + value + new end
				for (size_type s = 0; s < n; s++)
					this->_alloc.construct(this->_begin + s, value);	
				this->_end	= this->_begin + n;
				if (this->capacity() < n)
					this->_capacity = this->_end;
			}
			
			allocator_type		get_allocator() const {
				return this->_alloc;
			}
			
			//vector&		operator=(const vector& src) {
			vector<T,Alloc>&	operator=(const vector<T,Alloc>& src) {
				if (&src == this)
					return *this;
				this->assign(src.begin(), src.end());
				return *this;
			}

		// ITERATORS

			iterator			begin() {
				return iterator(this->_begin);
			}
			const_iterator 		begin() const {
				return const_iterator(this->_begin);
			}
			iterator 			end() {
				return iterator(this->_end);
			}
			const_iterator		end() const {
				return const_iterator(this->_end);
			}
			reverse_iterator 	rbegin() {
				return reverse_iterator(this->_end);
			}
			const_reverse_iterator	rbegin() const {
				return const_reverse_iterator(this->_end);
			}
			reverse_iterator 	rend() {
				return reverse_iterator(this->_begin);
			}
			const_reverse_iterator	rend() const {
				return const_iterator(this->_begin);
			}

		// CAPACITY

			size_type	size() const {
				return _end - _begin;
			}
			size_type	max_size() const {
				return _alloc.max_size();
			}
			void 		resize(size_type n, T value = T()) {
				if (n > this->size()) {
					if (n > this->capacity())
					{
						if (size() * 2 >= n)				// !!!
								reserve(size() * 2);		// !!!
						else								// !!!
							reserve(n);
					}
					// FUNC construct param size + value + new end
					for (size_type s = this->size(); s < n; s++)
						this->_alloc.construct(_begin + s, value);	
					this->_end = this->_begin + n;
					if (n > this->capacity())
						this->_capacity = this->_end;
				}
				else if (n < this->size()) {
					for (size_type s = n; s < this->size(); s++)
						_alloc.destroy(this->_begin + s);
					this->_end = this->_begin + n;
				}

			}

			size_type 	capacity() const {
				return _capacity - _begin;
			}
			bool 		empty() const {
				if (size())
					return false;
				return true;
			}
			void 		reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector::reserve");

				else if (n > this->capacity()) {
					//pointer tmp				= this->_alloc.allocate(n + 1);
					pointer tmp				= this->_alloc.allocate(n);
					size_type array_size	= this->size();
					
					for (size_type s = 0; s < this->size(); s++)
						this->_alloc.construct(tmp + s, *(this->_begin + s));
					for (size_type s = 0; s < this->size(); s++)
						this->_alloc.destroy(this->_begin + s);

					this->_alloc.deallocate(this->_begin, this->size());
					this->_begin	= tmp;
					this->_end		= this->_begin + array_size;
					this->_capacity = this->_begin + n;
				}
			}
		
		// ACCESS

			reference 	operator[](size_type n) {
				return *(this->_begin + n);
			}
			const_reference operator[](size_type n) const {
				return *(this->_begin + n);
			}
			const_reference at(size_type n) const {
				_range_check(n);
				return *(this->_begin + n);
			}
			reference 	at(size_type n) {
				_range_check(n);
				return *(this->_begin + n);
			}
			reference 	front() {
				return *(this->_begin);
			}
			const_reference front() const {
				return *(this->_begin);
			}
			reference 	back() {
				return *(this->_end - 1);
			}
			const_reference back() const {
				return *(this->_end - 1);
			}
		
		// MODIFIERS

			void 		push_back(const T& x) {
				if (this->empty())
					this->reserve(1);
				else if (this->size() + 1 > this->capacity())
					this->reserve(this->size() * 2);
				this->_end += 1;
				this->_alloc.construct(this->_end - 1, x);
			}

			void 		pop_back() {
				this->_alloc.destroy(this->_end - 1);
				this->_end -= 1;
			}
			
			iterator 	insert(iterator position, const T& x) {
				size_type offset = ft::distance(this->begin(), position);
			
				insert(position, 1, x);
				return this->begin() + offset;
			}

			void 		insert(iterator position, size_type n, const T& x) {
				pointer		new_array;
				size_type	new_capacity;
				size_type	new_size 		= this->size() + n;
				
				// check whether capacity calculation is ok or not ok
				if (this->size() + n > this->capacity())
					new_capacity = this->capacity() + n;
					//new_capacity = this->capacity() + (n * 2);
				else 
					new_capacity = this->capacity();
				new_array 	= this->_alloc.allocate(new_capacity);
				iterator it	= this->begin();
				for (size_type s = 0; s < new_size; s++) {
					if (it == position) {
						this->_fill(new_array + s, n, x);
						s += n;
						this->_alloc.construct(new_array + s, *it);
					}
					else
						this->_alloc.construct(new_array + s, *it);
					it++;
				}
				this->clear();
				this->_alloc.deallocate(this->_begin, this->size());
				this->_begin 	= new_array;
				this->_end 		= this->_begin + new_size;
				this->_capacity	= this->_begin + new_capacity;
			}

			// enable_if?
			template <class InputIt>
			void 	insert(	iterator position, 
							InputIt first, 
							InputIt last,	
							typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
							) {
				pointer		new_array;
				size_type	new_capacity;
				size_type 	length		= ft::distance(first, last);
				size_type	new_size	= this->size() + length;
				
				if (this->size() + length > this->capacity())
					new_capacity = new_size;
				else
					new_capacity = this->capacity();

				new_array 	= this->_alloc.allocate(new_capacity);
				iterator it	= this->begin();
				for (size_type s = 0; s < new_size; s++) {
					if (it == position) {
						this->_fill(new_array + s, first, last);
						s += length;
						this->_alloc.construct(new_array + s, *it);
					}
					else
						this->_alloc.construct(new_array + s, *it);
					it++;
				}
				this->clear();
				this->_alloc.deallocate(this->_begin, this->size());
				this->_begin 	= new_array;
				this->_end 		= this->_begin + new_size;
				this->_capacity	= this->_begin + new_capacity;
			}
			
			iterator 	erase(iterator first, iterator last) {
				//iterator	ret;
				size_t		dis		= ft::distance(first, last);
				iterator	it		= first;
					
				for (size_t i = 0; i < dis; ++i) {
					erase(first);
					//ret = erase(it);
				}
				//return ret; // ???? 
				return it; // ???? 
			}

			iterator 	erase(iterator position) {
				// check pos? must be valid and dereferenceable (not end())
				size_type	new_size 		= this->size() - 1;
				size_type	new_position	= ft::distance(this->begin(), position);
				size_type 	s 				= new_position;

				for (iterator it = position; it < this->end(); it++) {
					if (it == position) {
						this->_alloc.destroy(this->_begin + s);
						it++;
						this->_alloc.construct(this->_begin + s, *it);
					}
					else if (it > position) {
						this->_alloc.destroy(this->_begin + s);
						this->_alloc.construct(this->_begin + s, *it);
					}
					s++;
				}
				this->_alloc.destroy(this->_begin + s);
				this->_end 	= this->_begin + new_size;
				
				return this->begin() + new_position;
			}
			
			void 		swap(vector<T,Alloc>& src) {
				pointer	tmp_begin 		= this->_begin;
				pointer	tmp_end 		= this->_end;
				pointer	tmp_capacity 	= this->_capacity;
				
				this->_begin	= src._begin;
				this->_end 		= src._begin + src.size();
				this->_capacity	= src._begin + src.capacity();
				src._begin		= tmp_begin;
				src._end		= tmp_end;
				src._capacity	= tmp_capacity;

			}
			
			void 		clear() {
				for (size_type s = 0; s < this->size(); s++)
					this->_alloc.destroy(this->_begin + s);
				this->_end = this->_begin;
			}

		private:

		// ATTRIBUTES

			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;

		// UTILS

			void		_fill(pointer start, size_type size, const T& value) {
				for (size_type s = 0; s < size; s++)
					this->_alloc.construct(start + s, value);
			}

			void		_fill(pointer start, iterator first, iterator last) {
				for (iterator it = first; it != last; it++) {
					this->_alloc.construct(start++, *it);
				}
			}
			
			void		_range_check(size_type n) const {
				std::string	fmt;
				//fmt = "vector::_M_range_check: __n (which is ";
				fmt = "vector::_range_check: n (which is ";

				fmt.append(ft::long_to_str(n));
				fmt.append(") >= this->size() (which is ");
				fmt.append(ft::long_to_str(this->size()));
				fmt.append(")");
				if (n >= this->size())
					throw std::out_of_range(fmt);
			}
		
	};	/* class vector */

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return (x.size() == y.size()
	      && !(ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())));
		  //&& std::equal(x.begin(), x.end(), y.begin()));
		  //careful, using std::equal!!!!
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		//return x < y;
		return ft::lexicographical_compare(	x.begin(), x.end(),
											y.begin(), y.end() );	
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(x == y);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return y < x;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(x < y);
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(y < x);
	}
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
} 	/* namespace ft */

#endif	/* VECTOR_HPP */
