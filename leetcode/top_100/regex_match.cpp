#include <iostream>
#include <vector>
using namespace std;

bool isMatch(string s, string p) {
    // 2-D matrix where dp[i] matches the ith input up to the jth patern
    // dp[0][0] = true;
    // dp[0][j] = dp[j-2], empty string can only match nothing, which is the case if we had something like p = "x*", and propagated, dp[0][0] = true, dp[0][1] = false,  dp [0][2] = true
    // dp[i][0] = false, no character can match the empty pattern
    // For the rest: if s[i] == p[j] (valid character), dp[i][j] = dp[i-1][j-1], otherwise false if (valid character)
    // If p[j] == '*' and s[i] == p[j-1], we can match nothing => dp[i][j-2] or match to dp[i-1][j], which is matching 1 or more
    // else if (p[j] == '* and s[i]!=p[j-1], we match nothing => dp[i][j-2]
    
    vector<vector<bool>> dp (s.size() + 1, vector<bool>(p.size() + 1, false));
    dp[0][0] = true;
    for (int j = 0; j < p.size(); j++)
    {
        int jj = j + 1;
        if (p[j] == '*')
            dp[0][jj] = dp[0][jj-2];
    }

    for (int i = 0; i < s.size(); i++)
    {
        int ii = i + 1;
        for (int j = 0; j < p.size(); j++)
        {
            int jj = j + 1;
            if ( (p[j] >= 'a' && p[j] <= 'z') || p[j] == '.') {
                if (s[i] == p[j] || p[j] == '.')
                    dp[ii][jj] = dp[ii-1][jj-1];
                else
                    dp[ii][jj] = false;
                                cout << dp[ii][jj] << ",";

            } else if (p[j] == '*' && (s[i] == p[j-1] || p[j-1] == '.')) {
                dp[ii][jj] = dp[ii-1][jj] || dp[ii][jj-2];
                                cout << dp[ii][jj] << ",";

            } else {
                  cout << " w : " << p[j] << " ,Changing from " << dp[ii][jj] <<" -> " << dp[ii][jj-2];
                dp[ii][jj] = dp[ii][jj-2];
                cout << "with " << dp[ii][jj] <<":";
            }
        }
        cout << endl;
    }
    return dp[s.size()][p.size()];
}

int main() {
    cout << isMatch("mi", "mis*") << endl;
}