/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:01:37 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/04 17:24:52 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

template<class T>
class	IncrediblyComplex {
	public:
		IncrediblyComplex() : _nb(42), _ptr(new T) {}
		IncrediblyComplex(int n, T type) : _nb(n), _ptr(new T) {
			*_ptr = type;
		}
		IncrediblyComplex(IncrediblyComplex const &src)
			: _nb(src._nb), _ptr(new T) {
			*_ptr 	= *src._ptr;
		}
		~IncrediblyComplex() {
			delete _ptr;
		}
	private:
		int	_nb;
		T	*_ptr;

	std::ostream &	operator<<(std::ostream & o) {
		o << "(" << this->_nb << "; " << this->_ptr << ")"; 
		return	o;
	}
};

// TESTING UTILS

template<class Vec>
void	print_info(const Vec& v, std::string name) {
	std::cout	<< std::endl
			<< "// VECTOR " << name << " INFO" << std::endl
			<< "   size:       " << v.size() << std::endl
			<< "   capacity:   " << v.capacity() << std::endl
			<< "   max_size:   " << v.max_size() << std::endl;
			if (!v.empty()) {
				std::cout	<< "   front/back: [ " << v.front()
						<< " ... " << v.back() << " ]" << std::endl;
			}
	std::cout	<< std::endl;
}

template<class Vec>
void	print_vector(const Vec& v, std::string name) {
	std::cout	<< std::endl
			<< "// VECTOR " << name << " ARRAY" << std::endl;
	std::cout << "   [ ";
	for (size_t s = 0; s < v.size(); s++) {
		std::cout << v[s] << " ";
	}
	std::cout << "]" << std::endl << std::endl;
}

// how to randomize values for each type??

template<class Vec>
void	test_capacity(Vec& v, std::string name) {
	std::cout 	<< "// VECTOR " << name << std::endl;	
	std::cout 	<< "   >> IS EMPTY" 	<< std::endl;
	if (v.empty())
		std::cout << "     yes" << std::endl;
	else
		std::cout << "     no" << std::endl;
	
	std::cout	<< std::endl
			<< "   >> RESERVE"			<< std::endl;

	std::cout 	<< "	  reserve(0)" 			<< std::endl;
	v.reserve(0);
	std::cout 	<< "      reserve(max_size+1)" 		<< std::endl;
	try {
		v.reserve(v.max_size() + 1);
	}
	catch (std::length_error& le) {
		std::cerr << "      ERROR THROWN: " << le.what() << std::endl;
	}
	std::cout 	<< "	  reserve(size+10)" 		 << std::endl;
	v.reserve(v.size() + 10);
	
	std::cout	<< std::endl
			<< "   >> POP_BACK()"		<< std::endl;
	for (size_t s = 0; s < v.size(); s++)
		v.pop_back();
	//std::cout	<< "      reached size"		<< std::endl;
	//for (size_t s = 0; s < v.capacity(); s++)
		//v.pop_back();
	//std::cout	<< "      reached capacity"	<< std::endl;
	//v.pop_back();

	//print_vector(v);

	//std::cout	<< std::endl
			//<< "   >> PUSH_BACK(VALUE)"	<< std::endl;
	//for (size_t s = 0; s < 10; s++)	
		//v.push_back(value);
	
	//print_vector(v);

	//std::cout	<< std::endl
			//<< "   >> AT()"			<< std::endl
			//<< "      in range " 
			//<< "...at(0): " << v.at(0) << " ...at(size-1): " << v.at(v.size() - 1)
			//<< "      out of range ...at(size): ";
			//try {
				//std::cout << at(v.size());
			//}
			//catch (std::exception& e) {
				//std::cerr << "      ERROR THROWN: " << e.what() << std::endl;
			//}
	
	std::cout	<< std::endl
			<< "   >> RESIZE()"	<< std::endl;

	v.resize(0);
	try {
		v.resize(v.max_size() + 1);
	}
	catch (std::length_error& le) {
		std::cerr << "      ERROR THROWN: " << le.what() << std::endl;
	}
	v.resize(10);
	v.resize(v.size() + 10);
	v.resize(v.capacity() * 2);
	v.resize(v.size() / 2);
	
	//std::cout	<< std::endl
			//<< "   >> ASSIGN(N, VALUE)"	<< std::endl;

	//v.assign(v.size());
	//v.assign(v.size() * 2);
	//v.assign(v.capacity() * 4);
	//v.assign(v.capacity() * 2);
	//v.assign(v.size() / 2);
	//v.assign(0);
	
	std::cout 	<< std::endl;
}


#endif 	/* TEST_HPP */
