#pragma once
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>
#include <stack>



class Cell {
public:
	Cell();
	~Cell();
	int m_id = 0;
	int m_previousCellId{ -1 };
	bool m_marked = false;
	bool m_isPassable = true;

	int m_centreX = 0;
	int m_centreY = 0;

	float m_h;
	int m_pathCost =  -1;
	int myCost = -1;


	bool drawCost = false;
	std::vector<int> m_diagonalList;

	Cell* m_previous;

	Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font);
	Cell* previous() const;
	int weight() const;

	void setPrevious(Cell* previous)
	{
		m_previous = previous;
	}
	bool marked() const;
	void setMarked(bool t_marked);
	void addNeighbour(int t_cellID);
	int returnID() const {
		return m_id;
	}
	void render(sf::RenderWindow& t_window, bool t_cpress);

	sf::Text m_cellcost;
	sf::Font m_fonts;
	void addCost(int m_cost);
	bool m_showCost = false;
	bool myPath = false;

	int getCost();
	void setColor(sf::Vector3f t_RGBValue);
	sf::RectangleShape m_shape;

	sf::RectangleShape vectorline;


	std::vector<int> m_neighbours;

};

class Grid {
public:
	Grid();
	~Grid();
	int numberOfNonTraversals = 200;
	sf::RectangleShape m_notTraversal[200];
	sf::RectangleShape m_pathITtake[200];
	bool resets = false;
	std::vector<int> m_pathFound;
	Cell& returnCell(int t_id);
	bool cPress = false;
	bool isStartPosSelected;
	bool isEndPosSelected;
	int endPointId;
	int startPointId;
	void neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current);
	void reset();
	void resetPoints();
	void initialiseMap();
	void update(sf::RenderWindow& t_window);
	int makeStratPos(sf::RenderWindow& t_window);
	int makeEndPos(sf::RenderWindow& t_window);
	void makeCost();
	void verticalCells(int t_point, int t_row, int t_cost);
	void horizontalCells(int t_point, int t_col, int t_cost);
	void setCost(int t_p, int t_col, int t_cal, int t_cost);
	void notTraversalsCost();
	void callFlow(int t_start, int t_end);
	void render(sf::RenderWindow& t_window);
	void flowField(Cell* start, Cell* dest);
	void generateHeatMap();
	Cell* findCellPoint(sf::Vector2f point);
	sf::Vector2f findEndPos(int t_id);
	void makePath();
	void clearPath();

	sf::CircleShape player;

	void movePlayer(std::stack<Cell*> t_path);
	bool canPlayerMove;
	std::stack<Cell*> playerPath;
	int m = 1;

	std::vector<Cell>& returnAllCells();

	//sf::Text m_cellId[2501];
	sf::Font m_font;
	std::vector<std::vector<Cell>> m_cellsVectorArray;
	std::vector<Cell> m_cellsArray;


	int m_maxRows = 50;
	int m_maxCols = 50;
	int m_currentRow;
	int m_currentCol;
	int randomCellId = 0;

private:

};
