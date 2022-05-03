/*
** select.cpp
*/

#include <iostream>
#include <cstdlib>
#include <vector>

/* 
** generateVector - this function fills a vector with random numbers
*/
std::vector<int> generateVector(int size) 
{
    std::vector<int> v(size);

    for(int i = 0; i < size; i++) {
	v.at(i) = rand() % (100 * size);
    }
    return v;
}

/*
** insertionSort -  use the insertionSort algorithm that sorts the portion
** vector[first ... last] of vector and updates the number of comparisons made.
*/
template <class type>
void insertionSort(std::vector<type>& v, int first, int last, int &comparisons)
{
    for (int i = first + 1; i <= last; i++)
    {
        int index = i-1;
	type elem = v.at(i);

	/*
	** Move element "elem" into position within the part of v we care about.
	*/
        while (index >= first && elem < v.at(index))
	{
	    v.at(index + 1) = v.at(index);
	    comparisons++;
	    index--;
	}
	v.at(index+1) = elem;

	/*
	** Adjust the number of comparisons.
	*/
	if (index >= first)
	{
	    comparisons++;
	}
    }
}

/*
** A simple swap function.
*/
template<class type>
void swap(type& a, type& b)
{
    type tmp = a;
    a = b;
    b = tmp;
}

/*
** Now  the partition algorithm  of  quicksort, modified  to (1) count the
** number of comparisons it  is making and  (2) take as an extra parameter
** the position of the pivot to be used.
**
** This algorithm computes the Lesser and Greater vectors from our pseudo-
** code as follows: it moves the elements in vector[first ... last] so
** Lesser = vector[first ... mid-1], Greater = vector[mid+1 ... last] and
** the pivot is A[mid]. The function returns the position "mid".
*/
template<class type>
int partition(std::vector<type>&v, int first, int last, int pivotPosition, int &comparisons)
{
    swap(v.at(pivotPosition), v.at(last));
    type pivot = v.at(last);
    int back = first - 1;

    for (int front = first; front < last; front++)
    {
	comparisons++;
	if (v.at(front) <= pivot)
	{
	    back++;
	    swap(v.at(front), v.at(back)); 
	}
    }

    swap(v.at(back+1), v.at(last));
    return back+1;
}

/*
** print - function to print a vector (useful for debugging)
*/
template<class type>
void print(const std::vector<type>& v)
{
    for (unsigned int counter = 0; counter < v.size(); counter++) {
	std::cout << v.at(counter) << " ";
    }
    std::cout << std::endl;
}

/*
** Randomized function to  find the kth  smallest element of  a vector. It
** returns the position in the vector where the element was found.
*/
template<class type>
int randomizedQuickSelect(std::vector<type>& v, int first, int last, int i, int &comparisons)
{
    // Generate a random pivot position

    type pivot = rand() % last;

    // partition by pivot 
    type pivot_rank = partition(v, first, last, pivot, comparisons);

    // if we found the right element by chance return it
    if (pivot_rank == i-1)
    {
        return v.at(pivot_rank);
    }

    //if our chosen pivot was too big, search the lesser

    if (pivot_rank <i-1)
}
    
/*
** Now the deterministic selection algorithm.
**
*/
template<class type>
int select(std::vector<type>& v, int first, int last, int i, int &comparisons)
{
    /* You need to implement this */
}

/*
** Method runtests is really our main.
*/
void runtests() 
{
    /* You need to implement this */
}

int main()
{
    runtests();
}
