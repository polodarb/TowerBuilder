#ifndef Board_h
#define Board_h

namespace TownBuilder {
    class Board {
        float x, y, z;
        float width, height, depth;
        float* diffColor;
        float* ambiColor;
        float* specColor;
    public:
        Board(float x, float y, float z,
              float width, float height, float depth,
              float* diffColor, float* ambiColor, float* specColor);

        void draw();

        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        void setX(float val) { x = val; }
        void setY(float val) { y = val; }
        void setZ(float val) { z = val; }
    };
}

#endif