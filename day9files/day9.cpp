#include <fstream>  // file input
#include <iostream> // file input
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <stdlib.h>
#include <string>  //stings
#include <vector>
using namespace std; // iostream avoiding going std:: since no other namespace is used at present

void ReadData(std::vector<string> *datain) // inherited from previous days
{
    ifstream data("data.txt");
    if (data.is_open())
    {
        string line;
        while (getline(data, line))
        {
            datain->push_back(line);
        }
        data.close();
    }
    else
    {
        cout << "Error at reading files";
    }
}
void Print(short Carrier[], int maxX, int maxY)
{   cout << "maxX" << maxX << "maxY" << maxY << endl;
    for (int i = 0; i < maxY; i++)
    {
        for (int x = 0; x < maxX; x++)
        {
            cout << Carrier[x * maxY + i];
            if(Carrier[x * maxY + i] == -3936){
                cout << i << " " << x << endl;
            }
        }
        cout << endl;
    }
    cout << endl;
}

void GetDay1(short Data[], int maxX, int maxY)
{
    long Score = 0;
    // int y = 0;
    for (int y = 0; y <= maxY -1; y++)
    {
        for (int i = 0; i < maxX; i++)
        { // cout << "Number:" << Data[i * maxY + y] << endl;
            int tmp = Data[i * maxY + y];
            bool dir[4] = {0};
            if (y != 0)
            { // check up
                int t = y - 1;
                if (Data[i * maxY + t] > tmp)
                { // cout << "Up:" << Data[t * maxY + y] << endl;
                    dir[0] = 1;
                };
            }
            else
            {
                dir[0] = 1;
            }

            if (y != maxY - 1)
            { // check down
                int t = y + 1;
                if (Data[i * maxY + t] > tmp)
                { // cout << "Down:" << Data[t * maxY + y] << endl;
                    dir[1] = 1;
                };
            }
            else
            {
                dir[1] = 1;
            }

            if (i != 0)
            { // check left
                int t = i - 1;
                if (Data[t * maxY + y] > tmp)
                { // cout << "Lef:" << Data[t * maxY + y] << endl;
                    dir[2] = 1;
                };
            }
            else
            {
                dir[2] = 1;
            }
            if (i != maxX - 1)
            { // check right
                int t = i + 1;
                if (Data[t * maxY + y] > tmp)
                {
                    // cout << "Rig:" << Data[t * maxY + y] << endl;
                    dir[3] = 1;
                }
            }
            else
            {
                dir[3] = 1;
            }
            // cout << Score << " " << tmp << endl ;
            if (dir[0] && dir[1] && dir[2] && dir[3])
            {
                Score += 1 + tmp;
                cout << tmp << " " << endl;
                // cout << dir[0] << dir [1] << dir[2] << dir[3] << endl;
            }
            // if(tmp == 1){
            //    cout << " 0 :" << endl;
            //    cout << dir[0] << dir [1] << dir[2] << dir[3] << endl;

            // }
        }
    }
    cout << Score << endl;
}

void ConstructArray(std::vector<string> *datain, int maxX, int maxY)
{
    maxX = datain->at(0).size(); // check if works
    maxY = datain->size();
    cout << "maxX " << maxX << "maxY " << maxY << endl;
    const int a = 101 * sizeof(short) + 101;
    static short Carrier[a] = {0};
    for (int i = 0; i < maxY; i++)
    {
        string temp = datain->at(i);
        int x = 0;
        for(int b = 0; b < 100; b++)
        {   //cout << "X " << x << "Y " << i << "  " <<  temp << " " << (x * maxY + i) << endl;
            int t = temp[b] - '0'; //convert char to int
                //cout << t << endl;
            Carrier[x * maxY + i] = t;
            // temp = temp.substr(1);
            x++;
        }  
}
    Print(Carrier, maxX, maxY);
    GetDay1(Carrier, maxX, maxY);
}

int main()
{
    std::vector<string> data;
    ReadData(&data);
    int maxX = 0;
    int maxY = 0;
    ConstructArray(&data, maxX, maxY);
    //delete Array;
    // Print(Array, maxX, maxY); fix later
    // delete array
}
