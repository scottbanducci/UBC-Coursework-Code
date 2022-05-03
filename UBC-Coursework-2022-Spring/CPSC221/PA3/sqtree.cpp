/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  stats y = stats(imIn);
  pair<int,int> x = make_pair(0,0);
  root = buildTree(y, x, imIn.width(), imIn.height(), tol);
  cout<<size()<<endl;
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {

  if(w == 0 || h == 0){return NULL;}

  Node *theTree = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));

  if (theTree->var <= tol || w * h == 1){return theTree;}

  double overallLowestMaxVar = theTree->var; //local variable to hold lowest Max Variability

  pair<int,int> bestPairForSplit = {0,0};

  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++) {
      if (i == 0 && j == 0){continue;}
      pair<int, int> tempPixSE(i + ul.first, j + ul.second);
      pair<int, int> tempPixSW(ul.first, j + ul.second);
      pair<int, int> tempPixNE(i + ul.first, ul.second);
      pair<int, int> tempPixNW(ul.first, ul.second);
      double varSE = s.getVar(tempPixSE, w-i, h-j);
      double varSW = s.getVar(tempPixSW, i, h-j);
      double varNE = s.getVar(tempPixNE, w-i, j);
      double varNW = s.getVar(tempPixNW, i, j);
      
      double maxVar = max(max(varSE, varSW), max(varNE, varNW));
      
      if(maxVar < overallLowestMaxVar){
        overallLowestMaxVar = maxVar;
        bestPairForSplit = {i,j};
        }

    }
  } 
  
  pair<int,int> ulNE = {ul.first + bestPairForSplit.first, ul.second};
  pair<int,int> ulSW = {ul.first, ul.second + bestPairForSplit.second};
  pair<int,int> ulSE = {ul.first + bestPairForSplit.first, ul.second + bestPairForSplit.second};

  if(bestPairForSplit.first > 0 && bestPairForSplit.second > 0){
  theTree->NW = buildTree(s, ul, bestPairForSplit.first, bestPairForSplit.second, tol);
  theTree->NE = buildTree(s, ulNE, w - bestPairForSplit.first, bestPairForSplit.second, tol);
  theTree->SW = buildTree(s, ulSW, bestPairForSplit.first, h - bestPairForSplit.second, tol);
  theTree->SE = buildTree(s, ulSE, w - bestPairForSplit.first, h- bestPairForSplit.second, tol);
  } else if(bestPairForSplit.first > 0){
    theTree->SW = buildTree(s, ulSW, bestPairForSplit.first, h - bestPairForSplit.second, tol);
    theTree->SE = buildTree(s, ulSE, w - bestPairForSplit.first, h- bestPairForSplit.second, tol);
  } else if(bestPairForSplit.second > 0){
    theTree->NE = buildTree(s, ulNE, w - bestPairForSplit.first, bestPairForSplit.second, tol);
    theTree->SE = buildTree(s, ulSE, w - bestPairForSplit.first, h- bestPairForSplit.second, tol);
  }

  return theTree;
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG img = PNG(root->width, root->height);
  renderNodes(img, root);
  return img;
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  deleteNodes(this->root);
}

void SQtree::copy(const SQtree & other) {
  this->root = copyNodes(other.root);
}

int SQtree::size() {
  if(root == NULL){return 0;}
  int x = countNodes(root);
  return x;
}

void SQtree::renderNodes(PNG &img, Node *currentNode){
  if (currentNode == NULL){return;}
  if (currentNode->NW == NULL && currentNode->NE == NULL && currentNode->SW == NULL && currentNode->SE == NULL) {
    for (int i = currentNode->upLeft.first; i < currentNode->upLeft.first + currentNode->width; i++){
      for (int j = currentNode->upLeft.second; j < currentNode->upLeft.second + currentNode->height; j++){
        RGBAPixel *pixel = img.getPixel(i, j);
        *pixel = currentNode->avg;
      }
    }
  } else {
    renderNodes(img, currentNode->NW);
    renderNodes(img, currentNode->NE);
    renderNodes(img, currentNode->SW);
    renderNodes(img, currentNode->SE);
  }
}

void SQtree::deleteNodes(Node *currentNode){
  if (currentNode == NULL){return;}
  deleteNodes(currentNode->NW);
  deleteNodes(currentNode->NE);
  deleteNodes(currentNode->SW);
  deleteNodes(currentNode->SE);
  delete currentNode;
}

SQtree::Node* SQtree::copyNodes(Node *currentNode){
  if (currentNode == NULL){return NULL;}
  pair<int,int> ul = currentNode->upLeft;
  int w = currentNode->width;
  int h = currentNode->height;
  Node *destinationNode = new Node(ul, w, h, currentNode->avg, currentNode->var);
  destinationNode->NW = copyNodes(currentNode->NW);
  destinationNode->NE = copyNodes(currentNode->NE);
  destinationNode->SW = copyNodes(currentNode->SW);
  destinationNode->SE =  copyNodes(currentNode->SE);
  return destinationNode;
}

int SQtree::countNodes(Node *currentNode){
  if (currentNode == NULL){return 0;}
  int totalNodes = 1;
  totalNodes += countNodes(currentNode->NW);
  totalNodes += countNodes(currentNode->NE);
  totalNodes += countNodes(currentNode->SW);
  totalNodes += countNodes(currentNode->SE);
  return totalNodes;
}
