#! /bin/zsh

RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[34m'
ENDCOLOR='\033[0m'

echo "\n//// WELCOME TO CONTAINERS ////"

echo "\nthis script will test each containers:\n"
echo "   .differences of output with the STL over some tests"
echo "   .leaks and errors with our valgrind friend"
echo "   .performances with time"

rm test/outfiles/*.txt

echo "\nhave fun lol\n"

echo "// TESTING STACK //\n"

echo "compiling std::stack..."
c++ -Wall -Wextra -Werror -std=c++98 -DSTD test/main_stack.cpp -o std_stack > /dev/null
./std_stack > test/outfiles/std_stack_outfile.txt

echo "compiling ft::stack...\n"
make stack > /dev/null
./ft_stack > test/outfiles/ft_stack_outfile.txt

diff test/outfiles/ft_stack_outfile.txt test/outfiles/std_stack_outfile.txt > test/outfiles/stack_diff.txt
if [ $? -eq 0 ]; then
	echo "// DIFF:   ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/stack_diff.txt
else
	echo "// DIFF:   ${RED}not ok${ENDCOLOR}"
	echo "   now look what failed you:"
	echo "   logs are situated in \"test/outfiles\"\n"
	#cat test/outfiles/stack_diff.txt
fi

valgrind --log-file="test/outfiles/stack_leaks.txt" ./ft_stack > /dev/null

grep "total heap usage" test/outfiles/stack_leaks.txt > stack_time.txt

grep "ERROR SUMMARY: 0" test/outfiles/stack_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// ERRORS: ${GREEN}ok${ENDCOLOR}"
else
	echo "// ERRORS: ${RED}not ok${ENDCOLOR}"
fi

grep "All heap blocks were freed" test/outfiles/stack_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// LEAKS:  ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/stack_leaks.txt
else
	echo "// LEAKS:  ${RED}not ok${ENDCOLOR}"
	echo "   logs are situated in \"test/outfiles\"\n"
fi

{ time ./ft_stack > /dev/null; } 2>>stack_time.txt
{ time ./std_stack > /dev/null; } 2>>stack_time.txt

echo "// PERFORMANCES:"
echo "   ${BLUE}FT_STACK:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './ft_stack > /dev/null  \K.+' stack_time.txt
echo -n "   heap use.."
grep 'total heap usage' stack_time.txt | cut -c 31-
echo "   ${BLUE}STD_STACK:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './std_stack > /dev/null  \K.+' stack_time.txt
echo -n "   heap use.."
valgrind --log-file="grind.txt" ./std_stack > /dev/null
grep 'total heap usage' grind.txt | cut -c 31-
rm stack_time.txt
rm grind.txt

rm std_stack

echo "\n// TESTING VECTOR //\n"

echo "compiling std::vector..."
c++ -Wall -Wextra -Werror -std=c++98 -DSTD test/main_vector.cpp -o std_vector > /dev/null
./std_vector &> test/outfiles/std_vector_outfile.txt

echo "compiling ft::vector...\n"
make vector > /dev/null
./ft_vector &> test/outfiles/ft_vector_outfile.txt

diff test/outfiles/ft_vector_outfile.txt test/outfiles/std_vector_outfile.txt > test/outfiles/vector_diff.txt
if [ $? -eq 0 ]; then
	echo "// DIFF:   ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/vector_diff.txt
else
	echo "// DIFF:   ${RED}not ok${ENDCOLOR}"
	echo "   now look what failed you:"
	echo "   logs are situated in \"test/outfiles\"\n"
	#cat test/outfiles/vector_diff.txt
fi

valgrind --log-file="test/outfiles/vector_leaks.txt" ./ft_vector &> /dev/null

grep "total heap usage" test/outfiles/vector_leaks.txt > vector_time.txt

grep "ERROR SUMMARY: 0" test/outfiles/vector_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// ERRORS: ${GREEN}ok${ENDCOLOR}"
else
	echo "// ERRORS: ${RED}not ok${ENDCOLOR}"
fi

grep "All heap blocks were freed" test/outfiles/vector_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// LEAKS:  ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/vector_leaks.txt
else
	echo "// LEAKS:  ${RED}not ok${ENDCOLOR}"
	echo "   logs are situated in \"test/outfiles\"\n"
fi

{ time ./ft_vector > /dev/null; } 2>>vector_time.txt
{ time ./std_vector > /dev/null; } 2>>vector_time.txt

echo "// PERFORMANCES:"
echo "   ${BLUE}FT_VECTOR:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './ft_vector > /dev/null  \K.+' vector_time.txt
echo -n "   heap use.."
grep 'total heap usage' vector_time.txt | cut -c 31-
echo "   ${BLUE}STD_VECTOR:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './std_vector > /dev/null  \K.+' vector_time.txt
echo -n "   heap use.."
valgrind --log-file="grind.txt" ./std_vector > /dev/null
grep 'total heap usage' grind.txt | cut -c 31-
rm vector_time.txt
rm grind.txt

rm std_vector

echo "\n// TESTING MAP //\n"

echo "compiling std::map..."
c++ -Wall -Wextra -Werror -std=c++98 -DSTD test/main_map.cpp -o std_map
./std_map > test/outfiles/std_map_outfile.txt

echo "compiling ft::map...\n"
make map > /dev/null
./ft_map > test/outfiles/ft_map_outfile.txt

diff test/outfiles/ft_map_outfile.txt test/outfiles/std_map_outfile.txt > test/outfiles/map_diff.txt
if [ $? -eq 0 ]; then
	echo "// DIFF:   ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/map_diff.txt
else
	echo "// DIFF:   ${RED}not ok${ENDCOLOR}"
	echo "   now look what failed you:"
	echo "   logs are situated in \"test/outfiles\"\n"
	#cat test/outfiles/map_diff.txt
fi

valgrind --log-file="test/outfiles/map_leaks.txt" ./ft_map > /dev/null

grep "total heap usage" test/outfiles/map_leaks.txt > map_time.txt

grep "ERROR SUMMARY: 0" test/outfiles/map_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// ERRORS: ${GREEN}ok${ENDCOLOR}"
else
	echo "// ERRORS: ${RED}not ok${ENDCOLOR}"
fi

grep "All heap blocks were freed" test/outfiles/map_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// LEAKS:  ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/map_leaks.txt
else
	echo "// LEAKS:  ${RED}not ok${ENDCOLOR}"
	echo "   logs are situated in \"test/outfiles\"\n"
fi

{ time ./ft_map > /dev/null; } 2>>map_time.txt
{ time ./std_map > /dev/null; } 2>>map_time.txt

echo "// PERFORMANCES:"
echo "   ${BLUE}FT_MAP:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './ft_map > /dev/null  \K.+' map_time.txt
echo -n "   heap use.."
grep 'total heap usage' map_time.txt | cut -c 31-
echo "   ${BLUE}STD_MAP:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './std_map > /dev/null  \K.+' map_time.txt
echo -n "   heap use.."
valgrind --log-file="grind.txt" ./std_map > /dev/null
grep 'total heap usage' grind.txt | cut -c 31-
rm map_time.txt
rm grind.txt

rm std_map

echo "\n// TESTING SET //\n"

echo "compiling std::set..."
c++ -Wall -Wextra -Werror -std=c++98 -DSTD test/main_set.cpp -o std_set
./std_set > test/outfiles/std_set_outfile.txt

echo "compiling ft::set...\n"
make set > /dev/null
./ft_set > test/outfiles/ft_set_outfile.txt

diff test/outfiles/ft_set_outfile.txt test/outfiles/std_set_outfile.txt > test/outfiles/set_diff.txt
if [ $? -eq 0 ]; then
	echo "// DIFF:   ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/set_diff.txt
else
	echo "// DIFF:   ${RED}not ok${ENDCOLOR}"
	echo "   now look what failed you:"
	echo "   logs are situated in \"test/outfiles\"\n"
	#cat test/outfiles/set_diff.txt
fi

valgrind --log-file="test/outfiles/set_leaks.txt" ./ft_set > /dev/null

grep "total heap usage" test/outfiles/set_leaks.txt > set_time.txt

grep "ERROR SUMMARY: 0" test/outfiles/set_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// ERRORS: ${GREEN}ok${ENDCOLOR}"
else
	echo "// ERRORS: ${RED}not ok${ENDCOLOR}"
fi

grep "All heap blocks were freed" test/outfiles/set_leaks.txt > /dev/null
if [ $? -eq 0 ]; then
	echo "// LEAKS:  ${GREEN}ok${ENDCOLOR}"
	rm test/outfiles/set_leaks.txt
else
	echo "// LEAKS:  ${RED}not ok${ENDCOLOR}"
	echo "   logs are situated in \"test/outfiles\"\n"
fi

{ time ./ft_set > /dev/null; } 2>>set_time.txt
{ time ./std_set > /dev/null; } 2>>set_time.txt

echo "// PERFORMANCES:"
echo "   ${BLUE}FT_SET:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './ft_set > /dev/null  \K.+' set_time.txt
echo -n "   heap use.."
grep 'total heap usage' set_time.txt | cut -c 31-
echo "   ${BLUE}STD_SET:${ENDCOLOR}"
echo -n "   timing...."
grep -oP './std_set > /dev/null  \K.+' set_time.txt
echo -n "   heap use.."
valgrind --log-file="grind.txt" ./std_set > /dev/null
grep 'total heap usage' grind.txt | cut -c 31-
rm set_time.txt
rm grind.txt

rm std_set

echo

make fclean > /dev/null
