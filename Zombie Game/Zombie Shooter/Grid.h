#pragma once
#ifndef GRID
#define GRID


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Wall.h"
#include <vector>
#include <queue>

class Cell
{
public:
	Cell();
	
	sf::RectangleShape cellBody;
	int m_id;
	int m_previousCellId{ -1 };
	bool m_isPassable;
	sf::Text idText;
	std::vector<Cell*> neighbours;
	void markImpassable(std::vector<Wall*>& t_globalWalls);
	std::string neighboursText;
	sf::Text neighboursDisplayText;
	sf::Vector2f center;

	
	///breadthFirst
	bool m_isMarked{ false };
	int m_parentCellId;
	void setMarked(bool t_mark) { m_isMarked = t_mark; }
	void setParentCellId(int t_cellId) { m_parentCellId = t_cellId; };
	bool isMarked() const { return m_isMarked; }
	int getID() const {
		return m_id;
	}

	

};


class Grid
{
public:
	Cell& at(int t_index);
	Grid();
	void setupGrid(std::vector<Wall*>& t_globalWalls);
	void showNeighbours();
	sf::Font idFont;
	Cell cellGrid[10][10];
	void draw(sf::RenderWindow& m_window);
	void reset();
	int getCellPlayerIsIn(sf::Vector2f t_playerPos);
	int cellsThatShouldBePassable[12];
};


#endif // !GRID