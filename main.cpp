#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <ctime>
#include "Video_Game.h"
#include "Sort.h"
#include "FileWriter.h"
using namespace std;

int main() {
    //Establish header class and vector
    Video_Game project;
    Sort Sort;
    vector<Video_Game> video_games;

    //Data-out variables
    string arr[] = {"Bubble Sort","Insertion Sort","Quick Sort","Heap Sort","Two Sort"};
    vector<string> sortNames(arr, arr+5);

    //File Writer
    FileWriter FileWriter;
    FileWriter.makeHeader("writes.csv");
    FileWriter.makeHeader("reads.csv");

    //TIME VARS
    clock_t start;
    double duration;

    //Read csv file into vector
    project.readGamesFromFile("vgsales.csv",video_games);

    /* SORTS TO BE USED
     * 1. Bubble Sort
     * 2. Insertion Sort
     * 3. Quick Sort
     * 4. Heap Sort
     * 5. Two Sort (Merge Sort Global_Sales, then Radix Sort JP_Sales)

    /* Debug Code (goes in 2nd for loop)
         for (int j = 0; j < i; ++j) {
             //cout << j << endl;
            //Format global sales of each vg to 1 dec.
            //https://stackoverflow.com/questions/33125779/format-double-value-in-c
            /*double temp = video_games_subset[j].getGlobal_Sales();
            string s;
            stringstream sstream;
            sstream.setf(ios::fixed);
            sstream.precision(1);
            sstream << temp;
            s = sstream.str();

            out += s + ", ";
        }*/

    /*Use each sorting algorithm to sort a vector of the first 100 objects from your dataset. Record
    the number of reads (the number of times you retrieve and use an object from the vector) and
    writes (the number of times you assign an object into the vector). Then do the same for a
    vector of size 200, 300, 400, 500, 600, 700, 800, 900, and 1000. Each of the five sorting
    algorithms should be given identical unsorted vectors to begin with.*/

    /*
     * BUBBLE SORT
     */

    int numBubbleWrites = 0;
    int numBubbleReads = 0;
    vector<int> bubbleWritesVector;
    vector<int> bubbleReadsVector;
    for (int i=100; i <= 1000; i+=100)
    {
        //Make subset from item 0 to item i (100,200,etc)
        vector<Video_Game>::const_iterator first = video_games.begin();
        vector<Video_Game>::const_iterator last = video_games.begin() + i;
        vector<Video_Game> video_games_subset(first, last);
        string out = "";

        //TIME START
        start = clock();

        //Sort that subset vector
         Sort.bubbleSort(video_games_subset, numBubbleWrites, numBubbleReads);

        //PRINT TIME
        duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);

        //, the number subvector is: " <<  out << "and
        cout << "For a subvector of size " << i << " the # of reads w/ Bubble Sort is: " << numBubbleReads
        << "  and the # of writes is: " << numBubbleWrites << " DURATION: " << duration << "ms" << endl;

        //Add data to vectors
        bubbleWritesVector.push_back(numBubbleWrites);
        bubbleReadsVector.push_back(numBubbleReads);
    }

    /*
     * INSERTION SORT
     */

    int numInsertionWrites = 0;
    int numInsertionReads = 0;
    vector<int> insertionWritesVector;
    vector<int> insertionReadsVector;
    for (int i=100; i <= 1000; i+=100)
    {
        //Make subset from item 0 to item i (100,200,etc)
        vector<Video_Game>::const_iterator first = video_games.begin();
        vector<Video_Game>::const_iterator last = video_games.begin() + i;
        vector<Video_Game> video_games_subset(first, last);
        string out = "";

        //TIME START
        start = clock();

        //Sort that subset vector
        Sort.insertionSort(video_games_subset, numInsertionWrites, numInsertionReads);

        //PRINT TIME
        duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);

        //, the number subvector is: " <<  out << "and
        cout << "For a subvector of size " << i << " the # of reads w/ Insertion Sort is: " << numInsertionReads
             << "  and the # of writes is: " << numInsertionWrites << " DURATION: " << duration << "ms" << endl;

        //Add data to vectors
        insertionWritesVector.push_back(numInsertionWrites);
        insertionReadsVector.push_back(numInsertionReads);
    }



    /*
     * QUICK SORT
     */

    int numQuickWrites = 0;
    int numQuickReads = 0;
    vector<int> quickWritesVector;
    vector<int> quickReadsVector;
    for (int i=100; i <= 1000; i+=100)
    {
        //Make subset from item 0 to item i (100,200,etc)
        vector<Video_Game>::const_iterator first = video_games.begin();
        vector<Video_Game>::const_iterator last = video_games.begin() + i;
        vector<Video_Game> video_games_subset(first, last);

        //TIME START
        start = clock();

        //Sort that subset vector
        Sort.quickSort(video_games_subset,0,i,numQuickWrites,numQuickReads);

        //PRINT TIME
        duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);

        //Print reads
        cout << "For a subvector of size " << i << " the # of reads w/ Quick Sort is: " << numQuickReads <<
         " and the # of writes is: " << numQuickWrites << " DURATION: " << duration << "ms" << endl;

        //Data into vector
        quickWritesVector.push_back(numQuickWrites);
        quickReadsVector.push_back(numQuickReads);
    }

    /*
     * HEAP SORT
     */

    int numHeapWrites = 0;
    int numHeapReads = 0;
    vector<int> heapWritesVector;
    vector<int> heapReadsVector;
    for (int i=100; i <= 1000; i+=100)
    {
        //Make subset from item 0 to item i (100,200,etc)
        vector<Video_Game>::const_iterator first = video_games.begin();
        vector<Video_Game>::const_iterator last = video_games.begin() + i;
        vector<Video_Game> video_games_subset(first, last);
        string out = "";

        //TIME START
        start = clock();

        //Sort that subset vector
        Sort.heapSort(video_games_subset, numHeapWrites, numHeapReads);

        //PRINT TIME
        duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);

        //, the number subvector is: " <<  out << "and
        cout << "For a subvector of size " << i << " the # of reads w/ Heap Sort is: " << numHeapReads
        << " and the # of writes is: " << numHeapWrites << " DURATION: " << duration << "ms" << endl;

        //Add data to vectors
        heapWritesVector.push_back(numHeapWrites);
        heapReadsVector.push_back(numHeapReads);
    }

    /*
     * TWO SORT - Merge Global and then Radix JP
     */

    int numTwoSortWrites = 0;
    int numTwoSortReads = 0;
    vector<int> twoSortWritesVector;
    vector<int> twoSortReadsVector;
    for (int i=100; i <= 1000; i+=100)
    {
        //Make subset from item 0 to item i (100,200,etc)
        vector<Video_Game>::const_iterator first = video_games.begin();
        vector<Video_Game>::const_iterator last = video_games.begin() + i;
        vector<Video_Game> video_games_subset(first, last);
        string out = "";

        vector<int> video_games_subset_jp;

        //TIME START
        start = clock();

        //Sort that subset vector
        Sort.mergeSort(video_games_subset, numTwoSortWrites, numTwoSortReads);

        //Push back every JP_Sales from the sorted vector into an int vector
        for (int j=0; j < video_games_subset.size(); ++j) {
            video_games_subset_jp.push_back(video_games_subset[j].getJP_Sales());
        }

        //Sort
        Sort.radixSort(video_games_subset_jp, 10, numTwoSortWrites, numTwoSortReads);

        //PRINT TIME
        duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);

        //, the number subvector is: " <<  out << "and
        cout << "For a subvector of size " << i << " the # of reads w/ Two Sort is: " << numTwoSortReads <<
        " and the # of writes is: " << numTwoSortWrites << " DURATION: " << duration << "ms" << endl;

        //Add data to vectors
        twoSortWritesVector.push_back(numTwoSortWrites);
        twoSortReadsVector.push_back(numTwoSortReads);
    }

    /*
     * WRITE DATA TO FILES
     */

    /*
     * WRITES
     */
    ofstream writesFile;
    writesFile.open("../writes.csv");

    //FILE HEADER (0 through 1000 by 100s)
    for (int i=0; i <= 1000; i+=100){
        writesFile << i; //Add each entry to a csv file
        if (i<1000) {
            writesFile << ","; //Add a comma after each except the last entry
        }
    }
    writesFile << endl; //end line

    //EACH ROW AFTER
    writesFile << "Bubble Sort" << ","; //Row Name

    for (int j=0; j < bubbleWritesVector.size(); ++j) {
        writesFile << bubbleWritesVector[j]; // add each entry
        if (j < bubbleWritesVector.size() - 1) {
            writesFile << ","; //add comma after each entry but the last
        }
    }
    writesFile << endl; //end line

    writesFile << "Insertion Sort" << ","; //Row Name

    for (int j=0; j < insertionWritesVector.size(); ++j) {
        writesFile << insertionWritesVector[j]; // add each entry
        if (j < insertionWritesVector.size() - 1) {
            writesFile << ","; //add comma after each entry but the last
        }
    }
    writesFile << endl; //end line

    writesFile << "Quick Sort" << ","; //Row Name

    for (int j=0; j < quickWritesVector.size(); ++j) {
        writesFile << quickWritesVector[j]; // add each entry
        if (j < quickWritesVector.size() - 1) {
            writesFile << ","; //add comma after each entry but the last
        }
    }
    writesFile << endl; //end line

    writesFile << "Heap Sort" << ","; //Row Name

    for (int j=0; j < heapWritesVector.size(); ++j) {
        writesFile << heapWritesVector[j]; // add each entry
        if (j < heapWritesVector.size() - 1) {
            writesFile << ","; //add comma after each entry but the last
        }
    }
    writesFile << endl; //end line

    writesFile << "Two Sort" << ","; //Row Name

    for (int j=0; j < twoSortWritesVector.size(); ++j) {
        writesFile << twoSortWritesVector[j]; // add each entry
        if (j < twoSortWritesVector.size() - 1) {
            writesFile << ","; //add comma after each entry but the last
        }
    }
    writesFile << endl; //end line
    writesFile.close();


    /*
     * READS
     */
    ofstream readsFile;
    readsFile.open("../reads.csv");

    //FILE HEADER (0 through 1000 by 100s)
    for (int i=0; i <= 1000; i+=100){
        readsFile << i; //Add each entry to a csv file
        if (i<1000) {
            readsFile << ","; //Add a comma after each except the last entry
        }
    }
    readsFile << endl; //end line

    //EACH ROW AFTER

    readsFile << "Bubble Sort" << ","; //Row Name

    for (int j=0; j < bubbleReadsVector.size(); ++j) {
        readsFile << bubbleReadsVector[j]; // add each entry
        if (j < bubbleReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line

    readsFile << "Insertion Sort" << ","; //Row Name

    for (int j=0; j < insertionReadsVector.size(); ++j) {
        readsFile << insertionReadsVector[j]; // add each entry
        if (j < insertionReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line

    readsFile << "Quick Sort" << ","; //Row Name

    for (int j=0; j < quickReadsVector.size(); ++j) {
        readsFile << quickReadsVector[j]; // add each entry
        if (j < quickReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line

    readsFile << "Heap Sort" << ","; //Row Name

    for (int j=0; j < heapReadsVector.size(); ++j) {
        readsFile << heapReadsVector[j]; // add each entry
        if (j < heapReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line

    readsFile << "Two Sort" << ","; //Row Name

    for (int j=0; j < twoSortReadsVector.size(); ++j) {
        readsFile << twoSortReadsVector[j]; // add each entry
        if (j < twoSortReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line
    readsFile.close();

    return 0;
}