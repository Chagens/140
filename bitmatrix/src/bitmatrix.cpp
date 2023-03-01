#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include "bitmatrix.hpp"
using namespace std;

unsigned int djb_hash(const string &s){
	unsigned int h = 5381;
	unsigned int i, sz;

	sz = s.size();
	for(i = 0; i < sz; i++)
	{
		h = (h << 5) + h + s[i];
	}
	return h;
}

Bitmatrix::Bitmatrix(int rows, int cols)
{
	string str = "Bad rows";
	string str2 = "Bad cols";
	string putIN = "";
	if(rows <= 0)
	{
		throw(str);
	}
	if(cols <= 0)
	{
		throw(str2);
	}
    M.resize(rows, string(cols, '0')); 
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
  int i = 0;
  while(getline(fin, holder))
  {
	while(holder.empty())
	{
		getline(fin, holder);
	}
	M.resize(i+1);
	for(unsigned int j = 0; j < holder.size(); j++)
	{
		if(!(holder.at(j) == zero || holder.at(j) == one || holder.at(j) == blank))
		{
			throw(str2);
		}
		if(holder.at(j) != ' ' && !(holder.empty()))
		{
		M[i].push_back(holder.at(j));
		}
		if(holder.empty())
		{
			i--;
		}
	}
  i++;
  }
  fin.close();
}
        
Bitmatrix *Bitmatrix::Copy() const
{
	Bitmatrix *copy = new Bitmatrix(Rows(), Cols());
	*copy = *this;
    return copy;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
  ofstream fout;
  fout.open(fn.c_str());
    for(unsigned int i = 0; i < M.size(); i++)
  {
	  if(i != 0)
	  {
		fout << "\n";
	  }
	  for(unsigned int j = 0; j < M[0].size(); j++)
	  {
		fout << M[i][j];
      }
  }
	fout << "\n";
  fout.close();
  return true;
}
 
void Bitmatrix::Print(size_t w) const
{
	int spots = 0;
	//almost got it now code for 0;
	if(w == 0)
	{
	for(unsigned int i = 0; i < M.size(); i++)
	 {
		for(unsigned int j = 0; j < M[0].size(); j++)
		{ 	
			cout << M[i][j];
		}	
		cout << "\n";
		}
	}
	else{
	for(unsigned int i = 0; i < M.size(); i++)
	 {
		int spot = 0;
        	if(i%w == 0 && spots != 0)
		{
			cout << "\n";
		}
		for(unsigned int j = 0; j < M[0].size(); j++)
		{ 	
			if(j%w == 0 && spot != 0)
			{
				cout << " ";
			}
				cout << M[i][j];
				spot++;
		}	
	
		cout << "\n";
		spots++;
	}
	}
}
                 
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
  int r, c, i, j, k, l, iw, ih;
  int x1, x2, y1, y2;
  FILE *fp;
  vector< vector<unsigned char> > cache;
  fp = fopen(fn.c_str(), "w");
  if(fp == NULL)
  {
	return false;
  }

  c = Cols();
  r = Rows();

  iw = border + ((p + border) * c);
  ih = border + ((p + border) * r);

  cache.resize(ih, vector<unsigned char>(iw, 0));
	
  fprintf(fp, "P2\n%d %d\n255\n", iw, ih);
  x1 = y1 = border;
  for(j = 0; j < r; j++, y1 += p + border)
  {
	x1 = border;
	for(i = 0; i < c; i++, x1 += p + border)
	{
		x2 = x1 + p;
		y2 = y1 + p;

		for(l = y1; l < y2; l++)
			for(k = x1; k < x2; k++)
				cache[l][k] = (Val(j, i) == '0') ? 0xFF: 0x64;

	}
  }
  for(j = 0; j < ih; j++)
	  for(i = 0;i < iw; i++)
		  fprintf(fp, "%d\n", cache[j][i]);

	fclose(fp);
	return true;
}

int Bitmatrix::Rows() const
{
  return M.size();
}
                            
int Bitmatrix::Cols() const
{	
	if(M[0].size() == 0)
		{
			return 1;
		}
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
  if(!(val == '0' || val == '1'))
  {
	return false;
  }
  M[row][col] = val;
  return true;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  if(r1 < 0 || r2 < 0 || r1 >= Rows() || r2 >= Rows())
  {
	return false;
  }
  string hold;
	hold = M[r1];
	M[r1] = M[r2];
	M[r2] = hold;
  return true;
}
              
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
    if(r1 < 0 || r2 < 0 || r1 >= Rows() || r2 >= Rows())
    {
		return false;
    }
	for(int j = M[0].size(); j >= 0; j--)
	{
		if(M[r1][j] == '0' &&  M[r2][j] == '0')
		{
			M[r1][j] = '0';
		}
		else if(M[r1][j] == '0' &&  M[r2][j] == '1')
		{
			M[r1][j] = '1';

		}
		else if(M[r1][j] == '1' &&  M[r2][j] == '0')
		{
			M[r1][j] = '1';

		}
		else if(M[r1][j] == '1' && M[r2][j] == '1')
		{
			M[r1][j] = '0';
		} 
	}
  return true;
}
      

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
  (void) a1;
  (void) a2;
  Bitmatrix *copy = new Bitmatrix(a1 ->Rows(),a1 -> Cols());
  int i, j;
  if(a1 -> Rows() != a2 -> Rows() || a1 -> Cols() != a2 -> Cols())
  {
	return NULL;
  }
  for(i = 0; i < a1-> Rows(); i++){
	for(j = 0; j < a1-> Cols(); j++){
			if(a1 -> Val(i,j) == '0' && a2 -> Val(i, j) == '0')
		{
			copy -> Set(i,j, '0');
		}
			else if(a1 -> Val(i,j) == '0' && a2 -> Val(i, j) == '1')
		{
			copy -> Set(i,j, '1');
		}
		else if(a1 -> Val(i,j) == '1' && a2 -> Val(i, j) == '0')
		{
			copy -> Set(i,j, '1');
		}
		else if(a1 -> Val(i,j) == '1' && a2 -> Val(i, j) == '1')
		{
			copy -> Set(i,j, '0');
		}	 
	}
  }
  return copy;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
  Bitmatrix *copy = new Bitmatrix(a1 ->Rows(),a2 -> Cols());
  if(a1 -> Cols() != a2 -> Rows())
  {
	return NULL;
  }
  int i, j, k, total;
  for(i = 0; i < a1-> Rows(); i++){
	for(j = 0; j < a2-> Cols();j++){
		total = 0;
		for(k = 0; k < a2-> Rows();k++){
			if(a1 -> Val(i,k) == '0' && a2 -> Val(k, j) == '0')
		{
			total += 0;
		}
			else if(a1 -> Val(i,k) == '0' && a2 -> Val(k, j) == '1')
		{
			total += 0;
		}
		else if(a1 -> Val(i,k) == '1' && a2 -> Val(k, j) == '0')
		{
			total+= 0;
		}
		else if(a1 -> Val(i,k) == '1' && a2 -> Val(k, j) == '1')
		{
			total++;
		//	cout << "Total in the third for loop " << total << endl;
		}	
		//	total += a1 -> Val(i,k) * a2-> Val(k,j);
		}
	//	cout <<"total " << total << endl;
	//	cout <<"total mod 2 " <<  total % 2 << endl;
		if(total % 2 == 1)
		{
			copy -> Set(i,j, '1');
		}
		else{
			copy -> Set(i,j, '0');
		}
	}
  }
  return copy;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
  unsigned int i, spot;
  int j;
  if(rows.size() == 0)
  {
	return NULL;
  }
  for(i = 0; i < rows.size(); i++)
  {
	if(rows[i] > a1 -> Rows()){
		return NULL;
	}
  }
  Bitmatrix *copy = new Bitmatrix( rows.size() ,a1 -> Cols());
  for(i = 0; i < rows.size(); i++){
	for(j = 0; j < a1 -> Cols(); j++){
		spot = rows[i];
		copy -> Set(i, j, a1-> Val(spot,j));
	}
  }
  
  return copy;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
  int i, j, k;
  if(m->Rows() != m->Cols()){
	return NULL;
  }
  Bitmatrix *M = new Bitmatrix(m -> Rows() ,m -> Cols());
  for(i = 0; i < m -> Rows(); i++){
	for(j = 0; j < m -> Cols(); j++){
		M -> Set(i,j, m -> Val(i,j));
	}
  }
  Bitmatrix *inv = new Bitmatrix(m -> Rows() ,m -> Cols());
  for(i = 0; i < m -> Rows(); i++){
	for(j = 0; j < m -> Cols(); j++){
		inv -> Set(i,j, '0');
	}
  }
  for(i = 0; i < m -> Rows(); i++){
	inv -> Set(i,i, '1');
  }
  //for rows diagonal
  for(i = 0; i < m-> Rows(); i++){
	for(j = i+1; j < m-> Cols(); j++){
		if( M -> Val(i,i) != '1'){
			for(k = j; k < m -> Cols(); k++){
				if( M -> Val(k,i) == '1'){
					M -> Swap_Rows(i,k);
					inv -> Swap_Rows(i,k);
					k = m->Cols();
				}
			}
			if(M -> Val(i,i) != '1'){
				return NULL;
			}
		}
		if(M -> Val(j,i) == '1'){
			M -> R1_Plus_Equals_R2(j,i);
			inv -> R1_Plus_Equals_R2(j,i);
		}
		}

	
  }
  for(i = m -> Rows(); i >= 0; i--){
	for(j = i-1; j >= 0; j--){
		if(M -> Val(j,i) == '1'){
		M -> R1_Plus_Equals_R2(j,i);
		inv -> R1_Plus_Equals_R2(j,i);
		}
	}
  }
  return inv;
}



BM_Hash::BM_Hash(int size)
{
	Table.resize(size);
 string str = "Bad size";
  if(size <= 0)
  {
	throw(str);
  }
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
  unsigned int hash, i, sz_out, sz_in;
  HTE _push;

  sz_out = Table.size();
  hash = djb_hash(key);
  vector<HTE> &chain = Table[hash % sz_out];
  sz_in = chain.size();

  for(i = 0; i < sz_in; i++){
	if(chain[i].key == key)
		break;
  }

  if(i == sz_in){
	_push.key = key;
	_push.bm = bm;

	chain.push_back(_push);
  }
  else{
	return false;
  }
  return true;
}
    
Bitmatrix *BM_Hash::Recall(const string &key) const
{
  unsigned int hash, i, sz_out, sz_in;

  sz_out = Table.size();
  hash = djb_hash(key);
  const vector<HTE> &chain = Table[hash % sz_out];
  sz_in = chain.size();

  for(i = 0; i < sz_in; i++){
	if(chain[i].key == key){
		return chain[i].bm;
	}
  }
  return NULL;
}
      
vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;
  unsigned int i, j, sz_out, sz_in;
  sz_out = Table.size();

  for(i = 0; i < sz_out; i++)
  {
	sz_in = Table[i].size();
	for(j = 0; j < sz_in; j++){
		rv.push_back(Table[i][j]);
	}
  }
  return rv;
}
