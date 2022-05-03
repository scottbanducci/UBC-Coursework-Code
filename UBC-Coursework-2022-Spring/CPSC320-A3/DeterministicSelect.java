import java.io.*;

public class DeterministicSelect
{

    //
    // Random number generator.
    //
    private java.util.Random rng;

    //
    // Counter class - used to hold comparison numbers.
    //
    private static class Counter
    {
	private int count;

	public Counter()
	{
	    count = 0;
	}

	public void increment()
	{
	    count++;
	}

	public int valueOf()
	{
	    return count;
	}
    }

    // 
    // generateVector - this method fills two arrays with random numbers
    //
    private void generateVectors(int[] array1, int[] array2) 
    {
	int size = array1.length;
        for(int i = 0; i < size; i++) {
	    array1[i] = array2[i] = rng.nextInt(100 * size);
        }
    }

    //
    // insertionSort -  use the insertionSort algorithm that sorts the portion
    // vector[first ... last] of vector and updates the number of comparisons made.
    //
    private void insertionSort(int[] vector, int first, int last, Counter comparisons)
    {
        for (int i = first + 1; i <= last; i++)
        {
            int index = i-1;
	    int elem = vector[i];

	    /*
	    ** Move element "elem" into position within the part of v we care about.
	    */
            while (index >= first && elem < vector[index])
	    {
	        vector[index + 1] = vector[index];
	        comparisons.increment();
	        index--;
	    }
	    vector[index+1] = elem;

	    /*
	    ** Adjust the number of comparisons.
	    */
	    if (index >= first)
	    {
	        comparisons.increment();
	    }
        }
    }

    //
    // A simple swap method.
    //
    private void swap(int[] A, int x, int y)
    {
        int tmp = A[x];
        A[x] = A[y];
        A[y] = tmp;
    }

    //
    // Now  the partition algorithm  of  quicksort, modified  to (1) count the
    // number of comparisons it  is making and  (2) take as an extra parameter
    // the position of the pivot to be used.
    //
    // This algorithm computes the Lesser and Greater vectors from our pseudo-
    // code as follows: it moves the elements in vector[first ... last] so
    // Lesser = vector[first ... mid-1], Greater = vector[mid+1 ... last] and
    // the pivot is A[mid]. The method returns the position "mid".
    //
    private int partition(int[] vector, int first, int last, int pivotPosition, Counter comparisons)
    {
        swap(vector, pivotPosition, last);
        int pivot = vector[last];
        int back = first - 1;

        for (int front = first; front < last; front++)
        {
	    comparisons.increment();
	    if (vector[front] <= pivot)
	    {
	        back++;
	        swap(vector, front, back); 
	    }
        }

        swap(vector, back+1, last);
        return back+1;
    }

    //
    // print - method to print an array (useful for debugging)
    //
    private void print(int[] vector)
    {
        for (int counter = 0; counter < vector.length; counter++) {
	    System.out.print(vector[counter] + " ");
        }
        System.out.println();
    }

    //
    // Randomized method to  find the kth  smallest element of  a vector. It
    // returns the position in the vector where the element was found.
    //
    private int randomizedQuickSelect(int[] vector, int first, int last, int k, Counter comparisons)
    {
	/* You need to implement this */
    }
    
    //
    // Now the deterministic selection algorithm.
    //
    private int select(int[] vector, int first, int last, int k, Counter comparisons)
    {
	/* You need to implement this */
    }

    //
    // Method runtests is really our main.
    //
    public void runtests() 
    {
	/* You need to implement this */
    }
    
    //
    // Main.
    //
    public static void main(String[] s)
    {
	DeterministicSelect obj = new DeterministicSelect();
	obj.runtests();
    }
}
