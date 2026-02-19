#include <iostream>
#include <cmath>
#include <cstdint>
using namespace std;

int main() {
    const int width = 1024;
    const int height = 1024;
    float del=2;
    uint8_t centerR = 255;
    float cx = width / del;
    float cy = height / del;
    float maxDist = sqrt(cx * cx + cy * cy);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float dx = x - cx;
            float dy = y - cy;
            float dist = sqrt(dx * dx + dy * dy) / maxDist;
            uint8_t r = static_cast<uint8_t>((1 - dist) * centerR);
            cout <<"("<< x << "," << y << ") ("<< (int)r << "," <<"0" << "," << "0" <<")"<<"\n";
        }
    }

    return 0;
}
