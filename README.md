to compile program in USER standart input mode, use g++ main.cpp core.cpp

to compile program in USER standart input mode with make run {make -f Makefile-oos}

to compile program in TEST mode with make run {make -f Makefile-oos OPTIONS="-DTEST"}

to use program in command-line with "arguments-as-flags" mode, run ./main.out -flag=[float], where flag can be 'a', 'b' or 'c' 

to use program in terminal input mode, run ./main.out without flags

to compile program in test mode, use g++ main.cpp core.cpp -DTEST

to generate documentation, use doxygen doxygen.config
