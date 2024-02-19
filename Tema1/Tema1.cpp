#include "Tema1.h"

#include <vector>
#include <iostream>
#include <random>

#include "transform2D.h"
#include "objects2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // variables for shooting stars at equal intervals of time
    fixedTime = 3;
    contorTime = 0;

    // number of lives in the game
    gameLives = 3;

    // time passed since last star was rendered
    timeStarPassed = 0;

    // time passed since last enemy was rendered
    timeEnemyPassed = 0;

    // initial resources to get rhombus on the grid
    totalPoints = 5;
    // whether player pressed on a frame or not
    pressedOnFrame = false;
    detectedFrame = NULL;
     

    {
        squareSide = 120;
        halfSide = squareSide / 2;
    }

    // colors
    {
        backgroundColor = glm::vec3(0.4f, 0.5f, 0.8f);
        squareColor = glm::vec3(0.85f, 0.85f, 0.95f);
        rectColor = glm::vec3(0.55f, 0.13f, 0.13f);

        frameColor = glm::vec3(0, 0, 0);

        rhombColors = { glm::vec3(1, 0.43f, 0.78f),
                        glm::vec3(0.84f, 0.74f, 0.84f),
                        glm::vec3(0.35f, 0.35f, 0.67f),
                        glm::vec3(0.36f, 0.2f, 0.09f) };
        enemyColors = { glm::vec3(1, 0.43f, 0.78f),
                        glm::vec3(0.84f, 0.74f, 0.84f),
                        glm::vec3(0.35f, 0.35f, 0.67f),
                        glm::vec3(0.36f, 0.2f, 0.09f) };
        starColors = { glm::vec3(0.22f, 0.69f, 0.87f),
                       glm::vec3(0.65f, 0.65f, 0.65f) };
    }
    
    // initialize frames vector
    frames = vector<Frames>(4);
    for (int i = 0; i < frames.size(); i++) {
		frames[i].Frames::setColor(rhombColors[i]);
		frames[i].Frames::setLength(squareSide);
	}

    // initialize squares vector
    grid = vector<Square>(9);
    for (int i = 0; i < grid.size(); i++) {
        grid[i].setLength(squareSide);
    }

    // Initialize the centers of the 3x3 grid and frames
    {
        linesX.x = 130;
        linesY.x = 70;

        linesX.w = 105;
        linesY.w = 640;

        deltaGrid = squareSide * 1.25;
    }


    // enemy animation variables    
    enemyTranslateX = 1300; // out of the screen
    enemyTranslateY = 300;

    // star animation variables
    starTranslateX = 400;
    starTranslateY = 300;
    starRotate = 0;

    starTranslateX1 = 400;
    starTranslateY1 = 300;

    // radius for collision
    radiusEnemy = 50;
    scaleDownEnemy = radiusEnemy;
    radiusIntEnemy = 35;
    scaleDownIntEnemy = radiusIntEnemy;

    radiusStar = 50;

    // scale down animation variables
    scaleDownRhombusX = 0.3f;
    scaleDownRhombusY = 0.6f;

    scaleDownRectX = scaleDownRhombusX * sqrt(2);
    scaleDownRectY = 0.2f;

    

    // Initialize angularStep
    angularStep = PI / 4;

    // render state
    renderStar = true;
    renderRhombus = true;
    renderEnemy = true;

    // create meshes for grid and frames
    {
        Mesh* squareInOrigin = objects2D::CreateSquareInOrigin("squareInOrigin", squareSide, squareColor, true);
        AddMeshToList(squareInOrigin);

        Mesh* frame = objects2D::CreateSquareInOrigin("frame", squareSide, frameColor, false);
        AddMeshToList(frame);
    }

    // create mesh for rect
    {
        Mesh* rect = objects2D::CreateSquareInOrigin("rect", squareSide, rectColor, true);
        AddMeshToList(rect);
    }

    // create meshes for rhombus and rect
    {
        Mesh* rect1 = objects2D::CreateSquareInOrigin("rect1", squareSide, rhombColors[0], true, 2);
        AddMeshToList(rect1);

        Mesh* rect2 = objects2D::CreateSquareInOrigin("rect2", squareSide, rhombColors[1], true, 2);
        AddMeshToList(rect2);

        Mesh* rect3 = objects2D::CreateSquareInOrigin("rect3", squareSide, rhombColors[2], true, 2);
        AddMeshToList(rect3);

        Mesh* rect4 = objects2D::CreateSquareInOrigin("rect4", squareSide, rhombColors[3], true, 2);
        AddMeshToList(rect4);

        Mesh* romb1 = objects2D::CreateSquareInOrigin("romb1", squareSide, rhombColors[0], true, 2);
        AddMeshToList(romb1);

        Mesh* romb2 = objects2D::CreateSquareInOrigin("romb2", squareSide, rhombColors[1], true, 2);
        AddMeshToList(romb2);

        Mesh* romb3 = objects2D::CreateSquareInOrigin("romb3", squareSide, rhombColors[2], true, 2);
        AddMeshToList(romb3);

        Mesh* romb4 = objects2D::CreateSquareInOrigin("romb4", squareSide, rhombColors[3], true, 2);
        AddMeshToList(romb4);
    }

    // create meshes for hexagon
    {
        enemyMeshes = { "hexagon1", "hexagon2", "hexagon3", "hexagon4" };

        Mesh* hexagon1 = objects2D::CreateHexagon("hexagon1", enemyColors[0], 3);
        AddMeshToList(hexagon1);

        Mesh* hexagon2 = objects2D::CreateHexagon("hexagon2", enemyColors[1], 3);
        AddMeshToList(hexagon2);

        Mesh* hexagon3 = objects2D::CreateHexagon("hexagon3", enemyColors[2], 3);
        AddMeshToList(hexagon3);

        Mesh* hexagon4 = objects2D::CreateHexagon("hexagon4", enemyColors[3], 3);
        AddMeshToList(hexagon4);

        Mesh* hexagonInterior = objects2D::CreateHexagon("hexagonInterior", glm::vec3(0.96, 0.8, 0.69), 4);
        AddMeshToList(hexagonInterior);
    }

    // create meshes for star
    {
        Mesh* star = objects2D::CreateStar("star", starColors[0]);
        AddMeshToList(star);

        Mesh* star1 = objects2D::CreateStar("star1", rhombColors[0]);
        AddMeshToList(star1);

        Mesh* star2 = objects2D::CreateStar("star2", rhombColors[1]);
        AddMeshToList(star2);

        Mesh* star3 = objects2D::CreateStar("star3", rhombColors[2]);
        AddMeshToList(star3);

        Mesh* star4 = objects2D::CreateStar("star4", rhombColors[3]);
        AddMeshToList(star4);

        

        Mesh* points = objects2D::CreateStar("points", starColors[1]);
        AddMeshToList(points);
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}



void Tema1::Update(float deltaTimeSeconds)
{
    // render all the objects that are not animated
    ////////////////////////////////////////////////

    // render the 3x3 grid of squares
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            modelMatrix = glm::mat3(1);
            //modelMatrix *= transform2D::Scale(1.2, 1.2);
            float xCoord = linesX.x + i * deltaGrid;
            float yCoord = linesY.x + j * deltaGrid;
            modelMatrix *= transform2D::Translate(xCoord, yCoord);
            
            RenderMesh2D(meshes["squareInOrigin"], shaders["VertexColor"], modelMatrix);
            
            grid[i + 3 * j].setPosition(glm::vec2(xCoord, yCoord));

            if (i == 0) {
                if (j == 1)
                    linesY.y = yCoord;
                else if (j == 2)
                    linesY.z = yCoord;
            }

            if (j == 0) {
                if (i == 1)
					linesX.y = xCoord;
                else if (i == 2)
					linesX.z = xCoord;
            }
        }
    }

    

    // vector of strings
    vector<string> rhombusTypes = { "romb1", "romb2", "romb3", "romb4" };
    vector<string> rectTypes = { "rect1", "rect2", "rect3", "rect4" };

    // render the frames and the points
    for (int i = 0; i < 4; i++) {
        float xCoord = linesX.w + i * squareSide * 1.5;
        
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(xCoord, linesY.w);
		RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

        frames[i].setPosition(glm::vec2(xCoord, linesY.w));

        float scaleX = 0.3f;
        float scaleY = 2 * scaleX;

        // we scale the rhombus so that vertical diagonal is twice the horizontal one
        // than the rect is scaled so that the entire figure has a radius the length
        // of the vertical diagonal of the rhombus from the center of the rhombus
        
        // render the rhombus and the rect
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(xCoord, linesY.w);
        modelMatrix *= transform2D::Scale(scaleX, scaleY);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes[rhombusTypes[i]], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(xCoord + scaleX * squareSide * sqrt(2) / 2, linesY.w);
        modelMatrix *= transform2D::Scale(sqrt(2) * scaleX, 0.2f);
        RenderMesh2D(meshes[rectTypes[i]], shaders["VertexColor"], modelMatrix);

        frames[i].setMeshRect(rectTypes[i]);
        frames[i].setMeshRhomb(rhombusTypes[i]);

        if (i == 0) frames[i].setPoints(1);
        else if (i == 1 || i == 2) frames[i].setPoints(2);
		else if (i == 3) frames[i].setPoints(3);

        int scale = 20;

        for (int j = 0; j < frames[i].getPoints(); j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(xCoord - squareSide / 2 + scale + j * scale * 2, linesY.w - squareSide / 2 - scale);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["points"], shaders["VertexColor"], modelMatrix);
        }
	}

    // when an enemy touches the border, player loses a life
    border = linesX.x - squareSide / 1.2;

    // render the rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(border, linesY.y);
    modelMatrix *= transform2D::Scale(0.4, (2 * deltaGrid + squareSide) / squareSide);
    RenderMesh2D(meshes["rect"], shaders["VertexColor"], modelMatrix);

    float scaleSquare = 0.8f;
    float scaleStar = 20;


    // render the square lives
    for (int i = 0; i < gameLives; i++) {

		modelMatrix = glm::mat3(1);
        // 144 = 120 * 0.8 * 1.5
		modelMatrix *= transform2D::Translate(linesX.w + 4 * squareSide * 1.5 + i * squareSide * scaleSquare * 1.5, linesY.w);
        modelMatrix *= transform2D::Scale(scaleSquare, scaleSquare);
		RenderMesh2D(meshes["rect"], shaders["VertexColor"], modelMatrix);
	}

    // render the points
    for (int i = 0; i < totalPoints; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(linesX.w + 4 * squareSide * 1.5 - squareSide * scaleSquare / 2 + scaleStar + i * scaleStar * 2, linesY.w - squareSide * scaleSquare / 2 - scaleStar);
        modelMatrix *= transform2D::Scale(scaleStar, scaleStar);
        RenderMesh2D(meshes["points"], shaders["VertexColor"], modelMatrix);
    }

    ////////////////////////////////////////////////

    // get resolution of the window
    glm::ivec2 resolution = window->GetResolution();

    for (itR = rhombusList.begin(); itR != rhombusList.end();) {
		RhombusRect* rhombusRect = &(*itR);
        if (rhombusRect->getRendered() == true) {
			// render rhombus and rect
            if (rhombusRect->getShrinked() == true) {
                float scaleXRect = rhombusRect->getScaleXRect();
                float scaleYRect = rhombusRect->getScaleYRect();
                float scaleXRhombus = rhombusRect->getScaleXRhombus();
                float scaleYRhombus = rhombusRect->getScaleYRhombus();

                if (scaleXRect <= 0.3f && scaleYRect <= 0.3f && scaleXRhombus <= 0.3f && scaleYRhombus <= 0.3f) {
                    // erase element from vector
                    itR = rhombusList.erase(itR);
                    continue;
                }
                
                if (scaleXRect > 0.0f)
                    rhombusRect->setScaleXRect(scaleXRect - deltaTimeSeconds * scaleXRect);

				if (scaleYRect > 0.0f)
                    rhombusRect->setScaleYRect(scaleYRect - deltaTimeSeconds);

                if (scaleXRhombus > 0.0f)
					rhombusRect->setScaleXRhombus(scaleXRhombus - deltaTimeSeconds * scaleXRhombus * 7.5f);

                if (scaleYRhombus > 0.0f)
					rhombusRect->setScaleYRhombus(scaleYRhombus - deltaTimeSeconds * scaleYRhombus * 7.5f);

            }
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(rhombusRect->getRhombusCenter().x, rhombusRect->getRhombusCenter().y);
            modelMatrix *= transform2D::Scale(rhombusRect->getScaleXRhombus(), rhombusRect->getScaleYRhombus());
            modelMatrix *= transform2D::Rotate(angularStep);

            RenderMesh2D(meshes[rhombusRect->getRhombMesh()], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(rhombusRect->getRectCenter().x, rhombusRect->getRectCenter().y);
            modelMatrix *= transform2D::Scale(rhombusRect->getScaleXRect(), rhombusRect->getScaleYRect());

            RenderMesh2D(meshes[rhombusRect->getRectMesh()], shaders["VertexColor"], modelMatrix);

            
            itR++;
        }
        else if (rhombusRect->getRendered() == false) {
            // erase element from vector
            itR = rhombusList.erase(itR);
        }
    }

    
    std::random_device random;
    std::mt19937_64 gen(random());
    std::uniform_int_distribution<int> distColor(0, 3);
    std::uniform_int_distribution<int> distLines(0, 2);
    std::uniform_int_distribution<int> distEnemyTime(5, 8);
    std::uniform_int_distribution<int> distStarTime(10, 15);
    std::uniform_real_distribution<float> posXStar(radiusStar, resolution.x - radiusStar);
    std::uniform_real_distribution<float> posYStar(radiusStar, resolution.y - radiusStar);

    // we render a star every 3-5 seconds
    int randomTimeStar = distStarTime(gen);
    if (timeStarPassed > randomTimeStar) {
		// we render a star
        float randomXPos = posXStar(gen);
        float randomYPos = posYStar(gen);
        Star star1 = Star();
        star1.setStarCenter(glm::vec2(randomXPos, randomYPos));
        star1.setMeshStarName("star");
        pointsStars.push_back(star1);

        randomXPos = posXStar(gen);
        randomYPos = posYStar(gen);
        Star star2 = Star();
        star2.setStarCenter(glm::vec2(randomXPos, randomYPos));
        star2.setMeshStarName("star");
        pointsStars.push_back(star2);

        randomXPos = posXStar(gen);
        randomYPos = posYStar(gen);
        Star star3 = Star();
        star3.setStarCenter(glm::vec2(randomXPos, randomYPos));
        star3.setMeshStarName("star");
        pointsStars.push_back(star3);

        timeStarPassed = 0;
        
	}
    else {
		timeStarPassed += deltaTimeSeconds;
	}

    for (itS = pointsStars.begin(); itS != pointsStars.end();) {
        // render the stars
        Star* star = &(*itS);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(star->getStarCenter().x, star->getStarCenter().y);
        modelMatrix *= transform2D::Scale(star->getStarRadius(), star->getStarRadius());
        RenderMesh2D(meshes[star->getMeshStarName()], shaders["VertexColor"], modelMatrix);
        itS++;
    }

    int randomTimeEnemy = distEnemyTime(gen);
    if (timeEnemyPassed > randomTimeEnemy) {
		// we create an enemy and it to a list
        int randomLine = distLines(gen);
        int randomColor = distColor(gen);
        Enemy enemy = Enemy();
		enemy.setEnemyMesh(enemyMeshes[randomColor]);
        if (randomLine == 0) enemy.setLine(linesY.x);
        else if (randomLine == 1) enemy.setLine(linesY.y);
        else if (randomLine == 2) enemy.setLine(linesY.z);

        enemy.setEnemyCenter(glm::vec2(1300, enemy.getLine()));

        
		enemies.push_back(enemy);
		timeEnemyPassed = 0;
	}
    else {
		timeEnemyPassed += deltaTimeSeconds;
	}

    // erase enemies that are out of the screen
    for (itE = enemies.begin(); itE != enemies.end();) {
        Enemy* enemy = &(*itE);
        if (enemy->getEnemyCenter().x <= border) {
            // erase enemy
            gameLives--;
            if (gameLives == 0) {
                // shut down game window
                exit(0);
            }
            itE = enemies.erase(itE);

        }
        else {
            itE++;
        }
    }

    contorTime += deltaTimeSeconds;

    

    // parcuge lista de inamici si randeaza-i
    for (itE = enemies.begin(); itE != enemies.end();) {
        Enemy* enemy = &(*itE);
        if (enemy->getRendered() == true) {
            // render the enemy
            if (enemy->killed == true) {
                float scaleEnemy = enemy->getScaleEnemy();
                float scaleInt = enemy->getScaleInt();

                if (scaleEnemy < 1.0f && scaleInt < 1.0f) {
                    // erase element from vector
                    itE = enemies.erase(itE);
                    continue;
                }

                if (scaleEnemy > 0.0f)
                    enemy->setScaleEnemy(scaleEnemy - deltaTimeSeconds * scaleEnemy * 5);

                if (scaleInt > 0.0f)
                    enemy->setScaleInt(scaleInt - deltaTimeSeconds * scaleInt * 5);

                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(enemy->getEnemyCenter().x, enemy->getEnemyCenter().y);
                modelMatrix *= transform2D::Scale(enemy->getScaleEnemy(), enemy->getScaleEnemy());
                modelMatrix *= transform2D::Rotate(PI / 4);
                RenderMesh2D(meshes[enemy->getEnemyMesh()], shaders["VertexColor"], modelMatrix);

                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(enemy->getEnemyCenter().x, enemy->getEnemyCenter().y);
                modelMatrix *= transform2D::Scale(enemy->getScaleInt(), enemy->getScaleInt());
                modelMatrix *= transform2D::Rotate(PI / 4);
                RenderMesh2D(meshes["hexagonInterior"], shaders["VertexColor"], modelMatrix);

            }
            else {

                float xCoord = enemy->getEnemyCenter().x;
                xCoord -= deltaTimeSeconds * 50;
                enemy->setEnemyCenter(glm::vec2(xCoord, enemy->getLine()));

                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(enemy->getEnemyCenter().x, enemy->getEnemyCenter().y);
                modelMatrix *= transform2D::Scale(enemy->getScaleEnemy(), enemy->getScaleEnemy());
                modelMatrix *= transform2D::Rotate(PI / 4);
                RenderMesh2D(meshes[enemy->getEnemyMesh()], shaders["VertexColor"], modelMatrix);

                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(enemy->getEnemyCenter().x, enemy->getEnemyCenter().y);
                modelMatrix *= transform2D::Scale(enemy->getScaleInt(), enemy->getScaleInt());
                modelMatrix *= transform2D::Rotate(PI / 4);
                RenderMesh2D(meshes["hexagonInterior"], shaders["VertexColor"], modelMatrix);
                
            }
            itE++;


        }
    }

    
        // go through the enemies
        for (itE = enemies.begin(); itE != enemies.end(); itE++) {
            Enemy* enemy = &(*itE);
            int line = enemy->getLine();
            std::string mesh = enemy->getEnemyMesh();
            // get last character
            char colourId = mesh[mesh.length() - 1];
            Square* square = findSquareToCollideWith(line);
            if (square != NULL) {
                RhombusRect* rhombusRect = square->getRhombusRect();
                std::string meshName = rhombusRect->getRhombMesh();
                char colourId1 = meshName[meshName.length() - 1];
                bool collision = enemy->detectCollision(rhombusRect->getRhombusCenter(), rhombusRect->getRadius() * squareSide);
                if (collision == true) {
                    // shrinking the rhombus
                    square->setEmpty(true);
                    square->setRhombusRect(NULL);
                    rhombusRect->setShrinked(true);
                }
            }
        }

        for (int i = 0; i < grid.size(); i++) {
            Square* square = &grid[i];
            if (square->getEmpty() == true) continue;
            bool startShooting = enemyAppears(square);
            if (square->getShoot() == true) {
                square->contorTime += deltaTimeSeconds;
                if (square->contorTime > fixedTime) {
                    Star star = Star();
                    // concat a char to a string
                    std::string starMesh = square->getStarMeshName();
                    star.setMeshStarName(starMesh);
                    star.setStarCenter(glm::vec2(square->getPosition().x + square->getRadiusRhombus(), square->getPosition().y));

                    square->contorTime = 0;

                    square->stars.push_back(star);
                }
            }

        }

        for (int i = 0; i < grid.size(); i++) {
            Square* square = &grid[i];
            if (square->getShoot() == true) {

                for (itS = square->stars.begin(); itS != square->stars.end();) {

                    Star* star = &(*itS);

                    if (star->getStarCenter().x > resolution.x + radiusStar) {
                        // erase element from list
                        itS = square->stars.erase(itS);
                        continue;
                    }

                    if (star->getAngularStep() < -2 * PI) {
                        star->setAngularStep(0);
                    }


                    float angularStepStar = star->getAngularStep();
                    star->setAngularStep(angularStepStar - deltaTimeSeconds * 5);
                    float starXTranslate = star->getStarCenter().x;
                    starXTranslate += deltaTimeSeconds * 300;
                    star->setStarCenter(glm::vec2(starXTranslate, star->getStarCenter().y));

                    // render the star
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(star->getStarCenter().x, star->getStarCenter().y);
                    modelMatrix *= transform2D::Scale(star->getStarRadius(), star->getStarRadius());
                    modelMatrix *= transform2D::Rotate(star->getAngularStep());
                    RenderMesh2D(meshes[star->getMeshStarName()], shaders["VertexColor"], modelMatrix);

                    bool enemyKilled = false;
                    bool collision = enemyStarCollision(star, &enemyKilled);

                    // if the enemy is killed then we reset the shoot variable
                    // for a possible next enemy
                    if (enemyKilled == true) {
                        square->setShoot(false);
                        // if there are other squares that have the same colour set false as well
                        int j;
                        if (i >= 0 && i < 3) j = 0;
                        else if (i >= 3 && i < 6) j = 3;
						else if (i >= 6 && i < 9) j = 6;
                        for (int t = j; t < j + 3; t++) {
							Square* square1 = &grid[t];
							if (square1->getEmpty() == true) continue;
                            if (square1->getRhombusRect()->getRhombMesh() == square->getRhombusRect()->getRhombMesh()) {
								square1->setShoot(false);
							}
						}
                    }

                    if (collision == true) {
                        // erase element from list
                        itS = square->stars.erase(itS);
                        continue;
                    }
                    itS++;
                }


            }
        }

    
}

    



Square* Tema1::findSquareToCollideWith(int line) {
    int i, j;
    if (line == linesY.x) j = 0;
    else if (line == linesY.y) j = 3;
	else if (line == linesY.z) j = 6;
    i = j + 2;
	for (; i >= j; i--) {
        if (grid[i].getEmpty() == true) continue;
		return &grid[i];
	}
	return NULL;
}

// it verifies if a rhombus has an enemy on the same line, with the same colour
// and if it does it starts shooting
bool Tema1::enemyAppears(Square* square) {
    for (itE = enemies.begin(); itE != enemies.end(); itE++) {
		Enemy* enemy = &(*itE);
        string enemyMesh = enemy->getEnemyMesh();
        char colourIdEnemy = enemyMesh[enemyMesh.length() - 1];
        string rhombusMesh = square->getRhombusRect()->getRhombMesh();
        char colourIdRhombus = rhombusMesh[rhombusMesh.length() - 1];
        if (enemy->getLine() == square->getPosition().y && 
            colourIdEnemy == colourIdRhombus &&
            enemy->killed == false) {
            square->setShoot(true);
            std::string starMesh = "star";
            starMesh += colourIdEnemy;
            square->setStarMeshName(starMesh);
            square->setRadiusRhombus(square->getRhombusRect()->getRadius() * squareSide);
            return true;
        }
	}
    return false;
}

bool Tema1::enemyStarCollision(Star* star, bool* enemyKilled) {
    bool ret = false;
    for (itE = enemies.begin(); itE != enemies.end();) {
		Enemy* enemy = &(*itE);
		bool collision = enemy->detectCollision(star->getStarCenter(), star->getStarRadius());
        string meshEnemy = enemy->getEnemyMesh();
        string meshStar = star->getMeshStarName();
        char colourIdEnemy = meshEnemy[meshEnemy.length() - 1];
        char colourIdStar = meshStar[meshStar.length() - 1];
        if (collision == true && colourIdEnemy == colourIdStar && enemy->killed == false) {
            enemy->setHits(enemy->getHits() + 1);
            ret = true;


            if (enemy->getHits() == 3) {
                // erase enemy
                *enemyKilled = true;
                enemy->killed = true;
                
            }
            break;
        }
        itE++;
        
	}
	return ret;
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseY = window->GetResolution().y - mouseY;
    

    for (itR = rhombusList.begin(); itR != rhombusList.end(); itR++) {
        RhombusRect* rhombusRect = &(*itR);
        if (rhombusRect->getMoving() == true) {
			rhombusRect->setRhombusCenter(glm::vec2(mouseX, mouseY));
			glm::vec2 add = glm::vec2(rhombusRect->getScaleXRhombus() * squareSide * sqrt(2) / 2, 0);
			rhombusRect->setRectCenter(glm::vec2(mouseX, mouseY) + add);
		}
    }
    
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    mouseY = window->GetResolution().y - mouseY;
    
    // Add mouse button press event
    // on mouse click, the rhombus and rect are following the mouse
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        // use detect function to detect where I pressed
        for (int i = 0; i < frames.size(); i++) {
            detectedFrame = frames[i].detectFrame(glm::vec2(mouseX, mouseY));
            if (detectedFrame != NULL) {
                if (totalPoints >= detectedFrame->getPoints()) {
                    // start adding elements to the vector
                    RhombusRect rhombusRect = RhombusRect();
                    rhombusRect.setColor(detectedFrame->getColor());
                    rhombusRect.setRhombusCenter(glm::vec2(mouseX, mouseY));
                    glm::vec2 add = glm::vec2(rhombusRect.getScaleXRhombus() * squareSide * sqrt(2) / 2, 0);
                    rhombusRect.setRectCenter(glm::vec2(mouseX, mouseY) + add);
                    rhombusRect.setRectMesh(detectedFrame->getMeshRect());
                    rhombusRect.setRhombMesh(detectedFrame->getMeshRhomb());
                    

                    // add the rhombus to the list
                    rhombusList.push_back(rhombusRect);
                    
                }
                else {
                    detectedFrame = NULL;

                }
                break;

            }
        }

        for (itS = pointsStars.begin(); itS != pointsStars.end();) {
            // render the stars
            Star* star = &(*itS);
            if (star->pickStar(glm::vec2(mouseX, mouseY)) == true) {
                totalPoints++;
                itS = pointsStars.erase(itS);
                continue;
            }
			itS++;
        }
        
    }
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
		// if I press right click, I delete the last element from the vector
        Square* detectedSquare = NULL;
        for (int i = 0; i < grid.size(); i++) {
            detectedSquare = grid[i].detectSquare(glm::vec2(mouseX, mouseY));
            // print the position of the square

            if (detectedSquare != NULL && detectedSquare->getEmpty() == false) {
                detectedSquare->setEmpty(true);
                detectedSquare->getRhombusRect()->setShrinked(true);
                detectedSquare->setRhombusRect(NULL);
                break;
			}
        }
	}
}

int Tema1::findRhombusRect() {
    // find element in rhombus vector which has moving = true
    for (int i = 0; i < rhombus.size(); i++) {
		if (rhombus[i].getMoving() == true)
			return i;
	}
}

RhombusRect* Tema1::findRhombus() {
    for (itR = rhombusList.begin(); itR != rhombusList.end(); itR++) {
        RhombusRect* rhombusRect = &(*itR);
        if (rhombusRect->getMoving() == true) {
            return rhombusRect;
        }
    }
    return NULL;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    
    mouseY = window->GetResolution().y - mouseY;
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        // leave the object where the mouse is released
        Square* detectedSquare = NULL;
        RhombusRect* detectedRhombus = findRhombus();

        for (int i = 0; i < grid.size() && detectedFrame != NULL; i++) {
            detectedSquare = grid[i].detectSquare(glm::vec2(mouseX, mouseY));

            if (detectedSquare != NULL && detectedSquare->getEmpty() == true) {
                detectedSquare->setEmpty(false);
                detectedSquare->setRhombusRect(detectedRhombus);
                detectedRhombus->setMoving(false);
                detectedRhombus->setRhombusCenter(detectedSquare->getPosition());
                glm::vec2 add = glm::vec2(detectedRhombus->getScaleXRhombus() * squareSide * sqrt(2) / 2, 0);
                detectedRhombus->setRectCenter(grid[i].getPosition() + add);
                totalPoints -= detectedFrame->getPoints();
                detectedFrame = NULL;
                break;
            }
        }
        if (detectedSquare == NULL && detectedFrame != NULL) {
            detectedRhombus->setMoving(false);
            detectedRhombus->setRendered(false);
            detectedFrame = NULL;
        }
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
