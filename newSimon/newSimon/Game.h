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
#include <SFML/Audio.hpp>

const sf::Color RED{ 180,0,0,255 };
const sf::Color GREEN{ 0,180,0,255 };
const sf::Color BLUE{ 0,0,180,255 };
const sf::Color YELLOW{ 180,180,0,255 };
const sf::Color WHITE{ 255,255,255,255 };

/// <summary>
/// the four different modes our game can be in.
/// </summary>
enum class GameMode
{
	Showing,
	Recieving,
	GameOver,
	Starting
};

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
	void startingUpdate();
	void recievingUpdate(sf::Time time);

	void render();
	void setupButtons();
	void setupFontAndText();
	void resetButtons();
	void processGameEvents(sf::Event& t_event);
	void randomiseNotes();
	void countdownTimers();
	void showingUpdate();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_impactFont; // font used by game
	sf::RectangleShape m_buttonRed;// red button
	sf::RectangleShape m_buttonBlue;// blue button
	sf::RectangleShape m_buttonGreen;// green button
	sf::RectangleShape m_buttonYellow;// yellow button

	// text for title
	sf::Text m_titleText;
	// text for blue instructions 
	sf::Text m_instructionsTextBlue;
	// text for red instructions 
	sf::Text m_instructionsTextRed;
	// text for Green instructions 
	sf::Text m_instructionsTextGreen;
	// text for yellow instructions 
	sf::Text m_instructionsTextYellow;
	// status text
	sf::Text m_statusText;
	// current mode the game is in
	GameMode m_currentGameMode;
	bool m_exitGame; // control exiting game

	// red buttone pressed
	bool m_redButtonPressed;
	// blue buttone pressed
	bool m_blueButtonPressed;
	// yellow buttone pressed
	bool m_yellowButtonPressed;
	// green buttone pressed
	bool m_greenButtonPressed;
	// array of notes
	int m_noteSequence[32];
	// difficulty target 8,16,32
	int m_difficultyLevel;
	// current note count
	int m_currentNote;
	// current sequence lenght
	int m_currentCount;

	// sound buffer used to store tone wav
	sf::SoundBuffer m_toneBuffer;
	// sound for blue
	sf::Sound m_blueTone;
	// sound for red
	sf::Sound m_redTone;
	// sound for green
	sf::Sound m_greenTone;
	// sound for yellow
	sf::Sound m_yellowTone;


	// time till blue button returns to normal color
	int m_blueTimer;
	// time till red button returns to normal color
	int m_redTimer;
	// time till green button returns to normal color
	int m_greenTimer;
	// time till yellow button returns to normal color
	int m_yellowTimer;
	// current time delay for buttons to return to normal color
	int m_flashTime;

	// delay between modes
	int m_modeChangeTimer;
};

#endif // !GAME_HPP

