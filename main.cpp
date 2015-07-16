#include "Main_Header.h"

char symbol(Cell* a,Cell* b);
string FullPath(stack<Cell*> path)
{
	string str = "";
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
	else
		return ' ';
}

char* StringToChar(string str)
{
	char* p = new char[str.length()+1];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		p[i] = str[i];
	}
	p[str.length()] = '\0';
	return p;
}

int main(int argc, char* argv[])
{/*
	if(argc >= 2)
	{
		try
		{
			PathFinder pf;
			string* strArr = new string[argc-1];
			for (int i = 1; i < argc; i++)
			{
				strArr[i] = pf.FindPath(argv[i]);
				cout<<strArr[i];
			}
		}
		catch(bad_alloc)
		{
			cout<<"Something went wrong, please try again...\n";
		}
	}
		*/
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
		string str = FullPath(st);
		cout<<str<<endl;
		return 0;
	}
}
