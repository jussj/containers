/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/20 18:22:25 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector

#define NAMESPACE std

void	printStack(NAMESPACE::stack<int>)

int 	main() {
		// CTOR IS WORKING ON ANY UNDERLYING CONTAINER WITH ANY CONTAINER IN INPUT
	{	// BUILDING STACKS AND SIZE
		std::stack<int> 			myvector (3,100);          
		std::stack<int> 			first;				
		std::stack<int,std::vector<int> >	second;
		std::stack<int,std::vector<int> > 	third (myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
	}
	{	// STACK TOP, EMPTY, PUSH
		// EMPTY STACK, HUGE STACK
		std::stack<int> mystack;
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
