#ifndef utils_h
#define utils_h

namespace GraphUtils {
    extern float diffGray[], ambiGray[], specGray[];
    extern float diffRed[], specRed[];
    extern float diffYellowOrange[], ambiYellowOrange[], specYellowOrange[];
    const float shininess = 64.0f;

    void parallelepiped(float length, float width, float height);

    void drawString(void *font, const char *text, float x, float y);

    void drawWireCube(float width, float height, float depth);
}

#endif
