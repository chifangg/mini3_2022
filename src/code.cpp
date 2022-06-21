#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <set>
#include <utility>
#include <limits.h>
using namespace std;
int nowmap[16][16];


int my_score[]
{
    10000000,   //ooooo
    1000000,    //活四
    10000,        //死四
    10000,     //活三
    100,        //死三
    100,        //活二
    10,         //死二
    1,          //活一
    0,          //死一
    0
};

//int ai_score[]
//{
//    1000000,   //xxxxx
//    100000,    //活四
//    1000,        //死四
//    10000,     //活三
//    100,        //死三
//    100,        //活二
//    10,         //死二
//    5,          //一
//};



enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

int player;
//player = 1;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;



struct node
{
    int Board[SIZE][SIZE];
    node()
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                Board[i][j] = nowmap[i][j];
            }
        }
    }
    node(const node& n)
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                Board[i][j] = n.Board[i][j];
            }
        }
    }
//    node()
//    {
//
//    }
//
};
int alphabeta(node now, int depth, int alpha, int beta, bool maximizingPlayer);
void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> nowmap[i][j];
        }
    }
}

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x, y;
    // Keep updating the output until getting killed.
        // Choose a random spot.
//        int x = (rand() % SIZE);
//        int y = (rand() % SIZE);
        int value = -1000000000;
        node n;
        int count = 0;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                if(n.Board[i][j]==0)
                {
                    count++;
                    node newnode;
                    newnode.Board[i][j]=player;
                    int ab = alphabeta(newnode, 0, -INT_MAX, INT_MAX, false); //!!!!!
                    //x y
                    // cout << "ab" << ab << "ij" << i << j << endl;
                    cout << "{" << i <<", "<< j <<"} = "<< ab << "\n";
                    
                    // value = max(value, ab);
                
                    if(value<ab){ //!!!!!!!!!!!!!!!!!!!!!!!
                        value = ab;
                        x=i, y=j;
                    }
                }
            }
        }
        if(count == 225)
        {
            x = 7;
            y = 7;
        }
        else if(count == 224)
        {
            x = 6;
            y = 9;
        }
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
}


//bool checkneighbor(std::array<std::array<int, SIZE>, SIZE> boardnow, int i, int j)
//{
//    if(i>0 && i<14)
//    {
//        if(j>0 && j<14)
//        {
//            return boardnow[i-1][j-1]>0 || boardnow[i-1][j]>0 || boardnow[i-1][j+1]>0 || boardnow[i][j-1]>0 || boardnow[i][j+1]>0 || boardnow[i+1][j-1]>0 || boardnow[i+1][j]>0 || boardnow[i+1][j+1]>0;
//        }
//        else if(j==0)
//        {
//            return boardnow[i-1][j]>0 || boardnow[i-1][j+1]>0 || boardnow[i][j+1]>0 || boardnow[i+1][j]>0 || boardnow[i+1][j+1]>0;
//        }
//        else
//        {
//            return boardnow[i-1][j]>0 || boardnow[i-1][j-1]>0 || boardnow[i][j-1]>0 || boardnow[i+1][j]>0 || boardnow[i+1][j-1]>0;
//        }
//    }
//    else if(i == 0)
//    {
//                if(j>0 && j<14)
//                {
//                    return boardnow[i][j-1]>0 || boardnow[i][j+1]>0 || boardnow[i+1][j-1]>0 || boardnow[i+1][j]>0 || boardnow[i][j+1]>0;
//                }
//                else if(j==0)
//                {
//                    return boardnow[i+1][j]>0 || boardnow[i][j+1]>0 || boardnow[i+1][j+1]>0;
//                }
//                else
//                {
//                    return boardnow[i+1][j]>0 || boardnow[i][j-1]>0 || boardnow[i+1][j-1]>0;
//                }
//        }
//    else
//        {
//                if(j>0 && j<14)
//                {
//                    return boardnow[i][j-1]>0 || boardnow[i-1][j-1]>0 || boardnow[i-1][j]>0 || boardnow[i-1][j+1]>0 || boardnow[i][j+1]>0;
//                }
//                else if(j==0)
//                {
//                    return boardnow[i-1][j]>0 || boardnow[i-1][j+1]>0 || boardnow[i][j+1]>0;
//                }
//                else{
//                    return boardnow[i][j-1]>0 || boardnow[i-1][j-1]>0 || boardnow[i-1][j]>0;
//                }
//            }
//}

//set<Point> possibleMoves;
//{
//        for(int i=0; i<15; i++)
//        {
//            for(int j=0; j<15; j++)
//            {
//                if(board[i][j]>0) continue;
//                if(checkneighbor(board, i, j))
//                {
//                    possibleMoves.insert(Point(i,j));
//                }
//            }
//        }
//        return possibleMoves;
//}

int count_lines_vertical(node n, int player)
{
    int count = 0;
    bool right = true;
    bool left = true;
    int score = 0;
    //player = 1;
    //node n;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {

            if(n.Board[i][j] == player)
            {
                count = 1;
                if(j == 0 || n.Board[i][j-1] == 3-player) left = false;
                //if(j == 14 || nowmap[i][j+1] == 3-player) right = false;
                while(count <= 5)
                {
                    if(n.Board[i][j+1] == player && j+1 != 14)
                    {
                        count++;
                        j++;
                    }
                    else if(n.Board[i][j+1] == player && j+1 == 14)
                    {
                        count++;
                        right = false;
                        break;
                        //j++;
                    }
                    else if(n.Board[i][j+1] == 3-player)
                    {
                        right = false;
                        break;
                    }
                    else break;
                }
                
            
            if(count == 5)
            {
                score += my_score[0];
            }
            else if(count == 4)
            {
                if(right == false && left == false) score += my_score[9];
                else if(right == false || left == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(right == false && left == false) score += my_score[9];
                else if(right == false || left == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(right == false && left == false) score += my_score[9];
                else if(right == false || left == false)
                {
                    //cout << "hi1" << endl;
                    score += my_score[6];
                }
                else
                {
//                    cout << i<<j << endl;
                    score += my_score[5];
                }
            }
            else if(count == 1)
            {
                if(right == false && left == false) score += my_score[9];
                else if(right == false || left == false)
                {
                    score += my_score[8];
                }
                else
                {
//                    cout << i<<j << endl;
                    score += my_score[7];
                }
            }
                
        }
//        cout << score << endl;
//        cout << "count" << count << endl;
        count = 0;
        right = true;
        left = true;
    }
//    cout << score << endl;
}
return score;
}

    
    
    
int count_lines_horizontal(node n, int player)
{
    int count = 0;
    bool up = true;
    bool down = true;
    int score = 0;
    //player = 1;
    //node n;
    for(int j = 0; j < 15; j++)
    {
        for(int i = 0; i < 15; i++)
        {
            if(n.Board[i][j] == player)
            {
                count = 1;
                if(j == 0 || n.Board[j-1][j] == 3-player) up = false;
//                if(i == 14 || nowmap[i+1][j] == 3-player) down = false;
                while(count <= 5)
                {
                    if(n.Board[i+1][j] == player && i+1 != 14)
                    {
                        count++;
                        i++;
                    }
                    else if(n.Board[i+1][j] == player && i+1 == 14)
                    {
                        count++;
                        down = false;
                        break;
                        //j++;
                    }
                    else if(n.Board[i+1][j] == 3-player)
                    {
                        down = false;
                        break;
                    }
                    else break;
                }
                
            
            if(count == 5)
            {
                score += my_score[0];
            }
            else if(count == 4)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    //cout << "hi" << endl;
                    score += my_score[6];
                }
                else score += my_score[5];
            }
            else if(count == 1)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[8];
                }
                else
                {
//                    cout << i<<j << endl;
                    score += my_score[7];
                }
            }
//            count = 0;
        }
//        cout << "count" << count << endl;
        count = 0;
        up = true;
        down = true;
    }
//    cout << score << endl;
    
}
return score;
}
    
    
int count_left_slash(node n, int player)
{
        int count = 0;
        bool down = true;
        bool up = true;
        int score = 0;
        
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; i-j >= 0 && j < 15; j++)
            {
                if(nowmap[j][i-j] == player)
                {
                    up = true;
                    down = true;
                    count = 1;
                    if(j == 0 || nowmap[j-1][i-j+1] == 3-player) up = false;
                    while(1)
                    {
                        if(j < 14 && i-j >0)
                        {
                            if(nowmap[j+1][i-j-1] == player)
                            {
                                j++;
                                count++;
                            }
                            else
                            {
                                down = (nowmap[j+1][i-j-1] == 0? true:false);
                                break;
                            }
                        }
                        else
                        {
                            down = false;
                            break;
                        }
                    }
                
                if(count == 5)
         {
             score += my_score[0];
         }
            
            else if(count == 4)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    //cout << "hi" << endl;
                    score += my_score[6];
                }
                else score += my_score[5];
            }
            else if(count == 1)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[8];
                }
                else
                {
                    score += my_score[7];
                }
            }
            
        }
    }
}
        
//        up = true;
//        down = true;
//        count = 1;
    //node n;
        for(int i = 1; i < 15; i++)
        {
            for(int k = 0; k+i<15 && 14-k >= 0; k++)
            {
                if(n.Board[k+i][14-k] == player)
                {
                    up = true;
                    down = true;
                    count = 1;
                    if(k == 0 || n.Board[i+k-1][15-k] == 3-player)
                    {
                        up = false;
                    }
                    while(1)
                    {
                        if(i+k+1 < 15 && (14-k) >= 0)
                        {
                            if(n.Board[i+k+1][14-k] == player)
                            {
                                k++;
                                count++;
                            }
                            else
                            {
                                down = (n.Board[k+1+i][14-k] == 0? true:false);
                                break;
                            }
                        }
                        else
                        {
                            down = false;
                            break;
                        }
                    }
                
                if(count == 5)
         {
             score += my_score[0];
         }
            
            else if(count == 4)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    //cout << "hi" << endl;
                    score += my_score[6];
                }
                else score += my_score[5];
            }
            else if(count == 1)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[8];
                }
                else
                {
                    score += my_score[7];
                }
            }
            
            }
        }
    }
        return score;
}
    
    int count_right_slash(node n, int player)
    {
        int count = 0;
        bool down = true;
        bool up = true;
        int score = 0;
        
        //node n;
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; i+j < 15; j++)
            {
                if(n.Board[i+j][j] == player)
                {
                    up = true;
                    down = true;
                    count = 1;
                    if(j == 0 || n.Board[i+j-1][j-1] == 3-player) down = false;
                    while(1)
                    {
                        if(j < 14 && i+j < 14)
                        {
                            if(n.Board[i+j+1][j+1] == player)
                            {
                                j++;
                                count++;
                            }
                            else
                            {
                                up = (n.Board[i+j+1][j+1] == 0? true:false);
                                break;
                            }
                        }
                        else
                        {
                            up = false;
                            break;
                        }
                    }
                
                if(count == 5)
         {
             score += my_score[0];
         }
            
            else if(count == 4)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    //cout << "hi" << endl;
                    score += my_score[6];
                }
                else score += my_score[5];
            }
            else if(count == 1)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[8];
                }
                else
                {
                    score += my_score[7];
                }
            }
            
        }
    }
}
        
        up = true;
        down = true;
        count = 1;
        //node n;
        for(int j = 1; j < 15; j++)
        {
            for(int k = 0; k+j<15; k++)
            {
                if(n.Board[k][j+k] == player)
                {
                    up = true;
                    down = true;
                    count = 1;
                    if(k == 0 || n.Board[k-1][j+k-1] == 3-player)
                    {
                        down = false;
                    }
                    while(1)
                    {
                        if(j < 15 && j+k<14)
                        {
                            if(n.Board[k+1][j+k+1] == player)
                            {
                                k++;
                                count++;
                            }
                            else
                            {
                                up = (n.Board[k+1][j+k+1] == 0? true:false);
                                break;
                            }
                        }
                        else
                        {
                            up = false;
                            break;
                        }
                    }
                
                if(count == 5)
         {
             score += my_score[0];
         }
            
            else if(count == 4)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[2];
                }
                else score += my_score[1];
            }
            else if(count == 3)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[4];
                }
                else score += my_score[3];
            }
            else if(count == 2)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    //cout << "hi" << endl;
                    score += my_score[6];
                }
                else score += my_score[5];
            }
            else if(count == 1)
            {
                if(up == false && down == false) score += my_score[9];
                else if(up == false || down == false)
                {
                    score += my_score[8];
                }
                else
                {
                    score += my_score[7];
                }
            }
            
            }
        }
    }
        return score;
}
    
    
    
    
int finalscore = 0;
int add_all(node n, int player)
{
    finalscore = count_right_slash(n, player) + count_left_slash(n, player) + count_lines_vertical(n, player) + count_lines_horizontal(n, player);
    return finalscore;
}
    

    

//    for(int i = 0; i < 15; i++)
//    {
//        for(int j = 0; j < 15; j++)
//        {
//            nowmap[i][j] = 0;
//        }
//    }
//    nowmap[7][7] = 1;
//    nowmap[8][7] = 1;
//    nowmap[7][8] = 1;
//    nowmap[7][9] = 1;
//    nowmap[9][7] = 1;
////    nowmap[0][0] = 1;
//    nowmap[1][0] = 1;
//    for(int i = 0; i < 15; i++)
//    {
//        for(int j = 0; j < 15; j++)
//        {
//            cout << nowmap[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << count_lines_vertical() << endl;
//    cout << count_lines_horizontal() << endl;
//    cout << count_right_slash() << endl;
//    cout << count_left_slash() << endl;




int alphabeta(node now, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if(depth == 0)
    {
        return add_all(now, player) - add_all(now, 3-player);
    }
    if(maximizingPlayer)
    {
        int value = -1000000000;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                if(now.Board[i][j]==0)
                {
                    node newnode(now);
                    newnode.Board[i][j]=player;
                    int ab = alphabeta(newnode, depth-1, alpha, beta, !maximizingPlayer);
                    //x y
                    value = max(value, ab);
                    alpha = max(alpha, value);
                    if(alpha >= beta) break;
                }
            }
        }
        return value;
    }
        
    else
    {
        int value = 1000000000;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                if(now.Board[i][j]==0)
                {
                    node newnode(now);
                    newnode.Board[i][j]=3-player;
                    int ab = alphabeta(newnode, depth-1, alpha, beta, !maximizingPlayer);
                    //x y
                    value = min(value, ab);
                    beta = min(beta, value);
                    if(beta <= alpha) break;
                }
            }
        }
        return value;
    }
}

int main(int, char** argv)
{
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
