void	insert(iterator position, size_type n, const T& x) {
	size_type	new_size	= this->size() + n;
	
	if (n < 1)
		return ;
	// capacity is enough to insert
	else if (new_size <= this->capacity) {
		size_type elems_after = this->end() - position;
		if (elems_after > n) {
			// copy elements past position from backwards
			this->_copy_backwards(position, n, x);
			// fill the freed space with n x elements
			this->_fill(position, n, x);
		}
		else {
			// fill forwards (here is backwards)
			this->_copy_backwards(position, n, x);
			// fill the freed space with n x elements
			this->_fill(position, n, x);
		}
	}
	// capacity not enough to insert, reallocate:
	else {
		size_type	new_capacity	= this->capacity();
		// optimize capacity depending on new size
		if (new_size > this->capacity()) {
			if (new_size > this->size() * 2)
				new_capacity = new_size;
			else
				new_capacity = this->size() * 2;
		}
		// copy everything in a brand new allocation <3
		this->_reallocate(new_capacity, position, n)
	}
	// adapt end and capacity to new size
	this->_end 		= this->_begin + new_size;
	this->_capacity	= this->_begin + new_capacity;
}

void	_copy_backwards(iterator position, size_type new_size) {
	reverse_iterator	rlast_insert	= position + n - 1;
	reverse_iterator	rbegin_insert	= new_size - 1;
	size_type			copy_from		= this->size() - 1;

	for (reverse_iterator rit = rbegin_insert; rit != rlast_insert; ++rit) {
		// construct on rbegin with copy_from
		this->_alloc.construct(rbegin_insert, *(this->begin() + copy_from));
		// destroy copy_from
		this->_alloc.destroy(this->_begin + copy_from);
		--copy_from;
	}
}

void	_reallocate(size_type new_capacity, new_size, iterator position, const T& x) {
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
