#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG &tm, pair<int, int> s)
    : start(s), mapImg(tm)
{

   PNG copyImg = mapImg;
   
   pair<int, int> noParentAssigned;
   noParentAssigned = make_pair(-1, -1);

   //create 2d vector with width x height (full of bools)
   vector<vector<bool>> vecBools(copyImg.width(), vector<bool>(copyImg.height(), false));

   // create 2d vector with width x height (full of ints)
   vector<vector<int>> vecNums(copyImg.width(), vector<int>(copyImg.height(), -1));

   //creates a 2dVector of pairs that will hold the pixel that came before the current pixel
   vector<vector<pair<int, int>>> parentVector(copyImg.width(), vector<pair<int, int>>(copyImg.height(), noParentAssigned));

   Stack<pair<int, int>> pathToTreasure; //stack to hold the path to treasure

   Queue<pair<int, int>> myQueue; //create a queue of pairs for locations

   vecBools[start.first][start.second] = true; // set start to true in 2dvector for checking locations
   vecNums[start.first][start.second] = 0;     // set start to value 0 ''  '' etc.

   myQueue.enqueue(start); //load up the start position in the queue

   while (!myQueue.isEmpty())
   {
      pair<int, int> curr;
      curr = myQueue.dequeue(); //set curr to the first pixel in the queue (begins with "start" pixel)

      vector<pair<int, int>> neighbourPixels; //create a vector for neighbours
      neighbourPixels = neighbors(curr);      //set it equal to neighbours' return vector

      for (int i = 0; i <= 3; i++)
      {
         if (good(vecBools, vecNums, curr, neighbourPixels[i]))
         {                                                                                                       //check if neighbourpixels are good
            vecBools[neighbourPixels[i].first][neighbourPixels[i].second] = true;                                //mark good pixels as visited
            vecNums[neighbourPixels[i].first][neighbourPixels[i].second] = vecNums[curr.first][curr.second] + 1; // set pixels distance to curr's+1
            parentVector[neighbourPixels[i].first][neighbourPixels[i].second] = curr;
            myQueue.enqueue(neighbourPixels[i]); // put the neighbourpixels in the queue
         }
      }
      if (myQueue.isEmpty())
      {

         pathToTreasure.push(curr); // push last

         while (parentVector[curr.first][curr.second] != noParentAssigned)
         {
            curr = parentVector[curr.first][curr.second];
            pathToTreasure.push(curr);
         }

         while (pathToTreasure.isEmpty() == false)
         {
            pathPts.push_back(pathToTreasure.pop());
         }
      }
   }
}

PNG decoder::renderSolution()
{
   PNG copyImg = mapImg;
   
   RGBAPixel redSquareTemplatePix(255, 0, 0); //create a generic red pixel

   for (int i = 0; i <= pathPts.size() - 1; i++)
   {
      *copyImg.getPixel(pathPts[i].first, pathPts[i].second) = redSquareTemplatePix;
   }

   return copyImg;
}

PNG decoder::renderMaze()
{
   PNG copyImg = mapImg;

   //create 2d vector with width x height (full of bools)
   vector<vector<bool>> vecBools(copyImg.width(), vector<bool>(copyImg.height(), false));

   // create 2d vector with width x height (full of ints)
   vector<vector<int>> vecNums(copyImg.width(), vector<int>(copyImg.height(), -1));

   Queue<pair<int, int>> myQueue; //create a queue of pairs for locations

   vecBools[start.first][start.second] = true; // set start to true in 2dvector for checking locations
   vecNums[start.first][start.second] = 0;     // set start to value 0 ''  '' etc.

   myQueue.enqueue(start); //load up the start position in the queue

   while (!myQueue.isEmpty())
   {
      cout << "loaded hat";
      pair<int, int> curr;
      curr = myQueue.dequeue(); //set curr to the first pixel in the queue (begins with "start" pixel)

      vector<pair<int, int>> neighbourPixels; //create a vector for neighbours
      neighbourPixels = neighbors(curr);      //set it equal to neighbours' return vector

      for (int i = 0; i <= 3; i++)
      {
         if (good(vecBools, vecNums, curr, neighbourPixels[i]))
         {                                                                                                       //check if neighbourpixels are good
            vecBools[neighbourPixels[i].first][neighbourPixels[i].second] = true;                                //mark good pixels as visited
            vecNums[neighbourPixels[i].first][neighbourPixels[i].second] = vecNums[curr.first][curr.second] + 1; // set pixels distance to curr's+1
            setGrey(copyImg, neighbourPixels[i]);                                                                 // encode the distance
            myQueue.enqueue(neighbourPixels[i]);                                                                 // put the neighbourpixels in the queue
         }
      }
   }

   RGBAPixel redSquareTemplatePix(255, 0, 0); //create a generic red pixel

   // a nested for loop that will make the appropriate pixels red if they're in image
   for (int i = -3; i <= 3; i++)
   {
      for (int j = -3; j <= 3; j++)
      {
         if (start.first + i <= copyImg.width() - 1 && start.first + i >= 0 && start.second + j <= copyImg.height() - 1 && start.second + j >= 0)
         {
            *copyImg.getPixel(start.first + i, start.second + j) = redSquareTemplatePix;
         }
      }
   }

   return copyImg;
}

void decoder::setGrey(PNG &im, pair<int, int> loc)
{

   // i think this is correct
   RGBAPixel *targetPixel = im.getPixel(loc.first, loc.second);

   targetPixel->r = 2 * (targetPixel->r / 4); // these 3 lines are just changing pixel colour channels to 50% of what they were
   targetPixel->g = 2 * (targetPixel->g / 4);
   targetPixel->b = 2 * (targetPixel->b / 4);
}

pair<int, int> decoder::findSpot()
{
   return pathPts.back();
}

int decoder::pathLength()
{
   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> &v, vector<vector<int>> &d, pair<int, int> curr, pair<int, int> next)
{
   PNG copyImg = mapImg;

   if (next.first <= copyImg.width() - 1 && next.first >= 0 && next.second <= copyImg.height() - 1 && next.second >= 0)
   {
      if (v[next.first][next.second] != true)
      {
         if (compare(*copyImg.getPixel(next.first, next.second), d[curr.first][curr.second]) == true)
         {
            return true;
         }
      }
   }
   return false;
}

vector<pair<int, int>> decoder::neighbors(pair<int, int> curr)
{

   vector<pair<int, int>> neighbourVector; //create a empty vector of pair<int,int>

   pair<int, int> np1; // create 4 pairs for pixels
   pair<int, int> np2;
   pair<int, int> np3;
   pair<int, int> np4;

   np1 = make_pair(curr.first, curr.second - 1); //initialize pairs with values of target pixel coordinates
   np2 = make_pair(curr.first, curr.second + 1);
   np3 = make_pair(curr.first - 1, curr.second);
   np4 = make_pair(curr.first + 1, curr.second);

   neighbourVector.push_back(np1); //push pairs into vector
   neighbourVector.push_back(np2);
   neighbourVector.push_back(np3);
   neighbourVector.push_back(np4);

   return neighbourVector; //return the vector
}

bool decoder::compare(RGBAPixel p, int d)
{

   int red; // set up 3 ints
   int green;
   int blue;

   red = p.r & 3; // get last 2 bits of our color channels
   green = p.g & 3;
   blue = p.b & 3;

   red = red << 4; // move bits to proper spot
   green = green << 2;
   blue = blue;

   int code = 0; // create an int to capture all the bits in the appropriate spot

   code = code | red; // set the last 6 bits equal to our code
   code = code | green;
   code = code | blue;

   d = d % 64;

   if (code == (d + 1) % 64)
   {
      return true;
   }
   return false;
}