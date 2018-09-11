/*
 * This program generates a list of n random integers to use as input in the Experimentation part of Project #1.
 *
 * First, it reads an integer n. It then generates a sequence n random integers. The output consists of n, 
 * followed by the n integers, one per line. The output is written to stdout.
 *
 * Usage info:
 *    g++ -o randSeq randSeq.cc 
 *    ./randSeq 
 * To save the output in a file, redirect stdout to a file, i.e.,
 *    ./randSeq > file.txt
 * where file.txt is the desired name of the output file.
 */

#include<ctime>
#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

int main()
{
	int n;
	cerr << "How many random numbers do you want to generate?\n";
	cin >> n;
    cout << n << endl;

	srand( (unsigned) time(NULL) );
    
	for(int i = 0; i < n; i++){
		cout << rand() % 100000 << endl;
	}	
}
