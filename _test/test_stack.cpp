/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/24 16:22:59 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <stdexcept>
#include "../inc/stack.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<class T>
void	printStack(NAMESPACE::stack<T> & s) {
	std::cout << "[ ";
	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << "]" << std::endl;
}

int 	main() {
		// CTOR IS WORKING ON ANY UNDERLYING CONTAINER WITH ANY CONTAINER IN INPUT
	{	// BUILDING STACKS AND SIZE
		// TEST COPY CTOR AND COPY
		NAMESPACE::stack<int, std::deque<int> >			a;          
		NAMESPACE::stack<int, std::vector<int> >		b;
		NAMESPACE::stack<std::string> 				d;	// UNDERLYING CONTAINER IS DEQUE IN STD
		
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
		
		std::cout << "size of stack A: " << a.size() << std::endl;
		if (a.empty())
			std::cout << ">> stack A is empty" << std::endl;
		
		std::cout << "size of stack B: " << b.size() << std::endl;
		if (!b.empty())
			std::cout << ">> stack B is NOT empty" << std::endl;
		printStack(b);
		std::cout << "size of stack C: " << c.size() << std::endl;
		std::cout << "size of stack D: " << d.size() << std::endl;
		std::cout << "top of stack D is \"" << d.top() << "\"" << std::endl;
		printStack(d);

		std::cout << "popping three elements out of stack E..." << std::endl;
		e.pop();
		e.pop();
		e.pop();
		std::cout << "size of stack E: " << e.size() << std::endl;
		printStack(e);
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

		std::cout << "total sum of elements: " << sum << '\n';	
	}
  return 0;
}
