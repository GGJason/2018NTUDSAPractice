all:
		g++ main.cpp -std=c++11 -O2
		./a.out public_data.txt < 1.in > 1.out
		diff 1.out stdout/1.out
		./a.out public_data.txt < 2.in > 2.out
		diff 2.out stdout/2.out
		./a.out public_data.txt < 3.in > 3.out
		diff 3.out stdout/3.out
		./a.out public_data.txt < 4.in > 4.out
		diff 4.out stdout/4.out
