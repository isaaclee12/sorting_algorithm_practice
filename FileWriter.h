//
// Created by isaac on 10/23/2019.
//

/*
 *
 *
 *
 * UNUSED CODE - USED AS REFERENCE FOR FILE STUFF IN MAIN
 *
 *
 *
 *
 */

#ifndef PROJECT_3_FILEWRITER_H
#define PROJECT_3_FILEWRITER_H
#include <iostream>
#include <fstream>
#include "Video_Game.h"

using namespace std;

class FileWriter {
public:
    void makeHeader(string filename) {
        ofstream file;
        file.open ("../" + filename);
        for (int i=100; i <= 1000; i+=100){
            file << i; //Add each entry to a csv file
            if (i<1000) {
                file << ","; //Add a comma after each except the last entry
            }
        }
        file << endl; //end line
        file.close();
    }
    void writeToFile(string filename, vector<string> stringVector, int index, vector<int> intVector) {
        ofstream file;
        file.open ("../" + filename);
        file << stringVector[index];
        for (int i=0; i < intVector.size() ; ++i) {
            file << intVector[i] << ",";
            if (i < intVector.size() - 1) {
                file << ","; //Add a comma after each except the last entry
            }
        }
        file << endl;
        file.close();
    }

};


#endif //PROJECT_3_FILEWRITER_H
