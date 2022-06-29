/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/29 19:58:34 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <stdexcept>		// exceptions
# include <sstream>

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:

		// TYPES
			// iterator and const iterator are pointers
			typedef	T*				iterator;
			typedef	const T*			const_iterator;
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
			
			~vector() {
				for (size_type s = 0; s < this->size(); s++) {
					this->_alloc.destroy(this->_begin + s);
				}
				this->_alloc.deallocate(this->_begin, this->size());
			}
			
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
					for (size_type s = n; s < this->size(); s++) {
						_alloc.destroy(this->_begin + s);
					}
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
				else if (n > capacity()) {
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
				this->reserve(1);
				this->_end += 1;
				this->_alloc.construct(this->_end - 1, x);
			}
			void 		pop_back() {
				this->_alloc.destroy(this->_end - 1);
				//this->_alloc.deallocate(this->_end, 1);
				this->_end--;
			}
			
			iterator 	insert(iterator position, const T& x);
			void 		insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void 		insert(iterator position, InputIterator first, InputIterator last);
			iterator 	erase(iterator position);
			iterator 	erase(iterator first, iterator last);
			void 		swap(vector<T,Alloc>&);
			void 		clear();

		// ATTRIBUTES

			allocator_type		_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;

		// UTILS

			// put that ft in another utils header
			std::string	long_to_str(size_t n) {
				std::stringstream	stream;

				stream << n;
				std::string 		str = stream.str();
				return str;
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

//# include "vector.tpp"

#endif	/* VECTOR_HPP */
