#include "Scene.h"
#include "Board.h"
#include "utils.h"
#include <gl/glut.h>
#include <cmath>
#include <cstdio>
#include <Floor.h>
using namespace GraphUtils;

namespace TownBuilder {
    Scene::Scene(float widthStep, float heightStep)
        : blockWidth(widthStep),
          blockHeight(0.4f),
          blockDepth(widthStep),
          xMin(-2.0f),
          xMax(2.0f),
          moveSpeed(0.05f),
          angleX(0),
          angleY(20),
          distZ(-0.5f),
          score(0),
          finish(false),
          tick(0),
          time(0),
          current(nullptr),
          button(-1) {
        initGame();
    }

    Scene::~Scene() {
        for (auto *b: blocks) delete b;
        delete current;
    }

    void Scene::initGame() {
        for (auto *b: blocks) delete b;
        blocks.clear();
        score = 0;
        finish = false;
        time = 0;

        blocks.push_back(new Floor(0, 0, 0, blockWidth, blockHeight, blockDepth, diffGray, ambiGray, specGray, diffRed, specRed));
        spawnBlock();
    }

    void Scene::spawnBlock() {
        float y = static_cast<float>(blocks.size()) * blockHeight;
        current = new Floor(xMin, y, 0, blockWidth, blockHeight, blockDepth, diffYellowOrange, ambiYellowOrange,
                            specYellowOrange, diffRed, specRed);
        movingRight = true;
    }

    void Scene::dropBlock() {
        if (finish || !current) return;

        float dx = std::abs(current->getX() - blocks.back()->getX());

        if (dx > blockWidth / 2) {
            current->isFailed = true;
            blocks.push_back(current); // важно: добавляем блок в сцену
            current = nullptr;
            finish = true;
            return;
        }

        current->setY(static_cast<float>(blocks.size()) * blockHeight);
        blocks.push_back(current);
        score++;

        spawnBlock();
    }

    void Scene::on_paint() {
        char text[128];
        sprintf(text, finish ? "Game over! Score: %d  F2 - Restart" : "Score: %d", score);

        glViewport(0, 0, width, height);

        float lightAmbient[] = {0, 0, 0, 1};
        float lightDiffuse[] = {1, 1, 1, 1};
        float lightSpecular[] = {1, 1, 1, 1};
        float lightPosition[] = {1, 1, 1, 0};

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        glClearColor(0.6f, 0.8f, 1.0f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0);
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01f, 0.95f);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, width / height, 1, 100);


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, distZ);
        glTranslatef(0, -score * blockHeight, -5.0f);

        glRotatef(angleX, 0, 1, 0);
        glRotatef(angleY, 1, 0, 0);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        Board board(0, -blockHeight / 2, 0, 5.0f, 0.05f, 5.0f, diffGray, ambiGray, specGray);
        board.draw();

        for (auto *b: blocks) b->draw();
        if (!finish && current) current->draw();

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        glutSwapBuffers();
    }

    void Scene::on_size(int w, int h) {
        width = static_cast<float>(w);
        height = static_cast<float>(h == 0 ? 1 : h);
    }

    void Scene::on_mouse(int button, int state, int x, int y) {
        mouseX = x;
        mouseY = y;

        if (state == GLUT_UP) {
            this->button = -1;
            return;
        }

        this->button = button;
    }

    void Scene::on_motion(int x, int y) {
        if (button == GLUT_RIGHT_BUTTON) {
            angleX += x - mouseX;
            angleY += y - mouseY;
        }
        mouseX = x;
        mouseY = y;
    }

    void Scene::on_special(int key, int, int) {
        if (key == GLUT_KEY_UP && distZ < 1.0f) distZ += 0.1f;
        if (key == GLUT_KEY_DOWN) distZ -= 0.1f;
        if (key == GLUT_KEY_F2) initGame();
    }

    void Scene::on_keyboard(unsigned char key, int, int) {
        if (key == ' ') dropBlock();
    }

    void Scene::on_timer(int) {
        tick++;
        if (tick >= 40 && !finish) {
            time++;
            tick = 0;
        }

        if (!finish && current) {
            float x = current->getX();
            x += movingRight ? moveSpeed : -moveSpeed;
            if (x > xMax) {
                x = xMax;
                movingRight = false;
            }
            if (x < xMin) {
                x = xMin;
                movingRight = true;
            }
            current->setX(x);
        }

        on_paint();
    }
}
