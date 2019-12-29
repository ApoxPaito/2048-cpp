#include "gameboard.h"
#include <conio.h>
#include <ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void PrintGameframe(GameBoard*, int);

int main()
{
	srand(time(NULL));
	int undo = 5;
	int keyPressed;
	GameBoard* mainBoard = new GameBoard();
	
	mainBoard->RandomizeInitial();
	PrintGameframe(mainBoard, undo);
	
	while (1)
	{
		keyPressed = _getch();
		if (keyPressed == 0 || keyPressed == 224)
		{
			GameBoard* temp = new GameBoard(mainBoard);
			switch((keyPressed = _getch()))
			{
				case KEY_UP:
					mainBoard->PushUp();
					break;
				case KEY_DOWN:
					mainBoard->PushDown();
					break;
				case KEY_LEFT:
					mainBoard->PushLeft();
					break;
				case KEY_RIGHT:
					mainBoard->PushRight();
					break;
			}
			if (*mainBoard == *temp)
				delete temp;
			else
			{
				mainBoard->SetPrev(temp);
				GameBoard* cursor = mainBoard;
				int i = 0;
				while (undo > 0)
				{
					cursor = cursor->GetPrev();
					i++;
					if (cursor->GetPrev() == NULL && i <= undo)
						break;
					if (cursor->GetPrev()->GetPrev() == NULL && i >= undo)
					{
						GameBoard* temp = cursor->GetPrev();
						cursor->SetPrev(NULL);
						delete temp;
						i = 0;
						cursor = mainBoard;
					}
				}
				mainBoard->PutRandomNumbers();
				PrintGameframe(mainBoard, undo);
			}
			mainBoard->ResetBoxesChangedStatus();
			if (mainBoard->CheckIfMovePossible() == 0 && undo == 0)
			{
				std::cout << "Game's over, better luck next time!\n";
				break;
			}
		}
		if (keyPressed == 85 || keyPressed == 117)
		{
			if (undo == 0)
				std::cout << "Can't undo... there are no undos left!\n";
			else if (mainBoard->GetPrev() == NULL)
				std::cout << "Can't undo... there are no previous moves!\n";
			else
			{
				GameBoard* temp = mainBoard;
				mainBoard = mainBoard->GetPrev();
				delete temp;
				undo--;
			}
			PrintGameframe(mainBoard, undo);
		}
	}
	
	GameBoard* temp = mainBoard;
	while (temp->GetPrev() != NULL)
	{
		temp = temp->GetPrev();
		delete mainBoard;
		mainBoard = temp;
	}
	delete mainBoard;
	
	system("pause");
}

void PrintGameframe(GameBoard* mainBoard, int undo)
{
	system("cls");
	std::cout << "2048\n-------------------------\n";
	mainBoard->PrintBoard();
	std::cout << "-------------------------\nUndos Left: " << std::to_string(undo) << "\n";
}