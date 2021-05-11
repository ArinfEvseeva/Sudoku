#include "rdarray.h"

void sudoku::rdarray::narray()
{
	srand(rdseed);
	this->rdseed = rand();
	int queue[10];
	for (int i = 0; i < 9; ++i)
	{
		queue[i] = i+1;
	}
	for (int i = 0; i < 9; ++i)
	{
		int stp = rand()%9;
		while(!queue[stp])
		{
			stp ++;
			stp %= 9;
		}
		this->array[i] = queue[stp];
		queue[stp] = 0;
	}
}

sudoku::rdarray::rdarray()
{
	this->rdseed = time(NULL);
	narray();
}

int sudoku::rdarray::read(int i)
{
	return this->array[i];
}
