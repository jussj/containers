#include <ctime>
#include <iostream>

void
elapsed_time(void (*test)(void), std::string name) {
	time_t	start;
	clock_t	start_ms;
	time_t	end;
	clock_t	end_ms;
	double	res;

    time(&start);
    start_ms = clock();

    test();
    
	time(&end);
    end_ms = clock();
    
	res = difftime(end, start);
    
	std::cout	<< std::endl
				<< "---ELAPSED TIME " << name << ": "
				<< res << " s ("
				<< static_cast<float>(end_ms - start_ms) 
					/ CLOCKS_PER_SEC 
				<< " s)"<< std::endl;
}

void
measure_performance(void (*test)(void), std::string name) {
	elapsed_time(test, name);
}
