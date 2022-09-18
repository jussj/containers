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

			typedef	size_t							size_type;
			typedef	ptrdiff_t						difference_type;

			typedef	T								value_type;
			typedef Alloc							allocator_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			
			typedef	VectorIterator<T>						iterator;
			typedef	VectorIterator<const T>					const_iterator;
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
			vector(	InputIt first,
					InputIt last,
					const Alloc& Allocator = Alloc(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
					) : _alloc(Allocator) {
				this->_begin	= this->_alloc.allocate(0);
				this->_end		= this->_begin;
				this->_capacity = this->_begin;
				this->_alloc	= Alloc();
				this->assign(first, last);
			}
			
			vector(const vector<T,Alloc>& src) {
				this->_begin	= this->_alloc.allocate(src.size());
				pointer p		= this->_begin;
				for (size_type s = 0; s < src.size(); s++) {
					this->_alloc.construct(p++, *(src._begin + s));	
				}
				this->_end		= this->_begin + src.size();
				this->_capacity	= this->_begin + src.size();
				//use operator=?
			}
			
			~vector() {
				for (size_type s = 0; s < this->size(); s++)
					this->_alloc.destroy(this->_begin + s);
				this->_alloc.deallocate(this->_begin, this->capacity());
			}
			
			template <class InputIt>
			void 	assign(	InputIt first,
							InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
							) {
				size_type dis	= ft::distance(first, last);
			
				// assign from empty vec?
				// stl distance ft throws length error exception
				if (dis > this->capacity())
					this->reserve(dis);	
				this->clear();
				this->_fill(&(*this->begin()), first, last);
				this->_end = this->_begin + dis;
			}

			void	assign(size_type n, const value_type& value) {
				if (n > this->capacity())
					reserve(n);
				// NEW FUNC: construct param size + value + new end
				for (size_type s = 0; s < n; s++)
					this->_alloc.construct(this->_begin + s, value);	
				this->_end	= this->_begin + n;
				if (this->capacity() < n)
					this->_capacity = this->_end;
			}
			
			allocator_type		get_allocator() const {
				return this->_alloc;
			}
			
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
					if (n > this->capacity()) {
						if (this->size() * 2 > n)
							this->reserve(this->size() * 2);
						else
							this->reserve(n);
					}
					// NEW FUNC: construct param size + value + new end
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
					pointer		tmp			= this->_alloc.allocate(n);
					size_type	array_size	= this->size();
					
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


			void	insert(iterator position, size_type n, const T& x) {
				size_type	new_size		= this->size() + n;
				size_type	new_capacity	= this->capacity();
				
				if (n < 1)
					return ;
				// capacity is enough to insert
				else if (new_size <= this->capacity()) {
					size_type elems_after = this->end() - position;
					if (elems_after > n) {
						// copy elements past position from backwards
						this->_copy_backwards(position, new_size);
						// fill the freed space with n x elements
						this->_fill(&(*position), n, x);
					}
					else {
						// fill forwards (here is backwards)
						this->_copy_backwards(position, new_size);
						// fill the freed space with n x elements
						this->_fill(&(*position), n, x);
					}
				}
				// capacity not enough to insert, reallocate:
				else {
					// optimize capacity depending on new size
					if (new_size > this->capacity()) {
						if (new_size > this->size() * 2)
							new_capacity = new_size;
						else
							new_capacity = this->size() * 2;
					}
					// copy everything in a brand new allocation <3
					this->_reallocate(new_capacity, new_size, n, position, x);
				}
				// adapt end and capacity to new size
				this->_end 		= this->_begin + new_size;
				this->_capacity	= this->_begin + new_capacity;
				std::cout << "---POS IS " << *(this->_end - 1) << std::endl;
			}

			// private functions

			void	_copy_backwards(iterator position, size_type new_size) {
				reverse_iterator	rlast_insert(position - 1);
				reverse_iterator	rbegin_insert(this->_begin + new_size - 1);
				size_type			copy_from = this->size() - 1;

				std::cout << "---POS IS " << *position << std::endl;
				std::cout << "---POS IS " << *rlast_insert << std::endl;
				std::cout << "---POS IS " << *(this->_begin + copy_from) << std::endl;
				//std::cout << "---POS IS " << *rbegin_insert << std::endl;
				std::cout << "---" << std::endl;

				for (reverse_iterator rit = rbegin_insert; rit != rlast_insert; ++rit) {
					// construct on rbegin with copy_from
					this->_alloc.construct(&(*rbegin_insert.base()), *(this->begin() + copy_from));
					// destroy copy_from
					this->_alloc.destroy(this->_begin + copy_from);
					if (this->_begin + copy_from == &(*position))
							break ;
					--copy_from;
				}
				std::cout << "---END" << std::endl;
			}
	
			void	_reallocate(size_type new_capacity,
								size_type new_size,
								size_type n,
								iterator position,
								const T& x) {
				iterator	it			= this->begin();
				pointer		new_array	= this->_alloc.allocate(new_capacity + 1);
				
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
			}
			// end of private functions


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
				
				if (this->size() + length > this->capacity()) {
					//new_capacity = new_size;
					if (new_size > this->size() * 2)
						new_capacity = new_size;
					else
						new_capacity = this->size() * 2;
				}
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
				//return ret;	// ???? 
				return it;		// ???? 
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

			// call it range
			template<class Iterator>
			void		_fill(pointer start, Iterator first, Iterator last) {
				for (Iterator it = first; it != last; it++) {
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
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
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
