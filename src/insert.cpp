
// OLD INSERT


			void 		insert(iterator position, size_type n, const T& x) {
				pointer		new_array;
				size_type	new_capacity;
				size_type	new_size 		= this->size() + n;
				//iterator	rbegin_insert	= position + n - 1;
				//iterator	rlast_insert	= position;
				//size_type	copy_to			= new_size - 1;
				//size_type	copy_from		= this->size() - 1;

				// new vector each time insert is called??	
				// check whether capacity calculation is ok or not ok
				if (n < 1)
					return ;
				//if position is last() you know what to do
				if (new_size > this->capacity()) {
					if (new_size > this->size() * 2)
						//this->reserve(new_size);
						new_capacity = new_size;
					else
						//this->reserve(this->size() * 2);
						new_capacity = this->size() * 2;
				}
				else 
					new_capacity = this->capacity();
				// NEW INSERT: COPY/CONSTRUCT FROM THE END
				//for (iterator it = rbegin_insert; it != rlast_insert; ++it) {
					//std::cout<<"RBEGIN "<<*it<<" RLAST "<<*rlast_insert<<" CPY TO "<<copy_to<<" CPY FROM "<<copy_from<<std::endl;
					//this->_alloc.construct(this->_begin + copy_to, *(this->begin() + copy_from));
					//this->_alloc.destroy(this->_begin + copy_from);
					//--copy_to;
					//--copy_from;
					//this->_alloc.construct(this->_begin + copy_from, x);
				//}

				// OLD INSERT: FULL REALLOCATION
				// add capacity + 1 IS IT BAD ???? :((((((
				new_array 	= this->_alloc.allocate(new_capacity + 1);
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
