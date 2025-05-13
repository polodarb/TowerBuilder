#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <stdio.h>
#include "Scene.h"
using TownBuilder::Scene;

Scene *scene;

void on_paint() {
    scene->on_paint();
}

void on_size(int width, int height) {
    scene->on_size(width, height);
}

void on_mouse(int button, int state, int x, int y) {
    scene->on_mouse(button, state, x, y);
}

void on_motion(int x, int y) {
    scene->on_motion(x, y);
}

void on_special(int key, int x, int y) {
    scene->on_special(key, x, y);
}

void on_keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    scene->on_keyboard(key, x, y);
}

void on_timer(int value) {
    scene->on_timer(value);
    glutTimerFunc(25, on_timer, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    scene = new Scene(1, 0.5);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("TownBuilder");
    glutDisplayFunc(on_paint);
    glutReshapeFunc(on_size);
    glutMotionFunc(on_motion);
    glutMouseFunc(on_mouse);
    glutKeyboardFunc(on_keyboard);
    glutSpecialFunc(on_special);
    glutTimerFunc(25, on_timer, 0);
    glutMainLoop();
    delete scene;
    return 0;
}
