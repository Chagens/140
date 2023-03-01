#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std;

void do_enum(string &s, int index, int num){
	 int comp = s.size();
	if(index == comp)
	{
		cout << s << endl;
		return;
	}

	s[index] = '0';

	if( num > 0 && comp - index <= num)
	{
		s[index] = '1';
	}
	//recursion
	if(s[index] == '1')
	{
		do_enum(s, index + 1, num - 1);
	}
	else
	{
		do_enum(s, index + 1, num);
	}

	if(s[index] != '1' && num > 0)
	{
		s[index] = '1';
		do_enum(s, index + 1, num - 1);
	}

	s[index] = '-';
}

int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "usage: enum length nones\n");
		return 1;
	}
	int length, nones;
	string str;

	length = atoi(argv[1]);
	nones = atoi(argv[2]);

	str.resize(length, '-');

	do_enum(str, 0, nones);
}
