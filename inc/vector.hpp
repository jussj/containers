/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/08 21:29:41 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <stdexcept>		// exceptions
# include <sstream>		// stream
# include <iostream>
# include "VectorIterator.hpp"

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:

		// TYPES
			typedef	VectorIterator<T>			iterator;
			typedef	VectorIterator<const T>			const_iterator;
			typedef	size_t					size_type;
			typedef	ptrdiff_t				difference_type;

			typedef	T					value_type;
			typedef Alloc					allocator_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			
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

			// need enable_if and is_integral
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const Alloc& = Alloc());
			
			vector(const vector<T,Alloc>& src) {
				// if is same?
				this->_begin	= this->_alloc.allocate(src.capacity());
				pointer p	= this->_begin;
				for (size_type s = 0; s < src.size(); s++) {
					this->_alloc.construct(p++, src._begin + s);	
				}
				this->_end	= this->_begin + size();
				this->_capacity	= this->_begin + capacity();
			}
			
			~vector() {
				for (size_type s = 0; s < this->size(); s++)
					this->_alloc.destroy(this->_begin + s);
				this->_alloc.deallocate(this->_begin, this->size());
			}
			
			template <class InputIterator>
			void 			assign(InputIterator first, InputIterator last) {
				size_type dis	= this->distance(first, last);
				iterator it	= first;
				
				if (dis > this->capacity())
					this->reserve(dis);	
				this->clear();
				for (iterator it = first; it != last; it++) 
					this->push_back(*it);	
			}

			void			assign(size_type n, const value_type& value) {
				if (n > this->capacity())
					reserve(n);
				// not destroying elements???
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
			}

		// ITERATORS

			iterator		begin() {
				return iterator(this->_begin);
			}
			const_iterator 		begin() const {
				return const_iterator(this->_begin);
			}
			iterator 		end() {
				return iterator(this->_end);
			}
			const_iterator		end() const {
				return const_iterator(this->_end);
			}
			reverse_iterator 	rbegin() {
				return reverse_iterator(this->_begin);
			}
			const_reverse_iterator	rbegin() const {
				return const_reverse_iterator(this->_begin);
			}
			reverse_iterator 	rend() {
				return reverse_iterator(back());
			}
			const_reverse_iterator	rend() const {
				return const_iterator(back());
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
						reserve(n);
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
					pointer tmp		= this->_alloc.allocate(n + 1);
					size_type array_size	= this->size();
					
					for (size_type s = 0; s < this->size(); s++)
						this->_alloc.construct(tmp + s, *(this->_begin + s));
					for (size_type s = 0; s < this->size(); s++)
						this->_alloc.destroy(this->_begin + s);
					this->_alloc.deallocate(this->_begin, this->size());
					this->_begin	= tmp;
					this->_end	= this->_begin + array_size;
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
			const_reference at(size_type n) {
				_range_check(n);
				return *(this->_begin + n);
			}
			reference 	at(size_type n) const {
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
				if (this->size() + 1 > this->capacity())
					this->reserve(this->capacity() + 1);
				this->_end += 1;
				this->_alloc.construct(this->_end - 1, x);
			}
			void 		pop_back() {
				this->_alloc.destroy(this->_end - 1);
				this->_end--;
			}
			
			iterator 	insert(iterator position, const T& x);
			void 		insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void 		insert(		iterator position, 
							InputIterator first, 
							InputIterator last	);
			iterator 	erase(iterator position);
			iterator 	erase(iterator first, iterator last);
			
			void 		swap(vector<T,Alloc>& src) {
				pointer	tmp_begin 	= this->_begin;
				pointer	tmp_end 	= this->_end;
				
				this->_begin	= src._begin;
				this->_end 	= src._begin + src.size();
				this->_capacity	= src._begin + src.capacity();
				src._begin	= tmp_begin;
				src._end	= tmp_end;

			}
			
			void 		clear() {
				for (size_type s = 0; s < this->size(); s++)
					this->_alloc.destroy(this->_begin + s);
				this->_end = this->_begin;
			}

		private:

		// ATTRIBUTES

			allocator_type		_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;

		// UTILS

			// put these functions in another utils header
			std::string	long_to_str(size_t n) {
				std::stringstream	stream;

				stream << n;
				std::string 		str = stream.str();
				return str;
			}

			template<class It>
			difference_type	distance(It first, It last) {
				return last - first;
			}
			
			void		_range_check(size_type n) {
				std::string	fmt;
				fmt = "vector::_M_range_check: __n (which is ";

				fmt.append(long_to_str(n));
				fmt.append(") >= this->size() (which is ");
				fmt.append(long_to_str(this->size()));
				fmt.append(")");
				if (n >= this->size())
					throw std::out_of_range(fmt);
			}
		
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x == y;
	}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x < y;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x != y;
	}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x > y;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x >= y;
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return x <= y;
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif	/* VECTOR_HPP */
