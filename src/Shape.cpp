// #include "Shape.h"
// #include "utils.h"
// #include <gl/glut.h>
// using namespace GraphUtils;
//
// namespace TownBuilder {
//     Shape::Shape(float x, float y, float z,
//                  float xs, float ys, float zs,
//                  float *diff, float *ambi, float *spec)
//         : xCenter(x), yCenter(y), zCenter(z),
//           xSize(xs), ySize(ys), zSize(zs),
//           diffColor(diff), ambiColor(ambi), specColor(spec) {}
//
//     void Shape::draw() {
//         glMaterialfv(GL_FRONT, GL_AMBIENT, ambiColor);
//         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffColor);
//         glMaterialfv(GL_FRONT, GL_SPECULAR, specColor);
//         glMaterialf(GL_FRONT, GL_SHININESS, shininess);
//         glPushMatrix();
//         glTranslatef(xCenter, yCenter + ySize / 2, zCenter);
//         parallelepiped(xSize, ySize, zSize);
//         glPopMatrix();
//     }
// }
