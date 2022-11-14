#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>				// ptrdiff_t
# include <memory>				// allocator
# include <stdexcept>			// exceptions
# include <sstream>				// stream
# include <iostream>
# include <algorithm>			// equal
# include "vector_iterator.hpp"
# include "utils.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"

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
			
			typedef	vector_iterator<T>						iterator;
			typedef	vector_iterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CTOR/CPY/DTOR

			explicit
			vector(const Alloc& Allocator = Alloc())
				: _alloc(Allocator), _begin(NULL), _end(NULL), _capacity(NULL) {
					_begin		= _alloc.allocate(0);
					_end		= _begin;
					_capacity	= _begin;	
				}

			explicit
			vector(size_type n, const T& value = T(),
					const Alloc& Allocator = Alloc()) 
				: _alloc(Allocator) {
				this->_begin	= _alloc.allocate(n + 1);
				pointer p		= _begin;
				
				for (size_type s = 0; s < n; s++)
					_alloc.construct(p++, value);	
				_end		= _begin + n;
				_capacity	= _end;
			}

			template<class InputIt>
			vector(InputIt first, InputIt last, const Alloc& Allocator = Alloc())
					: _alloc(Allocator) {
				
				_begin		= _alloc.allocate(0);
				_end		= _begin;
				_capacity	= _begin;
				_alloc	= Alloc();
				
				_dispatch_assign(first, last, typename ft::is_integral<InputIt>::type());	
				//assign(first, last);
			}
			
			vector(const vector<T,Alloc>& src) {
				if (this == &src)
					return ;
				this->_begin	= _alloc.allocate(src.size());
				pointer p		= _begin;
				for (size_type s = 0; s < src.size(); s++) {
					this->_alloc.construct(p++, *(src._begin + s));	
				}
				_end		= _begin + src.size();
				_capacity	= _begin + src.size();
			}
			
			~vector() {
				for (size_type s = 0; s < size(); s++)
					_alloc.destroy(_begin + s);
				_alloc.deallocate(_begin, capacity());
			}

			template <class InputIt>
			void
			assign(InputIt first, InputIt last) {
				_dispatch_assign(first, last, typename ft::is_integral<InputIt>::type());	
			}
			
			void
			assign(size_type n, const value_type& value) {
				_dispatch_assign(n, value, typename ft::is_integral<size_type>::type());	
			}
			
			allocator_type
			get_allocator() const {
				return _alloc;
			}
			
			vector<T,Alloc>&
			operator=(const vector<T,Alloc>& src) {
				if (&src == this)
					return *this;
				this->assign(src.begin(), src.end());
				return *this;
			}

		// ITERATORS

			iterator
			begin() {
				return iterator(_begin);
			}
			const_iterator
			begin() const {
				return const_iterator(_begin);
			}
			iterator
			end() {
				return iterator(_end);
			}
			const_iterator
			end() const {
				return const_iterator(_end);
			}
			reverse_iterator
			rbegin() {
				return reverse_iterator(_end);
			}
			const_reverse_iterator
			rbegin() const {
				return const_reverse_iterator(_end);
			}
			reverse_iterator
			rend() {
				return reverse_iterator(_begin);
			}
			const_reverse_iterator
			rend() const {
				return const_iterator(_begin);
			}

		// CAPACITY

			size_type
			size() const {
				return _end - _begin;
			}
			size_type
			max_size() const {
				return _alloc.max_size();
			}
			void
			resize(size_type n, T value = T()) {
				if (n > size()) {
					if (n > capacity()) {
						if (size() * 2 > n)
							reserve(size() * 2);
						else
							reserve(n);
					}
					for (size_type s = size(); s < n; s++)
						_alloc.construct(_begin + s, value);	
					_end = _begin + n;
					if (n > capacity())
						_capacity = _end;
				}
				else if (n < size()) {
					for (size_type s = n; s < size(); s++)
						_alloc.destroy(_begin + s);
					_end = _begin + n;
				}
			}

			size_type
			capacity() const {
				return _capacity - _begin;
			}
			bool
			empty() const {
				if (size())
					return false;
				return true;
			}
			void
			reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector::reserve");

				else if (n > capacity()) {
					pointer		tmp			= _alloc.allocate(n);
					size_type	array_size	= size();
					
					for (size_type s = 0; s < size(); s++)
						_alloc.construct(tmp + s, *(_begin + s));
					for (size_type s = 0; s < size(); s++)
						_alloc.destroy(_begin + s);

					_alloc.deallocate(_begin, size());
					_begin	= tmp;
					_end		= _begin + array_size;
					_capacity = _begin + n;
				}
			}
		
		// ACCESS

			reference
			operator[](size_type n) {
				return *(_begin + n);
			}
			const_reference
			operator[](size_type n) const {
				return *(_begin + n);
			}
			const_reference
			at(size_type n) const {
				_range_check(n);
				return *(_begin + n);
			}
			reference
			at(size_type n) {
				_range_check(n);
				return *(_begin + n);
			}
			reference
			front() {
				return *(_begin);
			}
			const_reference
			front() const {
				return *(_begin);
			}
			reference
			back() {
				return *(_end - 1);
			}
			const_reference
			back() const {
				return *(_end - 1);
			}
		
		// MODIFIERS

			void
			push_back(const T& x) {
				if (empty())
					reserve(1);
				else if (size() + 1 > capacity())
					reserve(size() * 2);
				_end += 1;
				_alloc.construct(_end - 1, x);
			}

			void
			pop_back() {
				_alloc.destroy(_end - 1);
				_end -= 1;
			}
			
			iterator
			insert(iterator position, const T& x) {
				size_type offset = ft::distance(begin(), position);
			
				insert(position, 1, x);
				return begin() + offset;
			}

			void
			insert(iterator position, size_type n, const T& x) {
				_insert_dispatch(position, n, x, typename ft::is_integral<size_type>::type());
			}
				
			template <class InputIt>
			void
			insert(iterator position, InputIt first, InputIt last) {
				_insert_dispatch(position, first, last, typename ft::is_integral<InputIt>::type());
			}
			
			iterator
			erase(iterator first, iterator last) {
				iterator	it;
				size_t		dis		= ft::distance(first, last);
					
				for (size_t i = 0; i < dis; ++i)
					it = erase(first);
				return it;
			}

			iterator
			erase(iterator position) {
				// check pos? must be valid and dereferenceable (not end())
				size_type	new_size 		= size() - 1;
				size_type	new_position	= ft::distance(begin(), position);
				size_type 	s 				= new_position;

				for (iterator it = position; it < end(); it++) {
					if (it == position) {
						_alloc.destroy(_begin + s);
						it++;
						_alloc.construct(_begin + s, *it);
					}
					else if (it > position) {
						_alloc.destroy(_begin + s);
						_alloc.construct(_begin + s, *it);
					}
					s++;
				}
				_alloc.destroy(_begin + s);
				_end 	= _begin + new_size;
				
				return begin() + new_position;
			}
			
			void
			swap(vector<T,Alloc>& src) {
				pointer	tmp_begin 		= _begin;
				pointer	tmp_end 		= _end;
				pointer	tmp_capacity 	= _capacity;
				
				_begin		= src._begin;
				_end		= src._begin + src.size();
				_capacity	= src._begin + src.capacity();
				src._begin		= tmp_begin;
				src._end		= tmp_end;
				src._capacity	= tmp_capacity;
			}
			
			void
			clear() {
				for (size_type s = 0; s < size(); s++)
					_alloc.destroy(_begin + s);
				_end = _begin;
			}

		private:

		// ATTRIBUTES //

			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;

		// AUX MEMBER FUNCTIONS //
		
			// DISPATCH

			template <class InputIt>
			void
			_dispatch_assign(InputIt first, InputIt last, ft::false_type) {
				
				size_type dis	= ft::distance(first, last);
			
				// assign from empty vec?
				// stl distance ft throws length error exception
				if (dis > capacity())
					reserve(dis);	
				clear();
				_fill(&(*begin()), first, last);
				_end = _begin + dis;
			}

			void
			_dispatch_assign(size_type n, const value_type& value, ft::true_type) {
				
				if (n > capacity())
					reserve(n);
				for (size_type s = 0; s < n; s++)
					_alloc.construct(_begin + s, value);	
				_end	= _begin + n;
				if (capacity() < n)
					_capacity = _end;
			}

			void
			_insert_dispatch(iterator position, size_type n, const T& x, ft::true_type) {
				
				size_type	new_size		= size() + n;
				size_type	new_capacity	= capacity();
				
				if (n < 1)
					return ;
				else if (new_size <= capacity()) {
					size_type elems_after = end() - position;
					if (elems_after > n) {
						_copy_backwards(position, new_size);
						_fill(&(*position), n, x);
					}
					else {
						_copy_forward(position, elems_after, n, new_size);
						_fill(&(*position), n, x);
					}
				}
				else {
					if (new_size > capacity()) {
						if (new_size > size() * 2)
							new_capacity = new_size;
						else
							new_capacity = size() * 2;
					}
					_reallocate(new_capacity, new_size, n, position, x);
				}
				_end 		= _begin + new_size;
				_capacity	= _begin + new_capacity;
			}

			template <class InputIt>
			void
			_insert_dispatch(iterator position, InputIt first, InputIt last, ft::false_type) {	
				
				size_type 	length			= ft::distance(first, last);
				size_type	new_size		= size() + length;
				size_type	new_capacity	= capacity();
				
				if (length < 1)
					return ;
				else if (new_size <= capacity()) {
					size_type elems_after = end() - position;
					if (elems_after > length) {
						_copy_backwards(position, new_size);
						_fill(&(*position), first, last);
					}
					else {
						_copy_forward(position, elems_after, length, new_size);
						_fill(&(*position), first, last);
					}
				}
				else {
					if (new_size > capacity()) {
						if (new_size > size() * 2)
							new_capacity = new_size;
						else
							new_capacity = size() * 2;
					}
					_reallocate(new_capacity, new_size, position, first, last);
				}
				_end 		= _begin + new_size;
				_capacity	= _begin + new_capacity;
			}

			// EXCEPTION
			
			void
			_range_check(size_type n) const {
				std::string	fmt;
				fmt = "vector::_range_check: n (which is ";

				fmt.append(ft::long_to_str(n));
				fmt.append(") >= this->size() (which is ");
				fmt.append(ft::long_to_str(size()));
				fmt.append(")");
				if (n >= size())
					throw std::out_of_range(fmt);
			}
			
			//	FILL

			void
			_fill(pointer start, size_type size, const T& value) {
				for (size_type s = 0; s < size; s++)
					_alloc.construct(start + s, value);
			}

			// call it range
			template<class Iterator>
			void
			_fill(pointer start, Iterator first, Iterator last) {
				for (Iterator it = first; it != last; it++) {
					_alloc.construct(start++, *it);
				}
			}

			// COPY

			void
			_copy_backwards(iterator position, size_type new_size) {
				reverse_iterator	rlast_insert(position - 1);
				reverse_iterator	rbegin_insert(_begin + new_size - 1);
				size_type			copy_from = size() - 1;

				// condition NOT GOOD THOUGH
				for	(	reverse_iterator rit = rbegin_insert;
						rit != rlast_insert; 
						++rit	) {
					_alloc.construct(	&(*rit.base()),
											*(begin() + copy_from));
					_alloc.destroy(_begin + copy_from);
					if (_begin + copy_from == &(*position))
							break ;
					--copy_from;
				}
			}
			
			void
			_copy_forward(
					iterator position,
					size_type elems_after,
					size_type n,
					size_type new_size) {
				iterator	new_end = begin() + new_size - 1;
				iterator	it		= position;
					
				for (size_type i = 0; i < elems_after; ++i) {
					_alloc.construct(&(*it) + n, *it);
					_alloc.destroy(&(*it));
					++it;
				}
			}

			// REALLOCATION

			void
			_reallocate(
					size_type new_capacity,
					size_type new_size,
					size_type n,
					iterator position,
					const T& x) {
				iterator	it			= begin();
				pointer		new_array	= _alloc.allocate(new_capacity + 1);
				
				for (size_type s = 0; s < new_size; s++) {
					if (it == position) {
						_fill(new_array + s, n, x);
						s += n;
						_alloc.construct(new_array + s, *it);
					}
					else
						_alloc.construct(new_array + s, *it);
					it++;
				}
				clear();
				_alloc.deallocate(_begin, size());
				_begin 	= new_array;
			}
			
			template<class InputIt>	
			void
			_reallocate(	size_type new_capacity,
							size_type new_size,
							iterator position,
							InputIt first,
							InputIt last) {
				pointer new_array	= _alloc.allocate(new_capacity);
				iterator	it		= begin();
				size_type 	length	= ft::distance(first, last);

				for (size_type s = 0; s < new_size; s++) {
					if (it == position) {
						_fill(new_array + s, first, last);
						s += length;
						_alloc.construct(new_array + s, *it);
					}
					else
						_alloc.construct(new_array + s, *it);
					++it;
				}
				clear();
				_alloc.deallocate(_begin, size());
				_begin 	= new_array;
			}
			
	};	/* class vector */

	template <class T, class Alloc>
	bool
	operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return (x.size() == y.size()
	      && !(ft::lexicographical_compare(	x.begin(), x.end(),
											y.begin(), y.end())));
	}
	template <class T, class Alloc>
	bool
	operator<(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return ft::lexicographical_compare(	x.begin(), x.end(),
											y.begin(), y.end());	
	}
	template <class T, class Alloc>
	bool
	operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(x == y);
	}
	template <class T, class Alloc>
	bool
	operator>(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return y < x;
	}
	template <class T, class Alloc>
	bool
	operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(x < y);
	}
	template <class T, class Alloc>
	bool
	operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y) {
		return !(y < x);
	}
	template <class T, class Alloc>
	void
	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

} 	/* namespace ft */

#endif	/* VECTOR_HPP */
