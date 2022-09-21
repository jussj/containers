#ifndef TESTVECTOR_HPP
# define TESTVECTOR_HPP

// PRINTING VECTOR

template<class Vec>
void	print_info(const Vec& v, std::string name) {
	std::cout	<< "// VECTOR " << name << " INFO" << std::endl
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
void	print_content(const Vec& v, std::string name) {
	std::cout	<< "// VECTOR " << name << " ARRAY" << std::endl;
	if (v.empty()) {
		std::cout << "   [ IS EMPTY ]" << std::endl;
		return ;
	}
	std::cout << "   [ ";
	for (size_t s = 0; s < v.size(); s++) {
		std::cout << v[s] << " ";
	}
	std::cout << "]" << std::endl << std::endl;
}


// how to randomize values for each type??

// TESTING VECTOR FEATURES

template<class Vec>
void	test_capacity(Vec& v, std::string name) {
	std::cout 	<< "// VECTOR " << name << std::endl;	
	std::cout 	<< "   >> EMPTY()" 	<< std::endl;
	if (v.empty())
		std::cout << "\tyes" << std::endl;
	else
		std::cout << "\tno" << std::endl;
	
	std::cout	<< std::endl
			<< "   >> RESERVE()"			<< std::endl;

	std::cout 	<< "\treserve(0)" 			<< std::endl;
	v.reserve(0);
	std::cout 	<< "\treserve(max_size+1)" 		<< std::endl;
	try {
		v.reserve(v.max_size() + 1);
	}
	catch (std::length_error& le) {
		std::cerr << "\t\tERROR THROWN: " << le.what() << std::endl;
	}
	std::cout 	<< "\treserve(size+10)" 		 << std::endl;
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
		std::cerr << "\t\tERROR THROWN: " << le.what() << std::endl;
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

//template<class Vec, class T>
//void	test_manipulate(Vec& v, std::string name) {
	//std::cout 	<< "// VECTOR " << name << std::endl;	
	//std::cout 	<< "   >> ASSIGN(NB, T)" 	<< std::endl;
	//std::cout 	<< "   >> ASSIGN(IT, IT)" 	<< std::endl;
	//std::cout 	<< "   >> PUSH()" 	<< std::endl;
	//std::cout 	<< "   >> POP()" 	<< std::endl;


#endif 	/* TESTVECTOR_HPP */
