/*
 * INSTRUCTOR-GIVEN TEMPLATE
 * COSC 140: Lab 6 - Candy Crush
 *
 * Description:
 *     Implements a 1D variation of Candy Crush where you crush candy and all
 *     adjacent candies of the same kind.
 *
 * Author:
 *     Caleb
 */
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
//Our secret weapon
#include "candyCrush.hpp"

using namespace std;

// ----------------------------------------------------------------------------
// CandyCrush Class Methods                                                {{{1
// ----------------------------------------------------------------------------

/*
 * candyCrush(const string &)                                              {{{2
 *
 * Sets up the candyCrush instance via a file at "inputFile". This file will
 * specify the rules of the game, as well as points given for a specific number
 * of candies being broken in a row.
 */
//helping function
void fillCandyList(list<string> &fill, const vector<string> &flavors, const vector<int> &probabilities,int length){
	string candys;
	int prob, numAdded;
	while(fill.size() < length)	//for(int i = fill.size(); i < length; i++)
	{
		candys = flavors[rand() % flavors.size()];
		prob = rand() % 100;
		for(int j = 0; j < probabilities.size(); j++)
		{
			if(prob < probabilities[j])
			{
				numAdded = j + 1;
				break;
			}
		}
	fill.resize(fill.size() + numAdded, candys);
	}
	if(fill.size() > length)
	{
		fill.resize(length);
	}
}



candyCrush::candyCrush(const string &inputFile) {
	int seed, totalProb = 0, i, hold1, hold2, check = 0, lines = 0;
	string line;
	string flavor;
	ifstream fin;
	istringstream sin;

	fin.open(inputFile.c_str());
	if(fin.fail())
	{
	exit(1); //error
	}
	//first two items in file
	//use getline here you are reading in a new line character for the start and it is messing up the flavors vector
	getline(fin, line);
	lines++;
	sin.str(line);
	sin >> seed >> rowLength;
	if(rowLength < 1 || rowLength > 100){
		exit(1); //error
	}
	sin.clear();
	srand(seed);
	getline(fin, line);
	lines++;
	sin.str(line);
	while(sin >> flavor){
		check++;
		flavors.push_back(flavor);
	}
	sin.clear(); 
	totalProb = 0;
	while(getline(fin, line)){
		lines++;
		sin.str(line);
		sin >> hold1 >> hold2;
		totalProb += hold1;
		if(hold1 < 0)
		{
			exit(1); //error negative prob
		}
		probabilities.push_back(totalProb);
		points.push_back(hold2);
		sin.clear();
		if(totalProb > 100){
			cerr << "Line " << lines << ": The cumulative probability exceeds 100. It must be exactly 100 when all probabilities have been entered\n";
			exit(1);
		}
	}
	if(probabilities[points.size() -1] != 100)
	{
		cerr << "The probabilities you entered must sum to 100 but their sum was " << probabilities[points.size() -1] << endl;
		exit(1);
	}
	if(probabilities.size() != getRowLength())
	{
		cerr << "You entered " << probabilities.size() << " pairs of probabilities and points. You must enter the same number of pairs as the rowLength, which is " << getRowLength()  << endl;
		exit(1);
	}

	//total prob greater than 100 error check
	//
	//
	//
	//
	fillCandyList(candy, flavors, probabilities, rowLength);
	fin.close();
}

/*
 * getRowLength                                                            {{{2
 *
 * Gets the length of amount of candy in the row...
 */

int candyCrush::getRowLength() const {
	return rowLength;
}

/*
 * getScore                                                                {{{2
 *
 * Gets the current score in-game.
 */

int candyCrush::getScore() const {
	return score;
}

/*
 * printCandy                                                              {{{2
 * 
 * Prints candy to stdout.
 */

void candyCrush::printCandy() const {
	list<string>::const_iterator lit;
	string hold;
	int newLine = 0;
	for(lit = candy.begin(); lit != candy.end(); lit++)
	{
		hold = *lit;
		if(newLine % 8 == 0 && newLine != 0)
		{
		printf("\n");
		}
		printf("%-10s", hold.c_str());
		newLine++;
	}
	cout << "\n";
}

/*
 * play                                                                    {{{2
 *
 * Make a play in the game. The candy destroyed is determined by "choice".
 */

int candyCrush::play(int choice) {
	//error if choice is greater then length or if choice is less than 0
	int erase = 0, leftNum = 0, made = 0; //sub left
	string leftHold, rightHold, compare;
	list<string>::iterator lit;
	list<string>::iterator right;
	list<string>::iterator left; 
	right = candy.begin();
	left = candy.end();
	left--;
	lit = candy.begin(); 


	for(int i = 0; i < choice; i++) //the spot the player picks
	{
		lit++;
	}
		for(int i = 0; i < choice + 1; i++) //the spot after the player picks
	{
		right++;
	}
	if(choice != 0){
		for(int i = getRowLength(); i > choice - 1; i--) //the spot before the player picks
		{
			left--;
		}
	leftHold = *left;
	}
	rightHold = *right;
	//all variables are at right spot past this point
	compare = *lit;

	while(rightHold == compare && right != candy.end())
	{
		right++;
		rightHold = *right;
	}
	if(choice != 0 || left != candy.begin()){
	while(leftHold == compare && left != candy.begin()){
		left--;
		leftHold = *left;
	}
	}
	if(*left != compare){
		left++;
	}
	if(*left != compare){
		left++;
	}
	
	lit = left;

	while(lit != right)
	{
		lit++;
		erase++;
	}
	erase--;
	candy.erase(left, right);
	fillCandyList(candy, flavors, probabilities, getRowLength());
	for(int i = 0; i < points.size(); i++)
	{
		if(i == erase){
			score += points[i];
			made = points[i];
		}
	}
	if(erase > points.size() - 1)
	{
		score += points[points.size() -1];
		made = points[points.size() -1];
	}

	return made;
}
