#ifndef utils_h
#define utils_h

namespace GraphUtils {
    extern float diffGray[], ambiGray[], specGray[];
    extern float diffGreen[], ambiGreen[], specGreen[];
    const float shininess = 64.0f;

    void parallelepiped(float length, float width, float height);
    void drawString(void *font, const char *text, float x, float y);
}

#endif
