#include "Floor.h"
#include "utils.h"
#include <gl/glut.h>

namespace TownBuilder {
    Floor::Floor(float x, float y, float z,
                 float width, float height, float depth,
                 float* diffColor, float* ambiColor, float* specColor)
        : x(x), y(y), z(z), width(width), height(height), depth(depth),
          diffColor(diffColor), ambiColor(ambiColor), specColor(specColor) {}

    void Floor::draw() {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
        glPushMatrix();
        glTranslatef(x, y, z);
        GraphUtils::parallelepiped(width, height, depth);
        glPopMatrix();
    }
}