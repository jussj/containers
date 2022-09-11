void	insert(iterator position, size_type n, const T& x) {
	if (n < 1)
		return ;
	else if (new_size > capacity) {
		
	}
}

void	_reallocate(	pointer new_array,
						size_type new_size,
						size_type new_capacity, 
						iterator copy_start
						) {
	new_array 	= this->_alloc.allocate(new_capacity + 1);
	//iterator it	= this->begin();
	iterator it	= copy_start;
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
