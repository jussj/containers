//#include "ContainsAlloc.hpp"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#ifndef STD
 #define NAMESPACE ft
// #include "vector.hpp"
 #include "Vector.hpp"
#else
 #define NAMESPACE std
 #include <vector>
#endif

#ifdef CONTAINS_ALLOC
 #include "ContainsAlloc.hpp"
 #define T ContainsAlloc
 #define VAL1 ContainsAlloc("quarante deux")
 #define VAL2 ContainsAlloc("mille trois cent trente sept")
 #define VAL3 ContainsAlloc("moins un")
#else
	#ifdef STRING
	 #define T std::string
	 #define VAL1 std::string("quarante deux")
	 #define VAL2 std::string("mille trois cent")
	 #define VAL3 std::string("moins un")
	#else
		#ifdef FLOAT
		 #define T float
		 #define VAL1 1983.128f
		 #define VAL2 0.01f
		 #define VAL3 -3.14152589171f
		#else
		 #define T int
		 #define VAL1 42
		 #define VAL2 1337
		 #define VAL3 -1
		#endif
	#endif
#endif

#ifndef N
// #define N 10000		//	NOT 0 OR SEGFAULT
 #define N 100			//	NOT 0 OR SEGFAULT
						//	NOT < 0	OR LONG
#endif

#define FMT1	"===\t"
#define FMT2	"\t===\t"


using namespace NAMESPACE;

::vector<T>		g_v1;
::vector<T>		g_v2;
std::list<T>	g_l1;
std::string		context;

void	rand_push_back(vector<T> & v)
{
	int	n;

	for (int i = 0 ; i < N * 2 ; i++)
	{
		n = rand() % 3;
		if (n == 1)
			v.push_back(VAL1);
		else if (n == 2)
			v.push_back(VAL2);
		else
			v.push_back(VAL3);
	}
}

void	display_capacity(const ::vector<T> & v, std::string context)
{
	std::cout << std::boolalpha;
	std::cout << FMT1 << "display_capacity() :" << std::endl;
	std::cout << FMT1 << "CONTEXT : " << context << std::endl;
	std::cout << FMT2 << "v.empty()\t=\t" << v.empty() << std::endl;
	std::cout << FMT2 << "v.size()\t=\t" << v.size() << std::endl;
	std::cout << FMT2 << "v.capacity()\t=\t" << v.capacity() << std::endl;
	std::cout << FMT2 << "v.max_size()\t=\t" << v.max_size() << std::endl;
	std::cout << std::endl;
}

void	display_content(const ::vector<T> & v, std::string context)
{
	std::cout << FMT1 << "display_content() :" << std::endl;
	std::cout << FMT1 << "CONTEXT : " << context << std::endl;
	::vector<T>::const_iterator	it	=	v.begin();
	::vector<T>::const_iterator	ite	=	v.end();
	size_t						i	=	0;

	if (v.empty() == true)
	{
		std::cout << FMT2 << "NO CONTENT" << std::endl << std::endl;
		return ;
	}
	while (it != ite)
	{
		std::cout << FMT2 << "v[" << std::setw(7) << i 
			<< "]\t=\t" << v[i] << std::endl;
		it++;
		i++;
	}
	std::cout << std::endl;
}

template<class U>
/*
void	display_relationals(const vector<T> & v1,
		const vector<T> & v2,
		std::string context)
*/
void	display_relationals(const U & v1,
		const U & v2,
		std::string context)

{
	std::cout << std::boolalpha;
	std::cout << FMT1 << "display_relationals() :" << std::endl;
	std::cout << FMT1 << "CONTEXT : " << context << std::endl;
	std::cout << FMT2 << "(v1 == v2)\t=\t" << (v1 == v2) << std::endl;
	std::cout << FMT2 << "(v1 != v2)\t=\t" << (v1 != v2) << std::endl;
	std::cout << FMT2 << "(v1 <  v2)\t=\t" << (v1 < v2) << std::endl;
	std::cout << FMT2 << "(v1 <= v2)\t=\t" << (v1 <= v2) << std::endl;
	std::cout << FMT2 << "(v1 >  v2)\t=\t" << (v1 >  v2) << std::endl;
	std::cout << FMT2 << "(v1 >= v2)\t=\t" << (v1 >= v2) << std::endl;
	std::cout << std::endl;
}

void	display_elem_access(const vector<T> & v,
		std::string context)
{
	std::cout << std::boolalpha;
	std::cout << FMT1 << "display_elem_access() :" << std::endl;
	std::cout << FMT1 << "CONTEXT : " << context << std::endl;

	if (v.empty() == true)
	{
		std::cout << FMT2 << "NO CONTENT" << std::endl << std::endl;
		return ;
	}
	std::cout << FMT2 << "v.front()\t=\t" << v.front() << std::endl;
	std::cout << FMT2 << "v.at(0)\t\t=\t" << v.at(0) << std::endl;
	std::cout << FMT2 << "v[0]\t\t=\t" << v[0] << std::endl;
	std::cout << FMT2 << "v.back()\t=\t" << v.back() << std::endl;
	std::cout << FMT2 << "v.at(size()-1)\t=\t" << v.at(v.size() - 1)
		<< std::endl;
	std::cout << FMT2 << "v[v.size()-1]\t=\t" << v[v.size() - 1]
		<< std::endl;
	std::cout << std::endl;
}

/*
void	display_iterator_functions(vector<T> & v,
		std::string context)
{
	//	UNDEFINED IF EMPTY VECTOR
	std::cout << std::boolalpha;
	std::cout << FMT1 << "display_iterator_functions() :" << std::endl;
	std::cout << FMT1 << "CONTEXT : " << context << std::endl;
	std::cout << FMT2 << "*(v.begin())\t=\t" << *(v.begin()) << std::endl;
	std::cout << FMT2 << "*(v.end() - 1)\t=\t" << *(v.end() - 1) << std::endl;
	std::cout << FMT2 << "*(v.rbegin())\t=\t" << *(v.rbegin()) << std::endl;
	std::cout << FMT2 << "*(v.rend() - 1)\t=\t" << *(v.rend() - 1) << std::endl;
	std::cout << std::endl;
}
*/

void	construction(void)
{
	std::cout << "=========================" << std::endl;
	std::cout << "=\tCONSTRUCTION\t=" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;

	//	CONSTRUCTORS
	//	vector(void)	
	::vector<T>	v;
 	context = "default constructed empty vector";
	display_capacity(v, context);
	display_content(v, context);

	//	vector(n, val)
	::vector<T>	v_fill1(10, VAL1);
	context = "fill constructed 10 elems";
	display_capacity(v_fill1, context);
	display_content(v_fill1, context);
	::vector<T>	v_fill2(0, VAL1);
	context = "fill constructed 0 elem";
	display_capacity(v_fill2, context);
	display_content(v_fill2, context);
	//	vector(first, last)
	::vector<T>	v_range1(v_fill1.begin(), v_fill1.end() - 2);
	context = "range constructed from v_fill1 begin/end - 2";
	display_capacity(v_range1, context);
	display_content(v_range1, context);

	::vector<T>	v_range2(v_fill1.begin(), v_fill1.begin());
	context = "range constructed from v_fill1 begin/begin";
	display_capacity(v_range2, context);
	display_content(v_range2, context);

	//	vector(src)
	::vector<T>	v_copy(v_fill1);
	context = "copy constructed from v_fill1";
	display_capacity(v_copy, context);
	display_content(v_copy, context);
	display_relationals(v_fill1, v_copy, context);
}

/*
void	assignation(void)
{
	std::cout << "=========================" << std::endl;
	std::cout << "=\tASSIGNATION\t=" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;
//	ASSIGNATION
	vector<T>	v1(N, VAL3);
	vector<T>	v2;
	vector<T>	v3;

	v2 = v1;
	context = "vector<T> v1(N, VAL3); v2 = v1; with v1 bigger than v2";
	display_capacity(v2, context);
	display_content(v2, context);
	display_relationals(v1, v2, context);
	v2 = v3;
	context = "vector<T> v3; v2 = v3; v2 is empty";
	display_capacity(v2, context);
	display_content(v2, context);
	display_relationals(v1, v2, context);
	rand_push_back(v3);
	context = "rand_push_back(v3);";
	display_capacity(v3, context);
	display_content(v3, context);
	display_relationals(v1, v3, context);
//	v3 = v3;	//	WON'T COMPILE AT SCHOOL
//	context = "v3 = v3; self assignation test";
//	display_capacity(v3, context);
//	display_content(v3, context);
	v3 = v1 = v2;
	context = "v3 = v2 = v1; multiple assignations test";
	display_capacity(v3, context);
	display_content(v3, context);
	display_relationals(v1, v3, context);
	display_relationals(v1, v2, context);
}

void	capacity_changes(void)
{

	std::cout << "=================================" << std::endl;
	std::cout << "=\tCAPACITY CHANGES\t=" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << std::endl;

	vector<T>	v;

	rand_push_back(v);
	std::cout << FMT1 << "vector<T> v; rand_push_back(v);" << std::endl;
	//	resize
	//		if n < size
	v.resize(v.size() / 2);
	context = "v.resize(v.size() / 2); resizing with (n < size)";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	//		if n > size
	v.resize(v.size() * 3, VAL2);
	context = "v.resize(v.size() * 3); resizing with (n > size)";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	//		if n > size && n > capacity
	v.resize(v.capacity() + 3, VAL1);
	context = "v.resize(v.capacity() * 2); resizing with (n > capacity)";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	v.resize(N, VAL1);
	std::cout << FMT1 << "v.resize(N);" << std::endl;

	//	reserve(n)
	//		if n > capacity
	v.reserve(v.capacity() + 1);
	context = "v.reserve(v.capacity() + 1); reserving one more elem";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	//		if n == capacity
	v.reserve(v.capacity());
	context = "v.reserve(v.capacity()); reserving same capacity";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	//		if n < capacity
	v.reserve(v.capacity());
	context = "v.reserve(v.capacity() - 1); reserving lesser capacity";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	//		if n > max_size()
	try {
		v.reserve(v.capacity());
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	context = "v.reserve(v.max_size() + 1); exception thrown";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	
}

void	element_access(void)
{
	std::cout << "=========================" << std::endl;
	std::cout << "=\tELEMENT ACCESS\t=" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;

	vector<T>		v(N, VAL3);
	vector<T>		bckp(v);
	size_t			size;
	T				copy;

	copy = VAL2;
	rand_push_back(v);
	const vector<T>	const_v(v);
	size = v.size();

	//	operator[]
	std::cout << FMT1 << "operator[] access / assignation" << std::endl;
	for (size_t i = 0 ; i < size ; i++)
	{
		std::cout << FMT2 << v[i] << std::endl;
		v[i] = copy;
	}
	std::cout << std::endl;

	context = "v[i++] = copy; each member assigned";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	for (size_t i = 0 ; i < size ; i++)
	{
		copy = const_v[i];
//		const_v[i] = copy;	// 	WON'T COMPILE - const_reference
	}

	//	non-const access
	copy = v.front();
	v.front() = copy;
	copy = v.back();
	v.front() = copy;

	//	const access
	copy = const_v.front();
//	const_v.front() = copy;	// 	WON'T COMPILE - const_reference
	copy = const_v.back();
//	const_v.front() = copy;	// 	WON'T COMPILE - const_reference

	//	at() over-bounds exception test
	try {
		v.at(v.size());
	}
	catch (std::exception & e) {
		std::cerr << e.what();
	}

	copy = VAL3;
	v = const_v;
	//	at() retrieval and assignation
	std::cout << FMT1 << "at() access / assignation" << std::endl;
	for (size_t i = 0 ; i < size ; i++)
	{
		copy = v.at(i);
		v.at(i) = copy;
		copy = const_v.at(i);
		std::cout << FMT2 << copy << std::endl;
//		const_v.at(i) = copy;	// 	WON'T COMPILE - const_reference
	}
	context = "after at() retrieval and assignation test";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	context = "after at() retrieval and assignation test - const version";
	display_capacity(const_v, context);
	display_content(const_v, context);
	display_elem_access(const_v, context);
}

void	modifiers(void)
{
	std::cout << "=========================" << std::endl;
	std::cout << "=\tMODIFIERS\t=" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;

	vector<T>					v;
	vector<T>::iterator			it;
	vector<T>::const_iterator	cit;
	std::list<T>				l;

	//	push_back(val);
	for (int i = 0 ; i < N * 2 ; i++)
		v.push_back(VAL2);
	context = "pushed back N * 2 elements";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	pop_back();	// undef behavior if v empty
	for (int i = 0 ; i < N ; i++)
		v.pop_back();
	context = "pop_back()ed N last elements";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	insert(it pos, val);
	int							i;
	i = 0;
	for (it = v.begin() ; it != v.end() ; it += 1, i++)
		if (i % 2 == 0)
			it = v.insert(it, VAL3); 
	context = "inserted VAL3 between each element";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	size_t						cpct;
	cpct = v.capacity();
	while (v.size() < cpct + N)
		v.insert(v.begin(), VAL2);
	context = "inserted VAL3 until reallocation => while (v.size() < cpct + N)";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	insert(it pos, n, val);
	v.insert(v.end(), N, VAL1);
	v.insert(v.end(), N, VAL2);
	v.insert(v.end(), N, VAL3);
	context = "inserted N*VAL1, N*VAL2, N*VAL3 at v.end()";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

//	//	insert(it pos, first, last);
//	vector<T>		v2(v);
//	v.insert(v.end() - v.size() / 2, v.begin(), v.end());
//	context = "inserted v in the middle of itself";
//	display_capacity(v, context);
//	display_content(v, context);
//	display_elem_access(v, context);

	for (int i = 1 ; i < N ; i++)
		l.push_back(VAL1);
	v.insert(v.end(), l.begin(), l.end());
	context = "inserted a list l at the end of v";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	erase(it pos);
	v.erase(v.begin());
	context = "erased v.begin()";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	it = v.begin();
	i = 0;
	while (it != v.end())
	{
		if (i % 2 == 0)
			v.erase(it);
		i++;
		it++;
	}
	context = "erased all pair indexes";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	
	//	erase(first, last);
	v.erase(v.begin(), v.begin() + v.size() / 2);
	context = "erased first half of vector";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	vector<T>	copy(v);
	
	v.erase(v.begin(), v.end());
	context = "erased all elements";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	assign(first, last);
	v.assign(copy.begin(), copy.end());
	context = "assigned copy to v";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	display_relationals(v, copy, context);

	//	assign(n, val);
	v.assign(N * 5, VAL1);
	context = "assigned (N * 5) VAL1";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);

	//	swap(vector x);
	v.swap(copy);
	context = "swapped v and copy";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	display_relationals(v, copy, context);
	
	v.swap(v);
	context = "v self swap";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	
	v.swap(copy);
	copy.clear();
	v.swap(copy);
	context = "swapped v with cleared copy";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
}

void	iterator_functions(void)
{
	std::cout << "=========================" << std::endl;
	std::cout << "=\tITERATORS\t=" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;

	vector<T>								v;
	//	CONSTRUCTION
	vector<T>::iterator						it;
	vector<T>::iterator						ite(it);
	vector<T>::const_iterator				cit;
	vector<T>::const_iterator				cite(cit);
	vector<T>::reverse_iterator				rit;
	vector<T>::reverse_iterator				rite(rit);
	vector<T>::const_reverse_iterator		crit;
	vector<T>::const_reverse_iterator		crite(crit);

	rand_push_back(v);
	v.insert(v.end(), N, VAL1);
	v.insert(v.end() - v.size() / 2, N, VAL2);
	context = "created new vector";
	display_capacity(v, context);
	display_content(v, context);
	display_elem_access(v, context);
	display_iterator_functions(v, context);

	//	ITERATION / DEREFERENCING
	std::cout << FMT1 << "iterator iteration" << std::endl;
	it = v.begin();
	cite = v.end();
	while (it != cite)
	{
		std::cout << FMT2 << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	std::cout << FMT1 << "reverse_iterator iteration" << std::endl;
	rit = v.rbegin();
	crite = v.rend();
	while (rit != crite)
	{
		std::cout << FMT2 << *rit << std::endl;
		rit++;
	}
	std::cout << std::endl;
	std::cout << FMT1 << "const_iterator iteration" << std::endl;
	cit = v.begin();
	cite = v.end();
	while (cit != cite)
	{
		std::cout << FMT2 << *cit << std::endl;
		cit++;
	}
	std::cout << std::endl;
	std::cout << FMT1 << "const_reverse_iterator iteration" << std::endl;
	crit = v.rbegin();
	crite = v.rend();
	while (crit != crite)
	{
		std::cout << FMT2 << *crit << std::endl;
		crit++;
	}
	std::cout << std::endl;

	//	RELATIONALS
	ite = it;
	context = "ite = it; it and ite relationals";
	display_relationals(it, ite, context);
	it--;
	context = "it--; it and ite relationals";
	display_relationals(it, ite, context);
	cite = cit;
	context = "cite = cit; cit and cite relationals";
	display_relationals(cit, cite, context);
	cit--;
	context = "cit--; cit and cite relationals";
	display_relationals(cit, cite, context);

	rite = rit;
	context = "rite = rit; rit and rite relationals";
	display_relationals(rit, rite, context);
	rit--;
	context = "rit--; rit and rite relationals";
	display_relationals(rit, rite, context);
	crite = crit;
	context = "crite = crit; crit and crite relationals";
	display_relationals(crit, crite, context);
	crit--;
	context = "crit--; crit and crite relationals";
	display_relationals(crit, crite, context);

	//	ASSIGNATION
	it = v.begin();
	cit = v.begin();
	rit = v.rbegin();
	crit = v.rbegin();

	ite = it;
	*it = VAL3;
	std::cout << FMT1 << "ite = it; *it = VAL3;" << std::endl;
	std::cout << FMT1 << "(*ite == VAL3)\t=\t" << (*ite == VAL3) << std::endl;
	std::cout << FMT1 << "(ite == it)\t=\t" << (ite == it) << std::endl;
	std::cout << std::endl;
	rite = rit;
	*rit = VAL1;
	std::cout << FMT1 << "rite = rit; *rit = VAL1;" << std::endl;
	std::cout << FMT1 << "(*rite == VAL1)\t=\t" << (*rite == VAL1) << std::endl;
	std::cout << FMT1 << "(rite == rit)\t=\t" << (rite == rit) << std::endl;
	std::cout << std::endl;
	cite = cit;
	// *cit = VAL3;	// WON'T COMPILE
	std::cout << FMT1 << "cite = cit;" << std::endl;
	std::cout << FMT1 << "(cite == cit)\t=\t" << (cite == cit) << std::endl;
	std::cout << std::endl;
	crite = crit;
	// *crit = VAL1;	// WON'T COMPILE
	std::cout << FMT1 << "crite = crit;" << std::endl;
	std::cout << FMT1 << "(cite == crit)\t=\t" << (crite == crit) << std::endl;
	std::cout << std::endl;
	
	//	PRE/POST WEIRD ITERATION
	std::cout << FMT1 << "weird iteration" << std::endl;
	it = v.begin();
	ite = v.end();
	std::cout << FMT2 << "*(it++)\t=\t" << *(it++) << std::endl;
	std::cout << FMT2 << "*(--it)\t=\t" << *(--it) << std::endl;
	std::cout << FMT2 << "*(++it)\t=\t" << *(++it) << std::endl;
	std::cout << FMT2 << "*(it--)\t=\t" << *(it--) << std::endl;
	it++;
	std::cout << std::endl;

	std::cout << FMT1 << "reverse weird iteration" << std::endl;
	rit = v.rbegin();
	rite = v.rend();
	std::cout << FMT2 << "*(rit++)\t=\t" << *(rit++) << std::endl;
	std::cout << FMT2 << "*(--rit)\t=\t" << *(--rit) << std::endl;
	std::cout << FMT2 << "*(++rit)\t=\t" << *(++rit) << std::endl;
	std::cout << FMT2 << "*(rit--)\t=\t" << *(rit--) << std::endl;
	rit++;
	std::cout << std::endl;

	//	it + n
	it = v.begin();
	std::cout << FMT1 << "it = v.begin();" << std::endl;
	std::cout << FMT2 << "*(it + size() / 2)\t=\t" << *(it + v.size() / 2) << std::endl;
	//	it += n
	it += v.size() / 2;
	std::cout << FMT1 << "*it += size() / 2;" << std::endl;
	std::cout << FMT2 << "*it\t\t\t=\t" << *it <<  std::endl;
	//	it - n
	std::cout << FMT2 << "*(it - size() / 2)\t=\t" << *(it - v.size() / 2) << std::endl;
	//	it-= n
	std::cout << FMT1 << "*it -= size() / 2;" << std::endl;
	std::cout << FMT2 << "*it\t\t\t=\t" << *it << std::endl;
	std::cout << std::endl;
	//	it[]
	it = v.begin();
	size_t	i	= 0;
	while (i < v.size())
	{
		if (i % 3 == 0)
			it[i] = VAL1;
		else if (i % 3 == 1)
			it[i] = VAL2;
		else
			it[i] = VAL3;
		std::cout << FMT1 << "it[" << std::setw(8) << i << "]\t=\t" << it[i] << std::endl;
		i++;
	}
}
*/

int		main(void)
{
	srand(N);
	construction();
	/*
	assignation();
	capacity_changes();
	element_access();
	modifiers();
	iterator_functions();
	*/
	return (0);
}
