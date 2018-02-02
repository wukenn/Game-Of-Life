#ifndef BOOLMATRIX_H
#define BOOLMATRIX_X

#include <iostream>
#include <assert.h>
#include <iomanip>


class boolMatrix{
	public:
		boolMatrix();
		
		bool get(int row, int col) const;
		
		void set(int row, int col, bool value);
		
		int rowCount(int row) const;

		int colCount(int col) const;
		
		int totalCount() const;
		
		void print() const;
			
		static const int NUM_ROWS = 20;
		static const int NUM_COLS = 20;
	private:
		bool cell[20][20];      // represents the state of cell
		

};

boolMatrix::boolMatrix()
{
	for(int i=0; i<NUM_ROWS; i++)
		for(int j=0; j<NUM_COLS; j++)
			cell[i][j] = false;
}

bool boolMatrix::get(int row, int col) const
{
	assert(row >= 0 && row < NUM_ROWS);
	assert(col >= 0 && col < NUM_COLS);
	
	return cell[row][col];
}

void boolMatrix::set(int row, int col, bool value)
{
	assert(row >= 0 && row < NUM_ROWS);
	assert(col >= 0 && col < NUM_COLS);
	
	cell[row][col] = value;
}

int boolMatrix::rowCount(int row) const
{
	int count = 0;
	assert(row >= 0 && row < NUM_ROWS);
	
	for(int i = 0; i < NUM_COLS; i++)
		if(cell[row][i])
			count++;
	
	return count;
}

int boolMatrix::colCount(int col) const
{
	int count = 0;
	assert(col >= 0 && col < NUM_ROWS);
	
	for(int i = 0; i < NUM_ROWS; i++)
		if(cell[i][col])
			count++;
	
	return count;
}

int boolMatrix::totalCount() const
{
	int count = 0;
	for(int i=0; i<NUM_ROWS; i++)
		for(int j=0; j<NUM_COLS; j++)
			if(cell[i][j])
				count++;
				
	return count;
}

void boolMatrix::print() const
{
	std::cout << "  ";
	for (int col = 0; col < NUM_COLS; col++ )
		std::cout << col%10 << "";
	std::cout << std::endl;
	for(int i=0; i<NUM_ROWS; i++)
	{ 
		std::cout << std::fixed << std::setw(2) << i;
		for(int j=0; j<NUM_COLS; j++)
			if(cell[i][j])
				std::cout << "*";
			else
				std::cout << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

#endif

