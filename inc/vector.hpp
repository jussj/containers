/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:42:09 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/26 16:04:08 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <stdexcept>

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
			void 		resize(size_type sz, T c = T());

			size_type 	capacity() const {
				return _capacity - _end;
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
					pointer tmp	= this->_alloc.allocate(n);
					
					for (size_type s = 0; s < this->size(); s++)
						this->_alloc.construct(tmp + s, *(this->_begin + s));
					
					for (size_type s = 0; s < this->size(); s++) {
						this->_alloc.destroy(this->_begin + s);
					}
					this->_alloc.deallocate(this->_begin, this->size());
					this->_begin	= tmp;
					this->_end	= this->_begin + this->size();
					this->_capacity = this->_begin + n;
				}
			}
		
		// ACCESS

			reference 		operator[](size_type n) {
				return *(_begin + n);
			}
			const_reference 	operator[](size_type n) const {
				// implicit cast?
				return *(_begin + n);
			}
			const_reference 	at(size_type n) const;
			reference 		at(size_type n);
			reference 		front() {
				return *(_begin);
			}
			const_reference 	front() const {
				// implicit cast?
				return *(_begin);
			}
			reference 		back() {
				return *(_end - 1);
			}
			const_reference 	back() const {
				// implicit cast?
				return *(_end);
			}
		
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

//# include "vector.tpp"

#endif
