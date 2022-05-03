#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
	int height = data[0].size();
	return height;
}

int Block::width() const {
	int width = data.size();
	return width;
	
}

void Block::render(PNG &im, int x) const {
  /* your code here */
  int counter = 0;
 for (int i = x; i < data.size()+x; i++) {
		for (int j = 0; j < im.height();j++) {
			*im.getPixel(i,j) = data[counter][j];
		}
	counter++;
	}
	
}

void Block::build(PNG &im, int x, int width) {
  /* your code here */
	data.resize(width);
	for (int i = 0; i < width; i++) {
		data[i].resize(im.height());
		for (int j = 0; j < im.height(); j++) {
			data[i][j] = *im.getPixel(x, j);
		}
		x++;
	}
}
