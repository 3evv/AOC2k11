#include <fstream>   // file input
#include <iostream>  // file input
using namespace std; // iostream avoiding going std:: since no other namespace is used at present.
//#include <cmath> //min max
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <string>  //stings
#include <vector> 

long Fishes[9][1] = {0};

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
void Decodedata(std::vector<string> *datain){  //consolidate data into a single array of known states: 0-8 Days, where at 0 they spawn new 8, and go into 6
   //long Fishes[8][1] = {0}; Learn to return a 2d array 
   for(int i = 0; i < datain->size(); i++){
    string temp = datain->at(i); //iterate stoi till string empty
    while(temp.size() > 1){    //iterate stoi till string empty
    int tFish = stoi(temp.substr(0,temp.find(",",1)));
        Fishes[tFish][0]++;
        temp = temp.substr(temp.find_first_of(",")+1);
    } 
         Fishes[stoi(temp)][0]++;
         datain->clear();
   }
}
void TestFishes(){
    cout << "TEST: " << endl;
    for(int i = 0; i < 9; i++){
        
        cout << "Days " << i << " " << Fishes[i][0] << endl;
    }
}
void SimulateFishes(int Daystosim){ // scroll oldest to youngest. 
    long TemporaryFishes[8][1] = {0};
    for(int q = 0; q <= Daystosim; q++){
       //W cout << "TempFsh " << TemporaryFishes[0][0] << " " << Fishes[0][0] << endl;
        for(int i = 0; i < 9; i++){
        TemporaryFishes[i][0] = Fishes[i][0];
    }
        //TestFishes(); tu się jebie
        for(int i = 8; i > 0; i--){ //reassign all bigger than 0 days to a day lower. 
        Fishes[i-1][0] = TemporaryFishes[i][0];
    }   
        //TestFishes(); 
       // cout << "TempFsh " << TemporaryFishes[0][0] << " " << Fishes[0][7] << endl;
        Fishes[6][0] = Fishes[6][0] + TemporaryFishes[0][0];
        Fishes[8][0] = TemporaryFishes[0][0];
        //TestFishes(); 
    }
}
long CalculateFish(){
    long result = 0;
    for(int i = 0; i < 8; i++){
        result += Fishes[i][0]; // test +=
    }
    return result;
}

int main(){
    std::vector<string> datain;
    PassData(&datain);
    Decodedata(&datain);
    //TestFishes();
    int Days = 256;
    SimulateFishes(Days);
    TestFishes();
    cout << CalculateFish() << endl;
}