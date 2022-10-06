#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <stdexcept>
#include "../inc/stack.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<class Stack>
void	print_stack(Stack s, std::string name) {
	std::cout	<< std::endl
				<< "// STACK " << name << " ARRAY:" << std::endl
				<< "   size: " << s.size() << std::endl
				<< "   top:	\"" << s.top() << "\"" << std::endl;
	std::cout	<< "   [ ";
	if (s.empty())
		std::cout << "EMPTY STACK ";
	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << "]" << std::endl;
}

int 	main_stack() {
		// CTOR IS WORKING ON ANY UNDERLYING CONTAINER WITH ANY CONTAINER IN INPUT
		// BUILDING STACKS AND SIZE
		// TEST COPY CTOR AND COPY
	{
		NAMESPACE::stack<int, std::deque<int> > const	a;          
		NAMESPACE::stack<int, ft::vector<int> >			b;
		NAMESPACE::stack<std::string>					d;	// UNDERLYING CONTAINER IS DEQUE IN STD
	
		std::cout	<< "///////////////" << std::endl
					<< "//// STACK ////" << std::endl
					<< "///////////////" << std::endl;

		std::cout	<< "creating three stacks..." << std::endl
					<< "stack<" << "int" << ", std::deque>" << "a" << std::endl
					<< "stack<" << "int" << ", ft::vector>" << "b" << std::endl
					<< "stack<" << "std::string" << ">" << "d" << std::endl
					<< std::endl;

		std::cout << "pushing three elements to stack B..." << std::endl;
		
		b.push(7);
		b.push(-65);
		b.push(34);
		print_stack(b, "B");
		
		std::cout	<< std::endl
					<< "copy ctor stack c(b)..." << std::endl;
		
		NAMESPACE::stack<int, ft::vector<int> > 	c(b);

		std::cout	<< std::endl
					<< "pushing three elements to stack D..." << std::endl;

		d.push("WORDS");
		d.push("SIX");
		d.push("CONTAINS");
		d.push("STACK");
		d.push("MY");
		d.push("LOOK");

		std::cout << "copy ctor stack e(d)..." << std::endl;
		
		NAMESPACE::stack<std::string>	e(d);
		print_stack(e, "E");
	
		std::cout	<< std::endl;

		if (a.empty())
			std::cout << ">> stack A is empty" << std::endl;
		
		if (!b.empty())
			std::cout << ">> stack B is NOT empty" << std::endl;
		print_stack(b, "B");
		print_stack(d, "D");

		std::cout	<< std::endl
					<< "popping three elements out of stack E..." << std::endl;
		e.pop();
		e.pop();
		e.pop();
		print_stack(e, "E");
	}
	{	// STACK TOP, EMPTY, PUSH
		// EMPTY STACK, HUGE STACK
		NAMESPACE::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=100;i++) 
			mystack.push(i);

		while (!mystack.empty()) {
		   sum += mystack.top();
		   mystack.pop();
		}

		std::cout	<< std::endl
					<< "total sum of elements: " << sum << std::endl << std::endl;	
	}
	{
		std::cout	<< "//// RELATIONAL OPERATORS ////" << std::endl << std::endl;
		
		NAMESPACE::stack<int> a, b, c;
		
		a.push(10);
		a.push(20);
		a.push(30);

		b.push(10);
		b.push(20);
		b.push(30);

		c.push(30);
		c.push(20);
		c.push(10);

		if (a == b)
			std::cout << "a and b are equal\n";
		if (b != c) 
			std::cout << "b and c are not equal\n";
		if (b < c)
			std::cout << "b is less than c\n";
		if (c > b)
			std::cout << "c is greater than b\n";
		if (a <= b)
			std::cout << "a is less than or equal to b\n";
		if (a >= b)
			std::cout << "a is greater than or equal to b\n";
	}
	{
		NAMESPACE::stack<int> f;

		std::cout	<< "stack<" << "int" << "> f" << std::endl;

		std::cout	<< std::endl
					<< "//// EMPTY ////" << std::endl << std::endl;
		std::cout	<< "f.empty(): " <<  f.empty() << std::endl;
		std::cout	<< "f.size(): " << f.size() << std::endl;
		std::cout	<< std::endl
					<< "//// PUSH ////" << std::endl;
		f.push(42);
		print_stack(f, "F");
		std::cout	<< std::endl
					<< "f.push(42)" << std::endl;
		f.push(2);
		print_stack(f, "F");
		std::cout	<< std::endl
					<< "f.push(2)" << std::endl;
		std::cout	<< std::endl
					<< "//// POP ////" << std::endl << std::endl;
		f.pop();
		std::cout	<< "f.pop()" << std::endl;
		print_stack(f, "F");
		std::cout	<< std::endl;

		NAMESPACE::stack<int, ft::vector<int> > g;

		std::cout	<< "stack<" << "int" << ", " << "ft::vector" << "> g" << std::endl;

		std::cout	<< std::endl
					<< "//// EMPTY ////" << std::endl << std::endl;
		std::cout	<< "g.empty(): " <<  g.empty() << std::endl;
		std::cout	<< "g.size(): " << g.size() << std::endl;
		std::cout	<< std::endl
					<< "//// PUSH ////" << std::endl << std::endl;
		g.push(42);
		std::cout	<< "g.push(42)" << std::endl;
		print_stack(g, "G");
		g.push(2);
		std::cout	<< std::endl
					<< "g.push(2)" << std::endl;
		print_stack(g, "G");
		std::cout	<< std::endl
					<< "//// POP ////" << std::endl << std::endl;
		g.pop();
		std::cout	<< "g.pop()" << std::endl;
		print_stack(g, "G");

		std::cout	<< std::endl
					<< "//// COPY AND OPERATOR== ////" << std::endl << std::endl;
		
		NAMESPACE::stack<int>	h = f;
		std::cout	<< "stack<" << "int" << "> h = f" << std::endl;
		print_stack(h, "H");

		std::cout	<< std::endl
					<< "h == f:" << (h == f) << std::endl;
		h.push(7);
		std::cout	<< "h.push(7)" << std::endl;
		std::cout	<< "h == f:" << (h == f) << std::endl;

	}
  return 0;
}
