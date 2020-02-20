#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	// Variable declarations
	speed = 150.f;
	plSpeed = 300.f;
	rectSpeedX = 225.f;
	rectSpeedY = 225.f;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	rectangleSpeed = "X: " + std::to_string((int)rectSpeedX) + " Y: " + std::to_string((int)rectSpeedY);
	blueSpeed.setString(rectangleSpeed);
	blueSpeed.setFont(font);
	blueSpeed.setFillColor(sf::Color::Blue);
	blueSpeed.setCharacterSize(22);
	blueSpeed.setPosition(25, 25);

	Rectangle.setSize(sf::Vector2f(50, 25));
	Rectangle.setPosition(250, 250);
	Rectangle.setFillColor(sf::Color::Red);

	Circle.setRadius(15);
	Circle.setFillColor(sf::Color::Green);
	Circle.setPosition(150, 150);

	RectBounce.setSize(sf::Vector2f(50, 25));
	RectBounce.setPosition(650, 400);
	RectBounce.setFillColor(sf::Color::Blue);

}

Level::~Level()
{
}

// handle user input
void Level::handleInput(float dt)
{
	// Green circle
	if (input->isKeyDown(sf::Keyboard::W))
	{
		if (Circle.getPosition().y >= 0)
		{
			Circle.move(0, -plSpeed * dt);
		}
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		if (Circle.getPosition().x >= 0)
		{
			Circle.move(-plSpeed * dt, 0);
		}
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		if (Circle.getPosition().y <= window->getSize().y - 30)
		{
			Circle.move(0, plSpeed * dt);
		}
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		if (Circle.getPosition().x <= window->getSize().x - 30)
		{
			Circle.move(plSpeed * dt, 0);
		}
	}
	// Blue rectangle speed
	if (input->isKeyDown(sf::Keyboard::Add))
	{
		input->setKeyUp(sf::Keyboard::Add);
		rectSpeedX *= 1.1;
		rectSpeedY *= 1.1;
	}

	if (input->isKeyDown(sf::Keyboard::Subtract))
	{
		input->setKeyUp(sf::Keyboard::Subtract);
		rectSpeedX *= 0.9;
		rectSpeedY *= 0.9;
	}
}

// Update game objects
void Level::update(float dt)
{
	// Red rectangle
	if (Rectangle.getPosition().x + 50 >= window->getSize().x || Rectangle.getPosition().x <= 0)
	{
		speed *= -1;
	}
	Rectangle.move(speed * dt, 0);
	// Blue rectangle
	if (RectBounce.getPosition().x + 50 >= window->getSize().x || RectBounce.getPosition().x <= 0)
	{
		rectSpeedX *= -1;
	}
	if (RectBounce.getPosition().y + 25 >= window->getSize().y || RectBounce.getPosition().y <= 0)
	{
		rectSpeedY *= -1;
	}
	RectBounce.move(rectSpeedX * dt, rectSpeedY * dt);
	// Blue rectangle speed text
	rectangleSpeed = "X: " + std::to_string((int)rectSpeedX) + " Y: " + std::to_string((int)rectSpeedY);
	blueSpeed.setString(rectangleSpeed);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(blueSpeed);
	window->draw(Rectangle);
	window->draw(Circle);
	window->draw(RectBounce);

	endDraw();
}

// clear back buffer (100, 149, 237)
void Level::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}