#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
  M.resize(rows*cols);
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
  string str = "Can't open file";
  string str2 = "Bad file format";
  string holder;
  ifstream fin;
  char zero = '0';
  char one = '1';
  char blank = ' ';
 fin.open(fn.c_str());
//  if(out == NULL)
//  {
//	throw(str);
//  } 
  for(int k = 0; k < Rows();k++)
  {
	getline(fin, holder);
	for(unsigned int j = 0; j < holder.size(); j++)
	{
		if(!(holder.at(j) == zero || holder.at(j) == one || holder.at(j) == blank))
		{
			throw(str2);
		}
	}
	M[k] = holder;
  }
  fin.close();
}
        
Bitmatrix *Bitmatrix::Copy() const
{
  return NULL;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
  ofstream fout;
  fout.open(fn.c_str());
    for(int i = 0; i < Rows(); i++)
  {
	  if(i != 0)
	  {
		fout << "\n";
	  }
	  for(int j = 0; j < Cols(); j++)
	  {
		fout << M[i*j];
      }
  }
  fout.close();
  return true;
}
 
void Bitmatrix::Print(size_t w) const
{
	(void) w;
  for(int i = 0; i < Rows(); i++)
  {
	for(int j = 0; j < Cols(); j++)
	{ 	
		if(i*j%w == 0)
		{
			
		}
			cout << M[i][j];
	}
	cout << "\n";
  }
}
                 
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
  (void) fn;
  (void) p;
  (void) border;
  return false;
}

int Bitmatrix::Rows() const
{
  return M.size();
}
                            
int Bitmatrix::Cols() const
{	
  return M[0].size();
}
                            
char Bitmatrix::Val(int row, int col) const
{
  (void) row;
  (void) col;
  char ret;
  if(M[row][col] == '1')
  {
	ret  = '1';
  }
  else{
	ret = '0';
  }
  if(row*col > Rows() * Cols())
  {
	ret = 'x';
  }
  return ret;
}
            
bool Bitmatrix::Set(int row, int col, char val)
{
  (void) row;
  (void) col;
  (void) val;
  if(val != '0' || val != '1')
  {
	return false;
  }
  M[row][col] = val;
  return true;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  (void) r1;
  (void) r2;
  string hold;
  for(int i = 0;i < Rows(); i++)
  {
	hold = M[i*r1];
	M[i*r1] = M[i*r2];
	M[i*r2] = hold;
  }
  return true;
}
              
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
  (void) r1;
  (void) r2;
  for(int i = 0; i < Rows(); i++)
  {
	for(int j = 0; j < Cols(); j++)
	{
		if(M[r1][j] == '0' &&  M[r2][j] == '0')
		{
			M[r1][j] = '0';
		}
		if(M[r1][j] == '0' &&  M[r2][j] == '1')
		{
			M[r1][j] = '1';

		}
		if(M[r1][j] == '1' &&  M[r2][j] == '0')
		{
			M[r1][j] = '1';

		}
		if(M[r1][j] == '1' && M[r2][j] == '1')
		{
			M[r1][j] = '0';
		}
	}
  }
  return true;
}
      

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
  (void) a1;
  (void) a2;
  return NULL;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
  (void) a1;
  (void) a2;
  return NULL;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
  (void) a1;
  (void) rows;
  return NULL;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
  (void) m;
  return NULL;
}



BM_Hash::BM_Hash(int size)
{
	
  (void) size;
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
  (void) key;
  (void) bm;
  return false;
}
    
Bitmatrix *BM_Hash::Recall(const string &key) const
{
  (void) key;
  return NULL;
}
      
vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;

  return rv;
}
