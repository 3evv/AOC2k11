/* Plan:
0) get data Y
1) find out max grid size in x,y wip
2) design a cleanup function keeping only x,y line vectors
3a) paste data to a array x,y created in 1.
3b) design a graphical output for the grid (troubleshooting + nice views :>)
4) design a function to tell where do vectors intersect, where 0 -> no vectors, 1 -> one vector etc.
5) create a filter function to count any point where at least 2 vectors intersected (modifiable amount of intersections???) */

//#include <bitset> // size() etc.
#include <fstream>   // file input
#include <iostream>  // file input
using namespace std; // iostream avoiding going std:: since no other namespace is used at present.
//#include <cmath> //min max
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <string>  //stings
#include <vector>  //vectors

// declaration for global variables. try to avoid

struct Vector
{ // class private by default.
    int x1;
    int x2;
    int y1;
    int y2;
};

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

std::vector<Vector> DecodeDatatoVectors(std::vector<string> *datain)
{
    cout << "begin Decode: " << datain->size() << endl;
    std::vector<Vector> result;
    for (int i = 0; i < datain->size(); i++)
    { // get length of datain && protect from exceeding those limits.
        string line = datain->at(i);
        Vector v; // create a vector for each i.
        // cout << "t1 " << datain.at(i) << endl;
        // cout << "test " << line.substr(line.find_first_of(",")+1,line.find_first_of(" ") - 1) << endl;
        int x1, x2, y1, y2 = 0;
        v.x1 = stoi(line.substr(0, line.find_first_of(",")));                               // cout << "x1 ";
        v.y1 = stoi(line.substr(line.find_first_of(",") + 1, line.find_first_of(" ") - 1)); // cout << "y1 ";
        int endpos = line.find("-> ") + 3;                                                  // find x2 origin
        v.x2 = stoi(line.substr(endpos, line.find(",", endpos)));                           // cout << "x2 ";
        v.y2 = stoi(line.substr(line.find(",", endpos) + 1));                               // cout << "y2 ";
        result.push_back(v);
        // cout << i << " x: " << v[i].x1 << " " << v[i].x2 <<  " y: " << v[i].y1 << " " << v[i].y2 << endl; // test the values assigned. so far so good.
    }
    return result;
}

void test(std::vector<Vector> *input)
{
    for (int i = 0; i < input->size(); i++)
    {
        Vector v = input->at(i);
        cout << " x: " << v.x1 << " " << v.x2 << " y: " << v.y1 << " " << v.y2 << endl; // test the values assigned
    }
}

void ArrayConstructor(std::vector<Vector> *input)
{
    int size = input->size();
    Vector table[size];
    // for (int i = 0; i < size; i++)
    // { // reassign vector to array     Is it really neccesary? Clean up smaller corrds as 1 bigger as 2 ?
    //     input->at(i).x1 = input->at(i).x1;
    //     input->at(i).y1 = input->at(i).y1;
    //     input->at(i).x2 = input->at(i).x2;
    //     input->at(i).y2 = input->at(i).y2;
    // }
    // cout << table[1].x1 << " " << input->at(1).x1 << endl; test of reasigment

    // create array:

    // lowest X:
    int lX = 0;
    int hX = 0;
    int lY = 0;
    int hY = 0; // declare extremal coords.
    for (int i = 0; i < size; i++)
    {
        if (input->at(i).x1 > hX)
        {
            hX = input->at(i).x1;
        }
        if (input->at(i).x2 > hX)
        {
            hX = input->at(i).x2;
        }
        if (input->at(i).y1 > hY)
        {
            hY = input->at(i).y1;
        }
        if (input->at(i).y2 > hY)
        {
            hY = input->at(i).y2;
        }
        // finding lowest:
        if (input->at(i).x1 < lX)
        {
            lX = input->at(i).x1;
        }
        if (input->at(i).x2 < lX)
        {
            lX = input->at(i).x2;
        }
        if (input->at(i).y1 < lY)
        {
            lY = input->at(i).y1;
        }
        if (input->at(i).y2 < lY)
        {
            lY = input->at(i).y2;
        }
    }
    cout << "Extremal coords:" << lX << " " << lY << " " << hX << " " << hY << endl;
    hX++;
    hY++;
    // Declaring a array of vectors

    int Matrix[hX][hY]; // read about implementing {0} as zeroing methode
    for (int tx = 0; tx < hX; tx++)
    {
        for (int ty = 0; ty < hY; ty++)
        {
            Matrix[tx][ty] = 0;
        }
    }

    // cout << " MATRIX: " << endl;
    // for(int ty = 0;  ty != hY; ty++){
    //     for(int tx = hX; tx != 0; tx--){
    //  cout << Matrix[tx][ty] << " ";
    //     }
    //     cout << endl;
    // }
    // check and remove non-single plane vectors, then move vector data onto display matrix
    // int nonplane = 0;

    for (int i = 0; i < size; i++)
    { // check x
        if (input->at(i).x1 != input->at(i).x2)
        {
            if (input->at(i).y1 == input->at(i).y2)
            { // cout << "IN " << input->at(i).x1 << input->at(i).y1 << input->at(i).x2 << input->at(i).y2 << endl;
                int tempx = 0;
                int endx = 0;
                int y = input->at(i).y1;
                if (input->at(i).x1 < input->at(i).x2)
                {
                    tempx = input->at(i).x1;
                    endx = input->at(i).x2;
                    //cout << "IN " << input->at(i).x1 << input->at(i).y1 << input->at(i).x2 << input->at(i).y2 << endl;
                }
                else
                {
                    tempx = input->at(i).x2;
                    endx = input->at(i).x1;
                }
                while (tempx <= endx)
                {
                    Matrix[tempx][y]++;
                    tempx++;
                }            // else
            // {
            //     cout << input->at(i).x1 << input->at(i).y1 << input->at(i).x2 << input->at(i).y2 << endl;
            // }
            }
            // else
            // {
            //     cout << input->at(i).x1 << input->at(i).y1 << input->at(i).x2 << input->at(i).y2 << endl;
            // }
        }
        if (input->at(i).y1 != input->at(i).y2)
        {
            if (input->at(i).x1 == input->at(i).x2)
            { // cout << "IN " << input->at(i).x1 << input->at(i).y1 << input->at(i).x2 << input->at(i).y2 << endl;
                int tempy = 0;
                int endy = 0;
                int x = input->at(i).x1;
                if (input->at(i).y1 < input->at(i).y2)
                {
                    tempy = input->at(i).y1;
                    endy = input->at(i).y2;
                }
                else
                {
                    tempy = input->at(i).y2;
                    endy = input->at(i).y1;
                }
                while (tempy <= endy)
                {
                    Matrix[x][tempy]++;
                    tempy++;
                }
            }
        }
        if(input->at(i).x1 != input->at(i).x2 && input->at(i).y1 != input->at(i).y2){
            int tempx = input->at(i).x1 , 
            endx = input->at(i).x2 ,
             tempy = input->at(i).y1 , 
             endy = input->at(i).y2 ;
            while(tempx != endx && tempy != endy){
                Matrix[tempx][tempy]++;
                if(tempx != endx){
                    if(tempx < endx){
                        tempx++;
                    }else{
                        tempx--;
                    }
                }
                if(tempy != endy){
                    if(tempy < endy){
                        tempy++;
                    }else{
                        tempy--;
                    }
                
            }
        }
        Matrix[tempx][tempy]++;
    }
}
    int crosspoints = 0;
    cout << " MATRIX: " << endl;
    for (int ty = 0; ty < hY; ty++)
    {
        for (int tx = 0; tx < hX; tx++)
        {
           //cout << Matrix[tx][ty] << " ";
            if (Matrix[tx][ty] > 1)
            {
                crosspoints++;
            }
        }
       // cout << endl;
    }
    cout << "Crosspoints: " << crosspoints << endl;
}
int main()
{
    std::vector<string> datain; // data acceptor
    PassData(&datain);
    std::vector<Vector> vctrs; // vector carrier
    vctrs = DecodeDatatoVectors(&datain);
    datain.clear();
    // test(&vctrs);
    ArrayConstructor(&vctrs);
}