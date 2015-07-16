#include "Main_Header.h"

char symbol(Cell* a,Cell* b);
string FullPath(stack<Cell*> path)
{
	string str = " ";
	Cell* a = path.top();
	path.pop();
	Cell* b;
	while (!path.empty())
	{
		b = path.top();
		path.pop();
		str+= symbol(a,b);
		a = b;
	}
	return str;
}

char symbol(Cell* a,Cell* b)
{
	if(a->GetCol() < b->GetCol())
		return 'R';
	else if(a->GetCol() > b->GetCol())
		return 'L';
	else if(a->GetRow() < b->GetRow())
		return 'D';
	else if(a->GetRow() > b->GetRow())
		return 'U';
}

int main(int argc, char* argv[])
{
	// Will store the path to the file to open
	char path[_MAX_PATH];

	// If the path is supplied as a command line argument, read it
	if(argc == 2)
	{
		strcpy_s(path, _MAX_PATH, argv[1]);
	}
	else
	{
		std::cout << "Enter path to labyrinth file: ";
		std::cin.getline(path, _MAX_PATH);
	}

	// Create a board and try to load the contents of the file
	Board board;

	std::cout << "Trying to load labyrinth from \"" << path << "\"...";

	if(board.LoadFromFile(path))
	{
		std::cout << "done\n\n";

		// If loading was successful, print the board
		board.Print();

		if (board.GetRowsCount() == 0)
		{
			std::cout << "The board is empty.\n";
			return 0;
		}

		stack<Cell*> st = aStar(board,board.GetStart(),board.GetEnd());
		cout << endl;
		if (st.empty())
		{
			cout<< " There is no path\n";
		}
		board.Print();
		//string str = FullPath(st);
		//cout<<str;

	}

	

	return 0;
}
