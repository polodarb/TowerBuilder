#include "Floor.h"
#include "utils.h"
#include <gl/glut.h>

namespace TownBuilder {
    Floor::Floor(float x, float y, float z,
                 float width, float height, float depth,
                 float* diffColor, float* ambiColor, float* specColor, float* diffRed, float* specRed)
        : x(x), y(y), z(z), width(width), height(height), depth(depth),
          diffColor(diffColor), ambiColor(ambiColor), specColor(specColor), diffRed(diffRed), specRed(specRed) {}

    void Floor::draw() {
        glPushMatrix();
        glTranslatef(x, y, z);

        if (isFailed) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffRed);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffRed);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specRed);
        } else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
        }
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);

        GraphUtils::parallelepiped(width, height, depth);

        glDisable(GL_LIGHTING);
        glColor3f(0, 0, 0);
        glLineWidth(2.0f);
        GraphUtils::drawWireCube(width, height, depth);

        float marginX = width * 0.2f;
        float marginY = height * 0.2f;
        float frameZ = depth / 1.9f;

        float x1 = -width / 2 + marginX;
        float x2 = width / 2 - marginX;
        float y1 = -height / 2 + marginY;
        float y2 = height / 2 - marginY;

        glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, frameZ);
        glVertex3f(x2, y1, frameZ);
        glVertex3f(x2, y2, frameZ);
        glVertex3f(x1, y2, frameZ);
        glEnd();

        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

}