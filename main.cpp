/* 
 * File:   bishops.cpp
 * Author: Nikhil Pujari
 *
 * Created on October 24, 2013, 4:57 PM
 */

#include <iostream>
#include <vector>

using namespace std;

/* inputs:  x,y - define the house the bishop is in 
 *          max_pos - defines the size of chessboard
 *          i.e. for a 8X8 keyboard max_pos = 7, starting from zero
 * output: true if the position is vulnerable to attack from another bishop placed
 *         on the chessboard
 */
bool can_attack(int x, int y, vector< vector<int> >& chess_board, 
                           int max_pos)
{

    //Check in all four directions
    int i = x+1;
    int j = y+1;
    while (i <= max_pos && j <= max_pos) {
        if (chess_board[i][j]) {
            return true;
        } 
        i++; j++;
    }
    i = x - 1;
    j = y - 1;
    while (i >= 0 && j >= 0) {
        if (chess_board[i][j]) {
            return true;
        }
        i--; j--;
    }
    i = x - 1;
    j = y + 1;
    while (i >= 0 && j <= max_pos) {
        if (chess_board[i][j]) {
            return true;
        }
        i--; j++;
    }
    i = x + 1;
    j = y - 1;
    while (i <= max_pos && j >= 0) {
        if (chess_board[i][j]) {
            return true;
        }
        i++; j--;
    }
    return false;
}

/* inputs: n - size of chessboard (8 for a 8X8 chessboard)
 *         k - number of bishops
 * output: count - maximum number of combinations such that the bishops cant attack 
 */
void find_combinations(int n, int k, vector< vector<int> >& chess_board, int& count)
{
    if (k == 0) {
        //Either all the bishops are in place or no bishop provided
        count++;
        return;
    }
    
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if(!chess_board[x][y] && !can_attack(x, y, chess_board, n-1)) {
                //Safe position, place this bishop here
                chess_board[x][y] = 1;
                find_combinations(n, k-1, chess_board, count);
                //Done with this place, empty this place and try next spot
                chess_board[x][y] = 0;
            }
        }
    }
}

//Driving function for the recursion
int bishops(int n, int k)
{
    //n X n chessboard and k bishops
    int count = 0;
    vector< vector<int> > chessboard;
    //Initialize chessboard
    for (int i = 0; i < n; i++) {
        chessboard.push_back(vector<int>(n, 0));
    }
    find_combinations(n, k, chessboard, count);
    return count;
}

int main(int argc, char **argv)
{
    int n, k;
    cout << "Enter the size of the chessboard : " << endl;
    cin >> n;
    cout << "Enter the number of bishops: " << endl;
    cin >> k;
    int result = bishops(n,k);
    cout << "Result : " << result << endl;
    return 0;
}