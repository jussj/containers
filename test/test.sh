#!/bin/zsh

if [[ $1 == "vector" ]]; then
	echo "LAUNCHING VECTOR TEST"
	echo "compiling std::vector..."
	cd .. && make vector -DNAMESPACE=std
	valgrind ./containers > "test/outfiles/std_vector_outfile.txt"
	echo "compiling ft::vector..."
	make vector -DNAMESPACE=ft
	valgrind ./containers > "test/outfiles/ft_vector_outfile.txt"
	echo "performing diff between two outputs..."
	diff -c "test/outfiles/ft_vector_outfile.txt" "test/outfiles/std_vector_outfile.txt" > test/outfiles/diff_vector.txt
	cat "test/outfiles/std_vector_outfile.txt"
	# print out valgrind result?
else
	echo "I'M A SIMPLE SCRIPT, PLEASE DO:\n"
	echo "./test.sh <name of the container you wanna try out: stack, vector, map WHATEVER>\n"
fi

