#include "Scene.h"
#include "Floor.h"
#include "utils.h"
#include <gl/glut.h>
#include <cmath>
#include <cstdio>
using namespace GraphUtils;

namespace TownBuilder {
    Scene::Scene(float widthStep, float heightStep)
        : blockWidth(widthStep),
          blockHeight(0.4f),
          blockDepth(widthStep),
          xMin(-2.0f),
          xMax(2.0f),
          moveSpeed(0.05f),
          angleX(-10),
          angleY(20),
          distZ(-3.5f),
          score(0),
          finish(false),
          tick(0),
          time(0),
          current(nullptr),
          button(-1) {
        initGame();
    }

    Scene::~Scene() {
        for (auto* b : blocks) delete b;
        delete current;
    }

    void Scene::initGame() {
        for (auto* b : blocks) delete b;
        blocks.clear();
        score = 0;
        finish = false;
        time = 0;

        blocks.push_back(new Board(0, 0, 0, blockWidth, blockHeight, blockDepth, diffGray, ambiGray, specGray));
        spawnBlock();
    }

    void Scene::spawnBlock() {
        float y = static_cast<float>(blocks.size()) * blockHeight;
        current = new Board(xMin, y, 0, blockWidth, blockHeight, blockDepth, diffGreen, ambiGreen, specGreen);
        movingRight = true;
    }

    void Scene::dropBlock() {
        if (finish || !current) return;

        float dx = std::abs(current->getX() - blocks.back()->getX());
        if (dx > blockWidth / 2) {
            finish = true;
            return;
        }

        current->setY(static_cast<float>(blocks.size()) * blockHeight);
        blocks.push_back(current);
        score++;

        distZ -= 0.2f;

        spawnBlock();
    }

    void Scene::on_paint() {
        char text[128];
        sprintf(text, finish ? "Game over! Score: %d  F2 - Restart" : "Score: %d", score);

        glViewport(0, 0, width, height);

        float lightAmbient[] = { 0, 0, 0, 1 };
        float lightDiffuse[] = { 1, 1, 1, 1 };
        float lightSpecular[] = { 1, 1, 1, 1 };
        float lightPosition[] = { 1, 1, 1, 0 };

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
        glTranslatef(0, -score * blockHeight, -5.0f);
        glRotatef(angleY, 1, 0, 0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        Floor floor(0, -0.05f, 0, 5.0f, 0.05f, 5.0f, diffGray, ambiGray, specGray);
        floor.draw();

        for (auto* b : blocks) b->draw();
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
        if (state == GLUT_UP && !finish) dropBlock();
        this->button = (state == GLUT_DOWN) ? button : -1;
    }

    void Scene::on_motion(int x, int y) {
        if (button == GLUT_RIGHT_BUTTON) {
            angleX += x - mouseX;
            angleY += y - mouseY;
            mouseX = x;
            mouseY = y;
        }
    }

    void Scene::on_special(int key, int, int) {
        if (key == GLUT_KEY_UP && distZ < -1.5f) distZ += 0.1f;
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
