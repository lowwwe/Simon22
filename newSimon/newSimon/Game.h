/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const sf::Color RED{ 180,0,0,255 };
const sf::Color GREEN{ 0,180,0,255 };
const sf::Color BLUE{ 0,0,180,255 };
const sf::Color YELLOW{ 180,180,0,255 };
const sf::Color WHITE{ 255,255,255,255 };

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setupButtons();
	void setupFontAndText();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_impactFont; // font used by game
	sf::RectangleShape m_buttonRed;// red button
	sf::RectangleShape m_buttonBlue;// blue button
	sf::RectangleShape m_buttonGreen;// green button
	sf::RectangleShape m_buttonYellow;// yellow button

	// text for title
	sf::Text m_titleText;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

