#include <fstream>   // file input
#include <iostream>  // file input
using namespace std; // iostream avoiding going std:: since no other namespace is used at present.
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <string>  //stings
#include <vector>
#include <time.h>
// global var:
//  int crabs = 1;
//  int *crabpos; //declare array fix with pointers

void PassData(std::vector<string> *datain) // inherited from previous days
{
    ifstream data("data.txt"); // input file.
    if (data.is_open())        // check if opened
    {
        string line; // temporary string to pass data
        while (getline(data, line))
        {
            datain->push_back(line); // pass data to vector
        }
        data.close();
    }
    else
    {
        cout << "Error at reading files";
    }
}
int Decodedata(std::vector<string> *datain)
{                                // consolidate data into a single array of known states: 0-8 Days, where at 0 they spawn new 8, and go into 6
    int crabs = 1;               // Array of crabs pos [nb. of crab position] 0 - the position of the crab 1 -[fuel requied to get there by everyone]
    string temp = datain->at(0); // iterate stoi till string empty
    string length = datain->at(0);
    int n = 0;
    while (length.find(",") != -1)
    {
        length = length.substr(length.find(",") + 1);
        crabs++;
        // cout << length << endl;
    }
        cout << "crabs: " << crabs << endl;
    // cout << crabs << endl;
    int crabpos[crabs][2] = {0};
    while (temp.find(",") != -1)
    { // iterate stoi till string empty
        int tCrab = stoi(temp.substr(0, temp.find(",", 1)));
        crabpos[n][0] = tCrab;
        temp = temp.substr(temp.find_first_of(",") + 1);
        n++;
    }
    crabpos[n][0] = stoi(temp.substr(0, temp.find(",", 1)));
    for (int n = 0; n < crabs; n++)
    {
        for (int i = 0; i < crabs; i++)
        {   int tmp = 0;
            if (n >= crabpos[i][0])
            {   
                 tmp = (n - crabpos[i][0]);
            }
            else
            {
                tmp += (crabpos[i][0] - n);
            }
            for(int z = 1; tmp > 0; z++){
            crabpos[n][1] += z;
            tmp--;
            }
        }
    }

    int lowestFuel = 2147483647; // max int value
    for (int n = 0; n < crabs; n++)
    {
       //cout << lowestFuel << " Pos: " << n << " " << crabpos[n][1] << endl;
        if (lowestFuel > crabpos[n][1])
        {
            lowestFuel = crabpos[n][1];
        }
    }
    //datain->clear();
    return lowestFuel;
}

int main()
{
    clock_t start_time = clock();
    std::vector<string> datain;
    PassData(&datain);
    cout << Decodedata(&datain) << endl;
    cout << "Elapsed time: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << "s" << endl;
}
// TDL:
//  learn to pass an array ? pointer to addrs
//  fix global array or stick to vector.