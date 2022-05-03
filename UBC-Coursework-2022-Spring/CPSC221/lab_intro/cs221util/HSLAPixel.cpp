#include "HSLAPixel.h"

namespace cs221util {

HSLAPixel::HSLAPixel(){
    h = 0;
    s = 0;
    l = 1;
    a = 1;
};
HSLAPixel::HSLAPixel(double hue, double sat, double lum){
    h = hue;
    s = sat;
    l = lum;
    a = 1;
};
HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alf){
    h = hue;
    s = sat;
    l = lum;
    a = alf;
};

}