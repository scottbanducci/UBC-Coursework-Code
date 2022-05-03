#pragma once

namespace cs221util {

    class HSLAPixel {
    public:
        double h;
        double s;
        double l;
        double a;

        HSLAPixel();
        HSLAPixel(double hue, double sat, double lum);
        HSLAPixel(double hue, double sat, double lum, double alf);
    };
}
