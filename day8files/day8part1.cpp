#include <fstream>   // file input
#include <iostream>  // file input
using namespace std; // iostream avoiding going std:: since no other namespace is used at present.
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <string>  //stings
#include <vector>

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

int DecodeNbrs(std::vector<string> *datain, std::vector<string> *dataout){
    int sum = 0;
    for(int i = 0; i < datain->size(); i++){
    string temp = datain->at(i); 
    temp = temp.substr(temp.find("|")+2);
    string tnumber = temp;
    for(int z = 4; z != 0; z--){
        string tmp = tnumber.substr(0, tnumber.find(" "));
        switch(tmp.size()){
            case 2: sum++; //1
            break;
            case 4: sum++; //4
            break;
            case 3: sum++; //7
            break;
            case 7: sum++; //8
            break;
        }
        tnumber = tnumber.substr(tnumber.find(" ")+1);
    }
    }
    return sum;
}
int main()
{
    std::vector<string> data;
    PassData(&data);
    std::vector<string> digitcarrier;
    cout << DecodeNbrs(&data, &digitcarrier) << endl;
}