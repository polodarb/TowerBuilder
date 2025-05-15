#include "utils.h"
#include <gl/glut.h>

namespace GraphUtils {
    float diffGray[] = {0.6f, 0.6f, 0.6f};
    float ambiGray[] = {0.3f, 0.3f, 0.3f};
    float specGray[] = {0.8f, 0.8f, 0.8f};

    float diffYellowOrange[] = {1.0f, 0.6f, 0.0f};
    float ambiYellowOrange[] = {0.3f, 0.2f, 0.0f};
    float specYellowOrange[] = {1.0f, 0.8f, 0.3f};

    float diffRed[] = {1.0f, 0.2f, 0.2f};
    float specRed[] = {1.0f, 0.5f, 0.5f};

    void parallelepiped(float length, float width, float height) {
        glBegin(GL_QUAD_STRIP);
        glNormal3f(-1, 0, 0);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glVertex3f(-length / 2, width / 2, -height / 2);
        glVertex3f(-length / 2, width / 2, height / 2);
        glNormal3f(1, 0, 0);
        glVertex3f(length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, width / 2, height / 2);
        glVertex3f(length / 2, -width / 2, -height / 2);
        glVertex3f(length / 2, -width / 2, height / 2);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glVertex3f(-length / 2, width / 2, height / 2);
        glVertex3f(length / 2, width / 2, height / 2);
        glVertex3f(length / 2, -width / 2, height / 2);

        glNormal3f(0, 0, -1);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, -width / 2, -height / 2);
        glEnd();
    }

    void drawString(void *font, const char *text, float x, float y) {
        glRasterPos2f(x, y);
        while (*text)
            glutBitmapCharacter(font, *text++);
    }

    void drawWireCube(float width, float height, float depth) {
        float x = width / 2.0f;
        float y = height / 2.0f;
        float z = depth / 2.0f;

        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, -y, -z);
        glVertex3f(x, -y, -z);
        glVertex3f(x, -y, z);
        glVertex3f(-x, -y, z);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, y, -z);
        glVertex3f(x, y, -z);
        glVertex3f(x, y, z);
        glVertex3f(-x, y, z);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z);
        glVertex3f(x, -y, -z);  glVertex3f(x, y, -z);
        glVertex3f(x, -y, z);   glVertex3f(x, y, z);
        glVertex3f(-x, -y, z);  glVertex3f(-x, y, z);
        glEnd();
    }
}
