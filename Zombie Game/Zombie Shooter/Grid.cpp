#include "Grid.h"

Cell::Cell()
{
	cellBody.setFillColor(sf::Color(0, 255, 0, 130));
	cellBody.setSize(sf::Vector2f(412.8, 412.8));
	cellBody.setOutlineThickness(3);
	cellBody.setOutlineColor(sf::Color::Black);
	m_id = -1;
	m_isPassable = true;
	m_previousCellId = -1;

	


}




void Cell::markImpassable(std::vector<Wall*>& t_globalWalls)
{
	for (Wall *w : t_globalWalls)
	{
		if (cellBody.getGlobalBounds().intersects(w->body.getGlobalBounds()))
		{
			if (!w->isOuter)
			{
				for (int i = 0; i < 26; i++)
				{
					m_isPassable = false;
					cellBody.setFillColor(sf::Color(255, 0, 0, 130));

				}
				
			}
		}

	}

}




Cell& Grid::at(int t_index)
{
	int  secondValue = t_index / 10 % 10;
	int  firstValue = t_index % 10;
	
	

	return cellGrid[firstValue][secondValue];
}

Grid::Grid()
{
	for (int i = 0; i < 7; i++)
	{
		cellsThatShouldBePassable[i] = i * 10;
	}

	cellsThatShouldBePassable[7] = 72;
	cellsThatShouldBePassable[8] = 73;
	cellsThatShouldBePassable[9] = 74;
	cellsThatShouldBePassable[10] = 75;
	cellsThatShouldBePassable[11] = 76;

}




void Grid::setupGrid(std::vector<Wall*>& t_globalWalls)
{


	sf::Vector2f pos(0, 0);
	idFont.loadFromFile("ART/FONTS/ariblk.ttf");
	int counter = 0;

	int column = 0;
	for (int row = 0; row < 11; row++)
	{








		if (row % 10 == 0 && row != 0)
		{
			column++;
			std::cout << std::endl;
			row = 0;
			pos.y += cellGrid[row][column].cellBody.getSize().y;
			pos.x = 0;
		}



		cellGrid[row][column].cellBody.setPosition(sf::Vector2f(pos));


		cellGrid[row][column].idText.setPosition(cellGrid[row][column].cellBody.getPosition());

		pos.x += cellGrid[row][column].cellBody.getSize().x;




		cellGrid[row][column].m_id = row + column * 10;
		std::cout << cellGrid[row][column].m_id << ", ";
		cellGrid[row][column].idText.setFont(idFont);
		cellGrid[row][column].neighboursDisplayText.setFont(idFont);
		cellGrid[row][column].idText.setString(std::to_string(cellGrid[row][column].m_id));


		// List all neighbors:
		for (int direction = 0; direction < 9; direction++) {
			if (direction == 4) { direction++; }; // Skip 4, this is ourself.

			int n_row = row + ((direction % 3) - 1); // Neighbor row
			int n_col = column + ((direction / 3) - 1); // Neighbor column

			// Check the bounds:
			if (n_row >= 0 && n_row < 10 && n_col >= 0 && n_col < 10) {

				// A valid neighbor:
				cellGrid[row][column].neighbours.push_back(&cellGrid[n_row][n_col]);
				cellGrid[row][column].neighboursText += (std::to_string(n_col) + std::to_string(n_row) + "\n");

				cellGrid[row][column].neighboursDisplayText.setPosition(cellGrid[row][column].cellBody.getPosition() + sf::Vector2f(250,0));
				cellGrid[row][column].neighboursDisplayText.setString(cellGrid[row][column].neighboursText); 
			}
		}




		cellGrid[row][column].markImpassable(t_globalWalls);


		if (row == 9 && column == 9)
		{
			std::cout << std::endl;
			break;
		}




	}


	for (int i = 0; i < 12; i++)
	{
		at(cellsThatShouldBePassable[i]).m_isPassable = true;
		at(cellsThatShouldBePassable[i]).cellBody.setFillColor(sf::Color(0, 255, 0, 130));
	}


}

void Grid::showNeighbours()
{
	int column1 = 2;
	int row1 = 5;

	
}

void Grid::draw(sf::RenderWindow& m_window)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (cellGrid[i][j].isMarked())
			{
				cellGrid[i][j].cellBody.setFillColor(sf::Color(0, 124, 124, 120));
			}
			m_window.draw(cellGrid[i][j].cellBody);
			m_window.draw(cellGrid[i][j].idText);
			m_window.draw(cellGrid[i][j].neighboursDisplayText);
		}
	}
}

void Grid::reset()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			cellGrid[i][j].setMarked(false);
		}
	}
}

int Grid::getCellPlayerIsIn(sf::Vector2f t_playerPos)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (cellGrid[i][j].cellBody.getGlobalBounds().contains(t_playerPos))
			{
				return cellGrid[i][j].getID();
			}
		}
	}
}
