#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Function prototypes
void renderTitle(sf::RenderWindow &window, sf::Font &font, sf::Text &titleText);
void renderStartButton(sf::RenderWindow &window, sf::RectangleShape &button, sf::Text &buttonText);
void renderBackstoryScreen(sf::RenderWindow &window, sf::Font &font, sf::Sprite &backgroundSprite, sf::Text &backstoryText, sf::RectangleShape &backstoryBox, sf::RectangleShape &goToWorkButton, sf::Text &goToWorkButtonText);
void renderNamePrompt(sf::RenderWindow &window, sf::Font &font, sf::Text &namePromptText, sf::RectangleShape &nameBox);
void renderShop(sf::RenderWindow &window, sf::Font &font, sf::Text &shopTitle, sf::Text &shovelText, sf::Text &blowerText, sf::Text &poweredBlowerText, sf::Text &crewText);
void renderMainGame(sf::RenderWindow &window, sf::Font &font, sf::RectangleShape &workButton, sf::Text &workButtonText, sf::RectangleShape &shopButton, sf::Text &shopButtonText, sf::RectangleShape &toolsButton, sf::Text &toolsButtonText, sf::RectangleShape &quitButton, sf::Text &quitButtonText, sf::Text &gameInfoText);
void renderTools(sf::RenderWindow &window, sf::Font &font, sf::Text &toolsTitle, sf::Text &toolsList);

// Enumeration for game states
enum GameState {
    StartScreen,
    BackstoryScreen,
    MainGame,
    ShopScreen,
    ToolsScreen,
    WinScreen,
    LoseScreen
};

GameState gameState = StartScreen;

class Game {
public:
    int money;
    int day;
    int workEfficiency;
    int goal;
    int cost;
    std::vector<std::string> tools;

    Game() : money(0), day(0), workEfficiency(1), goal(10000), cost(20) {}

    void work() {
        money += workEfficiency;
        day++;
        checkWinLoseConditions();
    }

    void buyTool(int cost, int efficiency, const std::string& toolName) {
        if (money >= cost) {
            money -= cost;
            workEfficiency += efficiency;
            tools.push_back(toolName);
        }
    }

    void checkWinLoseConditions() {
        if (money >= goal) {
            gameState = WinScreen;
        } else if (day >= 60 && money < goal) {
            gameState = LoseScreen;
        }
    }

    void reset() {
        money = 0;
        day = 0;
        workEfficiency = 1;
        tools.clear();
        gameState = StartScreen;
    }
};

Game game;

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(736, 414), "Snow Remover 2000");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Error loading font\n";
        return 1;
    }

    // Load background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/startscreen.png"))
    {
        std::cerr << "Error loading background image\n";
        return 1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Setup title text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Snow Remover 2000");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(150, 60); // Adjusted for new window size and box

    // Setup start button
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(268, 300);                // Adjusted for new window size
    startButton.setFillColor(sf::Color(0, 102, 204)); // Winter theme blue
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2);

    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString("Start Game");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(288, 310); // Adjusted for new window size

    // Setup input for user name
    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::Black);
    playerText.setPosition(120, 150);
    playerText.setString("What is your name? "); // Initial prompt text

    // Setup name box
    sf::RectangleShape nameBox(sf::Vector2f(500, 60));
    nameBox.setPosition(118, 140);
    nameBox.setFillColor(sf::Color::White);
    nameBox.setOutlineColor(sf::Color::Black);
    nameBox.setOutlineThickness(2);

    // Setup backstory text
    sf::Text backstoryText;
    backstoryText.setFont(font);
    backstoryText.setCharacterSize(14);
    backstoryText.setFillColor(sf::Color::Black);
    backstoryText.setPosition(70, 50); // Adjust as needed

    // Setup backstory box
    sf::RectangleShape backstoryBox(sf::Vector2f(600, 200));
    backstoryBox.setPosition(68, 40);
    backstoryBox.setFillColor(sf::Color::White);
    backstoryBox.setOutlineColor(sf::Color::Black);
    backstoryBox.setOutlineThickness(2);

    // Setup go to work button
    sf::RectangleShape goToWorkButton(sf::Vector2f(150, 40));
    goToWorkButton.setPosition(293, 320);                // Adjusted for new window size
    goToWorkButton.setFillColor(sf::Color(0, 102, 204)); // Winter theme blue
    goToWorkButton.setOutlineColor(sf::Color::White);
    goToWorkButton.setOutlineThickness(2);

    sf::Text goToWorkButtonText;
    goToWorkButtonText.setFont(font);
    goToWorkButtonText.setString("Go to work");
    goToWorkButtonText.setCharacterSize(18);
    goToWorkButtonText.setFillColor(sf::Color::White);
    goToWorkButtonText.setPosition(308, 328); // Adjust as needed

    // Setup work button
    sf::RectangleShape workButton(sf::Vector2f(120, 40));
    workButton.setPosition(50, 350);
    workButton.setFillColor(sf::Color::Green);

    sf::Text workButtonText;
    workButtonText.setFont(font);
    workButtonText.setString("Work");
    workButtonText.setCharacterSize(18);
    workButtonText.setFillColor(sf::Color::White);
    workButtonText.setPosition(80, 360);

    // Setup shop button
    sf::RectangleShape shopButton(sf::Vector2f(120, 40));
    shopButton.setPosition(200, 350);
    shopButton.setFillColor(sf::Color::Yellow);

    sf::Text shopButtonText;
    shopButtonText.setFont(font);
    shopButtonText.setString("Shop");
    shopButtonText.setCharacterSize(18);
    shopButtonText.setFillColor(sf::Color::Black);
    shopButtonText.setPosition(230, 360);

    // Setup tools button
    sf::RectangleShape toolsButton(sf::Vector2f(120, 40));
    toolsButton.setPosition(350, 350);
    toolsButton.setFillColor(sf::Color::Blue);

    sf::Text toolsButtonText;
    toolsButtonText.setFont(font);
    toolsButtonText.setString("Tools");
    toolsButtonText.setCharacterSize(18);
    toolsButtonText.setFillColor(sf::Color::White);
    toolsButtonText.setPosition(380, 360);

    // Setup quit button
    sf::RectangleShape quitButton(sf::Vector2f(120, 40));
    quitButton.setPosition(500, 350);
    quitButton.setFillColor(sf::Color::Red);

    sf::Text quitButtonText;
    quitButtonText.setFont(font);
    quitButtonText.setString("Quit");
    quitButtonText.setCharacterSize(18);
    quitButtonText.setFillColor(sf::Color::White);
    quitButtonText.setPosition(540, 360);

    // Setup shop texts
    sf::Text shopTitle;
    shopTitle.setFont(font);
    shopTitle.setString("Shop");
    shopTitle.setCharacterSize(24);
    shopTitle.setFillColor(sf::Color::Black);
    shopTitle.setPosition(350, 50);

    sf::Text shovelText;
    shovelText.setFont(font);
    shovelText.setString("Shovel - $20");
    shovelText.setCharacterSize(18);
    shovelText.setFillColor(sf::Color::Black);
    shovelText.setPosition(100, 150);

    sf::Text blowerText;
    blowerText.setFont(font);
    blowerText.setString("Push Blower - $100");
    blowerText.setCharacterSize(18);
    blowerText.setFillColor(sf::Color::Black);
    blowerText.setPosition(100, 200);

    sf::Text poweredBlowerText;
    poweredBlowerText.setFont(font);
    poweredBlowerText.setString("Powered Blower - $500");
    poweredBlowerText.setCharacterSize(18);
    poweredBlowerText.setFillColor(sf::Color::Black);
    poweredBlowerText.setPosition(100, 250);

    sf::Text crewText;
    crewText.setFont(font);
    crewText.setString("Crew - $1000");
    crewText.setCharacterSize(18);
    crewText.setFillColor(sf::Color::Black);
    crewText.setPosition(100, 300);

    // Setup game info text
    sf::Text gameInfoText;
    gameInfoText.setFont(font);
    gameInfoText.setCharacterSize(18);
    gameInfoText.setFillColor(sf::Color::Black);
    gameInfoText.setPosition(50, 50);

    // Setup tools list text
    sf::Text toolsTitle;
    toolsTitle.setFont(font);
    toolsTitle.setString("Tools Inventory");
    toolsTitle.setCharacterSize(24);
    toolsTitle.setFillColor(sf::Color::Black);
    toolsTitle.setPosition(300, 50);

    sf::Text toolsList;
    toolsList.setFont(font);
    toolsList.setCharacterSize(18);
    toolsList.setFillColor(sf::Color::Black);
    toolsList.setPosition(100, 100);

    bool nameEntered = false;
    std::string playerName;

    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse click on start button
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (gameState == StartScreen) {
                        if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            gameState = BackstoryScreen;
                        }
                    }
                    else if (gameState == BackstoryScreen) {
                        if (nameEntered && goToWorkButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            gameState = MainGame;
                        }
                    }
                    else if (gameState == MainGame) {
                        if (workButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.work();
                        } else if (shopButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            gameState = ShopScreen;
                        } else if (toolsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            gameState = ToolsScreen;
                        } else if (quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            window.close();
                        }
                    }
                    else if (gameState == ShopScreen) {
                        if (shovelText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.buyTool(20, 1, "Shovel");
                        } else if (blowerText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.buyTool(100, 5, "Push Blower");
                        } else if (poweredBlowerText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.buyTool(500, 20, "Powered Blower");
                        } else if (crewText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.buyTool(1000, 50, "Crew");
                        }
                    }
                    else if (gameState == WinScreen || gameState == LoseScreen) {
                        if (quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            game.reset();
                        }
                    }
                }
            }

            // Handle text input
            if (gameState == BackstoryScreen && !nameEntered && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && playerInput.getSize() > 0)
                {
                    playerInput.erase(playerInput.getSize() - 1, 1);
                }
                else if (event.text.unicode < 128 && playerInput.getSize() < 10)
                {
                    playerInput += event.text.unicode;
                }
                playerText.setString("What is your name? " + playerInput);
            }

            // Handle enter key press for name submission
            if (gameState == BackstoryScreen && !nameEntered && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && playerInput.getSize() > 0)
            {
                nameEntered = true;
                playerName = playerInput;
                std::ostringstream backstoryStream;
                backstoryStream << "So your name is " << playerName << " huh? Well " << playerName << ", here's the jazz kid... \n";
                backstoryStream << "\n";
                backstoryStream << "Its been a bad winter and been snowing all year!\n";
                backstoryStream << "We need you to get this place up and running in 60 DAYS!\n";
                backstoryStream << "I'll need you to use your cunning and wit to manage us out of this pickle.\n";
                backstoryStream << "\n";
                backstoryStream << "Goal:\n";
                backstoryStream << "Your goal is to get us a big ol' truck and some new building upgrades but\n";
                backstoryStream << "its gonna run us $10000! Well.. I'm off to Florida with the wife. \n";
                backstoryStream << "See ya in a couple of months!";
                backstoryText.setString(backstoryStream.str());
            }
        }

        // Declare this outside the switch statement to avoid errors
        std::ostringstream toolsStream;

        // Clear the screen
        window.clear();

        switch (gameState) {
            case StartScreen:
                window.draw(backgroundSprite);
                renderTitle(window, font, titleText);
                renderStartButton(window, startButton, startButtonText);
                break;
            case BackstoryScreen:
                if (!nameEntered) {
                    window.draw(backgroundSprite);
                    window.draw(nameBox);
                    window.draw(playerText);
                } else {
                    renderBackstoryScreen(window, font, backgroundSprite, backstoryText, backstoryBox, goToWorkButton, goToWorkButtonText);
                }
                break;
            case MainGame:
                window.draw(backgroundSprite);
                renderMainGame(window, font, workButton, workButtonText, shopButton, shopButtonText, toolsButton, toolsButtonText, quitButton, quitButtonText, gameInfoText);
                break;
            case ShopScreen:
                window.draw(backgroundSprite);
                renderShop(window, font, shopTitle, shovelText, blowerText, poweredBlowerText, crewText);
                break;
            case ToolsScreen:
                window.draw(backgroundSprite);
                for (const auto& tool : game.tools) {
                    toolsStream << tool << "\n";
                }
                toolsList.setString(toolsStream.str());
                renderTools(window, font, toolsTitle, toolsList);
                break;
            case WinScreen:
                window.draw(backgroundSprite);
                window.draw(quitButton);
                window.draw(quitButtonText);
                break;
            case LoseScreen:
                window.draw(backgroundSprite);
                window.draw(quitButton);
                window.draw(quitButtonText);
                break;
        }

        // Update the window
        window.display();
    }

    return 0;
}

void renderTitle(sf::RenderWindow &window, sf::Font &font, sf::Text &titleText)
{
    window.draw(titleText);
}

void renderStartButton(sf::RenderWindow &window, sf::RectangleShape &button, sf::Text &buttonText)
{
    window.draw(button);
    window.draw(buttonText);
}

void renderBackstoryScreen(sf::RenderWindow &window, sf::Font &font, sf::Sprite &backgroundSprite, sf::Text &backstoryText, sf::RectangleShape &backstoryBox, sf::RectangleShape &goToWorkButton, sf::Text &goToWorkButtonText)
{
    window.draw(backgroundSprite);
    window.draw(backstoryBox);
    window.draw(backstoryText);
    window.draw(goToWorkButton);
    window.draw(goToWorkButtonText);
}

void renderMainGame(sf::RenderWindow &window, sf::Font &font, sf::RectangleShape &workButton, sf::Text &workButtonText, sf::RectangleShape &shopButton, sf::Text &shopButtonText, sf::RectangleShape &toolsButton, sf::Text &toolsButtonText, sf::RectangleShape &quitButton, sf::Text &quitButtonText, sf::Text &gameInfoText) {
    gameInfoText.setString("Money: $" + std::to_string(game.money) + "\nDay: " + std::to_string(game.day) + "\nEfficiency: " + std::to_string(game.workEfficiency));
    window.draw(gameInfoText);
    window.draw(workButton);
    window.draw(shopButton);
    window.draw(toolsButton);
    window.draw(quitButton);
    window.draw(workButtonText);
    window.draw(shopButtonText);
    window.draw(toolsButtonText);
    window.draw(quitButtonText);
}

void renderShop(sf::RenderWindow &window, sf::Font &font, sf::Text &shopTitle, sf::Text &shovelText, sf::Text &blowerText, sf::Text &poweredBlowerText, sf::Text &crewText) {
    window.draw(shopTitle);
    window.draw(shovelText);
    window.draw(blowerText);
    window.draw(poweredBlowerText);
    window.draw(crewText);
}

void renderTools(sf::RenderWindow &window, sf::Font &font, sf::Text &toolsTitle, sf::Text &toolsList) {
    window.draw(toolsTitle);
    window.draw(toolsList);
}
