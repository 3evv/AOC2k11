// CPP program
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n = 4;
	int m = 5;

	/*
	Create a vector containing "n"
	vectors each of size "m".
	*/
    vector<vector<vector<int>>> board;

    for(int z = 0; z<5;++z){
        board.push_back(vector<vector<int>>());
        for(int y=0;y<5;++y){
            board.at(z).push_back(vector<int>(5));
            for(int x=0;x<5;++x){
                board.at(z).at(y).at(x) = x;
            }
        }

    
    }
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            for(int k=0;k<5;++k){
                cout<<board[i][j][k]<<' ';
            }
            cout<<endl;
        }    
        cout<<endl;
    }
    
return 0;
}
