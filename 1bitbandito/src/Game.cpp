#include "Game.hpp"


Game::Game() : m_window("1bitbandito", sf::Vector2u(1280, 800))

{
	m_clock.restart();
	srand(time(nullptr));

    //load highscores
    nlohmann::json j2;
    std::ifstream inputFile("resources/data/highscore.json");
    if (!inputFile.good()) {
        highscore = 0;
    }
    else {
        inputFile >> j2;
        inputFile.close();

        highscore = j2["highscore"];
    }
    //mapSprite_ = nullptr;
    if (!font.loadFromFile("resources/fonts/pixel.ttf"))
    {
        std::cout << "failed to load font" << std::endl;
    }
	m_elapsed = 0.0f;

    exitButton = Button(
        sf::Vector2f((m_window.GetWindowSize().x / 2) - 200 / 2, m_window.GetWindowSize().y - 150),
        sf::Vector2f(200, 100),
        &font,
        1,
        sf::Color::White,
        sf::Color::Black,
        "Exit Game");

    levelSelectButton = Button(
        sf::Vector2f((m_window.GetWindowSize().x / 2)-200/2, m_window.GetWindowSize().y - 400),
        sf::Vector2f(200, 100),
        &font,
        1,
        sf::Color::White,
        sf::Color::Black,
        "Select Level");

    level1Button = Button(
        sf::Vector2f((m_window.GetWindowSize().x / 2) - 200 / 2, m_window.GetWindowSize().y - 500),
        sf::Vector2f(200, 100),
        &font,
        1,
        sf::Color::White,
        sf::Color::Black,
        "Level 1");

    level2Button = Button(
        sf::Vector2f((m_window.GetWindowSize().x / 2) - 200 / 2, m_window.GetWindowSize().y - 700),
        sf::Vector2f(200, 100),
        &font,
        1,
        sf::Color::White,
        sf::Color::Black,
        "Level 2");

    customLevel = Textbox(
        sf::Vector2f((m_window.GetWindowSize().x / 2) - 200 / 2, m_window.GetWindowSize().y - 300),
        sf::Vector2f(200, 100),
        "Custom level",
        &font
    );

    //playerHealthText.setScale({ 30,30 });
    playerHealthText.setPosition({ 30,30 });
    playerHealthText.setFillColor(sf::Color::White);
    playerHealthText.setFont(font);

    //waveText.setScale({ 30,30 });
    waveText.setPosition({ 30,70 });
    waveText.setFillColor(sf::Color::White); 
    waveText.setFont(font);
    auto textId = TextureManager::AddTexture("resources/images/banner.png");
    if (textId == -1) {
        std::cout << "error loading banner";
    }
    banner.setTexture(
        &TextureManager::GetTexture(textId)
    );
    banner.setSize({ 800, 250 });
    banner.setPosition(
        { sf::Vector2f((m_window.GetWindowSize().x / 2) - (banner.getSize().x / 2),
            100),

        }
    );

    highscoreText.setPosition(sf::Vector2f((m_window.GetWindowSize().x / 2)-50,350 ));
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setFont(font);
}

Game::~Game() {}

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }
customwindow::Window* Game::GetWindow() { return &m_window; }

void Game::HandleInput() {
    // Input handling.

    //std::cout << "updating input " << std::endl;
    for (auto& i : m_gameObjects)
    {
        if (i->isactive == false) continue;
        tookInput = false;
        ammounToMove = { 0,0 };
        auto movecmpt = i->GetComponent<MoveCmpt>();

        auto icmpt = i->GetComponent<inputControllerCmpt>();
        if (movecmpt == nullptr || icmpt == nullptr)
            continue;

        //std::cout << "reading input " << std::endl;
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::A) && !tookInput) {
            tookInput = true;
            //movecmpt->updatePosition({ -1,0 }, map);
            ammounToMove.x += -1;
            ammounToMove.y += 0;

        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::D) && !tookInput) {
            tookInput = true;
            //movecmpt->updatePosition({ 1,0 }, map);
            ammounToMove.x += 1;
            ammounToMove.y += 0;
        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::W) && !tookInput) {
            tookInput = true;
            //movecmpt->updatePosition({ 0,-1 }, map);
            ammounToMove.x += 0;
            ammounToMove.y += -1;
        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::S) && !tookInput) {
            tookInput = true;
            //movecmpt->updatePosition({ 0,1 }, map);
            ammounToMove.x += 0;
            ammounToMove.y += 1;
        }
        // std::cout << "would move " << ammounToMove.x << ammounToMove.y << std::endl;


        movecmpt->Update(0.01);


        auto wpn = i->GetComponent<WeaponCmpt>();
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::LEFT) && !tookInput) {
            tookInput = true;
            wpn->Shoot({ -1,0 }, movecmpt->getTilePos());


        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::RIGHT) && !tookInput) {
            tookInput = true;
            wpn->Shoot({ 1,0 }, movecmpt->getTilePos());

        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::UP) && !tookInput) {
            tookInput = true;
            wpn->Shoot({ 0,-1 }, movecmpt->getTilePos());

        }
        if (icmpt->IsKeyPressed(inputControllerCmpt::KEY::DOWN) && !tookInput) {
            tookInput = true;
            wpn->Shoot({ 0,1 }, movecmpt->getTilePos());
        }

        if (tookInput == true && !didMove) {
            movecmpt->updatePosition(ammounToMove, map);
            //std::cout << "moving " << ammounToMove.x << ammounToMove.y << std::endl;
            didMove = true;
        }
        if (!tookInput) {
            didMove = false;
        }
    }


}

void Game::AddObject(Object* obj) {
    m_gameObjects.push_back(obj);
}

void Game::Start() {
    for (auto& i : m_gameObjects) {
        auto sprtcmp = i->GetComponent<spriteCmpt>();
        if (sprtcmp != nullptr) {
            sprtcmp->setScale(map);
        }

        auto wpncmpt = i->GetComponent<WeaponCmpt>();
        if (wpncmpt != nullptr) {
            for (Object bullet : wpncmpt->GetBullets()) {
                bullet.GetComponent<AnimatedSpriteCmpt>()->setScale(map);
            }
        }

        auto info = i->GetComponent<ReadableInfoCMPT>();
        if (info != nullptr) {
            //std::cout << "has info" << std::endl;
            if (info->containsComponentDetails("Player")) {
                player = i;

                auto mvcmpt = i->GetComponent<MoveCmpt>();
                if (mvcmpt != nullptr) {
                    sf::Vector2f spawnPos = { 0,0 };
                    spawnPos.x = map.mapSize[0] / 2;
                    spawnPos.y = map.mapSize[1] / 2;
                    //std::cout << "Setting player tile pos: " << spawnPos.x << ", " << spawnPos.y << std::endl;
                    mvcmpt->setPositionTile(spawnPos);
                    auto sprCmpt = i->GetComponent<spriteCmpt>();
                    if (sprCmpt != nullptr)
                        sprCmpt->setPosition(mvcmpt->getPosition());

                    mvcmpt->updatePosition({ 0,0 }, map);
                }
            }   
        }
    }
}
void Game::Update(){
    sf::Time time = clock.restart();
    dt = time.asSeconds();
    if (firstRun) {
        Start();
        firstRun = false;
    }
    

    for (auto& i : m_gameObjects)
    {
        auto info = i->GetComponent<ReadableInfoCMPT>();
        if (info != nullptr) {
            if(info->containsComponentDetails("Player")){
                if (i->isactive == false) {
                    i->isactive = true;
                    if (wave > highscore) {
                        highscore = wave;
                    }
                    Reset();
                    return;
                }
                playerHealth = i->GetComponent<HealthCmpt>()->getHealth();
                playerHealthText.setString("Health: "+ std::to_string(playerHealth));
            
            }
        }

        if (i->isactive == false) continue;
        auto wpncmpt = i->GetComponent<WeaponCmpt>();
        if (wpncmpt != nullptr) {
            wpncmpt->Update(dt,m_gameObjects);
        }

        auto aicmpt = i->GetComponent<AICompt>();
        if (aicmpt != nullptr) {
            aicmpt->Update(dt, player, map);
        }

        auto managerCmpt = i->GetComponent<EnemyManagerCmpt>();
        if (managerCmpt != nullptr) {
            managerCmpt->Update(dt, m_gameObjects, map);
            wave = managerCmpt->getWave();
            waveText.setString("Wave: " + std::to_string(wave));
        }
    }
    
    
	m_window.Update();
}


void Game::Reset() {
    firstRun = true;
    for (auto& i : m_gameObjects)
    {
        auto wpncmpt = i->GetComponent<WeaponCmpt>();
        if (wpncmpt != nullptr) {
            wpncmpt->Reset();
        }

        auto healthcmpt = i->GetComponent<HealthCmpt>();
        if (healthcmpt != nullptr) {
            healthcmpt->setHealth(100);
        }

        auto managerCmpt = i->GetComponent<EnemyManagerCmpt>();
        if (managerCmpt != nullptr) {
            managerCmpt->Reset();
        }
        
        auto info = i->GetComponent<ReadableInfoCMPT>();
        if (info == nullptr)continue;
        if (info->containsComponentDetails("Enemy")) {
            i->isactive = false;
        }
    }
    isPlaying = false;
}
void Game::Render(){
	m_window.BeginDraw();
	// Render here.
    map.draw(m_window.GetRenderWindow());
    //m_window.GetRenderWindow()->draw();
    for (auto& i : m_gameObjects)
    {
        if (i->isactive == false) continue;
        auto sprCmpt = i->GetComponent<spriteCmpt>();
        auto moveCmpt = i->GetComponent<MoveCmpt>();
        if (sprCmpt != nullptr && moveCmpt != nullptr)    
            sprCmpt->setPosition(moveCmpt->getPosition());
            

        if (sprCmpt != nullptr) {
            sprCmpt->Draw(*m_window.GetRenderWindow(), 0.01);
            
        }

        auto wpncmpt = i->GetComponent<WeaponCmpt>();
        if (wpncmpt != nullptr) {
            wpncmpt->Draw(*m_window.GetRenderWindow(),map);
        }
        
    }

    m_window.GetRenderWindow()->draw(playerHealthText);
    m_window.GetRenderWindow()->draw(waveText);

	m_window.EndDraw();


}

void Game::MainMenu() {
    sf::Event event;

    while (m_window.GetRenderWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.GetRenderWindow()->close();
    }
    m_window.GetRenderWindow()->clear();
    sf::Vector2i localMousePosition = sf::Mouse::getPosition(*m_window.GetRenderWindow());
  
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouseReleased = true;
    }
    
    if (menuState == 0) {
        highscoreText.setString("Highscore: "+std::to_string(highscore));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseReleased)
        {   
            mouseReleased = false;
            if (levelSelectButton.isPressed(localMousePosition)) {
                //std::cout << "menu state 1" << std::endl;
                menuState = 1;
            }

            if (exitButton.isPressed(localMousePosition)) {
               //sf::Vector2u widthAndHeight(mapsize, mapsize), tileSize(tilesizeX, tilesizeY);
               
                nlohmann::json jsonFile;

                jsonFile["highscore"] = highscore;


                std::ofstream file("resources/data/highscore.json");
                file << jsonFile;
                file.close();
                m_window.Finish();
            }
        }
        m_window.GetRenderWindow()->draw(banner);
        m_window.GetRenderWindow()->draw(highscoreText);
        exitButton.draw(m_window.GetRenderWindow());
        levelSelectButton.draw(m_window.GetRenderWindow());
    }
    if (menuState == 1) {
        sf::Time time = clock.restart();
        dt = time.asSeconds();
        timeSinceTextEntered += dt;
        if (event.type == sf::Event::TextEntered)
			{
            if (timeSinceTextEntered > timeBetweenTextEnter) {
                timeSinceTextEntered = 0;
                if (event.text.unicode == '\b') { // handle backspace explicitly
                    if (customLevel.displayText.size() > 0) {
                        customLevel.displayText.erase(customLevel.displayText.size() - 1, 1);
                    }
                }
                else {
                    customLevel.displayText += event.text.unicode;
                }
                customLevel.UpdateDisplayText();
                }
			}

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseReleased)
        {
            mouseReleased = false;
            if (level1Button.isPressed(localMousePosition)) {
                map.Load("1bblevel1");
                isPlaying = true;
                menuState = 0;
            }

            if (level2Button.isPressed(localMousePosition)) {
                map.Load("1bblevel2");
                isPlaying = true;
                menuState = 0;
            }
            if (exitButton.isPressed(localMousePosition)) {
                menuState = 0;
            }
            if (customLevel.isPressed(localMousePosition)) {
                if (map.Load(customLevel.displayText)) {
                    isPlaying = true;
                    menuState = 0;
                }
            }
        }

        exitButton.draw(m_window.GetRenderWindow());
        level1Button.draw(m_window.GetRenderWindow());
        level2Button.draw(m_window.GetRenderWindow());
        customLevel.draw(m_window.GetRenderWindow());
    }
    m_window.GetRenderWindow()->display();
}
