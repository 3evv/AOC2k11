#include <fstream>   // file input
#include <iostream>  // file input
using namespace std; // iostream avoiding going std:: since no other namespace is used at present.
#include <algorithm>
#include <stdio.h> // streams. datastreams.
#include <string>  //stings
#include <vector>
#include <time.h>
#include <cmath>                           // power functions
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
string FindNumber(string target, int size)
{
    for (int i = 0; i < 10; i++)
    {
        string tmp = target.substr(0, target.find(" "));
        if (tmp.size() == size)
        {
            return tmp;
        }
        target = target.substr(target.find(" ") + 1);
    }
}

char Findupperright(string target, string ONE)
{
    for (int i = 0; i < 10; i++)
    {
        string dsp = "abcdefg";
        string tmp = target.substr(0, target.find(" "));
        // cout << tmp.size() << endl;
        if (tmp.size() == 6)
        { // cout << dsp << endl;
            if (tmp.find(ONE[0]) == -1 || tmp.find(ONE[1]) == -1)
            {
                for (int z = 6; z >= 0; z--)
                {
                    if (tmp.find(dsp[z]) == -1)
                    {
                        // cout << dsp[z] << endl;
                        return dsp[z];
                    }
                }
            }
        }
        target = target.substr(target.find(" ") + 1);
    }
}

long DecodeNbrs(std::vector<string> *datain)
{
    long csum = 0;
    for (int i = 0; i < datain->size(); i++)
    {
        int sum = 0;
        string temp = datain->at(i);
        string tnumber = temp.substr(temp.find("|") + 2);
        string unique = temp.substr(0, temp.find("|"));
        string ONE = FindNumber(unique, 2);
        string FOUR = FindNumber(unique, 4);
        char UR = Findupperright(unique, ONE);
        for (int z = 4; z != 0; z--)
        {
            string tmp = tnumber.substr(0, tnumber.find(" "));
            int number = -1;
            switch (tmp.size())
            {
            case 2: // 1
                number = 1;
                break;
            case 4: // 4
                number = 4;
                break;
            case 5: // 5 2 3
                if (tmp.find(ONE[0]) == -1 || tmp.find(ONE[1]) == -1)
                {
                    if (tmp.find(UR) == -1)
                    {
                        number = 5;
                    }
                    else
                    {
                        number = 2;
                    }
                }
                else
                {
                    number = 3;
                }
                break;
            case 6: // 0 9 6
                if (tmp.find(ONE[0]) != -1 && tmp.find(ONE[1]) != -1)
                {
                    if (tmp.find(FOUR[0]) == -1 || tmp.find(FOUR[1]) == -1 || tmp.find(FOUR[2]) == -1 || tmp.find(FOUR[3]) == -1)
                    {
                        number = 0;
                    }
                    else
                    {
                        number = 9;
                    }
                }
                else
                {
                    number = 6;
                }
                break;
            case 3: // 7
                number = 7;
                break;
            case 7: // 8
                number = 8;
                break;
            }
            tnumber = tnumber.substr(tnumber.find(" ") + 1);
            sum += number * pow(10, z - 1); // cout << number << endl;
        }
        //cout << sum << endl;
        csum += sum;
    }
    return csum;
}
int main()
{   clock_t start_time = clock();
    std::vector<string> data;
    PassData(&data);
    cout << DecodeNbrs(&data) << endl;
    cout << "Elapsed time: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << "s" << endl;
    
}

/*
    1 -       3        6
    2 - 1,    3, 4, 5,    7
    3 - 1,    3, 4,    6, 7
    4 - 2,    3, 4,    6
 v  5 - 1, 2,    4,    6, 7  not equal to 1, 6 has 1 char more.
 v  6 - 1, 2,    4, 5, 6, 7
    7 - 1,    3,       6
    8 - 1, 2, 3, 4, 5, 6, 7
    9 - 1, 2, 3, 4, 6,    7
    Scroll through, find unique displays/numbers
    Find remaining and discriminate among them using data gathered in step 1
    print result

    2 - 1,    3, 4, 5,    7
    5 - 1, 2,    4,    6, 7

    need to discriminate between 2 and 5?
    soo decode all others and base it on 6 ?
*/