#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){
    sumRed.resize(im.width(), vector<long>(im.height()));
    sumGreen.resize(im.width(), vector<long>(im.height()));
    sumBlue.resize(im.width(), vector<long>(im.height()));
    sumsqRed.resize(im.width(), vector<long>(im.height()));
    sumsqGreen.resize(im.width(), vector<long>(im.height()));
    sumsqBlue.resize(im.width(), vector<long>(im.height()));

    for (unsigned int i = 0; i < im.width(); i++){
        for (unsigned int j = 0; j < im.height(); j++){
            RGBAPixel *pixel = im.getPixel(i, j);
            if (i == 0 && j == 0) {
                sumRed[i][j] = pixel->r;
                sumGreen[i][j] = pixel->g;
                sumBlue[i][j] = pixel->b;
                sumsqRed[i][j] = pow(pixel->r, 2);
                sumsqGreen[i][j] = pow(pixel->g, 2);
                sumsqBlue[i][j] = pow(pixel->b, 2);
            } else if (j == 0) {
                sumRed[i][j] = pixel->r + sumRed[i-1][j];
                sumGreen[i][j] = pixel->g + sumGreen[i-1][j];
                sumBlue[i][j] = pixel->b + sumBlue[i-1][j];
                sumsqRed[i][j] = pow(pixel->r, 2) + sumsqRed[i-1][j];
                sumsqGreen[i][j] = pow(pixel->g, 2) + sumsqGreen[i-1][j];
                sumsqBlue[i][j] = pow(pixel->b, 2) + sumsqBlue[i-1][j];
            } else if (i == 0) {
                sumRed[i][j] = pixel->r + sumRed[i][j-1];
                sumGreen[i][j] = pixel->g + sumGreen[i][j-1];
                sumBlue[i][j] = pixel->b + sumBlue[i][j-1];
                sumsqRed[i][j] = pow(pixel->r, 2)  + sumsqRed[i][j-1];
                sumsqGreen[i][j] = pow(pixel->g, 2)  + sumsqGreen[i][j-1];
                sumsqBlue[i][j] = pow(pixel->b, 2)  + sumsqBlue[i][j-1];
            } else {
                sumRed[i][j] = pixel->r + sumRed[i][j-1] + sumRed[i - 1][j] - sumRed[i-1][j-1];
                sumGreen[i][j] = pixel->g + sumGreen[i][j-1] + sumGreen[i - 1][j] - sumGreen[i-1][j-1];
                sumBlue[i][j] = pixel->b + sumBlue[i][j-1] + sumBlue[i - 1][j] - sumBlue[i-1][j-1];
                sumsqRed[i][j] = pow(pixel->r, 2) + sumsqRed[i][j-1] + sumsqRed[i - 1][j] - sumsqRed[i-1][j-1];
                sumsqGreen[i][j] = pow(pixel->g, 2) + sumsqGreen[i][j-1] + sumsqGreen[i - 1][j] - sumsqGreen[i-1][j-1];
                sumsqBlue[i][j] = pow(pixel->b, 2) + sumsqBlue[i][j-1] + sumsqBlue[i - 1][j] - sumsqBlue[i-1][j-1];
            }
        }
    }
}

long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    long sum = 0;
    if (ul.first == 0 && ul.second == 0) {
        if (channel == 'r') {  
        sum = sumRed[ul.first+w-1][ul.second+h-1];
        } else if (channel == 'g') {
        sum = sumGreen[ul.first+w-1][ul.second+h-1];
        } else if(channel == 'b') {
        sum = sumBlue[ul.first+w-1][ul.second+h-1];
        }
    }else if (ul.first == 0) {
        if (channel == 'r') {  
        sum = sumRed[ul.first+w-1][ul.second+h-1] - sumRed[ul.first+w-1][ul.second-1];
        } else if (channel == 'g') {
        sum = sumGreen[ul.first+w-1][ul.second+h-1] - sumGreen[ul.first+w-1][ul.second-1];
        } else if (channel == 'b') {
        sum = sumBlue[ul.first+w-1][ul.second+h-1] - sumBlue[ul.first+w-1][ul.second-1];
        }
    } else if (ul.second == 0) {
        if (channel == 'r') {  
        sum = sumRed[ul.first+w-1][ul.second+h-1] - sumRed[ul.first-1][ul.second+h-1];
        } else if (channel == 'g') {
        sum = sumGreen[ul.first+w-1][ul.second+h-1] - sumGreen[ul.first-1][ul.second+h-1];
        } else if (channel == 'b') {
        sum = sumBlue[ul.first+w-1][ul.second+h-1] - sumBlue[ul.first-1][ul.second+h-1];
        }
    } else {
        if (channel == 'r') {  
        sum = sumRed[ul.first+w-1][ul.second+h-1] - sumRed[ul.first+w-1][ul.second-1]- sumRed[ul.first-1][ul.second+h-1] + sumRed[ul.first-1][ul.second-1];
        } else if (channel == 'g') {
        sum = sumGreen[ul.first+w-1][ul.second+h-1] - sumGreen[ul.first+w-1][ul.second-1]- sumGreen[ul.first-1][ul.second+h-1] + sumGreen[ul.first-1][ul.second-1];
        } else if (channel == 'b') {
        sum = sumBlue[ul.first+w-1][ul.second+h-1] - sumBlue[ul.first+w-1][ul.second-1]- sumBlue[ul.first-1][ul.second+h-1] + sumBlue[ul.first-1][ul.second-1];
        }
    }
    
    return sum;
}
    // for (int i = ul->a; i < w + ul->a; i++){
    //     for (int j = ul->b; j < h + ul->b; j++) {
    //         RGBAPixel *pixel = im.getPixel(i, j);
    //         if (channel == 'r') {
    //             sum += pixel->r;
    //         } else if (channel == 'g') {
    //             sum += pixel->g;
    //         } else if (channel == 'b') {
    //             sum += pixel->b;
    //         }
    //     }
    // } not efficient enough



long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    long sum = 0;
    if (ul.first == 0 && ul.second == 0) {
        if (channel == 'r') {  
        sum = sumsqRed[ul.first+w-1][ul.second+h-1];
        } else if (channel == 'g') {
        sum = sumsqGreen[ul.first+w-1][ul.second+h-1];
        } else if(channel == 'b') {
        sum = sumsqBlue[ul.first+w-1][ul.second+h-1];
        }
    } else if (ul.first == 0) {
        if (channel == 'r') {  
        sum = sumsqRed[ul.first+w-1][ul.second+h-1] - sumsqRed[ul.first+w-1][ul.second-1];
        } else if (channel == 'g') {
        sum = sumsqGreen[ul.first+w-1][ul.second+h-1] - sumsqGreen[ul.first+w-1][ul.second-1];
        } else if (channel == 'b') {
        sum = sumsqBlue[ul.first+w-1][ul.second+h-1] - sumsqBlue[ul.first+w-1][ul.second-1];
        }
    } else if (ul.second == 0) {
        if (channel == 'r') {  
        sum = sumsqRed[ul.first+w-1][ul.second+h-1] - sumsqRed[ul.first-1][ul.second+h-1];
        } else if (channel == 'g') {
        sum = sumsqGreen[ul.first+w-1][ul.second+h-1] - sumsqGreen[ul.first-1][ul.second+h-1];
        } else if (channel == 'b') {
        sum = sumsqBlue[ul.first+w-1][ul.second+h-1] - sumsqBlue[ul.first-1][ul.second+h-1];
        }
    } else {
        if (channel == 'r') {  
        sum = sumsqRed[ul.first+w-1][ul.second+h-1] - sumsqRed[ul.first+w-1][ul.second-1]- sumsqRed[ul.first-1][ul.second+h-1] + sumsqRed[ul.first-1][ul.second-1];
        } else if (channel == 'g') {
        sum = sumsqGreen[ul.first+w-1][ul.second+h-1] - sumsqGreen[ul.first+w-1][ul.second-1]- sumsqGreen[ul.first-1][ul.second+h-1] + sumsqGreen[ul.first-1][ul.second-1];
        } else if (channel == 'b') {
        sum = sumsqBlue[ul.first+w-1][ul.second+h-1] - sumsqBlue[ul.first+w-1][ul.second-1]- sumsqBlue[ul.first-1][ul.second+h-1] + sumsqBlue[ul.first-1][ul.second-1];
        }
    }
    
    return sum;

    // for (int i = ul->a; i < w + ul->a; i++){
    //     for (int j = ul->b; j < h + ul->b; j++) {
    //         RGBAPixel *pixel = im.getPixel(i, j);
    //         if (channel == 'r') {
    //             sum += pow(pixel->r, 2);
    //         } else if (channel == 'g') {
    //             sum += pow(pixel->g, 2);
    //         } else if (channel == 'b') {
    //             sum += pow(pixel->b, 2);
    //         }
    //     }
    // }

}


// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    if (w == 0 || h == 0){
        double var = 0.0;
        return var;
    }
    double n = w * h;
    double redVar = getSumSq('r',ul,w,h) - (getSum('r',ul,w,h) * getSum('r',ul,w,h)) / n;
    double greenVar = getSumSq('g',ul,w,h) - (getSum('g',ul,w,h) * getSum('g',ul,w,h)) / n;
    double blueVar = getSumSq('b',ul,w,h) - (getSum('b',ul,w,h) * getSum('b',ul,w,h)) / n;
    double var = redVar + greenVar + blueVar;
    return var;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    if (w * h == 0){
        RGBAPixel pixelAvg(0,0,0);
        return pixelAvg;
    }
    double n = w * h;
    RGBAPixel pixelAvg(getSum('r', ul, w, h)/n, getSum('g', ul, w, h)/n, getSum('b', ul, w, h)/n);
    return pixelAvg;
}
