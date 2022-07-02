/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:01:37 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/02 18:11:56 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

template<class T>
class	IncrediblyComplex {
	public:
		IncrediblyComplex() : nb(42), ptr(new T) {}
		IncrediblyComplex(int n, T type) : nb(n), ptr(new T) {
			*ptr = type;
		}
		IncrediblyComplex(IncrediblyComplex const &src)
			: nb(src.nb), ptr(new T) {
			*ptr 	= *src.ptr;
		}
		~IncrediblyComplex() {
			delete ptr;
		}
	private:
		int	nb;
		T	*ptr;

// overload << for accessing values
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

template<class T, class Vec>
void	test_vector(Vec v, std::string name, T value) {
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
	std::cout	<< "      reached size"		<< std::endl;
	for (size_t s = 0; s < v.capacity(); s++)
		v.pop_back();
	std::cout	<< "      reached capacity"	<< std::endl;
	v.pop_back();

	print_vector(v);

	std::cout	<< std::endl
			<< "   >> PUSH_BACK(VALUE)"	<< std::endl;
	for (size_t s = 0; s < 10; s++)	
		v.push_back(value);
	
	print_vector(v);

	std::cout	<< std::endl
			<< "   >> AT()"			<< std::endl
			<< "      in range " 
			<< "...at(0): " << v.at(0) << " ...at(size-1): " << v.at(v.size() - 1)
			<< "      out of range ...at(size): ";
			try {
				std::cout << at(v.size());
			}
			catch (std::exception& e) {
				std::cerr << "      ERROR THROWN: " << e.what() << std::endl;
			}
	
	std::cout	<< std::endl
			<< "   >> RESIZE()"	<< std::endl;
}


#endif 	/* TEST_HPP */
