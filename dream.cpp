// UCF HSPT Online (Dec 2022)
// C++ Solution for "Life is But a Dream"
// Solution by Chris Gittings

using namespace std;
#include <iostream>
#include <vector>

int INF = 1e9;
vector<vector<vector<int>>> dp;

// recursive dp that finds the maximum subset sum
int solve(int idx, int left, int sum, vector<int> &fireball)
{   
    // deal with base cases
    if(left == 0) return sum;
    if(idx >= fireball.size()) return -INF;
    if(dp[idx][left][sum] != -INF) return dp[idx][left][sum];

    // do not take this fireball
    dp[idx][left][sum] = solve(idx + 1, left, sum, fireball);

    // check if this fireball can be taken (no overlapping bits)
    if((sum & fireball[idx]) == 0)
    {
        dp[idx][left][sum] = max(dp[idx][left][sum], solve(idx + 1, left - 1, sum + fireball[idx], fireball));
    }

    // return the largest sum
    return dp[idx][left][sum];
}

int main()
{
    int n, k, cases;

    // take in the number of cases and loop through them
    cin >> cases;
    while(cases--)
    {
        // take in the number of fireballs and subset size
        cin >> n >> k;
        vector<int> fireball (n);

        // take in the value of each fireball
        for(int i = 0; i < n; i++)
        {
            cin >> fireball[i];
        }

        int sum = -INF;
        if(k <= 11)
        {
            // set up the dp array for the states idx, number of fireballs taken, and current sum
            dp = vector<vector<vector<int>>> (n, vector<vector<int>> (k + 1, vector<int> (1 << 11, -INF)));

            // calculate the maximum sum/bitwise OR
            sum = solve(0, k, 0, fireball);
        }

        // if the sum doesn't exist, output the given text
        if(sum == -INF)
            cout << "It do go down" << endl;
        
        // the maximum sum exists, so output it
        else
            cout << sum << endl;
    }
    
    return 0;
}
