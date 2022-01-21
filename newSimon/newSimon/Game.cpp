/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_buttonRed{ sf::Vector2f{200.0f,200.0f} },
	m_buttonGreen{ sf::Vector2f{200.0f,200.0f} },
	m_buttonBlue{ sf::Vector2f{200.0f,200.0f} },
	m_buttonYellow{ sf::Vector2f{200.0f,200.0f} },
	m_currentGameMode{ GameMode::Starting },
	m_flashTime(15),
	m_exitGame{false} //when true game will exit

{
	setupFontAndText(); // load font 
	setupButtons();
	resetButtons();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		processGameEvents(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentGameMode)
	{
	case GameMode::Starting:
		startingUpdate();
		break;
	case GameMode::Showing:
		
		break;
	case GameMode::Recieving:
		
		break;
	case GameMode::GameOver:
		
		break;
	default:
		break;
	}
	// reset the booleans after update before next process events call
	resetButtons();
	countdownTimers();
}

/// <summary>
/// @brief update game from menu.
/// 
/// using the four colour buttons the user can select
/// an easy,medium or hard game 8,16,32 notes
/// or blue to exit the game
/// 
/// </summary>
void Game::startingUpdate()
{
	m_statusText.setString("");
	if (m_blueButtonPressed)
	{
		m_window.close();
	}
	if (m_greenButtonPressed)
	{
		// test location of square flash
		m_greenTone.play();
		m_greenTimer = m_flashTime;
		m_buttonGreen.setFillColor(m_buttonGreen.getFillColor() + sf::Color(64, 64, 64, 255));

		randomiseNotes();	
		m_difficultyLevel = 8;	
		m_currentCount = 1;
		m_currentNote = 0;
	}
	if (m_redButtonPressed)
	{
		// test location of square flash
		m_redTone.play();
		m_redTimer = m_flashTime;
		m_buttonRed.setFillColor(m_buttonRed.getFillColor() + sf::Color(64, 64, 64, 255));


		randomiseNotes();
		m_currentCount = 1;
		m_currentNote = 0;
		m_difficultyLevel = 16;

	}
	if (m_yellowButtonPressed)
	{
		randomiseNotes();
		m_currentCount = 1;
		m_currentNote = 0;
		m_difficultyLevel = 32;
	}
	
}
/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_buttonRed);
	m_window.draw(m_buttonGreen);
	m_window.draw(m_buttonYellow);
	m_window.draw(m_buttonBlue);
	m_window.draw(m_titleText);

	m_window.draw(m_instructionsTextBlue);
	m_window.draw(m_instructionsTextGreen);
	m_window.draw(m_instructionsTextRed);
	m_window.draw(m_instructionsTextYellow);
	m_window.draw(m_statusText);

	m_window.display();
}

void Game::setupButtons()
{
	m_buttonRed.setFillColor(RED);
	m_buttonRed.setPosition(sf::Vector2f(570.0f, 30.0f));
	m_buttonBlue.setFillColor(BLUE);
	m_buttonYellow.setPosition(sf::Vector2f(350, 250));
	m_buttonYellow.setFillColor(YELLOW);
	m_buttonGreen.setPosition(sf::Vector2f(350, 30));
	m_buttonGreen.setFillColor(GREEN);
	m_buttonBlue.setPosition(sf::Vector2f(570, 250));


	if (m_toneBuffer.loadFromFile("assets/audio/tone.wav"))
	{
		std::cout << "beep loaded ok" << std::endl;
	}
	// assign the buffer to sounds and change pitch
	m_blueTone.setBuffer(m_toneBuffer);
	m_redTone.setBuffer(m_toneBuffer);
	m_redTone.setPitch(0.85f);
	
	m_yellowTone.setBuffer(m_toneBuffer);
	m_yellowTone.setPitch(0.7f);
	m_greenTone.setBuffer(m_toneBuffer);
	m_greenTone.setPitch(0.55f);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (m_impactFont.loadFromFile("assets/fonts/impact.ttf"))
	{
		std::cout << "font loaded ok" << std::endl;
	}
	//setup the title 
	m_titleText.setFont(m_impactFont);
	m_titleText.setFillColor(WHITE);
	m_titleText.setCharacterSize(64);
	m_titleText.setPosition(50, 30);
	m_titleText.setString("S I M O N");

	// setup green message easy game 8
	m_instructionsTextGreen.setFont(m_impactFont);
	m_instructionsTextGreen.setFillColor(GREEN);
	m_instructionsTextGreen.setCharacterSize(32);
	m_instructionsTextGreen.setPosition(50, 100);
	m_instructionsTextGreen.setString("Press green for \n an easy game");
	// set red text for medium game 16
	m_instructionsTextRed.setFont(m_impactFont);
	m_instructionsTextRed.setFillColor(RED);
	m_instructionsTextRed.setCharacterSize(32);
	m_instructionsTextRed.setPosition(50, 200);
	m_instructionsTextRed.setString("Press red for \n a medium game");
	// setup yellow text  for hard game 32
	m_instructionsTextYellow.setFont(m_impactFont);
	m_instructionsTextYellow.setFillColor(YELLOW);
	m_instructionsTextYellow.setCharacterSize(32);
	m_instructionsTextYellow.setPosition(50, 300);
	m_instructionsTextYellow.setString("Press yellow for \n a hard game");
	// setup status font
	m_instructionsTextBlue.setFont(m_impactFont);
	m_instructionsTextBlue.setFillColor(BLUE);
	m_instructionsTextBlue.setCharacterSize(32);
	m_instructionsTextBlue.setPosition(50, 400);
	m_instructionsTextBlue.setString("Press blue to \nexit game");

	m_statusText.setFont(m_impactFont);
	m_statusText.setFillColor(WHITE);
	m_statusText.setCharacterSize(22);
	m_statusText.setPosition(500, 453);
	m_statusText.setString(""); // no status on menu screen
}

/// <summary>
/// @brief reset buttons to false.
/// 
/// run this before processing events again after an update to deal with the button presses
/// </summary>
void Game::resetButtons()
{
	m_blueButtonPressed = false;
	m_redButtonPressed = false;
	m_yellowButtonPressed = false;
	m_greenButtonPressed = false;
}
/// <summary>
/// @brief detect buttons clicks.
/// 
/// detect the mouse button release event (for either button)
/// then check x co-ordinate for column and y corrdinate for row
/// if it's inside a button set the corresponding boolean 
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& t_event)
{
	const int COL_1_LEFT = 350;
	const int COL_1_RIGHT = 550;
	const int COL_2_LEFT = 570;
	const int COL_2_RIGHT = 770;
	const int ROW_1_TOP = 20;
	const int ROW_1_BOTTOM = 230;
	const int ROW_2_TOP = 250;
	const int ROW_2_BOTTOM = 450;

	// check if the event is a a mouse button release
	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//check if its on the first col
		if (t_event.mouseButton.x > COL_1_LEFT && t_event.mouseButton.x < COL_1_RIGHT)
		{
			//check which row
			if (t_event.mouseButton.y > ROW_1_TOP && t_event.mouseButton.y < ROW_1_BOTTOM)
			{
				m_greenButtonPressed = true;
			}
			if (t_event.mouseButton.y > ROW_2_TOP && t_event.mouseButton.y < ROW_2_BOTTOM)
			{
				m_yellowButtonPressed = true;
			}
		}
		// check if its on the scecond col
		if (t_event.mouseButton.x > COL_2_LEFT && t_event.mouseButton.x < COL_2_RIGHT)
		{
			//check which row
			if (t_event.mouseButton.y > ROW_1_TOP && t_event.mouseButton.y < ROW_1_BOTTOM)
			{
				m_redButtonPressed = true;
			}
			if (t_event.mouseButton.y > ROW_2_TOP && t_event.mouseButton.y < ROW_2_BOTTOM)
			{
				m_blueButtonPressed = true;
			}
		}
	}
}


/// <summary>
/// @brief get a new sequence of notes.
/// </summary>
void Game::randomiseNotes()
{
	for (int i = 0; i < 32; i++)
	{
		// looking for values of 0,1,2,3
		m_noteSequence[i] = std::rand() % 4;
	}
}

/// <summary>
/// decrement each colours timer and then reset the colour on the button
/// </summary>
void Game::countdownTimers()
{
	if (m_blueTimer > 0)
	{
		if (0 == --m_blueTimer)
		{
			m_buttonBlue.setFillColor(BLUE);
		}
	}
	if (m_redTimer > 0)
	{
		if (0 == --m_redTimer)
		{
			m_buttonRed.setFillColor(RED);
		}
	}
	if (m_yellowTimer > 0)
	{
		if (0 == --m_yellowTimer)
		{
			m_buttonYellow.setFillColor(YELLOW);
		}
	}
	if (m_greenTimer > 0)
	{
		if (0 == --m_greenTimer)
		{
			m_buttonGreen.setFillColor(GREEN);
		}
	}
}