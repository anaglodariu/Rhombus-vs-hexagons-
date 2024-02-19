#pragma once

#include "components/simple_scene.h"
#include "RhombusRect.h"
#include "Frames.h"
#include "Square.h"
#include "Enemy.h"
#include "Stars.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

        int Tema1::findRhombusRect();
        RhombusRect* findRhombus();

        Square* findSquareToCollideWith(int line);
        Square* shootEnemy(int line, char colorId);
        bool enemyStarCollision(Star *star, bool* enemyKilled);
        bool enemyAppears(Square* square);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        float halfSide;
        float squareSide;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float starTranslateX1, starTranslateY1;
        float scaleX, scaleY;
        float angularStep;
        float t;
        float pointx, pointy;

        // not needed
        bool renderSth = false;
        bool changePos = true;
        float pos1 = 500;
        float pos2 = 500;

        // render state variables
        bool renderStar;
        bool renderRhombus;
        bool renderEnemy;

        // colors
        glm::vec3 backgroundColor;
        glm::vec3 squareColor;
        glm::vec3 rectColor;
        glm::vec3 frameColor;
        
        std::vector<glm::vec3> rhombColors;
        std::vector<glm::vec3> enemyColors;
        std::vector<glm::vec3> starColors;

        // grid
        float deltaGrid;
        
        // PI constant
        const float PI = 3.14f;

        // enemy animation
        float enemyTranslateX;
        float enemyTranslateY;

        // coordinates for the 3x3 grid and frames
        glm::vec4 linesX;
        glm::vec4 linesY;


        // collision radius
        float radiusRhombus;
        float radiusEnemy;
        float radiusIntEnemy;
        float radiusStar;


        // star animation
        float starTranslateX;
        float starTranslateY;
        float starRotate;

        // scale down animation for rhombus and rect
        float scaleDownRhombusX;
        float scaleDownRhombusY;

        float scaleDownRectX;
        float scaleDownRectY;


        // scale down animation for enemy
        float scaleDownEnemy;
        float scaleDownIntEnemy;

        std::vector<RhombusRect> rhombus;
        std::list<RhombusRect> rhombusList;
        // iterator
        std::list<RhombusRect>::iterator itR;
        std::list<Star>::iterator itS;


        std::list<Star> pointsStars;
        
        // frames vector
        std::vector<Frames> frames;
        Frames* detectedFrame;
        int totalPoints;

        std::vector<Square> grid;
        bool pressedOnFrame;

        // for making objects appear ar random times
        float timeStarPassed;
        float timeEnemyPassed;
        
        std::list<Enemy> enemies;
        std::list<Enemy>::iterator itE;
        
        std::vector<std::string> enemyMeshes;
        int gameLives;
        float border;
        // TODO(student): If you need any other class variables, define them here.
        float fixedTime;
        float contorTime;
    };
}   // namespace m1
