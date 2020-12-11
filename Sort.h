//
// Created by isaac on 10/29/2019.
//

#ifndef PROJECT_4_SORT_H
#define PROJECT_4_SORT_H

#include <iostream>
#include <vector>
using namespace std;

class Sort {
public:
template<typename Comparable>
void printVec(const vector<Comparable> &items) {
    for (Comparable i : items) {
        cout << i << ", ";
    }
    cout << endl;
}

// To prepare for multiple sorting algorithms, we won't pass the vector by reference
// But we will return a reference to the copy of the vector that is passed in
template<typename Comparable>
vector<Comparable> bubbleSort(vector<Comparable> items, int &numWrites, int &numReads) {
    int numSwaps = -1, numIterations = 0, i;
    ++++numWrites; //+2 Writes

    Comparable temp;
    while (numSwaps != 0) {
        numSwaps = 0;
        ++numWrites; //+1 Write

        // Make one pass through the vector
        // The -1 in the condition makes sure i+1 stays in bounds
        for (i = 0; i < items.size() - numIterations - 1; ++i) {
            ++++numWrites; //+2 Writes (i=0, ++i)
            ++++numReads; //+2 Reads (a<b?)

            // Compare two consecutive elements to see if they are not in order
            if (items[i + 1] < items[i]) {
                ++numReads; //+2 Reads (a<b?)

                // Swap the elements
                temp = items[i];
                items[i] = items[i + 1];
                items[i + 1] = temp;
                // Increment numSwaps
                ++numSwaps;
                //Increment the good stuff
                ++++++numWrites; //+3 Writes
                ++++++numReads; //... and +3 Reads
            }

        }
        // Increment numIterations
        ++numIterations;
        //printVec(items);
    }
    // We didn't make any swaps in this pass. We are done.
    return items;
}


template<typename Comparable>
vector<Comparable> selectionSort(vector<Comparable> items) {
    int i, minIndex, swapIndex = 0;
    Comparable temp;
    while (swapIndex < items.size() - 1) {
        // Find the minimum value
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < items.size(); ++i) {
            if (items[i] < items[minIndex]) {
                minIndex = i;
            }
        }
        // See if we need to swap minimum into place
        if (swapIndex != minIndex) {
            temp = items[swapIndex];
            items[swapIndex] = items[minIndex];
            items[minIndex] = temp;
        }
        // Update swapIndex
        ++swapIndex;
        //printVec(items);
    }
    return items;
}

template<typename Comparable>
vector<Comparable> insertionSort(vector<Comparable> items, int &numWrites, int &numReads) {
    int insertionIndex, i;
    Comparable toBeInserted;
    for (insertionIndex = 1; insertionIndex < items.size(); ++insertionIndex) {
        ++++numWrites; //+2 Writes (index = 1, ++i)
        ++++numReads; //+2 Reads (a<b?)

        toBeInserted = items[insertionIndex];
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads

        i = insertionIndex - 1;
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads

        while (i >= 0 && items[i] > toBeInserted) {
            ++++++numReads; //+3 WHOLE READS WOW (i>=0, a>b?)

            // slide the larger element over
            items[i + 1] = items[i];
            --i;
            ++++numWrites; //+2 Writes (items, --i)
            ++numReads; //+1 Read (items[i]
        }
        // Reinsert the item back into the vector
        items[i + 1] = toBeInserted;
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads

        //printVec(items);
    }
    return items;
}

template<typename Comparable>
void mergeSortHelper(vector<Comparable> &items, int start, int end, int &numWrites, int &numReads) {
    // Recursive base case
    if (start == end) {
        ++++numReads; // +2 Reads for comparison

        // There is only one item left. Nothing to sort.
        return;
    }

    // Recursive calls
    int center = (start + end) / 2;
    ++numWrites; //+1 Write
    ++++numReads; //AND +2 Reads

    mergeSortHelper(items, start, center, numWrites, numReads);
    mergeSortHelper(items, center + 1, end, numWrites, numReads);

    // Now assume that the left and right halves are sorted. Merge the two halves.
    vector<Comparable> merged;
    int left = start, right = center + 1;
    ++++numWrites; //+2 Writes
    ++++numReads; //AND +2 Reads

    // While there are still elements in both halves
    while (left <= center && right <= end) {
        ++++++++numReads; //+4 WHOLE READS for the double comparison

        // Compare to see which element is smaller and put it in merged
        if (items[left] <= items[right]) {
            ++++numReads; //+2 Reads for comparison

            merged.push_back(items[left]);
            ++left;
            ++++numWrites; //+2 writes for vector write and ++left
            ++numReads; //+1 reads for items[left]

        } else {
            merged.push_back(items[right]);
            ++right;
            ++++numWrites; //+2 writes for vector write and ++right
            ++numReads; //+1 reads for items[right]
        }
    }

    // Only one of the halves is still populated.
    // Copy the rest of the elements into merged.
    while (left <= center) {
        merged.push_back(items[left]);
        ++left;
        ++++numWrites; //+2 writes for vector write and ++left
        ++++numReads; //+2 reads for comparison items[left]
    }
    while (right <= end) {
        merged.push_back(items[right]);
        ++right;
        ++++numWrites; //+2 writes for vector write and ++right
        ++++numReads; //+2 reads for comparison and items[right]
    }

    // Copy all of the elements back into items
    for (int i = start; i <= end; ++i) {
        ++++numWrites; //2 Writes for i and ++1
        ++++++numReads; //+3 READS for the = vars and a<b? vars
        items[i] = merged[i - start];
        ++numWrites; //+1 write for items[i]
        ++++++numReads; //+3 reads for merged and start
    }

    //printVec(items);
}

template<typename Comparable>
vector<Comparable> mergeSort(vector<Comparable> &items, int &numWrites, int &numReads) {
    mergeSortHelper(items, 0, items.size() - 1, numWrites, numReads);
    return items;
}

template<typename Comparable>
void quickSortHelper(vector<Comparable> &items, int start, int end, int &numWrites, int &numReads) {
    if (start != end) {
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads

        // Choose a partition value
        Comparable partition = items[start];
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads

        // Partition each element into three categories
        vector<Comparable> less, equal, greater;
        for (int i = start; i < end; ++i) {
            ++++numWrites; //+2 Writes for i and ++i
            ++++numReads; //+2 Reads for (a<b?)

            if (items[i] < partition) {
                ++++numReads; //+2 Reads for (a<b?)
                less.push_back(items[i]);
                ++numWrites; //+1 Write
                ++numReads; //AND +1 Reads

            } else if (items[i] == partition) {
                ++++numReads; //+2 Reads for (a==b?)
                equal.push_back(items[i]);
                ++numWrites; //+1 Write
                ++numReads; //AND +1 Reads

            } else {
                greater.push_back(items[i]);
                ++numWrites; //+1 Write
                ++numReads; //AND +1 Reads

            }
        }

        // Keep track of how many elements are in each vector

        // Move everything back into items
        int i = start;
        ++numWrites; //+1 Write
        for (Comparable &item : less) {
            ++numReads; //+1 for every item read

            items[i] = item;
            ++i;
            ++++numWrites; //+2 Writes for items[i] and ++i
            ++numReads; //+1 for item

        }
        for (Comparable &item : equal) {
            ++numReads; //+1 for every item read

            items[i] = item;
            ++i;
            ++++numWrites; //+2 Writes for items[i] and ++i
            ++numReads; //+1 for item
        }
        for (Comparable &item : greater) {

            ++numReads; //+1 for every item read
            items[i] = item;
            ++i;
            ++++numWrites; //+2 Writes for items[i] and ++i
            ++numReads; //+1 for item
        }

        //printVec(items);

        // Recursive calls for less and greater portion of items
        if (less.size() > 1) {
            ++numReads; //+1 Reads for (a>1?)
            quickSortHelper(items, start, start + less.size() - 1, numWrites, numReads);
        }
        if (greater.size() > 1) {
            ++numReads; //+1 Reads for (a>1?)
            quickSortHelper(items, end - (greater.size() - 1), end, numWrites, numReads);
        }
        //printVec(items);
    }

}

// Stable version
template<typename Comparable>
vector<Comparable> quickSort(vector<Comparable> items, int start, int end, int &numWrites, int &numReads) {
    quickSortHelper(items, start, end, numWrites, numReads);
    return items;
}

vector<int> radixSort(vector<int> items, int numDigits, int &numWrites, int &numReads) {
    if (numDigits > 0) {
        int denominator = 1;
        for (int i = 0; i < numDigits; ++i) {
            // Bucket sort a digit

            // Store the buckets in a 2-D vector
            // buckets[x] is one bucket/vector
            // buckets[x][y] is one integer
            vector<vector<int>> buckets;
            buckets.resize(10);

            // put the integers from items into the buckets
            for (int &item : items) {
                // access the digit
                int digit = (item / denominator) % 10;
                // put it in the bucket
                buckets[digit].push_back(item);
            }

            // Copy everything from the buckets back into items
            int index = 0;
            for (int bucket = 0; bucket < buckets.size(); ++bucket) {
                for (int num = 0; num < buckets[bucket].size(); ++num) {
                    items[index] = buckets[bucket][num];
                    ++index;
                }
            }

            denominator *= 10;

            //printVec(items);
        }
    }
    return items;
}

// Helper function for heapSort
    inline int leftChild(int i) {
        return 2 * i + 1;
    }

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
    template <typename Comparable>
    void percolateDown(vector<Comparable> &items, int i, int n, int &numWrites, int &numReads) {
        int child;
        Comparable tmp;

        for(tmp = items[i]; leftChild(i) < n; i = child) {
            ++++numWrites; //2 Writes for i and tmp
            ++++++++numReads; //A WHOPPING 4 READS for the = vars and a<b? vars

            child = leftChild(i);
            ++numWrites; //+1 Write
            ++numReads; //AND +1 Reads

            // choose the child with the larger value
            if (child != n - 1 && items[child] < items[child + 1]) {
                ++child;
                ++numWrites; //+1 writes for ++child
                ++++++numReads; //3 WHOLE READS for the comparisons
            }

            // if the parent is less than the child, swap them
            if (tmp < items[child]) {
                items[i] = items[child];
                ++numWrites; //+1 for items[i]
                ++++++numReads; //+3 reads for a<b? and items[child]
            } else {
                // parent is >= both children. nothing more to do.
                break;
            }
        }
        items[i] = tmp;
        ++numWrites; //+1 Write
        ++numReads; //AND +1 Reads
    }

    template <typename Comparable>
    vector<Comparable> heapSort(vector<Comparable> items, int &numWrites, int &numReads) {
        // build the heap (with max value at root)
        for (int i = items.size() / 2 - 1; i >= 0; --i) {
            ++++numWrites; //Two writes for i and --i
            ++++++numReads; //3 Reads for items.size and a>b

            percolateDown(items, i, items.size(), numWrites, numReads);
        }
        //`printVec(items);
        // keep deleting the max
        for (int j = items.size() - 1; j > 0; --j) {
            ++++numWrites; //Two writes for j and --j
            ++++++numReads; //3 Reads for items.size and a>b

            // swap comp[0] and comp[j]
            Comparable temp = items[0];
            ++numWrites; //+1 Write
            ++numReads; //AND +1 Reads

            items[0] = items[j];
            ++numWrites; //+1 Write
            ++numReads; //AND +1 Reads

            items[j] = temp;
            ++numWrites; //+1 Write
            ++numReads; //AND +1 Reads

            percolateDown(items, 0, j, numWrites, numReads);

            //printVec(items);
        }
        return items;
    }

    int main() {
        vector<int> unsorted = {7, 1, 7, 54, 0, 12, 8, 42, 26, 68, 16};
        printVec(unsorted);
        vector<int> sorted;
        //sorted = bubbleSort(unsorted);
        //sorted = selectionSort(unsorted);
        //sorted = insertionSort(unsorted);
        //sorted = mergeSort(unsorted);
        //sorted = quickSort(unsorted);
        //sorted = radixSort(unsorted, 2);
        //sorted = heapSort(unsorted);
        return 0;
    }




















};

#endif //PROJECT_4_SORT_H
