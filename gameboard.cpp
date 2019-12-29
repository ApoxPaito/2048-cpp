#include "gameboard.h"

GameBoard::GameBoard()
{
	this -> prev = NULL;
}

GameBoard::GameBoard(GameBoard* gameboard)
{
	this -> prev = gameboard -> GetPrev();
	*this = *gameboard;
}

GameBoard::~GameBoard()
{
	
}

void GameBoard::PushUp()
{
	int colChanged = 0;
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (matrix[i][j].GetValue() == 0 && matrix[i + 1][j].GetValue() == 0)
				continue;
			if (matrix[i][j].GetValue() == 0 && matrix[i+1][j].GetValue() != 0)
			{
				matrix[i][j].SetValue(matrix[i+1][j].GetValue());
				matrix[i+1][j].SetValue(0);
				colChanged = 1;
			}
			else if (matrix[i][j].GetValue() == matrix[i+1][j].GetValue()
				&& matrix[i][j].IsNewlyCombined() != 1 && matrix[i+1][j].IsNewlyCombined() != 1)
			{
				matrix[i][j].SetValue(matrix[i+1][j].GetValue() * 2);
				matrix[i][j].ChangeCombinedState();
				matrix[i+1][j].SetValue(0);
				colChanged = 1;
			}
			if (colChanged == 1)
			{
				i = -1;
				colChanged = 0;
			}
		}
	}
}

void GameBoard::PushDown()
{
	int colChanged = 0;
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = SIZE - 1; i > 0; i--)
		{
			if (matrix[i][j].GetValue() == 0 && matrix[i - 1][j].GetValue() == 0)
				continue;
			if (matrix[i][j].GetValue() == 0 && matrix[i-1][j].GetValue() != 0)
			{
				matrix[i][j].SetValue(matrix[i-1][j].GetValue());
				matrix[i-1][j].SetValue(0);
				colChanged = 1;
			}
			else if (matrix[i][j].GetValue() == matrix[i-1][j].GetValue()
				&& matrix[i][j].IsNewlyCombined() != 1 && matrix[i-1][j].IsNewlyCombined() != 1)
			{
				matrix[i][j].SetValue(matrix[i-1][j].GetValue() * 2);
				matrix[i][j].ChangeCombinedState();
				matrix[i-1][j].SetValue(0);
				colChanged = 1;
			}
			if (colChanged == 1)
			{
				i = SIZE;
				colChanged = 0;
			}
		}
	}
}

void GameBoard::PushLeft()
{
	int rowChanged = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (matrix[i][j].GetValue() == 0 && matrix[i][j + 1].GetValue() == 0)
				continue;
			if (matrix[i][j].GetValue() == 0 && matrix[i][j+1].GetValue() != 0)
			{
				matrix[i][j].SetValue(matrix[i][j+1].GetValue());
				matrix[i][j+1].SetValue(0);
				rowChanged = 1;
			}
			else if (matrix[i][j].GetValue() == matrix[i][j+1].GetValue()
				&& matrix[i][j].IsNewlyCombined() != 1 && matrix[i][j+1].IsNewlyCombined() != 1)
			{
				matrix[i][j].SetValue(matrix[i][j+1].GetValue() * 2);
				matrix[i][j].ChangeCombinedState();
				matrix[i][j+1].SetValue(0);
				rowChanged = 1;
			}
			if (rowChanged == 1)
			{
				j = -1;
				rowChanged = 0;
			}
		}
	}
}

void GameBoard::PushRight()
{
	int rowChanged = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = SIZE - 1; j > 0; j--)
		{
			if (matrix[i][j].GetValue() == 0 && matrix[i][j - 1].GetValue() == 0)
				continue;
			if (matrix[i][j].GetValue() == 0 && matrix[i][j-1].GetValue() != 0)
			{
				matrix[i][j].SetValue(matrix[i][j-1].GetValue());
				matrix[i][j-1].SetValue(0);
				rowChanged = 1;
			}
			else if (matrix[i][j].GetValue() == matrix[i][j-1].GetValue()
				&& matrix[i][j].IsNewlyCombined() != 1 && matrix[i][j-1].IsNewlyCombined() != 1)
			{
				matrix[i][j].SetValue(matrix[i][j-1].GetValue() * 2);
				matrix[i][j].ChangeCombinedState();
				matrix[i][j-1].SetValue(0);
				rowChanged = 1;
			}
			if (rowChanged == 1)
			{
				j = SIZE;
				rowChanged = 0;
			}
		}
	}
}

void GameBoard::RandomizeInitial()
{	
	int i = rand() % SIZE;
	int j = rand() % SIZE;
	
	matrix[i][j].SetValue(2);
	
	i = rand() % SIZE;
	j = rand() % SIZE;
	
	while (matrix[i][j].GetValue() != 0)
	{
		i = rand() % SIZE;
		j = rand() % SIZE;
	}
	matrix[i][j].SetValue(2);
}

void GameBoard::PutRandomNumbers()
{
	int i = rand() % SIZE;
	int j = rand() % SIZE;
	
	if (HasZeroes() == 0)
		return;
	while (matrix[i][j].GetValue() != 0)
	{
		i = rand() % SIZE;
		j = rand() % SIZE;
	}
	matrix[i][j].SetValue((rand() % 2 + 1) * 2);
}

void GameBoard::PrintBoard()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			std::cout << std::to_string(matrix[i][j].GetValue()) << "\t";
		std::cout << "\n";
	}
}

void GameBoard::ResetBoxesChangedStatus()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j].IsNewlyCombined() == 1)
				matrix[i][j].ChangeCombinedState();
		}
	}
}

void GameBoard::SetPrev(GameBoard* prev)
{
	this -> prev = prev;
}

GameBoard* GameBoard::GetPrev() const
{
	return prev;
}

int GameBoard::GetMatrixElement(int i, int j) const
{
	return matrix[i][j].GetValue();
}

int GameBoard::HasZeroes()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j].GetValue() == 0)
				return 1;
		}
	}
	return 0;
}

int GameBoard::CheckIfMovePossible()
{
	if (HasZeroes() == 1)
		return 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int val = matrix[i][j].GetValue();
			if (i + 1 != SIZE)
			{
				if (val == matrix[i+1][j].GetValue())
					return 1;
			}
			if (j + 1 != SIZE)
			{
				if (val == matrix[i][j+1].GetValue())
					return 1;
			}
			if (i - 1 >= 0)
			{
				if (val == matrix[i-1][j].GetValue())
					return 1;
			}
			if (j - 1 >= 0)
			{
				if (val == matrix[i][j-1].GetValue())
					return 1;
			}
		}
	}
	return 0;
}

void GameBoard::operator=(const GameBoard& eq)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			matrix[i][j].SetValue(eq.GetMatrixElement(i, j));
	}
}

int GameBoard::operator==(GameBoard& eq)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j].GetValue() != eq.GetMatrixElement(i, j))
				return 0;
		}
	}
	return 1;
}
