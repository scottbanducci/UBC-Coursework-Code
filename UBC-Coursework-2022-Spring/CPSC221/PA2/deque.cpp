/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque()
{

    n1 = 0;
    n2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T targetObject = data[n1]; // store left-most object we're about to pop

    if (n2 - n1 <= n1 + 1)
    { // if we have enough left-side speace to resize

        vector<T> tempData; // temp vector to store objects in data

        for (int i = n1 + 1; i < n2 + 1; i++)
        {
            tempData.push_back(data[i]); // iterate through data starting at the object to the right of targetObject, filling the new vector
        }

        data = tempData; // use = operator to resize and copy

        n1 = 0;               // set n1 to 0
        n2 = data.size() - 1; // since data is resized, this should be index of last object in data
        return targetObject;
    }

    // if we don't need to resize
    n1++;
    return targetObject;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T targetObject = data[n2]; // store right-most object we're about to pop

    if (n2 - n1 <= n1)
    { // if we have enough left-side speace to resize

        vector<T> tempData; // temp vector to store objects in data

        for (int i = n1; i < n2; i++)
        {
            tempData.push_back(data[i]); // iterate through data starting at the object to the right of targetObject, filling the new vector
        }

        data = tempData; // use = operator to resize and copy

        n1 = 0;               // set n1 to 0
        n2 = data.size() - 1; // since data is resized, this should be index of last object in data
        return targetObject;
    }
    // if we don't need to resize
    n2--;
    data.pop_back();
    return targetObject;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    T targetObject = data[n1]; // store right-most object we're about to pop
    return targetObject;
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    T targetObject = data[n2]; // store right-most object we're about to pop
    return targetObject;
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    bool truth;
    if (n2 < 0)
    { // n2 will be negative if the vector is empty
        truth = true;
        return truth;
    }
    else
    {
        truth = false;
        return truth;
    }
}
