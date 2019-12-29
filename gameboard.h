#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "box.h"
#include <stdlib.h>
#include <iostream>
#include <string>

#define SIZE 4 //Change this if you want to modify the gameboard size

class GameBoard
{
private:
	Box matrix[SIZE][SIZE];
	GameBoard* prev;
public:
	GameBoard();
	GameBoard(GameBoard*);
	~GameBoard();
	void PushUp();
	void PushDown();
	void PushLeft();
	void PushRight();
	void RandomizeInitial();
	void PutRandomNumbers();
	void PrintBoard();
	void ResetBoxesChangedStatus();
	void SetPrev(GameBoard*);
	GameBoard* GetPrev() const;
	int GetMatrixElement(int, int) const;
	int HasZeroes();
	int CheckIfMovePossible();
	void operator=(const GameBoard&);
	int operator==(GameBoard&);
};

#endif