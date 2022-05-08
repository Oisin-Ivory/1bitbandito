#pragma once
#include <fstream>
#include "json.hpp"
#include "components/inputControllerCmpt.hpp"
#include "components/ReadableInfoCMPT.hpp"
#include "components/WeaponCmpt.hpp"
#include "components/spriteCmpt.hpp"
#include "components/MoveCmpt.hpp"
#include "components/HealthCmpt.hpp"
#include "components/AICompt.hpp"
#include "components/EnemyManagerCmpt.hpp"
#include "../Button.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "../Textbox.hpp"

//#include "ResourcePath.hpp"
//#include "ResourcePath.hpp"
class Game{
public:
	Game();
	~Game();
	void AddObject(Object* obj);
	void HandleInput();
	void Update();
	void Render();
	void Start();
	sf::Time GetElapsed();
	void RestartClock();
	Map map;
	customwindow::Window* GetWindow();
	float dt;
	sf::Clock clock;
	bool isPlaying = false;
	void MainMenu();
	void Reset();
	sf::Font font;
	
private:
	bool mouseReleased = true;
	customwindow::Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	bool tookInput = false;
	bool didMove = false;
	sf::Vector2f ammounToMove;
	bool firstRun = true;
	std::vector<Object*> m_gameObjects;
	Object* player;

	int menuState = 0;

	float playerHealth;
	int wave;
	sf::Text playerHealthText;
	sf::Text waveText;


	int highscore;
	sf::Text highscoreText;

	sf::RectangleShape banner;

	Button exitButton;
	Button levelSelectButton;
	Button level1Button;
	Button level2Button;
	Textbox customLevel;

	float timeSinceTextEntered = 0;
	float timeBetweenTextEnter = 0.2;
};
