#ifndef Scene_h
#define Scene_h

#include <Floor.h>

#include "Board.h"
#include <vector>

namespace TownBuilder {
    class Scene {
        std::vector<Floor*> blocks;
        Floor* current;
        float blockWidth, blockHeight, blockDepth;

        bool movingRight;
        bool finish;
        float xMin, xMax;
        float moveSpeed;

        int score;
        int button;
        float angleX, angleY;
        float mouseX, mouseY;
        float width, height;
        float distZ;
        int tick, time;

    public:
        Scene(float widthStep, float heightStep);
        ~Scene();

        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_keyboard(unsigned char key, int x, int y);
        void on_timer(int value);

    private:
        void initGame();
        void spawnBlock();
        void dropBlock();
    };
}

#endif