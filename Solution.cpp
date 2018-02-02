#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <conio.h>
#include "boolMatrix.h"

using namespace std;
void read_matrix(boolMatrix&);							// for initializing the start state of cells from file
void game_of_life(boolMatrix&, int);						// execution of game is here
void update_state(boolMatrix&);							// generates the new state for each cell
int count_neighbors(const boolMatrix&, int, int);		// calculates the number of neighbours
void print_results(const boolMatrix&);
int main()
{
	int num_gen;
	
	boolMatrix life;
		
	read_matrix(life);				// read values from file
	
	// prompt for number of generations
	cout << "Enter number of generations: ";
	cin  >> num_gen; 
	cout << endl;
	// start game of life
	game_of_life(life, num_gen);
	
	print_results(life);
	
	return 0;
}

/**
* initialize the state 0 of cells by reading states from file
*/
void read_matrix(boolMatrix &life)
{
	ifstream lifeFile;
	
	// open file
	lifeFile.open("life.txt", ios::in );
	
	// assert if faild to open the file
	assert(lifeFile.fail() == false);
	
	int row, col;
	// read values
	while(lifeFile >> row >> col)
		life.set(row,col, true);		// update matrix
	
	// close the file
	lifeFile.close();
}

/**
* updates the states for specified generations and prints the results.
*/
void game_of_life(boolMatrix &life, int num_gen)
{
	for(int i = 1; i <= num_gen; i++)
	{		
		// update state to next life
		update_state(life);				
	}
}

void print_results(const boolMatrix &life){	// print the results
	life.print();
	cout << "Total alive in row 10 = " << life.rowCount(10)  << endl;
	cout << "Total alive in col 10 = " << life.colCount(10) << endl;
	cout << "Total alive = " << life.totalCount() << endl;

}
/**
* generates the new state of cells based on four rules of neighbours
*/
void update_state(boolMatrix& life)
{
	int neighbours = 0;
	
	boolMatrix nextLife;
	

	for (int i = 0; i < boolMatrix::NUM_ROWS; i++)
	{
		for (int j = 0; j < boolMatrix::NUM_COLS; j++)				
		{	
			neighbours = count_neighbors(life, i, j);		// count neighbours
			
			if (life.get(i,j))		// if cell is alive
			{
				/* under-population  OR  over-population */
				if (neighbours <= 1 || neighbours >= 4)
					nextLife.set(i,j,false);		// mark as dead

				/* else cell has two or three neighbors */
				else
					nextLife.set(i,j,true);			// remain alive in next life
			}
			else /* CELL IS EMPTY */
			{
				/* cell has exactly three living neighbors */
				if (neighbours == 3)
					nextLife.set(i,j,true);		// mark as alive
					
				// else, it will remain empty
			}
		}
		
	}

	// make next life as current life.
	life = nextLife;
	
}

/**
* counts the total number of neighbours of a cell in matrix
*/
int count_neighbors(const boolMatrix& life, int row, int col) {     	
	int count = 0;     
	
	int rowCount = row-1; 		// represents the row of matrix
	
	// check if rowCount is -1
	if(rowCount < 0)
		rowCount = 0;		// set row = zero
		
	while(rowCount < boolMatrix::NUM_ROWS && rowCount <= row+1 )
	{	 
		int colCount = col-1;		// represents the column of matrix
		
		// check if colCount is -1
		if(colCount < 0) 
			colCount = 0;	// set colCount to zero

		while(colCount < boolMatrix::NUM_COLS && colCount <= col+1)
		{	
			if(life.get(rowCount, colCount))		// if cell is alive
				count++;							// increment the counter
			colCount++;			// move to next column
		}
		rowCount++;				// move to next row
	}
	
	// if state of current cell is also counted
	if (life.get(row, col) && count > 0)
		 count--;     	
		 
	return count; 
} 
