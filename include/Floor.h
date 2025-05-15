#ifndef Floor_h
#define Floor_h

namespace TownBuilder {
    class Floor {
        float x, y, z;
        float width, height, depth;
        float* diffColor;
        float* ambiColor;
        float* specColor;
        float* diffRed;
        float* specRed;
    public:
        Floor(float x, float y, float z,
              float width, float height, float depth,
              float* diffColor, float* ambiColor, float* specColor, float* diffRed, float* specRed);

        void draw();
        bool isFailed = false;

        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        void setX(float val) { x = val; }
        void setY(float val) { y = val; }
        void setZ(float val) { z = val; }
    };
}

#endif