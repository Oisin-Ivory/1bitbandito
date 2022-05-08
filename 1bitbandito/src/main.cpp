#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


#include "Object.hpp"
#include "components/component.hpp"
#include "components/GraphicsCmpt.hpp"
#include "components/spriteCmpt.hpp"
#include "components/AnimatedSpriteCmpt.hpp"
#include "components/MoveCmpt.hpp"
#include "components/HealthCmpt.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "components/inputControllerCmpt.hpp"
#include "components/ReadableInfoCMPT.hpp"
#include "components/WeaponCmpt.hpp"
#include "components/AICompt.hpp"
#include "components/EnemyManagerCmpt.hpp"



int main(int, char const**)
{
    srand(time(NULL));
    Object player;
    player.AttachComponent<ReadableInfoCMPT>();
    player.AttachComponent<spriteCmpt>();
    player.GetComponent<ReadableInfoCMPT>()->addComponentDetails("spriteCmpt");
    
    player.GetComponent<spriteCmpt>()->setPosition(sf::Vector2f (0,0));
    player.AttachComponent<MoveCmpt>(sf::Vector2f (10,10));
    player.GetComponent<ReadableInfoCMPT>()->addComponentDetails("MoveCmpt");

    player.AttachComponent<WeaponCmpt>();


    player.AttachComponent<inputControllerCmpt>();
    player.GetComponent<ReadableInfoCMPT>()->addComponentDetails("inputControllerCmpt");

    player.AttachComponent<HealthCmpt>();
    player.GetComponent<ReadableInfoCMPT>()->addComponentDetails("HealthCmpt");
    player.GetComponent<ReadableInfoCMPT>()->addComponentDetails("Player");


    auto tempTextureID = TextureManager::AddTexture("resources/player/bandit.png");
    if (tempTextureID == -1)
    {
      std::cout<<"couldn't add texture to player sprite component\n";
      exit(0);
    }
    auto sprcmpt = player.GetComponent<spriteCmpt>();
    sprcmpt->setTexture(TextureManager::GetTexture(tempTextureID));
    sprcmpt->setPosition(sf::Vector2f(10,5));
    
    
    
    int maxNumOfEnemies = 50;

    Object enemyManager;
    enemyManager.AttachComponent<EnemyManagerCmpt>(maxNumOfEnemies);
    enemyManager.AttachComponent<ReadableInfoCMPT>();
    enemyManager.GetComponent<ReadableInfoCMPT>()->addComponentDetails("Manager");
   
    
    
  
    
    
    
    Game game;
    for (int i = 0; i < maxNumOfEnemies; i++) {
        Object* Enemy = new(Object);
        Enemy->AttachComponent<ReadableInfoCMPT>();
        Enemy->AttachComponent<spriteCmpt>();
        Enemy->AttachComponent<AICompt>();
        Enemy->AttachComponent<WeaponCmpt>();

        Enemy->GetComponent<ReadableInfoCMPT>()->addComponentDetails("spriteCmpt");

        Enemy->GetComponent<spriteCmpt>()->setPosition(sf::Vector2f(0, 0));
        Enemy->AttachComponent<MoveCmpt>(sf::Vector2f(30, 10));
        Enemy->GetComponent<ReadableInfoCMPT>()->addComponentDetails("MoveCmpt");

        Enemy->AttachComponent<HealthCmpt>();
        Enemy->GetComponent<ReadableInfoCMPT>()->addComponentDetails("HealthCmpt");
        Enemy->GetComponent<ReadableInfoCMPT>()->addComponentDetails("Enemy");

        std::string filename("Resources/enemies/law.png");
        tempTextureID = TextureManager::AddTexture(filename);
        if (tempTextureID == -1)
        {
            std::cout << "couldn't add texture to player sprite component\n";
            exit(0);
        }
        auto sprcmpt1 = Enemy->GetComponent<spriteCmpt>();
        sprcmpt1->setTexture(TextureManager::GetTexture(tempTextureID));
        sprcmpt1->setPosition(sf::Vector2f(40, 20));
        Enemy->GetComponent<MoveCmpt>()->setPosition({ 40,50 });

        auto enemyAI = Enemy->GetComponent<AICompt>();
        enemyAI->SetMoveCmpt(Enemy->GetComponent<MoveCmpt>());
        enemyAI->SetWeaponCmpt(Enemy->GetComponent<WeaponCmpt>());
        Enemy->isactive = false;
        game.AddObject(Enemy);
    }

    game.AddObject(&enemyManager);
    game.AddObject(&player);
    
    while(!game.GetWindow()->IsDone()){
        if(game.isPlaying){
            game.HandleInput();
            game.Update();
            game.Render();
            game.RestartClock();
        }
        else {
            game.MainMenu();
        }
    }
    
    
    return EXIT_SUCCESS;
}
