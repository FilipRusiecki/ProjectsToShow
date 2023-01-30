#include "Grid.h"

class AStarComparer
{
public:
	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getCost() + t_n1->myCost) > (t_n2->getCost() + t_n2->myCost);

	}
};

Cell::Cell()
{
	
}

Cell::~Cell()
{
}

Cell::Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font)
{
	//if (!m_fonts.loadFromFile("Assets/Fonts/Pixellari.ttf"))
	//{
	//	std::cout << "error with font file file";
	//}
	
	vectorline.setFillColor(sf::Color::Red);
	vectorline.setSize(sf::Vector2f(2.0f, 10.0f));
	vectorline.setPosition(t_position.x + 8,t_position.y + 4);
	m_cellcost.setFont(t_font);
	m_id = t_cellID;
	m_shape.setSize(sf::Vector2f(900 / 50, 900 / 50));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color{ 204, 176, 129 });
	m_shape.setOutlineThickness(1);
	m_shape.setPosition(t_position);
	m_isPassable = true;
	m_previousCellId = -1;

	



}

Cell* Cell::previous() const
{
	return m_previous;
}

int Cell::weight() const
{
	return 1;
}

bool Cell::marked() const
{
	return m_marked;
}

void Cell::setMarked(bool t_marked) //bool that is checking if the cell is marked
{
	m_marked = t_marked;
}

void Cell::render(sf::RenderWindow& t_window, bool t_cpress)
{
	t_window.draw(m_shape);
	if (drawCost == true)
	{
		if (t_cpress == true)
		{
			t_window.draw(m_cellcost);
		}
	}
		t_window.draw(vectorline);
}

void Cell::addCost(int m_cost)
{
	myCost = m_cost;
//	std::cout << m_cost << std::endl;
	

	if (myCost != -1)
	{
		m_cellcost.setPosition(m_shape.getPosition());
		m_cellcost.setCharacterSize(8);
		m_cellcost.setString(std::to_string(m_cost));
		
		m_showCost = true;
	}
	else
	{
		m_showCost = false;
	}
}

int Cell::getCost()
{
	return myCost;
}

void Cell::setColor(sf::Vector3f t_RGBValue)
{
	sf::Uint8 red = t_RGBValue.x;
	sf::Uint8 green = t_RGBValue.y;
	sf::Uint8 blue = t_RGBValue.z;
	m_shape.setFillColor(sf::Color{ red, green ,blue });
}

void Cell::addNeighbour(int t_cellID) // adding a cell id to the neighbours
{
	m_neighbours.push_back(t_cellID);
}


Grid::Grid()
{
	
	initialiseMap();
	/*Cell* goal = findCellPoint(t_player.getPosition());
	callAstar();*/
}

Grid::~Grid()
{
}


Cell& Grid::returnCell(int t_id)
{
	return m_cellsArray.at(t_id);
}

void Grid::neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current)
{
	// List all neighbors:
	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = t_row + ((direction % 3) - 1); // Neighbor row
		int n_col = t_col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < m_maxRows && n_col >= 0 && n_col < m_maxCols) {

			// A valid neighbor:
			//std::cout << "Neighbor: " << n_row << "," << n_col << " - " << t_current << std::endl;
			t_cells.at(t_current).addNeighbour(n_row + (n_col * 50));
			// add the cell id 
			if (direction == 0 || direction == 2 || direction == 6 || direction == 8)
			{
				int diagId = t_cells.at(n_row + (n_col * 50)).m_id;
				t_cells.at(t_current).m_diagonalList.push_back(t_cells.at(n_row + (n_col * 50)).m_id);
			}

		}
	}
}

void Grid::reset()
{

	for (int i = 0; i < m_cellsArray.size(); i++)
	{
		m_cellsArray.at(i).setMarked(false);
		m_cellsArray.at(i).setPrevious(nullptr);
	}

}

void Grid::resetPoints()
{
	m_pathFound.clear();
	//isStartPosSelected = false;
	isEndPosSelected = false;
	for (int i = 0; i < 200; i++)
	{
		
		m_pathITtake[i].setPosition(0,0);
		m_cellsArray.at(i).myPath = false;
	}
	startPointId = 0;
}

void Grid::initialiseMap()
{
	srand(time(NULL));

	if (!m_font.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}
	player.setFillColor(sf::Color::White);
	player.setRadius(10.0f);
	sf::Vector2f cellPositions{0,0 };
	int count = 0;
	for (int row = 0; row < m_maxRows; row++)
	{

		for (int i = 0; i < m_maxCols; i++)
		{
			Cell cell(cellPositions, count, m_font);

			cellPositions.x += 900 / 50; // adjusting cell position on screen - x axis
			if (cellPositions.x >= 900)
			{
				cellPositions.x = 0;
				cellPositions.y += 900 / 50; // adjusting cell position on screen - y axis
				
			}
			
			count++;
			m_cellsArray.push_back(cell);// pushing back the cell
		}
	}
	int p = 0;


	for (int index = 0; index < numberOfNonTraversals; index++)
	{
		randomCellId = rand() % 2500;
		//m_notTraversal[index].setSize(sf::Vector2f(18.0f, 18.0f));
		//m_notTraversal[index].setFillColor(sf::Color::Black);

		//m_pathITtake[index].setSize(sf::Vector2f(18.0f, 18.0f));
		//m_pathITtake[index].setFillColor(sf::Color::Yellow);
		
		/*m_notTraversal[index].setPosition((m_cellsArray.at(randomCellId).m_shape.getPosition()));
		m_cellsArray.at(randomCellId).setMarked(true);*/


		m_cellsArray.at(randomCellId).m_shape.setFillColor(sf::Color::Black);
		m_cellsArray.at(randomCellId).m_shape.setSize(sf::Vector2f(18.0f, 18.0f));
		m_cellsArray.at(randomCellId).m_isPassable = false;
	}


	for (int i = 0; i < 2500; i++) // 50 * 50 = 2500
	{
		int posY = i / 50;
		int posX = i % 50;
		neighbours(posX, posY, m_cellsArray, i);
	}
	m_cellsArray.size();
	int i = 0;
	int h = 0;
}

void Grid::update(sf::RenderWindow& t_window) // update method
{
	makeStratPos(t_window);
	makeEndPos(t_window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		resetPoints();
		resets = true;
	}
	if (canPlayerMove == true)
	{
		if (player.getPosition() != m_cellsArray.at(endPointId).m_shape.getPosition())
		{
			movePlayer(playerPath);
		}
	}
}

int Grid::makeStratPos(sf::RenderWindow& t_window)
{
	if (isStartPosSelected == false )
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0; i < m_cellsArray.size(); i++)
			{
				if (m_cellsArray.at(i).marked() == true)
				{
					m_cellsArray.at(i).m_marked = false;
				}
			}
			sf::Vector2f translated_pos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
			int xPos = translated_pos.x / 18; int yPos = translated_pos.y / 18;
			float id = yPos * 50;
			id += xPos;
			if (m_cellsArray.at(id).marked() == false)
			{
				m_cellsArray.at(id).m_shape.setFillColor(sf::Color::White);
				isStartPosSelected = false;
				startPointId = id;
				return startPointId;
			}
		}
	}
}
int Grid::makeEndPos(sf::RenderWindow& t_window)
{
	if (isEndPosSelected == false)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f translated_pos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
			int xPos = translated_pos.x / 18; int yPos = translated_pos.y / 18;
			float id = yPos * 50;
			id += xPos;
			if (m_cellsArray.at(id).marked() == false)
			{
			
				isEndPosSelected = false;
				endPointId = id;
				for (int i = 0; i < 2500; i++) // 50 * 50 = 2500
				{
					sf::Vector2f endPos = findEndPos(endPointId);


				  float dx = m_cellsArray[i].m_shape.getPosition().x - endPos.x;
				  float dy = m_cellsArray[i].m_shape.getPosition().y - endPos.y;
				  float rotation = (-atan2(dx, dy)) * 180 / 3.141;

				  m_cellsArray[i].drawCost = true;
				//  m_cellsArray[i].m_isPassable = true;
				  m_cellsArray[i].vectorline.setRotation(rotation);
				}
				makeCost();
				notTraversalsCost();
				generateHeatMap();
				clearPath();
				callFlow(startPointId, endPointId);
				player.setPosition(playerPath.top()->m_shape.getPosition());

				makePath();
				return endPointId;
				
			}
		}
	}
}

void Grid::makeCost()
{
	if (m_cellsArray.at(endPointId).marked() == false)
	{
		int cost = 0;
		m_cellsArray[endPointId].addCost(cost);
		verticalCells(endPointId, 50, cost);
		verticalCells(endPointId, -50, cost);
		horizontalCells(endPointId, +1, cost);
		horizontalCells(endPointId,-1, cost);

		setCost(endPointId, -50, -1, cost);
		setCost(endPointId, -50, +1, cost);
		setCost(endPointId, +50, -1, cost);
		setCost(endPointId, +50, +1, cost);
		
	}
}

void Grid::verticalCells(int t_point, int t_row, int t_cost)
{
	int p = t_point;
	int c = t_cost;
	while (p >= 0 && p < 2500)
	{
		m_cellsArray[p].addCost(c);
		p += t_row;
		c++;
	}

}

void Grid::horizontalCells(int t_point, int t_col, int t_cost)
{
	int p = t_point + t_col;
	int c = t_cost + 1;

	if (t_col > 0)
	{
		while (p % 50 <= 50 - 1 && p % 50 != 0)
		{
			m_cellsArray[p].addCost(c);
			p += t_col;
			c++;
		}
	}
	else if (t_col < 0)
	{
		while (p % 50 != 50 - 1 && p % 50 >= 0)
		{
			m_cellsArray[p].addCost(c);
			p += t_col;
			c++;
		}
	}
}

void Grid::setCost(int t_p, int t_col, int t_cal, int t_cost)
{
	int calc = t_p + t_col + t_cal;
	if (calc > 0 && calc < 2500 && t_p % 50 == 0)
	{
		m_cellsArray[calc].addCost(t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
	}
	else if (calc > 0 && calc < 2500 && t_p % 50 >= 50 - 1)
	{
		m_cellsArray[calc].addCost(t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
	}
	else if (calc >= 0 && calc < 2500)
	{
		m_cellsArray[calc].addCost(t_cost);
		setCost(calc, t_col, t_cal, t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
		verticalCells(calc, t_col, t_cost + 1);
		horizontalCells(calc, t_cal, t_cost + 1);
	}
}

void Grid::notTraversalsCost()
{
	for (int i = 0; i < 2500; i++)
	{
		if (m_cellsArray[i].marked() == true) {

			m_cellsArray[i].addCost(10000);
			m_cellsArray[i].drawCost = false;
			m_cellsArray[i].m_isPassable = false;
			
		}
	}
}

void Grid::generateHeatMap()
{
	for (int i = 0; i < 2500; i++)
	{
		if (m_cellsArray.at(i).m_isPassable == false)
		{
			m_cellsArray.at(i).m_shape.setFillColor(sf::Color::Black);

		}
		else if (m_cellsArray.at(i).m_isPassable == true)
		{
			int reverseColour = 7 * m_cellsArray.at(i).myCost;
			sf::Color newColour(0.0f, 0.0f, 255.0f - reverseColour);
			m_cellsArray.at(i).m_shape.setFillColor(newColour);
		}

	}
	/*for (int i = 0; i < 2500; i++)
	{
		if (m_cellsArray.at(i).m_isPassable == true)
		{
			if (m_cellsArray.at(i).myPath == false)
			{
				sf::Vector3f colourValue = { 0.0f,0.0f, 255.0f - (m_cellsArray.at(i).getCost() * 8) }; 
				if (colourValue.z < 100)
				{
					colourValue.z = 100;
				}
				m_cellsArray.at(i).setColor(colourValue);
			}
		}
	}*/
}

void Grid::callFlow(int t_start, int t_end)
{
	Cell* start;
	Cell* end;
	start = &returnCell(t_start);
	end = &returnCell(t_end);
	flowField(start,end);
	int i = 0;
	int index = end->m_id;
	m_pathITtake[i].setPosition(m_cellsArray.at(index).m_shape.getPosition());
	if (m_pathFound.empty() == true)
	{
		m_pathFound.push_back(index);
		while (m_cellsArray.at(index).m_previous != nullptr)
		{
			m_pathFound.push_back(m_cellsArray.at(index).m_previous->m_id);
			m_pathITtake[i].setPosition(m_cellsArray.at(index).m_shape.getPosition());
			m_cellsArray.at(index).myPath = true;
			index = m_cellsArray.at(index).m_previous->m_id;
			i++;
		}
	}
	
}

std::vector<Cell>& Grid::returnAllCells() // returning all the cells
{
	return m_cellsArray;
}




void Grid::flowField(Cell* start, Cell* dest)
{
	Cell* s = start; // s start node
	Cell* goal = dest; //g goal node
	std::priority_queue<Cell*, std::vector<Cell*>, AStarComparer > pq; //pq = new priority queue

	int dist = std::numeric_limits<int>::max();    // Initialise dist[v] to infinity

	//for each node v in graph G
	for (int i = 0; i < m_cellsArray.size(); i++)
	{
		int xOne = m_cellsArray[i].m_centreX;
		int yOne = m_cellsArray[i].m_centreY;

		int xTwo = goal->m_centreX;
		int yTwo = goal->m_centreY;

		m_cellsArray[i].myCost = dist / 10;  //Initialise g[v] to infinity
		m_cellsArray[i].setPrevious(nullptr);
		m_cellsArray[i].setMarked(false);
		

	}

	if (goal != nullptr && start != nullptr)
	{
		start->myCost = 0; //Initialise g[start] to 0
		start->setMarked(true); //Mark(start)
		pq.push(start); //Add start to pq

		while (pq.size() != 0 && pq.top() != goal) //While the queue is not empty AND pq.top() != g
		{
			auto iter = pq.top()->m_neighbours.begin();
			auto endIter = pq.top()->m_neighbours.end();

			for (; iter != endIter; iter++) //For each child node of pq.top()
			{
				Cell* mychild = &returnAllCells().at(*iter);
				//std::cout << "Visiting: " << mychild->m_id << std::endl;

				if (mychild != pq.top()->previous()) //If (child !=previous(pq.top())
				{
					float weightOfArc = 0;
					float distToChild = 0;

					weightOfArc = mychild->weight(); //g(child)

					distToChild = (weightOfArc + pq.top()->myCost);

					if (distToChild < mychild->myCost && mychild->m_isPassable == true ) //If ( distToChild < f(child) )
					{
						mychild->myCost = distToChild; //let f[child] = distToChild
						mychild->setPrevious(pq.top()); //Set previous pointer of child to pq.top()
							//mychild->m_shape.setFillColor(sf::Color::Red);						//uncomment to see how it expands

						if (mychild == goal)
						{
							std::cout << "hewo" << std::endl;
						}

					} //End if
					if (mychild->marked() == false) //If (notMarked(child))
					{
						//pq.push(mychild);//Add child to the pq
						if (mychild->m_isPassable == true)
						{
							pq.push(mychild);//Add child to the pq
						}
						mychild->setMarked(true); //Mark Child
						
					} //end if
						Cell* pathNode = goal;
						Cell* pathNode2 = goal;
						while (pathNode->previous() != nullptr)
						{
							playerPath.push(pathNode);
							pathNode = pathNode->previous();
							sf::Vector3f colourValue = { 200.0f,255.0f,0.0f };
							pathNode->setColor(colourValue);
						}

						//for (auto i = 49; i >= 0; i--)
						//{
						//    playerPath2[i] = pathNode2->getID();
						//    pathNode2 = pathNode2->previous();
						//}

						canPlayerMove = true;






				}

			}//end for
			pq.pop();
		} //end while
	}
}

Cell* Grid::findCellPoint(sf::Vector2f point)
{
	for (int i = 0; i < m_cellsArray.size(); i++)
	{
		if (m_cellsArray.at(i).m_shape.getGlobalBounds().contains(point))
		{
			return &m_cellsArray.at(i);
		}
	}
	return nullptr;
}

sf::Vector2f Grid::findEndPos(int t_id)
{
	for (int i = 0; i < m_cellsArray.size(); i++)
	{

		return m_cellsArray.at(t_id).m_shape.getPosition();
	}
 
}

void Grid::makePath()
{
	for (int i = 0; i < m_pathFound.size(); i++)
	{
		m_cellsArray.at(m_pathFound.at(i)).m_shape.setFillColor(sf::Color::Yellow);
	}
}

void Grid::clearPath()
{
	for (int i = 0; i < m_pathFound.size(); i++)
	{
		int reverseColour = 5 * m_cellsArray.at(i).myCost;
		sf::Color newColour(0.0f, 0.0f, 255.0f - reverseColour);
		m_cellsArray.at(i).m_shape.setFillColor(newColour);
		m_cellsArray.at(m_pathFound.at(i)).m_shape.setFillColor(newColour);
	}
	m_pathFound.clear();
}

void Grid::movePlayer(std::stack<Cell*> t_path)
{
	if (player.getPosition().x > t_path.top()->m_shape.getPosition().x)
	{
		player.move(-1, 0);
	}
	if (player.getPosition().x < t_path.top()->m_shape.getPosition().x)
	{
		player.move(1, 0);
	}
	if (player.getPosition().y > t_path.top()->m_shape.getPosition().y)
	{
		player.move(0, -1);
	}
	if (player.getPosition().y < t_path.top()->m_shape.getPosition().y)
	{
		player.move(0, 1);
	}
	if (player.getPosition() == t_path.top()->m_shape.getPosition())
	{
		playerPath.pop();
	}
}



void Grid::render(sf::RenderWindow& t_window) // rendering the grid
{

	for (int index = 0; index < 2500; index++)
	{
		m_cellsArray.at(index).render(t_window,cPress);
		//t_window.draw(m_cellsArray.at(index).m_cellcost);
		//t_window.draw(m_cellId[index]);
	}
	t_window.draw(player);
	//for (int index = 0; index < numberOfNonTraversals; index++)
	//{
	//	t_window.draw(m_notTraversal[index]);
	//	t_window.draw(m_pathITtake[index]);
	//}
}