#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <ctime>
const int globalWidth = 1000;
const int globalHeight = 800;

struct myRectangle
{
	sf::RectangleShape shape;
	int xPos = 0;
	int width = 5;
	int height = 0;

	//constructor given xPosition, every rect will have same width and random height
	myRectangle(int xPos, int randomHeight)
	{
		this->xPos = xPos;
		height = randomHeight;
		sf::Vector2f dimensions(width, height);
		shape.setSize(dimensions);
		shape.setFillColor(sf::Color::Magenta);
		sf::Vector2f pos(xPos, globalHeight-height);
		shape.setPosition(pos);
	}

	void setxPos(int xPos)
	{
		this->xPos = xPos;
		sf::Vector2f newPos(xPos, globalHeight - this->height);
		shape.setPosition(newPos);
	}

	void setyPos(int yPos)
	{
		this->height = yPos;
		sf::Vector2f newDims(width, yPos);
		sf::Vector2f newPos(xPos, globalHeight - this->height);
		shape.setSize(newDims);
		shape.setPosition(newPos);
	}
};

void fillVector(std::vector<myRectangle>&rectangleVector);
void drawVector(std::vector<myRectangle>&rectangleVector,sf::RenderWindow&window);
void bubbleSort(std::vector<myRectangle>&rectangleVector, sf::RenderWindow&window);

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(globalWidth, globalHeight), "Bubble Sort Visualizer");
	
	bool spaceIsPressed = false;

	std::vector<myRectangle> rectangleVector;
	fillVector(rectangleVector);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					spaceIsPressed = true;				
				}
			}
		}

		
		window.clear(sf::Color::White);

		if (spaceIsPressed)
		{
			bubbleSort(rectangleVector,window); 
			spaceIsPressed = false;
		}
		else
		{
			drawVector(rectangleVector, window);

			window.display();
		}
		
	}


	return 0;
}

//sort all the bars using bubble sort
void bubbleSort(std::vector<myRectangle>&rectangleVector, sf::RenderWindow&window)
{
	int elemsSwitched = 1;
	myRectangle temp2(0, 0);
	std::vector<myRectangle> newVector;
	while (elemsSwitched > 0)
	{
		elemsSwitched = 0;
		std::vector<myRectangle>newVector;
		for (int i = 0; i < rectangleVector.size() - 1; i++)
		{
			if (rectangleVector[i].height > rectangleVector[i + 1].height)
			{
				//1.draw the big on top of the small, left -> right
				window.clear(sf::Color::White);
				myRectangle temp1(rectangleVector[i+1].xPos, rectangleVector[i].height);
				newVector.push_back(rectangleVector[i]);
				newVector.push_back(temp1);
				
				//window.draw(rectangleVector[i].shape);
				//window.draw(temp1.shape);

				//2.clear out the big on the left
				//3.draw on the left


				//switch heights in vector
				temp2.setyPos(rectangleVector[i].height);
				rectangleVector[i].setyPos(rectangleVector[i + 1].height);
				rectangleVector[i + 1].setyPos(temp2.height);
				drawVector(rectangleVector, window);
				window.display();
				elemsSwitched++;
			}

		}
			
	}


}

void drawVector(std::vector<myRectangle>&rectangleVector,sf::RenderWindow&window)
{
	for (int i = 0; i < rectangleVector.size(); i++)
	{
		window.draw(rectangleVector[i].shape);
		float j = .0009999999;
		sf::sleep(sf::seconds(j));
	}
}
void fillVector(std::vector<myRectangle>&rectangleVector)
{
	//essentially fill up screen with rectangles that have random height
	int xOffset = 0;
	int count = 0;
	while (xOffset < globalWidth)
	{
		int randomHeight = rand() % globalHeight - 75;
		if (randomHeight < 5)
			randomHeight = 5;

		myRectangle rect(xOffset, randomHeight);
		rectangleVector.push_back(rect);

		xOffset += 5;
		count++;
	}
}