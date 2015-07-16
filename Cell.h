#ifndef CELL_H
#define CELL_H

class Cell;

#include "Board.h"

class Cell
{
private:

	///
	/// The symbol used to dispay this cell.
	/// It is also used to determine its type:
	///		- ' ' - Corridor
	///		- '#' - Wall
	///		- '$' - Target
	///		- '^' - Start
	///
	char Symbol;

	/// The row on whiche the cell is located
	int Row;

	/// The column on which the cell is located
	int Col;

	/// Specifies whether the cell has been visited or not
	bool Visited;

	/// A pointer to the board in which this Cell is located
	/// or NULL if the cell is not a partof a board.
	Board * pBoard;

public:
	Cell(Board* pBoard=NULL, char symbol='#', int Row=0, int Col=0);

public:
	char GetSymbol() const;
	void SetSymbol(char s);

	bool IsPassable() const;
	bool IsCorridor() const;
	bool IsWall() const;
	bool IsStart() const;
	bool IsTarget() const;

	int GetRow() const;
	int GetCol() const;

	void MarkVisited();
	void MarkNotVisited();
	bool IsVisited() const;

	const Board* GetBoard() const;

	Cell* GetLeftNeighbour() const;
	Cell* GetRightNeighbour() const;
	Cell* GetTopNeighbour() const;
	Cell* GetBottomNeighbour() const;

	void PrintInfo() const;
	
private:
	void SetBoard(Board* pBoard);

	friend class Board;


	// Extra fields for the A* pathfinder
private:
	Cell* parent;
	bool opened, closed;
	int far;

public:
	Cell* GetParent() const { return parent;}
	void SetParent(Cell* p) { parent = p;}
	bool HasParent() const { return parent != nullptr;}

	bool IsOpened() const { return opened;}
	void SetOpened(bool val) { opened = val;}

	bool IsClosed() const { return closed;}
	void SetClosed(bool val) { closed = val;}

	int GetFar() const { return far;}

	void ComputeScores(Cell* end);

};

#endif // CELL_H