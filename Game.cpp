
#include "Game_Assets.hpp"

using namespace sf;
using namespace std;

bool Game::isBossAlive() {
    for (Entity* entity : *manager->getEntityList()[manager->ENEMY]) {
        if (entity->getIsBoss()) { return true; }
    }
    return false;
}

Game::Game() {
    inputMovement = Vector2f(0.f, 0.f);
    cout << "\nnew game\n";
    //title and chrono
    fontTitle.loadFromFile("Fonts/race-space/RACESPACESTRIPE.ttf");
    title.setFont(fontTitle); title.setCharacterSize(80); title.setString("BATTLESKY"); title.setFillColor(Color(0, 222, 222, 255));
    title.setOrigin(Vector2f(250.f, 40.f)); title.setPosition(Vector2f(screenWidth / 2, 100.f));
    chronoText.setFont(fontMain); chronoText.setCharacterSize(22);
    chronoText.setPosition(Vector2f(15.f, 80.f));
    //sounds
    shootSoundBuffer.loadFromFile("SoundEffects/futuristic-gun-shot-sci-fi.wav");
    shootSound.setBuffer(shootSoundBuffer); shootSound.setVolume(8.f);
    shootEnemySB.loadFromFile("SoundEffects/sci-fi-weapon-shoot-firing-plasma.mp3");
    shootEnemy.setBuffer(shootEnemySB); shootEnemy.setVolume(10.f);
    explosionSound.setBuffer(explosionSB); explosionSound.setVolume(8.f);
    musicSB.loadFromFile("SoundEffects/Sci-Fi Music Pack/Loops/mp3/Sci-Fi 8 Loop.mp3");
    music.setBuffer(musicSB); music.setVolume(10.f); music.setLoop(true);
    uiSB.loadFromFile("SoundEffects/SCI-FI_UI_SFX_PACK/SCI-FI_UI_SFX_PACK/Tone1/Basic Tones/Tone1B.wav");
    uiSound.setBuffer(uiSB); uiSound.setVolume(10.f);
    uiClicSB.loadFromFile("SoundEffects/SCI-FI_UI_SFX_PACK/SCI-FI_UI_SFX_PACK/Tone1/Basic Tones/Tone1A.wav");
    uiClicSound.setBuffer(uiClicSB); uiClicSound.setVolume(10.f);
    menuMusicSB.loadFromFile("SoundEffects/Sci-Fi Music Pack Vol. 2/Tracks/wav/6 - Orbital Echoes.wav");
    menuMusic.setBuffer(menuMusicSB); menuMusic.setVolume(10.f); menuMusic.setLoop(true);
    //Dash
    dashIconGreenTexture.loadFromFile("Images/DashIconGreen.png"); dashIconRedTexture.loadFromFile("Images/DashIconRed.png");
    dashIcon.setTexture(dashIconRedTexture); dashIcon.setOrigin(Vector2f(dashIconGreenTexture.getSize()) / 2.f); dashIcon.setScale(Vector2f(1.5f, 1.5f));
    dashIcon.setPosition(Vector2f(screenWidth / 2, screenHeight - dashIcon.getGlobalBounds().height / 1.5f));
    dashArrowGreenTexture.loadFromFile("Images/dashArrowGreen.png"); dashArrowRedTexture.loadFromFile("Images/dashArrowRed.png");
    dashArrowGreenTexture.setSmooth(true); dashArrowRedTexture.setSmooth(true);
    dashArrow.setTexture(dashArrowRedTexture); dashArrow.setScale(Vector2f(1.3f, 1.3f));
    Vector2f center = Vector2f(dashArrowGreenTexture.getSize()) / 2.f;
    dashArrow.setOrigin(center.x, center.y + 40);
    //score
    fontMain.loadFromFile("Fonts/space-crusaders-cufonfonts/SpaceCrusaders-x3DP0.ttf");
    score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
    score.setFont(fontMain);
    score.setCharacterSize(40); score.setFillColor(Color(255, 255, 255, 220));
    score.setOrigin(Vector2f(100.f, 10.f));
    score.setPosition(Vector2f(screenWidth / 1.2, screenHeight / 1.13));
    //title screen buttons
        //play button
    playButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Start_BTN.png"); playButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Start_BTN_on.png");
    playButtonOffTexture.setSmooth(true); playButtonOnTexture.setSmooth(true);
    playButton.setTexture(playButtonOffTexture); playButton.setOrigin(Vector2f(playButtonOffTexture.getSize()) / 2.f); playButton.setPosition(Vector2f(float(screenWidth / 2), 410.f));
        //exit button
    exitButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Exit_BTN.png"); exitButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Exit_BTN_on.png");
    exitButtonOffTexture.setSmooth(true); exitButtonOnTexture.setSmooth(true);
    exitButton.setTexture(exitButtonOffTexture); exitButton.setOrigin(Vector2f(exitButtonOffTexture.getSize()) / 2.f); exitButton.setPosition(Vector2f(float(screenWidth / 2), 650.f));
        //class choice
    arrowButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs/Backward_BTN.png"); arrowButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Backward_BTN.png");
    arrowButtonOffTexture.setSmooth(true); arrowButtonOnTexture.setSmooth(true);
        //left arrow
    arrowButtonLeft.setTexture(arrowButtonOffTexture); arrowButtonLeft.setOrigin(Vector2f(arrowButtonOffTexture.getSize()) / 2.f);
    arrowButtonLeft.setPosition(Vector2f(float(screenWidth / 10), 270.f)); arrowButtonLeft.setScale(0.5, 0.5);
        //right arrow
    arrowButtonRight.setTexture(arrowButtonOffTexture); arrowButtonRight.setOrigin(Vector2f(arrowButtonOffTexture.getSize()) / 2.f);
    arrowButtonRight.setPosition(Vector2f(float(screenWidth / 10 * 9), 270.f)); arrowButtonRight.setScale(0.5, 0.5); arrowButtonRight.rotate(180.f);
         //ship class icon
    currentPlayerIcon.setTexture(playerShipYellowTexture); currentPlayerIcon.setOrigin(Vector2f(playerShipYellowTexture.getSize()) / 2.f);
    currentPlayerIcon.setPosition(Vector2f(float(screenWidth / 6 * 2), 265.f)); currentPlayerIcon.setScale(2.5, 2.5);
    classDescription.setString("Life\nDamage\nAttack Speed"); classDescription.setCharacterSize(20); classDescription.setFont(fontMain);  classDescription.setPosition(Vector2f(float(screenWidth / 7 * 3), 225));
    classDescriptionStats1.setString("  ++\n  ++++\n  ++"); classDescriptionStats1.setCharacterSize(20); classDescriptionStats1.setFont(fontMain);  classDescriptionStats1.setPosition(Vector2f(float(screenWidth / 8 * 5), 225));
    classDescriptionStats2.setString("  ++++\n  ++\n  ++"); classDescriptionStats2.setCharacterSize(20); classDescriptionStats2.setFont(fontMain);  classDescriptionStats2.setPosition(Vector2f(float(screenWidth / 8 * 5), 225));
    classDescriptionStats3.setString("  ++\n  ++\n  ++++"); classDescriptionStats3.setCharacterSize(20); classDescriptionStats3.setFont(fontMain);  classDescriptionStats3.setPosition(Vector2f(float(screenWidth / 8 * 5), 225));
    //pause menu
    float pauseMenuOffset = 150.f;
    pauseHeaderTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Header.png");
    pauseHeader.setTexture(pauseHeaderTexture); pauseHeader.setOrigin(Vector2f(pauseHeaderTexture.getSize().x / 2, 0.f)); pauseHeader.setPosition(Vector2f(float(screenWidth / 2), 8.f + pauseMenuOffset));
    pauseBgTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Window.png");
    pauseBg.setTexture(pauseBgTexture); pauseBg.setColor(Color(255, 255, 255, 220));
    pauseBg.setOrigin(Vector2f(pauseBgTexture.getSize().x / 2, 0.f)); pauseBg.setScale(Vector2f(0.55f, 0.5f)); pauseBg.setPosition(Vector2f(float(screenWidth / 2), pauseMenuOffset));
        //menu button
    menuButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Menu_BTN.png"); menuButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Menu_BTN.png");
    menuButton.setTexture(menuButtonOffTexture); menuButton.setOrigin(Vector2f(menuButtonOffTexture.getSize()) / 2.f); menuButton.setScale(Vector2f(0.4f, 0.4f)); menuButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 150.f + pauseMenuOffset));
    menuText.setString("MAIN MENU"); menuText.setFont(fontMain); menuText.setCharacterSize(40); menuText.setOrigin(Vector2f(0.f, 30.f)); menuText.setPosition(menuButton.getPosition() + Vector2f(60.f, 0.f));
        //resume button
    resumeButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs/Play_BTN.png"); resumeButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Play_BTN.png");
    resumeButton.setTexture(resumeButtonOffTexture); resumeButton.setOrigin(Vector2f(resumeButtonOffTexture.getSize()) / 2.f); resumeButton.setScale(Vector2f(0.4f, 0.4f)); resumeButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 250.f + pauseMenuOffset));
    resumeText.setString("RESUME"); resumeText.setFont(fontMain); resumeText.setCharacterSize(40); resumeText.setOrigin(Vector2f(0.f, 30.f)); resumeText.setPosition(resumeButton.getPosition() + Vector2f(60.f, 0.f));
        //exit button
    pauseExitButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs/Close_BTN.png"); pauseExitButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Close_BTN.png");
    pauseExitButton.setTexture(pauseExitButtonOffTexture); pauseExitButton.setOrigin(Vector2f(pauseExitButtonOffTexture.getSize()) / 2.f); pauseExitButton.setScale(Vector2f(0.4f, 0.4f)); pauseExitButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 350.f + pauseMenuOffset));
    pauseExitText.setString("CLOSE GAME"); pauseExitText.setFont(fontMain); pauseExitText.setCharacterSize(40); pauseExitText.setOrigin(Vector2f(0.f, 30.f)); pauseExitText.setPosition(pauseExitButton.getPosition() + Vector2f(60.f, 0.f));
        //admin button
    adminButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Upgrade/admin_BTN_off.png"); adminButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Upgrade/admin_BTN_on.png");
    adminButtonOffTexture.setSmooth(true); adminButtonOnTexture.setSmooth(true);
    adminButton.setTexture(adminButtonOffTexture); adminButton.setOrigin(Vector2f(adminButtonOffTexture.getSize()) / 2.f); adminButton.setScale(Vector2f(0.6f, 0.6f)); adminButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 450.f + pauseMenuOffset));
    adminText.setString("ADMIN\nPROTECTION"); adminText.setFont(fontMain); adminText.setCharacterSize(40); adminText.setOrigin(Vector2f(0.f, 60.f)); adminText.setPosition(adminButton.getPosition() + Vector2f(60.f, 0.f));
    //health and death
    hpText.setFont(fontMain); hpText.setCharacterSize(30); hpText.setPosition(Vector2f(20.f, float(screenHeight - 50))); hpText.setFillColor(Color(157, 217, 146));
    hpBarTexture10.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_UI/Health_Bar_Table_10.png");
    hpBarTexture5.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_UI/Health_Bar_Table_5.png");
    hpBar.setTexture(hpBarTexture10); hpBar.setColor(Color(255,255,255, 220)); hpBar.setPosition(hpText.getPosition() + Vector2f(100.f, 0.f)); hpBar.setScale(Vector2f(0.5f, 0.5f));


    hpDotTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_UI/Health_Dot.png");
    hpDot.setTexture(hpDotTexture); hpDot.setColor(Color(255,255,255, 220)); hpDot.setScale(Vector2f(0.5f, 0.5f));
    hpBonusText.setFont(fontMain); hpBonusText.setCharacterSize(25); hpBonusText.setPosition(hpText.getPosition() - Vector2f(-10.f, 20.f));
    hpBonusText.setString("+1"); hpBonusText.setFillColor(Color(20, 180, 200));
    deathText.setFont(fontMain); deathText.setString("YOU DIED"); deathText.setCharacterSize(60); deathText.setFillColor(Color(150, 10, 10));
    deathText.setOrigin(Vector2f(100.f, 10.f)); deathText.setPosition(pauseExitText.getPosition() + Vector2f(50.f, -130));
    table.loadFromFile("Images/Space_Game_GUI_PNG/PNG/You_Lose/Table.png"); table.setSmooth(true);
    bossHpTableTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Loading_Bar/Table.png");
    //background
    backgroundTexture.loadFromFile("Images/space_background_pack/Assets/Blue Version/layered/blue-with-stars.png");
    backgroundAlienTexture.loadFromFile("Images/pixelart_circuit_board_background2.png");
    backgroundNautolanTexture.loadFromFile("Images/backgroundNautolan.gif");
    backgroundPlanetTexture1.loadFromFile("Images/space_background_pack/Assets/Blue Version/layered/prop-planet-big.png");
    backgroundBlackHoleTexture.loadFromFile("Images/Planets/Black_hole.png");
    backgroundAlienBaseTexture.loadFromFile("Images/techybg-fixed-and-updated-alpha.png");
    backgroundAsteroidTexture1.loadFromFile("Images/space_background_pack/Assets/Blue Version/layered/asteroid-1.png");
    backgroundAsteroidTexture2.loadFromFile("Images/space_background_pack/Assets/Blue Version/layered/asteroid-2.png");
    backgroundWaterBubbleTexture.loadFromFile("Images/water_bubble.png");

    interludeStartText.setFont(fontMain); interludeStartText.setCharacterSize(35);
    interludeStartText.setString("        STAGE CLEARED!\nmove forward to continue");
    interludeStartText.setOrigin(Vector2f(180, 0)); interludeStartText.setPosition(Vector2f(screenWidth / 2 - interludeStartText.findCharacterPos(33).x, 60));
    interludeStartText.setFillColor(Color(255, 255, 255, 0));
    
    screenEffect.setFillColor(Color(255, 255, 255, 0));
    //cursor
    cursorTexture.loadFromFile("Images/CoB_cursor/Layer 1_sprite_1.png");
    cursor.setTexture(cursorTexture);
    cursor.setOrigin(Vector2f(7.f, 7.f));
    cursor.setScale(Vector2f(2.f, 2.f));
    //volume bar
    volumeBar.setSize(Vector2f(150, 8));
    volumeIndicator.setSize(Vector2f(15, 30));
    volumeBar.setFillColor(Color(150, 150, 150)); volumeIndicator.setFillColor(Color(210, 210, 210));
    volumeBar.setOrigin(static_cast<Vector2f>(volumeBar.getSize()) / 2.f); volumeIndicator.setOrigin(static_cast<Vector2f>(volumeIndicator.getSize()) / 2.f);
    volumeBar.setPosition(Vector2f(screenWidth - volumeBar.getSize().x, 30)); volumeIndicator.setPosition(volumeBar.getPosition());
    cout << "\nend of game constructor\n";
}

void Game::userInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
            isPauseMenu = true;
        }
        else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
    }
    inputMovement = Vector2f(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Scancode::W)) {
        inputMovement += Vector2f(0.f, -1.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Scancode::S)) {
        inputMovement += Vector2f(0.f, 1.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Scancode::D)) {
        inputMovement += Vector2f(1.2f, 0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Scancode::A)) {
        inputMovement += Vector2f(-1.2f, 0.f);
    }
    if (dashCooldown > 3) {
        dashIcon.setTexture(dashIconGreenTexture);
        dashArrow.setTexture(dashArrowGreenTexture);
        if (Keyboard::isKeyPressed(Keyboard::LShift)) {
            dashCooldown = 0;
            dashIcon.setTexture(dashIconRedTexture);
            dashArrow.setTexture(dashArrowRedTexture);
            Vector2i posMouse = Mouse::getPosition(window);
            float distX = posMouse.x - player.getPos().x;
            float distY = posMouse.y - player.getPos().y;

            float distance = sqrt(distX * distX + distY * distY);
            float distanceMax = 120;

            if (distance <= distanceMax) {
                player.getSprite()->setPosition(Vector2f(posMouse.x, posMouse.y));
            }
            else {
                float directionX = (posMouse.x - player.getPos().x) / distance;
                float directionY = (posMouse.y - player.getPos().y) / distance;

                player.getSprite()->setPosition(
                    player.getPos().x + directionX * distanceMax,
                    player.getPos().y + directionY * distanceMax);
            }
        }
    }
    if ((Keyboard::isKeyPressed(Keyboard::Space) or Mouse::isButtonPressed(Mouse::Left))) {
        playerPreviousSpeed = player.getSpeed();
        player.setSpeed(player.getSpeed() * 0.75f);
        if (shootCooldown.getElapsedTime().asSeconds() > player.getFrameRate()) {
            for (int i = 0; i < player.getAmmoAmount(); i++) {
                Ammo* ammoAdded = manager->addAmmo(player.getLinkedAmmoTexture(), Vector2f(player.getPos().x, player.getUp()), player.getAmmoDirections()[i], player.getWeaponDamage());
                ammoAdded->setColor(playerAmmoColor.r, playerAmmoColor.g, playerAmmoColor.b);
            }
            shootCooldown.restart();
            shootSound.play();
        }
    }
}

void Game::update() {
    Time timeSinceLastFrame = mainClock.restart() - menuTime;
    chronoDecrease += menuTime.asSeconds();

    if (isInterlude) {
        player.move(Vector2f(0,1) * timeSinceLastFrame.asSeconds() * 0.5f);
    }
    if (isInterlude and interludeChrono < 1.6f) { inputMovement = Vector2f(inputMovement.x, 0.5f); }
    player.move(inputMovement * timeSinceLastFrame.asSeconds());
    player.setSpeed(playerPreviousSpeed);

    if (player.getLeft() > screenWidth) { player.setX(0.f); }
    if (player.getRight() < 0) { player.setX(screenWidth); }
    if (player.getUp() < 0) { player.setY(player.getHeight() / 2.f + 0.5f); }
    float bottomLimit = screenHeight - 120.f;
    if (player.getDown() > bottomLimit) { player.setY(bottomLimit - player.getHeight() / 2.f - 0.5f); }
    player.addToHurtTime(timeSinceLastFrame.asSeconds());
    if (player.getHurtTime() >= 0.3f) { player.setColor(255, 255, 255); }
    else if (player.getHurtTime() >= 0.15f) { player.getSprite()->setColor(player.getSprite()->getColor() - Color(0,0,0, 20)); }

    //dash arrow position update
    dashArrow.setPosition(player.getPos());
    //arrow angle
    Vector2i mousePosition = Mouse::getPosition(window);
    float deltaX = mousePosition.x - player.getPos().x;
    float deltaY = mousePosition.y - player.getPos().y;
    float angle = atan2(deltaY, deltaX);
    float angleDeg = angle * 180 / 3.14159f;
    dashArrow.setRotation(angleDeg + 90);

    for (int i = 0; i < (*manager->getBackgroundPropList())[manager->PLANET]->size(); i++) {
        SFX* planet = (*(*manager->getBackgroundPropList())[manager->PLANET])[i];
        Sprite* sprite = planet->getSprite();
        sprite->move(Vector2f(0, 1) * timeSinceLastFrame.asSeconds() * 50.f * meteorSpeed);
        if (!planet->getIsOffMap() and (sprite->getGlobalBounds().top + sprite->getGlobalBounds().height) > screenHeight) {
            BackgroundProp* newPlanet = manager->addBackgroundProp(manager->PLANET, Vector2f(sprite->getPosition().x, sprite->getGlobalBounds().height / -2), sprite->getScale().x, planet->getType());
            newPlanet->getSprite()->setColor(planet->getSprite()->getColor());
            planet->setIsOffMap(true);
        }
        if (sprite->getGlobalBounds().top > screenHeight) {
            delete planet;
            auto pos = find((*manager->getBackgroundPropList())[manager->PLANET]->begin(), (*manager->getBackgroundPropList())[manager->PLANET]->end(), planet);
            (*manager->getBackgroundPropList())[manager->PLANET]->erase(pos);
        }
    }
    for (int i = 0; i < (*manager->getBackgroundPropList())[manager->ASTEROID]->size(); i++) {
        SFX* astero = (*(*manager->getBackgroundPropList())[manager->ASTEROID])[i];
        Sprite* sprite = astero->getSprite();
        sprite->move(Vector2f(0, 1) * timeSinceLastFrame.asSeconds() * 200.f * meteorSpeed);
        if (!astero->getIsOffMap() and sprite->getGlobalBounds().top + sprite->getGlobalBounds().height > screenHeight) {
            BackgroundProp* newAstero = manager->addBackgroundProp(manager->ASTEROID, Vector2f(sprite->getPosition().x, sprite->getGlobalBounds().height / -2), sprite->getScale().x, astero->getType());
            newAstero->getSprite()->setColor(astero->getSprite()->getColor());
            astero->setIsOffMap(true);
        }
        if (sprite->getGlobalBounds().top > screenHeight) {
            delete astero;
            auto pos = find((*manager->getBackgroundPropList())[manager->ASTEROID]->begin(), (*manager->getBackgroundPropList())[manager->ASTEROID]->end(), astero);
            (*manager->getBackgroundPropList())[manager->ASTEROID]->erase(pos);
        }
    }
    enemiesSpawnCooldownNum += timeSinceLastFrame.asSeconds();
    bonusCooldownNum += timeSinceLastFrame.asSeconds();
    timeInRay += timeSinceLastFrame.asSeconds();
    meteorCooldownChrono += timeSinceLastFrame.asSeconds();
    dashCooldown += timeSinceLastFrame.asSeconds();

    if (scoreNum < 10) {
        if (enemiesSpawnCooldownNum >= 7 and manager->getEntityList()[manager->ENEMY]->size() < 8) {
            for (int i = 0; i < 3; i++) {
                if (manager->getEntityList()[manager->ENEMY]->size() < 8) {
                    int randType = rand() % 100;
                    if (randType < 65) { manager->addEnemy(manager->BASIC_SHIP); }
                    else { manager->addEnemy(manager->SPEC_SHIP); }
                }
            }
            enemiesSpawnCooldownNum = 0;
        }
    }
    else if (scoreNum < 20) {
        if (enemiesSpawnCooldownNum >= 6 and manager->getEntityList()[manager->ENEMY]->size() < 10) {
            for (int i = 0; i < 4; i++) {
                if (manager->getEntityList()[manager->ENEMY]->size() < 10) {
                    int randType = rand() % 100;
                    if (randType < 40) { manager->addEnemy(manager->BASIC_SHIP); }
                    else if (randType < 70) { manager->addEnemy(manager->SPEC_SHIP); }
                    else { manager->addEnemy(manager->DOUBLE_BARREL_SHIP); }
                }
            }
            enemiesSpawnCooldownNum = 0;
        }
    }
    else if (waveCount == 3) {
        if (isBossAlive()) {
            if (enemiesSpawnCooldownNum >= 6 and manager->getEntityList()[manager->ENEMY]->size() < 6) {
                for (int i = 0; i < 2; i++) {
                    if (manager->getEntityList()[manager->ENEMY]->size() < 6) {
                        manager->addEnemy(manager->DOUBLE_BARREL_SHIP);
                    }
                }
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (manager->getEntityList()[manager->ENEMY]->size() == 0) {
            if (!isInterlude) {
                interludeStartText.setFillColor(Color(255, 255, 255, 200));
                if (player.getPos().y < 100) {
                    isInterlude = true;
                    player.setSpeed(player.getSpeed() * 1.25f);
                    meteorSpeed = 2.5f;
                    interludeChrono = 0;
                    interludeStartText.setFillColor(Color(255, 255, 255, 0));
                }
            }
            else {
                interludeChrono += timeSinceLastFrame.asSeconds();
                if (interludeChrono > 2.f) { meteorProb = 80; }
                if (interludeChrono > 15.f) {
                    meteorProb = 0;
                    shade += 100.f * timeSinceLastFrame.asSeconds();
                    screenEffect.setFillColor(Color(255, 255, 255, int(shade)));
                    if (int(shade) == 255) {
                        player.getSprite()->setPosition(Vector2f(screenWidth / 2.f, screenHeight * 0.75f));
                        background.setTexture(backgroundAlienTexture);
                        background.setColor(Color(100, 255, 150));
                        background.setOrigin(Vector2f(backgroundAlienTexture.getSize()) / 2.f);
                        background.setScale(Vector2f(screenHeight / backgroundAlienTexture.getSize().y, screenHeight / backgroundAlienTexture.getSize().y));
                        background.setPosition(Vector2f(screenWidth / 2, screenHeight / 2));
                        for (SFX* planet : *(*manager->getBackgroundPropList())[manager->PLANET]) {
                            delete planet;
                        }
                        (*manager->getBackgroundPropList())[manager->PLANET]->clear();
                        for (SFX* astero : *(*manager->getBackgroundPropList())[manager->ASTEROID]) {
                            delete astero;
                        }
                        (*manager->getBackgroundPropList())[manager->ASTEROID]->clear();
                        waveCount = 4;
                    }
                }
            }
        }
    }
    else if (waveCount == 4) {
        if (isInterlude) {
            for (int i = 0; i < 5; i++) {
                BackgroundProp* propLeft = manager->addBackgroundProp(manager->PLANET, Vector2f(screenWidth * (1.f/4.f), 0), (screenWidth / backgroundAlienBaseTexture.getSize().x / 2), manager->ALIENBASE);
                BackgroundProp* propRight = manager->addBackgroundProp(manager->PLANET, Vector2f(screenWidth * (3.f/4.f), 0), (screenWidth / backgroundAlienBaseTexture.getSize().x / 2), manager->ALIENBASE);
                propLeft->getSprite()->move(Vector2f(0, propLeft->getSprite()->getGlobalBounds().height / 2.f + propLeft->getSprite()->getGlobalBounds().height * i));
                propRight->getSprite()->move(Vector2f(0, propLeft->getSprite()->getGlobalBounds().height / 2.f + propLeft->getSprite()->getGlobalBounds().height * i));
            }
            player.setSpeed(player.getSpeed() / 1.25f);
            meteorSpeed = 1.f;
            obstacleTexture = alienDebrisTexture;
            isInterlude = false;
        }
        if (int(shade) > 0) {
            shade -= 100.f * timeSinceLastFrame.asSeconds();
            screenEffect.setFillColor(Color(255, 255, 255, int(shade)));
        }
        else {
            shade = 0;
            meteorProb = 10;
            if (enemiesSpawnCooldownNum >= 2 and manager->getEntityList()[manager->ENEMY]->size() == 0) {
                for (int i = 0; i < 6; i++) {
                    manager->addEnemy(manager->ALIEN_SHIP);
                }
                enemiesSpawnCooldownNum = 0;
            }
        }
    }
    if (waveCount == 5) {
        if (enemiesSpawnCooldownNum >= 5 and manager->getEntityList()[manager->ENEMY]->size() < 8) {
            for (int i = 0; i < 2; i++) {
                if (manager->getEntityList()[manager->ENEMY]->size() < 8) {
                    int randType = rand() % 100;
                    if (randType < 65) { manager->addEnemy(manager->ALIEN_SHIP); }
                    else { manager->addEnemy(manager->SPEC_SHIP); }
                }
            }
            enemiesSpawnCooldownNum = 0;
        }
    }
    if (waveCount == 6) {
        if (isBossAlive()) {
            if (enemiesSpawnCooldownNum >= 4 and manager->getEntityList()[manager->ENEMY]->size() < 5) {
                for (int i = 0; i < 1; i++) {
                    if (manager->getEntityList()[manager->ENEMY]->size() < 5) {
                        int randType = rand() % 100;
                        if (randType < 65) { manager->addEnemy(manager->ALIEN_SHIP); }
                        else { manager->addEnemy(manager->SPEC_SHIP); }
                    }
                }
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (manager->getEntityList()[manager->ENEMY]->size() == 0) {
            if (!isInterlude) {
                interludeStartText.setFillColor(Color(255, 255, 255, 200));
                if (player.getPos().y < 100) {
                    isInterlude = true;
                    player.setSpeed(player.getSpeed() * 1.25f);
                    meteorSpeed = 2.5f;
                    interludeChrono = 0;
                    interludeStartText.setFillColor(Color(255, 255, 255, 0));
                }
            }
            else {
                interludeChrono += timeSinceLastFrame.asSeconds();
                if (interludeChrono > 2.f) { meteorProb = 80; }
                if (interludeChrono > 15.f) {
                    meteorProb = 0;
                    shade += 100.f * timeSinceLastFrame.asSeconds();
                    screenEffect.setFillColor(Color(255, 255, 255, int(shade)));
                    if (int(shade) == 255) {
                        player.getSprite()->setPosition(Vector2f(screenWidth / 2.f, screenHeight * 0.75f));
                        background.setTexture(backgroundNautolanTexture);
                        background.setTextureRect(IntRect(0,0, backgroundNautolanTexture.getSize().x, backgroundNautolanTexture.getSize().y));
                        background.setColor(Color(170, 170, 170));
                        background.setOrigin(Vector2f(backgroundNautolanTexture.getSize()) / 2.f);
                        background.setScale(Vector2f(screenWidth / float(backgroundNautolanTexture.getSize().x), screenWidth / float(backgroundNautolanTexture.getSize().x)));
                        background.setPosition(Vector2f(screenWidth / 2, screenHeight / 2));
                        for (SFX* planet : *(*manager->getBackgroundPropList())[manager->PLANET]) {
                            delete planet;
                        }
                        (*manager->getBackgroundPropList())[manager->PLANET]->clear();
                        for (SFX* astero : *(*manager->getBackgroundPropList())[manager->ASTEROID]) {
                            delete astero;
                        }
                        (*manager->getBackgroundPropList())[manager->ASTEROID]->clear();
                        waveCount = 7;
                    }
                }
            }
        }
    }
    else if (waveCount == 7) {
        if (isInterlude) {
            for (int i = 0; i < 4; i++) {
                int type, offset = 175;
                if (rand() % 2 == 0) { type = manager->ASTERO1; }
                else { type = manager->ASTERO2; }
                Vector2f randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset);
                bool out = false;
                while (i > 0 and !out) {
                    for (int index = 0; index < (*manager->getBackgroundPropList())[manager->PLANET]->size(); index++) {
                        SFX* other = (*(*manager->getBackgroundPropList())[manager->PLANET])[index];
                        if (abs(randPos.y - other->getPosition().y) > 50 and abs(randPos.x - other->getPosition().x) > 50) {
                            if (index == (*manager->getBackgroundPropList())[manager->PLANET]->size() - 1) { out = true; break; }
                            continue;
                        }
                        else { randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset); break; }
                    }
                }
                BackgroundProp* prop = manager->addBackgroundProp(manager->PLANET, randPos, 5.f, type);
                prop->getSprite()->setColor(Color(10, 130, 90));
            }
            for (int i = 0; i < 50; i++) {
                int offset = 20;
                Vector2f randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset);
                bool out = false;
                while (i > 0 and !out) {
                    for (int index = 0; index < (*manager->getBackgroundPropList())[manager->ASTEROID]->size(); index++) {
                        SFX* other = (*(*manager->getBackgroundPropList())[manager->ASTEROID])[index];
                        if (abs(randPos.y - other->getPosition().y) > 10 and abs(randPos.x - other->getPosition().x) > 10) {
                            if (index == (*manager->getBackgroundPropList())[manager->ASTEROID]->size() - 1) { out = true; break; }
                            continue;
                        }
                        else { randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset); break; }
                    }
                }
                BackgroundProp* prop = manager->addBackgroundProp(manager->ASTEROID, randPos, 0.4f, manager->WATER_BUBBLE);
            }
            player.setSpeed(player.getSpeed() / 1.25f);
            meteorSpeed = 1.f;
            obstacleTexture = alienDebrisTexture;
            isInterlude = false;
        }
        if (int(shade) > 0) {
            shade -= 100.f * timeSinceLastFrame.asSeconds();
            screenEffect.setFillColor(Color(255, 255, 255, int(shade)));
        }
        else {
            shade = 0;
            meteorProb = 10;
            if (enemiesSpawnCooldownNum >= 2 and manager->getEntityList()[manager->ENEMY]->size() == 0) {
                for (int i = 0; i < 2; i++) {
                    manager->addEnemy(manager->NAUTOLAN_SHIP);
                }
                enemiesSpawnCooldownNum = 0;
            }
        }
    }
    else if (waveCount == 9) {
        if (enemiesSpawnCooldownNum >= 5 and manager->getEntityList()[manager->ENEMY]->size() < 10) {
            for (int i = 0; i < 3; i++) {
                int randType = rand() % 100;
                if (randType < 70) { manager->addEnemy(manager->NAUTOLAN_SHIP); }
                else { manager->addEnemy(manager->ALIEN_SHIP); }
            }
            enemiesSpawnCooldownNum = 0;
        }
    }

    if (meteorCooldownChrono >= meteorCooldownLimit) {
        meteorCooldownChrono = 0;
        int spawnProb = rand() % 100;
        if (spawnProb < meteorProb) {
            float offset = 100;
            Ammo* meteor = manager->addAmmo(obstacleTexture, Vector2f(screenWidth/2,0), Vector2f(0, 1.5f) * meteorSpeed, 5);
            Vector2f randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, meteor->getHeight()/-2);
            meteor->getSprite()->setPosition(randPos);
            meteor->getSprite()->setScale(Vector2f(2.5f, 2.5f));
        }
    }

    for (int i = 0; i < manager->getEntityList()[manager->ENEMY]->size(); i++) {
        Entity* enemy = (*manager->getEntityList()[manager->ENEMY])[i];
        enemy->addToHurtTime(timeSinceLastFrame.asSeconds());
        if (enemy->getHurtTime() >= 0.3f) { enemy->setColor(255, 255, 255); }
        else if (enemy->getHurtTime() >= 0.15f) { enemy->getSprite()->setColor(enemy->getSprite()->getColor() - Color(0, 0, 0, 20)); }
        if (enemiesBehaviorCooldown.getElapsedTime().asSeconds() - menuTime.asSeconds() >= 0.8f) {
            int randBehav = rand() % 8;
            int edge = 120;
            int forwardLimit = screenHeight / 3;
            int backLimit = edge;
            int rightLimit = screenWidth - edge;
            int leftLimit = edge;
            if (randBehav == 0 and enemy->getPos().y < forwardLimit) { enemy->setBehavior(Vector2f(0.f, 1.f)); } //moves forward
            else if (randBehav == 1 and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, 0.f)); } //moves right
            else if (randBehav == 2 and enemy->getPos().y > backLimit) { enemy->setBehavior(Vector2f(0.f, -1.f)); } //moves back
            else if (randBehav == 3 and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, 0.f)); } //moves left
            else if (randBehav == 4 and enemy->getPos().y < forwardLimit and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, 1.f)); } //moves forward-right
            else if (randBehav == 5 and enemy->getPos().y > backLimit and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, -1.f)); } //moves back-left
            else if (randBehav == 6 and enemy->getPos().y < forwardLimit and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, 1.f)); } //moves forward-left
            else if (randBehav == 7 and enemy->getPos().y > backLimit and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, -1.f)); } //moves back-right
            if (i == manager->getEntityList()[manager->ENEMY]->size() - 1) { enemiesBehaviorCooldown.restart(); }
        }
        enemy->move(enemy->getBehavior() * timeSinceLastFrame.asSeconds());
        if (enemy->getLeft() > screenWidth) { enemy->setX(0.f); }
        if (enemy->getRight() < 0) { enemy->setX(screenWidth); }
        if (enemy->getUp() < 0) { enemy->setY(enemy->getHeight() / 2.f); }
        if (enemy->getDown() > screenHeight) { enemy->setY(screenHeight - enemy->getHeight() / 2.f); }
        Entity* parent = enemy;
        while (true) {
            if (parent->getLinkedEntities().size() == 0) { break; }
            for (Entity* ray : parent->getLinkedEntities()) {
                ray->getSprite()->setPosition(Vector2f(parent->getPos().x, parent->getDown()));
                ray->addToFrameRate(timeSinceLastFrame.asSeconds());
                ray->addToLifeTime(timeSinceLastFrame.asSeconds());
                if (player.isColiding(ray) and timeInRay > 0.8f) {
                    player.decreaseHp();
                    timeInRay = 0;
                }
                ray->addToFrameRate(timeSinceLastFrame.asSeconds());
                if (ray->getFrameRate() > 0.5f) {
                    ray->setFrameRate(0);
                    ray->continueAnimation();
                }
                if (ray->getLifeTime() > enemy->getFrameRate()) {
                    manager->deleteEntity(manager->RAY, ray);
                    enemy->eraseLinkedEntities();
                    enemy->restartShootCooldown();
                    shootCooldownDecrease = 0;
                }
                parent = ray;
            }
            
        }
        if (enemy->getShootCooldown().getElapsedTime().asSeconds() - shootCooldownDecrease >= enemy->getFrameRate()) {
            shootEnemy.play();
            for (int i = 0; i < enemy->getAmmoAmount(); i++) {
                Vector2f currentDirection = enemy->getAmmoDirections()[i];
                Vector2f currentPos = Vector2f(enemy->getPos().x + enemy->getAmmoPositions()[i], enemy->getDown());
                Texture texture = ammoTexture;
                if (enemy->getType() == manager->ALIEN_SHIP or enemy->getType() == manager->BOSS_ALIEN_SHIP) {
                    texture = spinningAmmoTexture;
                }
                if (enemy->getType() == manager->NAUTOLAN_SHIP or enemy->getType() == manager->BOSS_NAUTOLAN_SHIP) {
                    texture = rayTexture;
                    Entity* adding = enemy;
                    for (int i = 0; i < 10; i++) {
                        Ray* ray = manager->addRay(texture, currentPos, currentDirection);
                        adding->addToLinkedEntities(ray);
                        if (enemy->getType() == manager->BOSS_NAUTOLAN_SHIP) {
                            ray->getSprite()->setScale(Vector2f(3.f, 3.f));
                        }
                        adding = ray;
                    }
                }
                else {
                    manager->addAmmo(texture, currentPos, currentDirection);
                }
            }
            enemy->restartShootCooldown();
            shootCooldownDecrease = 0;
        }
    }

    for (int i = 0; i < manager->getEntityList()[manager->EFFECT]->size(); i++) {
        Entity* ammo = (*manager->getEntityList()[manager->EFFECT])[i];
        ammo->move(ammo->getBehavior() * timeSinceLastFrame.asSeconds());
        ammo->addToFrameRate(timeSinceLastFrame.asSeconds());
        if (ammo->getFrameRate() > 0.08f) {
            ammo->setFrameRate(0);
            ammo->continueAnimation();
        }
        if (ammo->getDown() < 0 or ammo->getUp() > screenHeight) { manager->deleteEntity(manager->EFFECT, ammo); }
        else {
            if (ammo->getBehavior().y < 0.f) {
                for (int j = 0; j < manager->getEntityList()[manager->ENEMY]->size(); j++) {
                    Entity* currentEntity = (*manager->getEntityList()[manager->ENEMY])[j];
                    if (ammo->isColiding(currentEntity)) {
                        cout << "\n\033[32menemy hit!\033[0m\n";
                        currentEntity->decreaseHp(ammo->getMaxHp());
                        manager->deleteEntity(manager->EFFECT, ammo);
                        currentEntity->setHurtTime(0);
                        currentEntity->setColor(255, 100, 100);
                        cout << "remaining hp : " << currentEntity->getHp() << endl;
                        if (currentEntity->getHp() <= 0) {
                            int randIsBonus = rand() % 100;
                            if (randIsBonus < 100) {
                                int randType = rand() % 100;
                                int type = 0;
                                float healProb = 50, rifleProb = 50.f / 3.f, sniperProb = 50.f / 3.f, pistolProb = 50.f / 3.f;
                                if (randType < healProb) { type = manager->HEALING; }
                                else if (randType < healProb + rifleProb) { type = manager->RIFLE; }
                                else if (randType < healProb + rifleProb + sniperProb) { type = manager->SNIPER; }
                                else { type = manager->PISTOL; }
                                manager->addBonus(currentEntity->getPos(), type);
                            }
                            manager->addExplosion(currentEntity->getPos(), currentEntity->getHeight() * 0.015);
                            explosionSound.play();
                            manager->deleteEntity(manager->ENEMY, currentEntity);
                            scoreNum++;
                            if (scoreNum == 10) { waveCount = 2; }
                            if (scoreNum == 20) {
                                manager->addEnemy(manager->BOSS_CRUISER);
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->DOUBLE_BARREL_SHIP);
                                }
                                waveCount = 3;
                            }
                            if (waveCount == 4 and manager->getEntityList()[manager->ENEMY]->size() == 0) {
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->ALIEN_SHIP);
                                }
                                waveCount = 5;
                            }
                            if (waveCount == 5 and scoreNum == 60) {
                                manager->addEnemy(manager->BOSS_ALIEN_SHIP);
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->ALIEN_SHIP);
                                }
                                waveCount = 6;
                            }
                            if (waveCount == 8 and manager->getEntityList()[manager->ENEMY]->size() == 0) {
                                manager->addEnemy(manager->BOSS_NAUTOLAN_SHIP);
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->NAUTOLAN_SHIP);
                                }
                                waveCount = 9;
                            }
                            score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
                        }
                    }
                }
            }
            else {
                if (player.isColiding(ammo)) {
                    cout << "\n\033[32player hit!\033[0m\n";
                    player.decreaseHp(ammo->getMaxHp());
                    manager->deleteEntity(manager->EFFECT, ammo);
                    player.setHurtTime(0);
                    player.setColor(255, 100, 100);
                }
            }
        }
    }
    for (int i = 0; i < manager->getEntityList()[manager->BONUS]->size(); i++) {
        Entity* bonus = (*manager->getEntityList()[manager->BONUS])[i];
        bonus->move(Vector2f(0, 1) * timeSinceLastFrame.asSeconds());
        bonus->addToFrameRate(timeSinceLastFrame.asSeconds());
        bonus->addToLifeTime(timeSinceLastFrame.asSeconds());
        if (bonus->isColiding(&player)) {
            if (bonus->getType() == manager->HEALING and player.getHp() <= player.getMaxHp()) {
                manager->deleteEntity(manager->BONUS, bonus);
                player.decreaseHp(-1);
            }
            else if (bonus->getType() == manager->RIFLE) {
                manager->deleteEntity(manager->BONUS, bonus);
                player.setFrameRate(0.15f);
                playerAmmoColor = Color(255, 255, 10);
                player.setAmmoDirections({ Vector2f(0, -1) });
                player.setWeaponDamage(100);
            }
            else if (bonus->getType() == manager->SNIPER) {
                manager->deleteEntity(manager->BONUS, bonus);
                player.setFrameRate(0.6f);
                playerAmmoColor = Color(255, 50, 255);
                player.setAmmoDirections({ Vector2f(0, -2) });
                player.setWeaponDamage(5);
            }
            else if (bonus->getType() == manager->PISTOL) {
                manager->deleteEntity(manager->BONUS, bonus);
                player.setFrameRate(0.25f);
                playerAmmoColor = Color(255, 255, 255);
                player.setAmmoDirections({ Vector2f(0, -1) });
                player.setWeaponDamage(2);
            }
        }
        else if (bonus->getLifeTime() > 4.5f) {
            manager->deleteEntity(manager->BONUS, bonus);
        }
        else if (bonus->getLifeTime() > 3.5f) {
            if (bonus->getFrameRate() > 0.25f) {
                bonus->setFrameRate(0);
                bonus->continueAnimation();
            }
        }
    }

    for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
        SFX* sfx = (*manager->getExplosionList())[i];
        if (sfx->getFrameClock()->getElapsedTime().asSeconds() > 0.04f) {
            IntRect newRect = sfx->getSprite()->getTextureRect();
            newRect.left += sfx->getSize().y;
            if (sfx->getTexture().getSize().x <= newRect.left) {
                delete sfx;
                auto pos = manager->getExplosionList()->begin() + i;
                manager->getExplosionList()->erase(pos);
            }
            else {
                sfx->getSprite()->setTextureRect(newRect);
                sfx->getFrameClock()->restart();
            }
        }
    }
    menuTime = Time().Zero;
    //death
    if (player.getHp() <= 0 and !isAdmin) {
        bool isDeath = true;
        bool onMenu = false; resumeButton.setTexture(resumeButtonOffTexture);
        bool onExit = false; pauseExitButton.setTexture(pauseExitButtonOffTexture);
        bool onVolume = false;
        Sprite tableRect(table); tableRect.setOrigin(Vector2f(table.getSize().x / 2, table.getSize().y / 2));
        while (isDeath) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                    if (onMenu) {
                        uiClicSound.play();
                        isMainMenu = true; isDeath = false;
                    }
                    else if (onExit) {
                        uiClicSound.play();
                        window.close(); delete manager; exit(1);
                    }
                }
                else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
            }
            if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
                if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x / 2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x / 2) {
                    volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                    for (Sound* currentSound : soundVector) {
                        currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                    }
                }
            }
            window.clear();
            display();
            window.draw(chronoText);
            RectangleShape blurry(Vector2f(screenWidth, screenHeight));
            blurry.setFillColor(Color(255, 255, 255, 150));
            window.draw(blurry);
            tableRect.setScale(Vector2f(0.6f, 0.5f)); tableRect.setPosition(volumeBar.getPosition() + Vector2f(0.f, 2.f));
            window.draw(tableRect);
            window.draw(volumeBar); window.draw(volumeIndicator);
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    volumeIndicator.setFillColor(Color(255, 255, 255));
                }
                else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
                if (!onVolume) {
                    onVolume = true;
                    if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        uiSound.play();
                    }
                }
            }
            else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }

            tableRect.setScale(Vector2f(1.2f, 1.2f));
            tableRect.setPosition(menuText.getPosition() + Vector2f(80, 5));
            window.draw(tableRect);
            tableRect.setPosition(pauseExitText.getPosition() + Vector2f(80, 5));
            window.draw(tableRect);
            window.draw(menuButton); window.draw(menuText); window.draw(deathText);

            if (menuButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onMenu) {
                    menuButton.setTexture(menuButtonOnTexture);
                    onMenu = true; uiSound.play();
                }
            }
            else if (onMenu) { menuButton.setTexture(menuButtonOffTexture); onMenu = false; }
            window.draw(pauseExitButton); window.draw(pauseExitText);
            if (pauseExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onExit) {
                    pauseExitButton.setTexture(pauseExitButtonOnTexture);
                    onExit = true; uiSound.play();
                }
            }
            else if (onExit) { pauseExitButton.setTexture(pauseExitButtonOffTexture); onExit = false; }
            cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(cursor);
            window.display();
        }
    }
}

void Game::display() {
    window.clear();
    window.draw(background);
    for (SFX* planet : *(*manager->getBackgroundPropList())[manager->PLANET]) {
        window.draw(*planet->getSprite());
    }
    for (SFX* astero : *(*manager->getBackgroundPropList())[manager->ASTEROID]) {
        window.draw(*astero->getSprite());
    }
    window.draw(interludeStartText);
    for (Entity* bonus : *(manager->getEntityList()[manager->BONUS])) {
        window.draw(*bonus->getSprite());
    }
    for (Entity* ray : *(manager->getEntityList()[manager->RAY])) {
        Vector2f basePos = ray->getPos();
        window.draw(*ray->getSprite());
        for (int i = 1; i < 20; i++) {
            ray->getSprite()->setPosition(Vector2f(ray->getPos().x, ray->getPos().y + ray->getHeight()));
            window.draw(*ray->getSprite());
        }
        ray->getSprite()->setPosition(basePos);
    }
    Text bossText;
    bossText.setFont(fontMain); int bossTextCharSize = 30; bossText.setCharacterSize(bossTextCharSize);
    bossText.setFillColor(Color(230, 100, 100, 190));
    Sprite bossHpTable;
    RectangleShape bossHpBar;
    for (Entity* enemy : *(manager->getEntityList()[manager->ENEMY])) {
        window.draw(*enemy->getSprite());
        if (enemy->getIsBoss() and isBossAlive()) {
            bossText.setString(enemy->getName());
            bossText.setOrigin(Vector2f(enemy->getName().size() * bossTextCharSize / 3.333, bossTextCharSize / 2));
            bossHpTable.setTexture(bossHpTableTexture);
            bossHpTable.setColor(bossHpTable.getColor() - Color(0, 0, 0, 100));
            bossHpTable.setOrigin(Vector2f(0, bossHpTableTexture.getSize().y / 2));
            float barWidth = 600.f, barHeight = 20.f;
            bossHpTable.setScale(Vector2f(barWidth / bossHpTableTexture.getSize().x + 5 / barWidth, barHeight / bossHpTableTexture.getSize().y + 3 / barHeight));
            bossHpBar = RectangleShape(Vector2f(barWidth, barHeight));
            bossHpBar.setFillColor(Color(230, 100, 100, 190));
            bossHpBar.setOrigin(Vector2f(0, barHeight / 2));
            bossHpBar.setScale(Vector2f(float(enemy->getHp()) / enemy->getMaxHp(), 1));
            bossHpBar.setPosition(Vector2f(screenWidth / 2 - barWidth / 2, 60));
            bossHpTable.setPosition(bossHpBar.getPosition() - Vector2f(5, 0));
            bossText.setPosition(Vector2f(screenWidth / 2, bossHpBar.getPosition().y - 35));
        }
    }
    for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
        window.draw(*((*manager->getExplosionList())[i]->getSprite()));
    }
    window.draw(*player.getSprite());
    for (Entity* ammo : *(manager->getEntityList()[manager->EFFECT])) {
        window.draw(*ammo->getSprite());
    }
    window.draw(bossText);
    window.draw(bossHpTable);
    window.draw(bossHpBar);

    if (player.getHp() > player.getMaxHp()) { window.draw(hpBonusText); hpText.setString(to_string(player.getHp() - 1) + "/" + to_string(player.getMaxHp())); }
    else { hpText.setString(to_string(player.getHp()) + "/" + to_string(player.getMaxHp())); }
    window.draw(hpText);


    window.draw(hpBar);
    for (int i = 0; i < player.getHp(); i++) {
        Sprite heart = hpDot;
        heart.setPosition(hpBar.getPosition() + Vector2f(4.0f, 3.f) + float(i) * Vector2f(15.0f, 0.f));
        if (i >= player.getMaxHp()) { heart.setColor(Color(50, 150, 255)); }
        window.draw(heart);
    }
    window.draw(dashIcon);
    window.draw(dashArrow);
    window.draw(score);
    window.draw(screenEffect);
}

void Game::pauseMenu() {
    Clock pauseMenuClock;
    bool onResume = false; menuButton.setTexture(menuButtonOffTexture);
    bool onMenu = false; resumeButton.setTexture(resumeButtonOffTexture);
    bool onExit = false; pauseExitButton.setTexture(pauseExitButtonOffTexture);
    bool onAdmin = false;
    bool onVolume = false;
    music.pause();
    Color previousScreenEffectColor = screenEffect.getFillColor();
    screenEffect.setFillColor(screenEffect.getFillColor() + Color(0,0,0, 60));
    while (isPauseMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                screenEffect.setFillColor(previousScreenEffectColor);
                isPauseMenu = false; menuTime = pauseMenuClock.getElapsedTime(); shootCooldownDecrease = menuTime.asSeconds(); shootCooldown.restart(); music.play();
            }
            else if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                if (onMenu) {
                    uiClicSound.play();
                    screenEffect.setFillColor(Color(255, 255, 255, 0));
                    isMainMenu = true; isPauseMenu = false;
                }
                else if (onResume) {
                    uiClicSound.play();
                    screenEffect.setFillColor(previousScreenEffectColor);
                    isPauseMenu = false; menuTime = pauseMenuClock.getElapsedTime(); shootCooldownDecrease = menuTime.asSeconds(); shootCooldown.restart(); music.play();
                }
                else if (onExit) {
                    uiClicSound.play();
                    window.close(); delete manager; exit(1);
                }
                else if (onAdmin) {
                    uiClicSound.play();
                    if (!isAdmin) {
                        adminButton.setTexture(adminButtonOnTexture);
                        isAdmin = true;
                    }
                    else {
                        adminButton.setTexture(adminButtonOffTexture);
                        isAdmin = false;
                    }
                }
            }
            else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
        }
        if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
            if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x / 2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x / 2) {
                volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                for (Sound* currentSound : soundVector) {
                    currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                }
            }
        }
        window.clear();
        display();
        window.draw(chronoText);
        window.draw(pauseBg);
        window.draw(pauseHeader);
        //menu button
        window.draw(menuButton); window.draw(menuText);
        if (menuButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onMenu) {
                menuButton.setTexture(menuButtonOnTexture);
                onMenu = true; uiSound.play();
            }
        }
        else if (onMenu) { menuButton.setTexture(menuButtonOffTexture); onMenu = false; }
        //resume button
        window.draw(resumeButton); window.draw(resumeText);
        if (resumeButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onResume) {
                resumeButton.setTexture(resumeButtonOnTexture);
                onResume = true; uiSound.play();
            }
        }
        else if (onResume) { resumeButton.setTexture(resumeButtonOffTexture); onResume = false; }
        //exit button
        window.draw(pauseExitButton); window.draw(pauseExitText);
        if (pauseExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onExit) {
                pauseExitButton.setTexture(pauseExitButtonOnTexture);
                onExit = true; uiSound.play();
            }
        }
        else if (onExit) { pauseExitButton.setTexture(pauseExitButtonOffTexture); onExit = false; }
        //admin button
        window.draw(adminButton); window.draw(adminText);
        if (adminButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onAdmin) {
                //set texture
                onAdmin = true; uiSound.play();
            }
        }
        else if (onAdmin) { /*set texture*/ onAdmin = false; }
        //volume
        window.draw(volumeBar); window.draw(volumeIndicator);
        if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                volumeIndicator.setFillColor(Color(255, 255, 255));
            }
            else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
            onVolume = true;
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) and !onVolume) {
                uiSound.play();
            }
        }
        else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }

        cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
        window.draw(cursor);
        window.display();
    }
}

void Game::mainMenu() {
    Clock mainMenuClock;
    bool onLeft = false; arrowButtonLeft.setTexture(arrowButtonOffTexture);
    bool onRight = false; arrowButtonRight.setTexture(arrowButtonOffTexture);
    bool onStart = false; playButton.setTexture(playButtonOffTexture);
    bool onExit = false; exitButton.setTexture(exitButtonOffTexture);
    bool onAdmin = false;
    bool onVolume = false;
    menuMusic.play();
    Vector2f buttonAmplification = Vector2f(0.05, 0.05);
    Sprite menuAdminButton = adminButton;
    menuAdminButton.setPosition(playButton.getPosition().x - playButton.getGlobalBounds().width/2 - 50, playButton.getPosition().y);
    background.setTexture(backgroundTexture);
    background.setColor(Color(200, 0, 200));
    background.setOrigin(Vector2f(backgroundTexture.getSize()) / 2.f);
    background.setScale(Vector2f(screenWidth / backgroundTexture.getSize().x, screenWidth / backgroundTexture.getSize().x));
    background.setPosition(Vector2f(screenWidth / 2, screenHeight / 2));
    obstacleTexture = meteorTexture;
    playerAmmoColor = Color(255, 255, 255);

    while (isMainMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) { window.close(); exit(1); }
            else if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                if (onStart) {
                    uiClicSound.play();
                    for (Clock* clock : clockTab) {
                        clock->restart();
                    }
                    chronoDecrease = 0; enemiesSpawnCooldownNum = 0; bonusCooldownNum = 0; dashCooldown = 3;
                    scoreNum = 0; waveCount = 1; score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
                    for (int type = 0; type < manager->getEntityList().size(); type++) {
                        for (Entity* entity : *manager->getEntityList()[type]) {
                            manager->deleteEntity(type, entity);
                        }
                    }
                    player = *(manager->addPlayer());
                    for (int i = 0; i < 2; i++) {
                        manager->addEnemy(manager->BASIC_SHIP);
                    }
                    for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
                        SFX* sfx = (*manager->getExplosionList())[i];
                        delete sfx;
                        auto pos = manager->getExplosionList()->begin() + i;
                        manager->getExplosionList()->erase(pos);
                    }
                    menuMusic.stop(); music.stop(); music.play();

                    for (SFX* planet : *(*manager->getBackgroundPropList())[manager->PLANET]) {
                        delete planet;
                    }
                    (*manager->getBackgroundPropList())[manager->PLANET]->clear();
                    for (SFX* astero : *(*manager->getBackgroundPropList())[manager->ASTEROID]) {
                        delete astero;
                    }
                    (*manager->getBackgroundPropList())[manager->ASTEROID]->clear();
                    for (int i = 0; i < 2; i++) {
                        int type, offset = 150;
                        if (i == 0) { type = manager->PLANET1; }
                        else { type = manager->BLACK_HOLE; }
                        Vector2f randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset);
                        bool out = false;
                        while (i > 0 and !out) {
                            for (int index = 0; index < (*manager->getBackgroundPropList())[manager->PLANET]->size(); index++) {
                                SFX* other = (*(*manager->getBackgroundPropList())[manager->PLANET])[index];
                                if (abs(randPos.y - other->getPosition().y) > 100 and abs(randPos.x - other->getPosition().x) > 100) {
                                    if (index == (*manager->getBackgroundPropList())[manager->PLANET]->size() - 1) { out = true; break; }
                                    continue;
                                }
                                else { randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset); break; }
                            }
                        }
                        BackgroundProp* prop = manager->addBackgroundProp(manager->PLANET, randPos, background.getScale().x, type);
                        prop->getSprite()->setColor(background.getColor());
                    }
                    for (int i = 0; i < 4; i++) {
                        int type, offset = 175;
                        if (rand() % 2 == 0) { type = manager->ASTERO1; }
                        else { type = manager->ASTERO2; }
                        Vector2f randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset);
                        bool out = false;
                        while (i > 0 and !out) {
                            for (int index = 0; index < (*manager->getBackgroundPropList())[manager->ASTEROID]->size(); index++) {
                                SFX* other = (*(*manager->getBackgroundPropList())[manager->ASTEROID])[index];
                                if (abs(randPos.y - other->getPosition().y) > 50 and abs(randPos.x - other->getPosition().x) > 50) {
                                    if (index == (*manager->getBackgroundPropList())[manager->ASTEROID]->size() - 1) { out = true; break; }
                                    continue;
                                }
                                else { randPos = Vector2f(rand() % int(screenWidth - offset * 2) + offset, rand() % int(screenHeight - offset * 2) + offset); break; }
                            }
                        }
                        BackgroundProp* prop = manager->addBackgroundProp(manager->ASTEROID, randPos, background.getScale().x, type);
                        prop->getSprite()->setColor(background.getColor());
                    }
                    isMainMenu = false;
                }
                if (onLeft or onRight or onStart) {
                    if (onLeft)
                    {
                        if (shipNumber <= 1) { shipNumber = 3; }
                        else shipNumber -= 1;
                    }
                    else if (onRight)
                    {
                        if (shipNumber >= 3) { shipNumber = 1; }
                        else shipNumber += 1;
                    }
                    player.getSprite()->setTexture(*currentPlayerIcon.getTexture());
                    switch (shipNumber)
                    {
                    case 1:
                        player.setWeaponDamage(4);
                        player.setMaxHp(5); 
                        hpBar.setTexture(hpBarTexture5);
                        break;
                    case 2:
                        player.setWeaponDamage(2);
                        player.setMaxHp(10);
                        hpBar.setTexture(hpBarTexture10);
                        break;
                    case 3:
                        player.setWeaponDamage(2);
                        player.setMaxHp(5);
                        hpBar.setTexture(hpBarTexture5);
                        player.setFrameRate(0.2f);
                        break;
                    default:
                        break;
                    }
                }
                else if (onExit) {
                    uiClicSound.play();
                    window.close(); delete manager; exit(1);
                }
                else if (onAdmin) {
                    uiClicSound.play();
                    if (!isAdmin) {
                        menuAdminButton.setTexture(adminButtonOnTexture);
                        adminButton.setTexture(adminButtonOnTexture);
                        isAdmin = true;
                    }
                    else {
                        menuAdminButton.setTexture(adminButtonOffTexture);
                        adminButton.setTexture(adminButtonOffTexture);
                        isAdmin = false;
                    }
                }
            }
        }
        if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
            if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x / 2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x / 2) {
                volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                for (Sound* currentSound : soundVector) {
                    currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                }
            }
        }
        window.clear();
        window.draw(background);
        if (arrowButtonLeft.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onLeft) {
                arrowButtonLeft.setTexture(arrowButtonOnTexture);
                onLeft = true; uiSound.play();
            }
        }
        else if (onLeft) { arrowButtonLeft.setTexture(arrowButtonOffTexture); onLeft = false; }
        window.draw(arrowButtonLeft);
        //droit
        if (arrowButtonRight.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onRight) {
                arrowButtonRight.setTexture(arrowButtonOnTexture);
                onRight = true; uiSound.play();
            }
        }
        else if (onRight) { arrowButtonRight.setTexture(arrowButtonOffTexture); onRight = false; }
        window.draw(arrowButtonRight);

        window.draw(classDescription);
        switch (shipNumber)
        {
        case 1:
            currentPlayerIcon.setTexture(playerShipYellowTexture);
            window.draw(classDescriptionStats1);
            break;
        case 2:
            currentPlayerIcon.setTexture(playerShipBlueTexture);
            window.draw(classDescriptionStats2);
            break;
        case 3:
            currentPlayerIcon.setTexture(playerShipGreenTexture);
            window.draw(classDescriptionStats3);
            break;
        default:
            break;
        }
        window.draw(currentPlayerIcon);
        //start-button check
        if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onStart) {
                playButton.setTexture(playButtonOnTexture);
                playButton.setScale(playButton.getScale() + buttonAmplification);
                onStart = true; uiSound.play();
            }
        }
        else if (onStart) { playButton.setTexture(playButtonOffTexture); playButton.setScale(playButton.getScale() - buttonAmplification); onStart = false; }
        window.draw(playButton);
        //exit-button check
        if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onExit) {
                exitButton.setTexture(exitButtonOnTexture);
                exitButton.setScale(exitButton.getScale() + buttonAmplification);
                onExit = true; uiSound.play();
            }
        }
        else if (onExit) { exitButton.setTexture(exitButtonOffTexture); exitButton.setScale(exitButton.getScale() - buttonAmplification); onExit = false; }
        window.draw(exitButton);
        //admin button
        window.draw(menuAdminButton);
        if (menuAdminButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (!onAdmin) {
                //set texture
                onAdmin = true; uiSound.play();
            }
        }
        else if (onAdmin) { /*set texture*/ onAdmin = false; }
        //volume bar
        window.draw(volumeBar); window.draw(volumeIndicator);
        if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                volumeIndicator.setFillColor(Color(255, 255, 255));
            }
            else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
            if (!onVolume) {
                onVolume = true;
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    uiSound.play();
                }
            }
        }
        else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }
        //title
        window.draw(title);
        //cursor
        cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
        window.draw(cursor);
        window.display();
    }
}

void Game::gameLoop() {

    while (window.isOpen()) {
        if (!isMainMenu and !isPauseMenu) {
            userInput();
            update();
            display();
            cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            string chronoTextStr = "chrono\n";
            string gameTimeStr = to_string(gameTime.getElapsedTime().asSeconds() - chronoDecrease);
            for (int i = 0; i < gameTimeStr.size(); i++) {
                if (i > 1) {
                    if (gameTimeStr[i - 2] == '.') { chronoTextStr += " s\n----------"; break; }
                }
                chronoTextStr += gameTimeStr[i];
            }
            chronoText.setString(chronoTextStr);
            window.draw(chronoText);
            window.draw(cursor);
            window.display();
        }
        else if (isMainMenu) {
            mainMenu();
        }
        else if (isPauseMenu) {
            pauseMenu();
        }
    }
}