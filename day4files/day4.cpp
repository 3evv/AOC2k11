
#include <bitset>
#include <fstream>
#include <iostream>
//#include <map>
#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
std::vector<string> command;
string numbers;
std::vector<string> scores;
std::vector<vector<vector<int>>> board; //(1, vector< vector<int> > (5, vector<int>(5)));
        class Winno {
            public:
            int moves = 999;
            int boardnumber = 0;
            int sum = 0;
            int maxmoves = 0;
            int losingboard = 0;
            int losingsum = 0;
        };
// initialize :

void PassData()
{
    ifstream data("data.txt");
    if (data.is_open())
    {
        string line;
        while (getline(data, line))
        {
            command.push_back(line);
        }
        data.close();
    }
    else
        cout << "broke";
}
void DecodeData()
{
    int dlength = command.size();
    if (true) 
    {         
        {
            numbers = command.at(0); 

        }
        cout << "done with scores" << endl;
    }

    
    int n = 1; // number of the bingo board
    for (int i = 1; i < dlength; ++i)
    { // creates matrices of bingo data boards
        string line = command.at(i);
        if (line.size() == 0)
        {
            line.clear();
            
            //cout << " line skipped" << n << endl;
        }
        else
        {   board.push_back(vector<vector<int>>());
            // cout << "t1" << endl;
             int y = 0;
             int x = 0;
            while(y < 5){ 
                line = command.at(i);     
                //cout << "t2" << endl;
                board.at(n).push_back(vector<int>(5));
                while(line.size() > 0)
                {
                    string tmp = line.substr(0, 2);
                    tmp = tmp.substr(tmp.find_first_not_of(" "));
                    board.at(n).at(y).at(x)=(stoi(tmp));
                    if (line.size() >= 3)
                    {
                        line = line.substr(3);
                    }
                    else
                    {
                        line.clear();
                    }
                    // cout << x << " y " << y << " n: " << n << endl;
                     x++;
                }
               // cout << "y2:" << y << endl;
                x = 0;
                y++;
                i++;
            }
            n++;
        }
    }
    cout << "done with boards" << endl;
    // while(true);
}
int calculateScore(int boardnumber, int moves, int sum){
// calculate score
    int storage[25];
    for(int i = 0; i < 25; i++){         //reassign board to a one dimensional array
        for(int y = 0; y < 5;y++){
            for(int x = 0; x < 5; x++){
                storage[i] = board.at(boardnumber).at(y).at(x);
                //cout << storage[i] << " " << endl;
                i++;
            }
        }
    }   
        
        for(int i = 0; i < 25; i++){ //overwrite chosen numbers with 0
        if(numbers.find(","+to_string(storage[i])+",") < moves){
           // cout << storage [i] << " " << numbers.find(to_string(storage[i]));
            storage[i] = 0;
        }
       // cout << endl;
        }   
           for(int i = 0; i < 25; i++){  //sum up
            //cout << storage[i] << endl;
            sum = storage[i] + sum;
        }
        //cout << "SUM: " << sum << endl;
        return sum;
}
void findMovestowin()
{   Winno winner;
    // for (int y = 0; y < 5; y++){
        
    //         for (int x = 0; x < 5; x++){
    //             int nmb = board.at(1).at(y).at(x);
    //             cout << "tst " << nmb << "pos " << numbers.find(to_string(nmb)) << endl;
    //         }
    // }
//cout << board.size() << endl;
    for(int n = 1; n < board.size(); n++){    //select board, respect vector size
        int win[2][5];
        if(1){
        int y = 0;
        while(y < 5){// moves to win x
        int x = 0;
        int moves = 0;
        while(x < 5){
        int tmp = numbers.find(to_string(board.at(n).at(y).at(x)));
        //cout << tmp << endl;
        if(moves < tmp){
            moves = tmp;
        } 
        x++;
        }
        win[1][y] = moves;
        y++;
        //cout << "mov " << moves << " " << y << endl; //<< n << y << x << endl;
        }
        }
    //moves to win y
    if(1){
        int x = 0;
        while(x < 5){// moves to win y
        int y = 0;
        int moves = 0;
        while(y < 5){
        int tmp = numbers.find(to_string(board.at(n).at(y).at(x)));
        //cout << tmp << endl;
        if(moves < tmp){
            moves = tmp;
        } 
        y++;
        }
        win[2][x] = moves;
        x++;
        //cout << "mov " << moves << " " << y << endl; //<< n << y << x << endl;
        }
        }
    // compare x to y 
    int minx = numbers.size()+1;
    int miny = numbers.size()+1;
    for(int x = 0; x < 5;x++){
        if(minx > win[1][x]){
            minx = win[1][x];
        }
        if(miny > win[2][x]){
            miny = win[2][x];
        }
    }
    //cout << minx << " " << miny << endl;
    int tmp = 999;
    int tmp2 = 0;
    if(minx < miny){
        tmp = minx;
    } else {
        tmp = miny;
    }
      if(minx > miny){
        tmp2 = minx;
    } else {
        tmp2 = miny;
    }
    if(tmp < winner.moves){   //winner
        winner.moves = tmp;
        winner.boardnumber = n;
    }
        if(tmp2 > winner.maxmoves){ //loser
        winner.maxmoves = tmp;
        winner.losingboard = n;
    }

    
    }
    cout << winner.boardnumber << " w: " << winner.moves << endl; // declare winning board && moves
    cout << winner.losingboard << " l: " << winner.maxmoves << endl; // declare loser
    //mulitypluy + return. the end
    int winningnumber = stoi(numbers.substr(winner.moves, numbers.find(",", winner.moves)));
    int losernumber = stoi(numbers.substr(winner.maxmoves, numbers.find(",", winner.maxmoves)));
    cout << winningnumber << " " << calculateScore(winner.boardnumber, winner.moves,winner.sum) * winningnumber << endl;
    cout << losernumber << " " << calculateScore(winner.losingboard, winner.maxmoves,winner.losingsum) * losernumber << endl;
    while(true);
}

void printResults()
{
    cout << "result" << endl;
    for (auto vec_parent : board)
    {
        for (auto vec : vec_parent)
        {
            int x = 0;
            for (auto val : vec)
            {
                cout << val << " ";
                if (x == 4)
                {
                    cout << endl;
                    x = 0;
                }
                else
                {
                    x++;
                }
            }
            // cout << endl;
        }
        cout << endl;
    }
}
int main()
{
    board.push_back(std::vector<std::vector<int>>()); // initialize vector
    board.at(0).push_back(std::vector<int>());
    PassData();
    //    for (auto v : command) {cout << v << endl;}
    DecodeData();
    //printResults();
    findMovestowin();
    return 0;
}
