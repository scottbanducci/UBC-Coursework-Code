#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG &baseim, const PNG &mazeim, pair<int, int> s)
{
    start.first = s.first;
    start.second = s.second; // initialize start x,y

    base = baseim;
    maze = mazeim; // initialize base and maze
}

void treasureMap::setGrey(PNG &im, pair<int, int> loc)
{

    // i think this is correct
    RGBAPixel *targetPixel = im.getPixel(loc.first, loc.second);

    targetPixel->r = 2 * (targetPixel->r / 4); // these 3 lines are just changing pixel colour channels to 50% of what they were
    targetPixel->g = 2 * (targetPixel->g / 4);
    targetPixel->b = 2 * (targetPixel->b / 4);
}

void treasureMap::setLOB(PNG &im, pair<int, int> loc, int d)
{

    //  same as above, may need to deref
    RGBAPixel *targetPixel = im.getPixel(loc.first, loc.second);

    int sixBitInt;
    int b1b2;
    int b3b4;
    int b5b6;

    sixBitInt = d % 64;          // getting my 6 bit int
    b1b2 = (sixBitInt >> 4) & 3; // getting first 2 bits
    b3b4 = (sixBitInt >> 2) & 3; // ''       second
    b5b6 = sixBitInt & 3;        // ''       third

    targetPixel->r = (targetPixel->r & (-4)) | b1b2; //first turn last 2 bits to 0, then OR it with my b1b2
    targetPixel->g = (targetPixel->g & (-4)) | b3b4;
    targetPixel->b = (targetPixel->b & (-4)) | b5b6;
}

PNG treasureMap::renderMap()
{

    PNG baseCopy = base; // create a copy of base map

    //create 2d vector with width x height (full of bools)
    vector<vector<bool>> vecBools(base.width(), vector<bool>(base.height(), false));

    // create 2d vector with width x height (full of ints)
    vector<vector<int>> vecNums(base.width(), vector<int>(base.height(), -1));

    Queue<pair<int, int>> myQueue; //create a queue of pairs for locations

    vecBools[start.first][start.second] = true; // set start to true in 2dvector for checking locations
    vecNums[start.first][start.second] = 0;     // set start to value 0 ''  '' etc.

    setLOB(baseCopy, start, vecNums[start.first][start.second]); //encode the value into copy of maps start pixel

    myQueue.enqueue(start); //load up the start position in the queue

    while (!myQueue.isEmpty())
    {
        pair<int, int> curr;
        curr = myQueue.dequeue(); //set curr to the first pixel in the queue (begins with "start" pixel)

        vector<pair<int, int>> neighbourPixels; //create a vector for neighbours
        neighbourPixels = neighbors(curr);      //set it equal to neighbours' return vector

        for (int i = 0; i <= 3; i++)
        {
            if (good(vecBools, curr, neighbourPixels[i]))
            {                                                                                                        //check if neighbourpixels are good
                vecBools[neighbourPixels[i].first][neighbourPixels[i].second] = true;                                //mark good pixels as visited
                vecNums[neighbourPixels[i].first][neighbourPixels[i].second] = vecNums[curr.first][curr.second] + 1; // set pixels distance to curr's+1
                setLOB(baseCopy, neighbourPixels[i], vecNums[neighbourPixels[i].first][neighbourPixels[i].second]);  // encode the distance
                myQueue.enqueue(neighbourPixels[i]);                                                                 // put the neighbourpixels in the queue
            }
        }
    }

    return baseCopy;
}

PNG treasureMap::renderMaze()
{

    PNG baseCopy = base; // create a copy of base map

    //create 2d vector with width x height (full of bools)
    vector<vector<bool>> vecBools(base.width(), vector<bool>(base.height(), false));
    // create 2d vector with width x height (full of ints)
//    vector<vector<int>> vecNums(base.width(), vector<int>(base.height(), -1));

    Queue<pair<int, int>> myQueue; //create a queue of pairs for locations

    vecBools[start.first][this->start.second] = true; // set start to true in 2dvector for checking locations
//    vecNums[this->start.first][this->start.second] = 0;     // set start to value 0 ''  '' etc.

    setGrey(baseCopy, start); //encode the value into copy of maps start pixel

    myQueue.enqueue(start); //load up the start position in the queue
    pair<int, int> curr;          // create a pair to store a location

    while (!myQueue.isEmpty())
    {
        pair<int, int> curr;          // create a pair to store a location
        curr = myQueue.dequeue(); //set curr to the first pixel in the queue (begins with "start" pixel)

        vector<pair<int, int>> neighbourPixels; //create a vector for neighbours
        neighbourPixels = neighbors(curr);      //set it equal to neighbours' return vector
        for (int i = 0; i <= 3; i++)
        {
            if (good(vecBools, curr, neighbourPixels[i]))
            {                                                                         //check if neighbourpixels are good
                vecBools[neighbourPixels[i].first][neighbourPixels[i].second] = true; //mark good pixels as visited
                setGrey(baseCopy, neighbourPixels[i]);                                // encode the distance
                myQueue.enqueue(neighbourPixels[i]);                                  // put the neighbourpixels in the queue
            }
        }
    }

    RGBAPixel redSquareTemplatePix(255, 0, 0); //create a generic red pixel

    // a nested for loop that will make the appropriate pixels red if they're in image
    for (int i = -3; i <= 3; i++)
    {
        for (int j = -3; j <= 3; j++)
        {
            if (start.first + i <= baseCopy.width() - 1 && start.first + i >= 0 && start.second + j <= baseCopy.height() - 1 && start.second + j >= 0)
            {
                *baseCopy.getPixel(start.first + i, start.second + j) = redSquareTemplatePix;
            }
        }
    }

    return baseCopy;
}

bool treasureMap::good(vector<vector<bool>> &v, pair<int, int> curr, pair<int, int> next)
{

    //first check if in image
    if (next.first <= base.width() - 1 && next.first >= 0 && next.second <= base.height() - 1 && next.second >= 0)
    {

        // then we check if it's unvisited
        if (v[next.first][next.second] != true)
        {

            // then we check if it's the same colour
            if (*maze.getPixel(curr.first, curr.second) == *maze.getPixel(next.first, next.second))
            {

                return true; //if it's same colour return true
            }
            else
                return false; // if it's in image and unvisited but not same colour we return false
        }
    } 
    return false;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
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
