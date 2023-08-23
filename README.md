to compile program in user mode, use g++ main.cpp core.cpp

to use program in command-line mode, run ./main.out -flag=[float], where flag can be 'a', 'b' or 'c' 

to use program in terminal input mode, run ./main.out without flags

to compile program in test mode, use g++ main.cpp core.cpp -DTEST

to generate documentation, use doxygen doxygen.config