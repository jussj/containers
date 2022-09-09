/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/09 12:15:22 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <stdexcept>
#include "../inc/stack.hpp"

#ifndef NAMESPACE
# define NAMESPACE std
#endif

template<class Stack>
void	print_stack(Stack& s, std::string name) {
	std::cout	<< "// STACK " << name << " ARRAY:" << std::endl
				<< "   size:       " << s.size() << std::endl;
	std::cout	<< "[ ";
	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << "]" << std::endl << std::endl;
}

int 	main() {
		// CTOR IS WORKING ON ANY UNDERLYING CONTAINER WITH ANY CONTAINER IN INPUT
		// BUILDING STACKS AND SIZE
		// TEST COPY CTOR AND COPY
	{
		NAMESPACE::stack<int, std::deque<int> >			a;          
		NAMESPACE::stack<int, std::vector<int> >			b;
		NAMESPACE::stack<std::string>					d;	// UNDERLYING CONTAINER IS DEQUE IN STD
		
		std::cout << "pushing three elements to stack B..." << std::endl;
		
		b.push(7);
		b.push(-65);
		b.push(34);

		std::cout << "copy ctor stack c(b)..." << std::endl;
		
		NAMESPACE::stack<int, std::vector<int> > 	c(b);

		std::cout << "pushing three elements to stack D..." << std::endl;

		d.push("WORDS");
		d.push("SIX");
		d.push("CONTAINS");
		d.push("STACK");
		d.push("MY");
		d.push("LOOK");

		std::cout << "copy ctor stack e(d)..." << std::endl;
		
		NAMESPACE::stack<std::string>	e(d);
		print_stack(e, "E");
		
		std::cout << "size of stack A: " << a.size() << std::endl;
		if (a.empty())
			std::cout << ">> stack A is empty" << std::endl;
		
		std::cout << "size of stack B: " << b.size() << std::endl;
		if (!b.empty())
			std::cout << ">> stack B is NOT empty" << std::endl;
		print_stack(b, "B");
		std::cout << "size of stack C: " << c.size() << std::endl;
		std::cout << "size of stack D: " << d.size() << std::endl;
		std::cout << "top of stack D is \"" << d.top() << "\"" << std::endl;
		print_stack(d, "D");

		std::cout << "popping three elements out of stack E..." << std::endl;
		e.pop();
		e.pop();
		e.pop();
		std::cout << "size of stack E: " << e.size() << std::endl;
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

		std::cout << "total sum of elements: " << sum << std::endl << std::endl;	
	}
	{
		std::cout << "//// RELATIONAL OPERATORS ////" << std::endl << std::endl;
		
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
		NAMESPACE::stack<int> mystack;

		std::cout << "stack<" << "int" << "> mystack" << std::endl;
		std::cout << std::endl;


		std::cout << "# empty" << std::endl;
		std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
		std::cout << "mystack.size(): " << mystack.size() << std::endl;
		std::cout << "# one element" << std::endl;
		mystack.push(42);
		std::cout << "mystack.push(42)" << std::endl;
		std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
		std::cout << "mystack.size(): " << mystack.size() << std::endl;
		std::cout << "mystack.top(): " << mystack.top() << std::endl;
		std::cout << "# two element" << std::endl;
		mystack.push(2);
		std::cout << "mystack.push(2)" << std::endl;
		std::cout << "mystack.size(): " << mystack.size() << std::endl;
		std::cout << "mystack.top(): " << mystack.top() << std::endl;
		std::cout << "# pop element" << std::endl;
		mystack.pop();
		std::cout << "mystack.pop()" << std::endl;
		std::cout << "mystack.size(): " << mystack.size() << std::endl;
		std::cout << "mystack.top(): " << mystack.top() << std::endl;
		std::cout << std::endl;

		NAMESPACE::stack<int, ft::vector<int> > mystack2;

		std::cout << "stack<" << "int" << ", " << "ft::vector" << "> mystack2" << std::endl;
		std::cout << std::endl;


		std::cout << "# empty" << std::endl;
		std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
		std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
		std::cout << "# one element" << std::endl;
		mystack2.push(42);
		std::cout << "mystack2.push(42)" << std::endl;
		std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
		std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
		std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
		std::cout << "# two element" << std::endl;
		mystack2.push(2);
		std::cout << "mystack2.push(2)" << std::endl;
		std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
		std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
		std::cout << "# pop element" << std::endl;
		mystack2.pop();
		std::cout << "mystack2.pop()" << std::endl;
		std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
		std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
		std::cout << std::endl;

		std::cout << "# test cpy and equality" << std::endl;
		NAMESPACE::stack<int>	cpystack = mystack;
		std::cout << "stack<" << "int" << "> cpystack = mystack" << std::endl;
		std::cout << std::endl;

		std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
		cpystack.push(7);
		std::cout << "cpystack.push(7)" << std::endl;
		std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;

	}
  return 0;
}
