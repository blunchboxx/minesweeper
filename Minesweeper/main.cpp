#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <cmath>
#include "board.h"
#include "tile.h"
#include "Button.h"
#include "Digit.h"
using namespace std;

void readConfig(vector<int>& configValues)
{
    ifstream configFile;
    string newLine, token;

    configFile.open("boards/config.cfg");

    if (!configFile.is_open()) {
        cout << "Cannot open configuration file to read." << endl;
        cout << "Loading default configuration..." << endl;
        configValues.push_back(25);
        configValues.push_back(16);
        configValues.push_back(50);
    }
    else
    {
        while (getline(configFile, newLine))
        {
            istringstream ss(newLine); // Send next line to stream

            while (getline(ss, token))  // Loop through entire stream
            {
                configValues.push_back(stoi(token));
            }

        }
        for (int i = 0; i < configValues.size(); ++i)
            cout << "Config Value " << i << ": " << configValues[i] << endl;
    }
}

void drawCurrentScreen()
{
    /*
    window.clear(sf::Color::Color(211, 211, 211, 255));  // mandatory before drawing or previous image will remain

    gameBoard.drawBoard(window);
    smileButton.drawButton(window, smileButton.normalButtonTexture);
    debugButton.drawButton(window, debugButton.debugButtonTexture);
    test1Button.drawButton(window, test1Button.test1ButtonTexture);
    test2Button.drawButton(window, test2Button.test2ButtonTexture);
    test3Button.drawButton(window, test3Button.test3ButtonTexture);

    window.display(); // mandatory after drawing*/
}

// Maybe obsolete?
void initializeCounterTiles(map<int, Digit*>& digitMap, map<string, sf::Texture>& textures)
{
    Digit onesDigit(63, 515, textures);
    Digit tensDigit(42, 515, textures);
    Digit hundredsDigit(21, 515, textures);
    Digit negDigit(0, 515, textures);

    Digit* onesPtr = &onesDigit;
    Digit* tensPtr = &tensDigit;
    Digit* hundredsPtr = &hundredsDigit;
    Digit* negPtr = &negDigit;

    digitMap.emplace(1, onesPtr);
    digitMap.emplace(10, tensPtr);
    digitMap.emplace(100, hundredsPtr);
    digitMap.emplace(-1, negPtr);
}

void drawButtons()
{

}

void resizeWindow(sf::RenderWindow& screen, map<int, Digit*>& digitMap, map<string, Button*>& buttonMap, sf::View& mainView, int newWidth, int newHeight)
{
    screen.setSize(sf::Vector2u(newWidth, newHeight));

    mainView.reset(sf::FloatRect(0, 0, newWidth, newHeight));
    mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    // Reset button positions for new window
    buttonMap["smile"]->setButtonPos(newWidth / 2 - 32, newHeight - 85);
    buttonMap["debug"]->setButtonPos(newWidth - 75, newHeight - 85);
    buttonMap["test1"]->setButtonPos(newWidth - 275, newHeight - 85);
    buttonMap["test2"]->setButtonPos(newWidth - 215, newHeight - 85);
    buttonMap["test3"]->setButtonPos(newWidth - 155, newHeight - 85);

    buttonMap["smile"]->drawButton(screen);
    buttonMap["debug"]->drawButton(screen);
    buttonMap["test1"]->drawButton(screen);
    buttonMap["test2"]->drawButton(screen);
    buttonMap["test3"]->drawButton(screen);

    sf::Vector2f buttonLocation(buttonMap["smile"]->getSprite().getPosition().x, buttonMap["smile"]->getSprite().getPosition().y);

    digitMap[1]->setDigitPos(63, newHeight - 95);
    digitMap[10]->setDigitPos(42, newHeight - 95);
    digitMap[100]->setDigitPos(21, newHeight - 95);
    digitMap[-1]->setDigitPos(0, newHeight - 95);
}

void initializeTextures(map<string, sf::Texture>& textureMap)
{
    // Create Texture Objects
    sf::Texture hiddenTileTexture;
    sf::Texture revealedTileTexture;
    sf::Texture flaggedTileTexture;
    sf::Texture mineTileTexture;
    sf::Texture digitTexture;
    sf::Texture numOneTexture;
    sf::Texture numTwoTexture;
    sf::Texture numThreeTexture;
    sf::Texture numFourTexture;
    sf::Texture numFiveTexture;
    sf::Texture numSixTexture;
    sf::Texture numSevenTexture;
    sf::Texture numEightTexture;
    sf::Texture smileButtonTexture;
    sf::Texture clickedButtonTexture;
    sf::Texture defeatButtonTexture;
    sf::Texture winButtonTexture;
    sf::Texture debugButtonTexture;
    sf::Texture test1ButtonTexture;
    sf::Texture test2ButtonTexture;
    sf::Texture test3ButtonTexture;

    // Load corresponding image file to texture
    hiddenTileTexture.loadFromFile("images/tile_hidden.png");
    revealedTileTexture.loadFromFile("images/tile_revealed.png");
    flaggedTileTexture.loadFromFile("images/flag.png");
    mineTileTexture.loadFromFile("images/mine.png");
    digitTexture.loadFromFile("images/digits.png");
    numOneTexture.loadFromFile("images/number_1.png");
    numTwoTexture.loadFromFile("images/number_2.png");
    numThreeTexture.loadFromFile("images/number_3.png");
    numFourTexture.loadFromFile("images/number_4.png");
    numFiveTexture.loadFromFile("images/number_5.png");
    numSixTexture.loadFromFile("images/number_6.png");
    numSevenTexture.loadFromFile("images/number_7.png");
    numEightTexture.loadFromFile("images/number_8.png");
    smileButtonTexture.loadFromFile("images/face_happy.png");
    clickedButtonTexture.loadFromFile("images/face_clicked.png");
    defeatButtonTexture.loadFromFile("images/face_lose.png");
    winButtonTexture.loadFromFile("images/face_win.png");
    debugButtonTexture.loadFromFile("images/debug.png");
    test1ButtonTexture.loadFromFile("images/test_1.png");
    test2ButtonTexture.loadFromFile("images/test_2.png");
    test3ButtonTexture.loadFromFile("images/test_3.png");

    // Place loaded textures into texture map
    textureMap.emplace("hidden", hiddenTileTexture);
    textureMap.emplace("revealed", revealedTileTexture);
    textureMap.emplace("flagged", flaggedTileTexture);
    textureMap.emplace("mined", mineTileTexture);
    textureMap.emplace("digits", digitTexture);
    textureMap.emplace("1", numOneTexture);
    textureMap.emplace("2", numTwoTexture);
    textureMap.emplace("3", numThreeTexture);
    textureMap.emplace("4", numFourTexture);
    textureMap.emplace("5", numFiveTexture);
    textureMap.emplace("6", numSixTexture);
    textureMap.emplace("7", numSevenTexture);
    textureMap.emplace("8", numEightTexture);
    textureMap.emplace("smile", smileButtonTexture);
    textureMap.emplace("cSmile", clickedButtonTexture);
    textureMap.emplace("defeat", defeatButtonTexture);
    textureMap.emplace("victory", winButtonTexture);
    textureMap.emplace("debug", debugButtonTexture);
    textureMap.emplace("test 1", test1ButtonTexture);
    textureMap.emplace("test 2", test2ButtonTexture);
    textureMap.emplace("test 3", test3ButtonTexture);
}

void updateCounter(Board board, map<int, Digit*>& digitMap, map<string, sf::Texture>& textures)
{
    int tempNum;
    vector<int> digitVals;
    
    int counterNum = board._numMines - board._numFlags;

    // Check if mine counter is negative
    if (counterNum < 0)
    {
        digitMap[-1]->setDigitDisplay(10);  // Display negative symbol if negative
    }
    else
    {
        digitMap[-1]->setDigitDisplay(0); // Set to 0 if not negativve
    }

    counterNum = abs(counterNum);

    for (int j = 0; j < 3; ++j)
    {
        tempNum = counterNum % 10;
        digitVals.push_back(tempNum);

        counterNum = counterNum / 10;
    }

    // Set 1's digit IntRect
    digitMap[1]->setDigitDisplay(digitVals[0]);

    // Set 10's digit IntRect
    digitMap[10]->setDigitDisplay(digitVals[1]);

    // Set 100's digit IntRect
    digitMap[100]->setDigitDisplay(digitVals[2]);
}

bool recursiveReveal(Board& gameBoard, int clickRow, int clickCol)
{
    for (unsigned int i = 0; i < gameBoard._tileVector[clickRow][clickCol]._adjacentTiles.size(); i++)
    {
        // Get actual tile row and column for reference (BUG: FIXME - ADJACENT TILE VECTOR TILES NOT UPDATING. COPIES CREATED? FIXME)
        unsigned int tempRow = gameBoard._tileVector[clickRow][clickCol]._adjacentTiles[i]->_row;
        unsigned int tempCol = gameBoard._tileVector[clickRow][clickCol]._adjacentTiles[i]->_col;

        if (gameBoard._tileVector[tempRow][tempCol]._revealed == false) {
                        
            // Reveal adjacent tile as long as it is not flagged
            if ((gameBoard._tileVector[tempRow][tempCol]._flagged == false)) {
                gameBoard._tileVector[tempRow][tempCol]._revealed = true;

                if (gameBoard._tileVector[tempRow][tempCol]._numAdjacentMines == 0) { // If adjacent tile was revealed, check if it has any adjacent mines. If not, move to next adjacent tile
                    recursiveReveal(gameBoard, tempRow, tempCol);
                }
            }
        }
    }

    return false; // If all adjacent tiles looped through and no further recursive calls required, return to calling function.
}

void checkWin(Board& board, bool& gameWin, bool& gameOver)
{
    int tempNum = 0;

    for (int row = 0; row < board._numRows; row++)  // Loop through each tile
    {
        for (int col = 0; col < board._numCols; ++col)
        {
            if ((board._tileVector[row][col]._revealed == true) && (board._tileVector[row][col]._mined == false))
            {
                tempNum++;  // Calculate number of non-mine tiles player has revealed so far
            }
        }
    }

    board._numNotMines = (board._numCols * board._numRows) - board._numMines - tempNum; // Calculate number of tiles left to reveal in order to win

    // If all non-mine tiles revealed, set game win flags
    if (board._numNotMines == 0) 
    {
        gameWin = true;
        gameOver = true;
    }
}

int main()
{
    // Read in and store configuration data
    vector<int> configurationData;
    readConfig(configurationData);

    // Set initial window and board values based on configuration data
    float windowWidth = configurationData[0] * 32;
    float windowHeight = configurationData[1] * 32 + 100;
    int numColumns = configurationData[0];
    int numRows = configurationData[1];
    int numberOfMines = configurationData[2];

    // Initialize screen/window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    
    // Set up view to allow window resize
    sf::View mainView;
    mainView.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
    mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    // Initialize textures
    map<string, sf::Texture> textureMap;
    initializeTextures(textureMap);


    // Initialize buttons and pointers
    Button smileButton(windowWidth / 2 - 32, windowHeight - 85, "smile", textureMap);
    Button debugButton(windowWidth - 75, windowHeight - 85, "debug", textureMap);
    Button test1Button(windowWidth - 275, windowHeight - 85, "test 1", textureMap);
    Button test2Button(windowWidth - 215, windowHeight - 85, "test 2", textureMap);
    Button test3Button(windowWidth - 155, windowHeight - 85, "test 3", textureMap);
    
    Button* smilePtr = &smileButton;
    Button* debugPtr = &debugButton;
    Button* test1Ptr = &test1Button;
    Button* test2Ptr = &test2Button;
    Button* test3Ptr = &test3Button;

    // Store button pointers in map
    map<string, Button*> buttonMap;
    buttonMap.emplace("smile", smilePtr);
    buttonMap.emplace("debug", debugPtr);
    buttonMap.emplace("test1", test1Ptr);
    buttonMap.emplace("test2", test2Ptr);
    buttonMap.emplace("test3", test3Ptr);
    
    // Initialize counter tiles and map of pointers for storage
    map<int, Digit*> digitPtrMap;

    Digit onesDigit(63, windowHeight - 95, textureMap);
    Digit tensDigit(42, windowHeight - 95, textureMap);
    Digit hundredsDigit(21, windowHeight - 95, textureMap);
    Digit negDigit(0, windowHeight - 95, textureMap);

    Digit* onesPtr = &onesDigit;
    Digit* tensPtr = &tensDigit;
    Digit* hundredsPtr = &hundredsDigit;
    Digit* negPtr = &negDigit;

    // Store digit pointers in map
    digitPtrMap.emplace(1, onesPtr);
    digitPtrMap.emplace(10, tensPtr);
    digitPtrMap.emplace(100, hundredsPtr);
    digitPtrMap.emplace(-1, negPtr);

    // Initialize initial game board and game over flag
    Board gameBoard(textureMap, numRows, numColumns, numberOfMines);
    bool gameOver = false;
    bool gameWon = false;

    updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer

    // DEBUG - remove
    gameBoard.printBoard();
    cout << endl;

    while (window.isOpen())
    {
        int clickCol = -1;
        int clickRow = -1;

        sf::Event event;
        while (window.pollEvent(event))
        {      
           
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                /*------------------ Gameboard click loop -------------------*/
                if (((event.mouseButton.y / 32) <= gameBoard._numRows - 1) and gameOver == false)  // If click is within game board and game is not over
                {
                    // Left click check loop
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        auto xCoordinate = event.mouseButton.x;
                        auto yCoordinate = event.mouseButton.y;
                        clickCol = xCoordinate / 32; // Convert click pixel location to row and column
                        clickRow = yCoordinate / 32;

                        // If clicked tile is not flagged and is not already revealed
                        if ((gameBoard._tileVector[clickRow][clickCol]._flagged == false) and (gameBoard._tileVector[clickRow][clickCol]._revealed == false))
                        {
                            gameBoard._tileVector[clickRow][clickCol]._revealed = true;

                            // If clicked tile is a mine, set game over (loss) conditions
                            if (gameBoard._tileVector[clickRow][clickCol]._mined == true)
                            {
                                gameOver = true;
                                gameWon = false;
                            }
                            // Else, if clicked tile has no adjacent mines and is not a mine
                            else if ((gameBoard._tileVector[clickRow][clickCol]._numAdjacentMines == 0) and (gameBoard._tileVector[clickRow][clickCol]._mined == false))
                            {
                                recursiveReveal(gameBoard, clickRow, clickCol); // Run recursion reveal to reveal neighboring tiles

                            }
                        }

                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                        checkWin(gameBoard, gameWon, gameOver); // Check if game has been won
                        
                        // Game over - defeat conditions
                        if ((gameOver == true) and (gameWon == false))
                        {
                            // Set main button to game loss texture
                            smileButton.setButtonTexture("defeat", textureMap);

                            for (int row = 0; row < gameBoard._numRows; row++)
                            {
                                for (int col = 0; col < gameBoard._numCols; col++)
                                {
                                    if ((gameBoard._tileVector[row][col]._mined == true) and ((gameBoard._tileVector[row][col]._revealed == false)))
                                    {
                                        gameBoard._tileVector[row][col]._revealed = true;  // Reveal all mines after defeat

                                    }
                                }
                            }

                            updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                        }

                        // Game over - victory conditions
                        else if (gameWon == true)
                        {
                            // Set main button to game loss texture
                            smileButton.setButtonTexture("victory", textureMap);

                            // Turn off debug mode
                            gameBoard.debug(window, textureMap);

                            for (int row = 0; row < gameBoard._numRows; row++)
                            {
                                for (int col = 0; col < gameBoard._numCols; col++)
                                {
                                    if ((gameBoard._tileVector[row][col]._mined == true) and ((gameBoard._tileVector[row][col]._revealed == false)))
                                    {
                                        gameBoard._tileVector[row][col]._flagged = true; // Flag all unrevealed mines
                                        gameBoard._numFlags++; // Increase number of flags by 1
                                    }
                                }
                            }

                            updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                        }
                    }
                    // Right click check loop
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        auto xCoordinate = event.mouseButton.x;
                        auto yCoordinate = event.mouseButton.y;

                        clickCol = xCoordinate / 32;
                        clickRow = yCoordinate / 32;

                        if ((gameBoard._tileVector[clickRow][clickCol]._flagged == false) and ((gameBoard._tileVector[clickRow][clickCol]._revealed == false)))
                        {
                            gameBoard._tileVector[clickRow][clickCol]._flagged = true;
                            gameBoard._numFlags++; // Increase number of flags by 1
                        }

                        else if ((gameBoard._tileVector[clickRow][clickCol]._flagged == true) and ((gameBoard._tileVector[clickRow][clickCol]._revealed == false)))
                        {
                            gameBoard._tileVector[clickRow][clickCol]._flagged = false;
                            gameBoard._tileVector[clickRow][clickCol]._revealed = false;

                            gameBoard._numFlags--; // Decrease number of flags by 1
                        }

                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                        checkWin(gameBoard, gameWon, gameOver); // Check if game has been won
                    }
                }

                /*------------------ Control bar click loop -------------------*/
                else if ((event.mouseButton.y / 32) > gameBoard._numRows - 1)
                {

                    sf::Vector2f mouseClick = window.mapPixelToCoords(sf::Mouse::getPosition(window));                

                    if (smileButton.getBounds().contains(mouseClick)) // Check if mouse is inside main smile button
                    {
                        gameBoard.resetBoard(textureMap);
                        gameBoard.loadDefaultBoard(textureMap, configurationData[1], configurationData[0], configurationData[2]);
                        smileButton.setButtonTexture("smile", textureMap);
                        gameOver = false; // Reset game over flag
                        gameWon = false;

                        windowWidth = gameBoard._numCols * 32;
                        windowHeight = gameBoard._numRows * 32 + 100;
                        resizeWindow(window, digitPtrMap, buttonMap, mainView, windowWidth, windowHeight);
                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                    }
                    else if ((debugButton.getBounds().contains(mouseClick)) and gameOver == false)// Check if mouse is inside debug button
                    {
                        gameBoard.debug(window, textureMap);
                    }
                    else if (test1Button.getBounds().contains(mouseClick)) // Check if mouse is inside Test Button 1
                    {
                        gameBoard.resetBoard(textureMap);
                        smileButton.setButtonTexture("smile", textureMap);
                        gameOver = false; // Reset game over flag
                        gameWon = false;
                        gameBoard.loadBoard("boards/testBoard1.brd");
                        gameBoard.initializeTiles(textureMap, gameBoard._numRows, gameBoard._numCols, gameBoard._numMines);
                        gameBoard.printBoard();
                        
                        windowWidth = gameBoard._numCols * 32;
                        windowHeight = gameBoard._numRows * 32 + 100;
                        resizeWindow(window, digitPtrMap, buttonMap, mainView, windowWidth, windowHeight);
                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                        cout << "Number of unrevealed tiles = " << gameBoard._numNotMines << endl;
                        cout << "New board size: " << gameBoard._numRows << " " << gameBoard._numCols << endl;
                    }
                    else if (test2Button.getBounds().contains(mouseClick)) // Check if mouse is inside Test Button 2
                    {
                        gameBoard.resetBoard(textureMap);
                        smileButton.setButtonTexture("smile", textureMap);
                        gameOver = false; // Reset game over flag
                        gameWon = false;
                        gameBoard.loadBoard("boards/testBoard2.brd");
                        gameBoard.initializeTiles(textureMap, gameBoard._numRows, gameBoard._numCols, gameBoard._numMines);
                        gameBoard.printBoard();

                        windowWidth = gameBoard._numCols * 32;
                        windowHeight = gameBoard._numRows * 32 + 100;
                        resizeWindow(window, digitPtrMap, buttonMap, mainView, windowWidth, windowHeight);
                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                    }
                    else if (test3Button.getBounds().contains(mouseClick)) // Check if mouse is inside Test Button 3
                    {
                        cout << "Test 3 Button clicked" << endl;
                        smileButton.setButtonTexture("smile", textureMap);
                        gameBoard.resetBoard(textureMap);
                        gameOver = false; // Reset game over flag
                        gameWon = false;
                        gameBoard.loadBoard("boards/testBoard3.brd");
                        gameBoard.initializeTiles(textureMap, gameBoard._numRows, gameBoard._numCols, gameBoard._numMines);
                        gameBoard.printBoard();

                        windowWidth = gameBoard._numCols * 32;
                        windowHeight = gameBoard._numRows * 32 + 100;
                        resizeWindow(window, digitPtrMap, buttonMap, mainView, windowWidth, windowHeight);
                        updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                    }

                    updateCounter(gameBoard, digitPtrMap, textureMap); // Update counter with every click with pointer
                    checkWin(gameBoard, gameWon, gameOver); // Check if game has been won
                }
            }
        }

        // Main drawing commands
        window.clear(sf::Color::Color(211, 211, 211, 255));  // mandatory before drawing or previous image will remain

        // Draw board, tiles, buttons
        gameBoard.drawBoard(window, textureMap);
        smileButton.drawButton(window);
        debugButton.drawButton(window);
        test1Button.drawButton(window);
        test2Button.drawButton(window);
        test3Button.drawButton(window);

        // Draw mine counter
        digitPtrMap[1]->drawDigit(0, window);
        digitPtrMap[10]->drawDigit(0, window);
        digitPtrMap[100]->drawDigit(0, window);
        digitPtrMap[-1]->drawDigit(0, window);

        window.setView(mainView); // Set view to current view

        window.display(); // mandatory after drawing
    }

    return 0;
}