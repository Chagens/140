#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
  (void) rows;
  (void) cols;
  M.resize(rows*cols);
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
  string str = "Can't open file";
  string str2 = "Bad file format";
  char holder[256];
  int hold;
  int i = 0;
  (void) fn;
  ofstream fin;
  fin.open(fn.c_str());
//  if(!(fin.open(fn.c_str()))
//  {
//	throw(str);
//  } 
  while(i == 0)
  {
	if(fin.eof() == true)
	{
		i++;
	}
	getline(fin, holder);
	for(unsigned int j = 0; j < sizeof(holder); j++)
	{
		if(holder.at(j) != "1" || holder.at(j) != "0" || holder.at(j) != " ")
		{
			throw(str2);
		}
	}
  }
  fin.close();
}
        
Bitmatrix *Bitmatrix::Copy() const
{
  return NULL;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
  (void) fn;
  ofstream fout;
  fout.open(fn.c_str());
    for(int i = 0; i < Rows(); i++)
  {
	  if(i != 0)
	  {
		fprintf(fn.c_str(), "\n");
	  }
	  for(int j = 0; j < Cols(); j++)
	  {
		fprintf(fn,"%c", M[i*j].c_str());
      }
  }
  fout.close();
  return true;
}
 
void Bitmatrix::Print(size_t w) const
{
  (void) w;
  for(int i = 0; i < M.size(); i++)
  {
	if(i%w == 0)
	{
		printf("%c\n", M[i].c_str()); 
	}
	else{
		printf("%c", M[i].c_str());
	}
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
  return Rows;
}
                            
int Bitmatrix::Cols() const
{	
  return Cols;
}
                            
char Bitmatrix::Val(int row, int col) const
{
  (void) row;
  (void) col;
  char ret;
  if(M[row*col].c_str() == '1')
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
  M[row*col] = val;
  return true;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  (void) r1;
  (void) r2;
  string hold;
  for(int i = 0;i < Cols(); i++)
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
  int hold;

  return false;
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
