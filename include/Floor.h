#ifndef Floor_h
#define Floor_h

namespace TownBuilder {
    class Floor {
        float x, y, z;
        float width, height, depth;
        float* diffColor;
        float* ambiColor;
        float* specColor;
    public:
        Floor(float x, float y, float z,
              float width, float height, float depth,
              float* diffColor, float* ambiColor, float* specColor);

        void draw();
    };
}

#endif