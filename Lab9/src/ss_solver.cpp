/*
 * INSTRUCTOR-GIVEN TEMPLATE
 * COSC 140: Lab 9B - Shape Shifter!
 *
 * Description:
 *     A simple introduction to recursion. Brute force through all possible
 *     combinations of a puzzle until a valid solution is found. If none are
 *     discovered, print nothing. If a solution does exist, print out the
 *     pieces and the positions where they would solve the puzzle.
 *
 * Author:
 *     Your Name
 */

//C++
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <sstream>

//C
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// helper functions
bool done(vector<string> Grid)
{
	for(unsigned int i = 0; i < Grid.size(); i++)
	{
		for(unsigned int j = 0; j < Grid[0].size(); j++)
		{
			if(Grid[i][j] == '0')
			{
				return false;
			}
		}
	}
	return true;
}
char add(char a, char b)
{
	char one, zero;
	one = '1';
	zero = '0';
	if(a == '0' && b == '0')
	{
		return zero;
	}
	if(a == '0' && b == '1')
	{
		return one;
	}
	if(a == '1' && b == '1')
	{
		return zero;
	}
	if(a == '1' && b == '0')
	{
		return one;
	}
	return b;
}
class Shifter {
  public:

    /* Read_Grid_And_Shapes() initializes the grid from argc/argv, and the
       reads from standard input to get the shapes. */

    bool Read_Grid_And_Shapes(int argc,char **argv);

    /* Apply_Shape() applies the shape in Shapes[index] to the grid,
       starting at row r and column c.  You'll note, if you call
       Apply_Shape twice with the same arguments, you'll end up 
       with the same grid as before the two calls. */

    bool Apply_Shape(int index, int r, int c);

    /* Find_Solution() is the recursive procedure.  It tries all possible
       starting positions for Shape[index], and calls Find_Solution() 
       recursively to see if that's a correct way to use Shape[index].
       If a recursive call returns false, then it "undoes" the shape by
       calling Apply_Shape() again. */

    bool Find_Solution(int index);

    /* This prints the solution on standard output. */

    void Print_Solution() const;

  protected:

    /* This is the grid.  I have this be a vector of 0's and 1's, because it makes
       it easy to print the grid out. */

    vector <string> Grid;                   

    /* These are the shapes, in the order in which they appear in standard input. */

    vector < vector <string> > Shapes;     

    /* These two vectors hold the starting positions of the shapes, both as you
       are finding a solution, and when you are done finding a solution. */

    vector <int> Solution_Rows;            
    vector <int> Solution_Cols;            
};


bool Shifter::Read_Grid_And_Shapes(int argc, char **argv){
	istringstream ss;
	string str, mv;
	
	for(int i = 1; i < argc; i++)
	{
		Grid.push_back(string(argv[i])); //row one
	}

	vector<string> hold; //temp vector
	

	//SHAPE loop
	while(getline(cin, str)){
	ss.str(str);
	while(ss >> mv) //so if there is more than one piece
	{
		hold.push_back(mv);
	}
	Shapes.push_back(hold);
	hold.clear(); //so I can use it again
	ss.clear();
	}
	return true;	
}

bool Shifter::Apply_Shape(int index, int r, int c){
	int check = Grid[0].size() - c; //check for width
	int comp = Shapes[index][0].size(); //shape width
	
	int check2 = Grid.size() - r; //check for hight
	int comp2 = Shapes[index].size();
	//checking
	if(comp > check || comp2 > check2){
		return false;
	}
	//if it gets to here we assume that the shape fits
	for(unsigned int i = 0; i < Shapes[index].size(); i++)
	{
		for(unsigned int j = 0; j < Shapes[index][i].size(); j++)
		{
			Grid[i+r][j+c] = add(Shapes[index][i][j],Grid[i+r][j+c]);
		}
	}
	return true;
}
	
bool Shifter::Find_Solution(int index){

	if(index >= Shapes.size()){
	//		if(done(Grid)){
	//			return true;
	//		}
	//		else{
				return false;
	//		}
	}
	for(unsigned int i = 0; i < Grid.size(); i++)
	{
		for(unsigned int j = 0; j < Grid[0].size(); j++)
		{
			if(Apply_Shape(index, i, j)){
			//	Solution_Rows.push_back(i);
			//	Solution_Cols.push_back(j);
				if(done(Grid) || Find_Solution(index+1)){
					//print backwards
					Solution_Rows.push_back(i);
					Solution_Cols.push_back(j);
					return true;
				}
				else{
						Apply_Shape(index, i, j);
					}
				}
			}
		}
	return false;
}

void Shifter::Print_Solution() const{
	//print backwards
	unsigned fix = Solution_Rows.size() - 1;
	for(unsigned int i = 0; i < Solution_Rows.size(); i++){ //currently printing backwords and sometimes seg faulting
		
		for(unsigned int j = 0; j < Shapes[i].size(); j++){
			cout << Shapes[i][j] << " ";
		}
		cout << Solution_Rows[fix] << " " << Solution_Cols[fix] << endl;
		fix--;
	}

}

int main(int argc, char **argv) {
	Shifter s;
	s.Read_Grid_And_Shapes(argc, argv);
	s.Find_Solution(0);
	s.Print_Solution();
	
	return 0;
}
