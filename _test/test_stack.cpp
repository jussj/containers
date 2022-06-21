/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/21 14:51:21 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector

#define NAMESPACE std

template<class T, class Cont>
void	printNumbers(NAMESPACE::stack<T, Cont<T> > stack) {

	T	t;

	if (stack.empty())
		return ;

	t = stack.top();
	stack.pop();
	printStack(stack);
	std::cout << t << " ";
	stack.push(t);
}

template<class T, class Cont>
void	printStack(NAMESPACE::stack<T, Cont<T> > stack) {
	std::cout << "[ ";
	printNumbers(stack);
	std::cout << " ]" << std::endl;
}

int 	main() {
		// CTOR IS WORKING ON ANY UNDERLYING CONTAINER WITH ANY CONTAINER IN INPUT
	{	// BUILDING STACKS AND SIZE
		// TEST COPY CTOR AND COPY
		NAMESPACE::stack<int, std::vector<int> >	a;          
		NAMESPACE::stack<int, std::vector<int> >	b;
		NAMESPACE::stack<int, std::vector<int> > 	c;
		NAMESPACE::stack<int> 				d;	// UNDERLYING CONTAINER IS DEQUE
		
	
		b.push(7);
		b.push(-65);
		b.push(34);

		std::cout << "size of stack A: " << a.size() << std::endl;
		if (a.empty())
			std::cout << "stack A is empty (and empty function seems to work...)" << std::endl;
		std::cout << "size of stack B: " << b.size() << std::endl;
		printStack(b);
		std::cout << "size of stack C: " << c.size() << std::endl;
		std::cout << "size of stack D: " << d.size() << std::endl;
	}
	{	// STACK TOP, EMPTY, PUSH
		// EMPTY STACK, HUGE STACK
		NAMESPACE::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) 
			mystack.push(i);

		while (!mystack.empty()) {
		   sum += mystack.top();
		   mystack.pop();
		}

		std::cout << "total: " << sum << '\n';	
	}
  return 0;
}
