#include "Main_Header.h"


stack<Cell*> aStar(Board& board,Cell* start,Cell* end)
{
	stack<Cell*> path;

	Cell *current;
	Cell *child;

	// Define the open and the close list
	list<Cell*> openList, closeList;
	list<Cell*>::iterator i;

	unsigned int n = 0, size = board.GetRowsCount() * board.GetColsCount();

    // Add the start point to the openList
	openList.push_back(start);
	start->SetOpened(true);

	while (n==0 || ( current!=end && n<size) )
	{
		// Look for the smallest F value in the openList and make it the current point
		for (i = openList.begin(); i != openList.end(); i++)
		{
			if (i==openList.begin() || (*i)->GetFar() <= current->GetFar())
			{
				current = (*i);
			}
		}
		// Stop if we reached the end
		if(current==end)
			break;

		// Remove the current point from the openList
		openList.remove(current);
		current->SetOpened(false);

		// Add the current point to the closedList
		closeList.push_back(current);
		current->SetClosed(true);

		// Get all current's adjacent walkable points
		for (int r = -1; r < 2; r++)
		{
			for (int c = -1; c < 2; c++)
			{
				if( (r==0 && c==0) || (r==-1 && c==-1) || (r==-1 && c==1) || (r==1 && c==-1) || (r==1 && c==1) )
					continue;

				child = board.GetCell(current->GetRow() + r, current->GetCol() + c);
				
				// If it's closed or not walkable or if we are at a corner then pass
				if( child == nullptr || child->IsClosed() || child->IsWall() )
					continue;

				if( !child->IsOpened())
				{
					// Add it to the openList with current point as parent
					openList.push_back(child);
					child->SetOpened(true);
					// Compute it's far score
					child->SetParent(current);
					child->ComputeScores(end);
				}
			}
		}
		n++;
	}
	
	// Reset all the cells
	for (i = openList.begin(); i != openList.end(); ++ i)
    {
		(*i)->SetOpened(false);
    }
    for (i = closeList.begin(); i != closeList.end(); ++ i)
    {
		(*i)->SetClosed(false);
    }
	if (current != end)
	{
		return path;
	}
	// Resolve the path starting from the end point
	while (current->HasParent() && current != start)
    {
        path.push(current);
		//current->SetSymbol('+');
        current = current->GetParent();
        n ++;
    }
	path.push(start);
    return path;
}
/*


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

*/