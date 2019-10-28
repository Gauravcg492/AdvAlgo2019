#include "../include/the_messenger.hpp"
#include <vector>
#include <string>
using namespace std;


class the_messenger_implementation : public the_messenger
{
public:
    int solve(int, int, int, string);
    int f2(vector<int> &dp,int,int,int,int,string);
    int f3(vector<int> &dp,int,int,int,int,string);
    int min(int,int);
};

int the_messenger_implementation::solve(int x,int y,int l, string m)
{
    vector<int> dp(l+1,0);
    int i = 1;
    dp[1] = f2(dp,x,y,l,i,m) + x;
    return dp[1];
}

int the_messenger_implementation::min(int x,int y)
{
    return x<=y?x:y;
}

int the_messenger_implementation::f2(vector<int> &dp,int x,int y,int l,int i, string m)
{
    if(i == l)
    {
        return 0;
    }
    int index = min((l+1) - (l-i),l);
    if(dp[index] == 0)
    {
        string s = m;
        s.erase(i);
        if(s.find(m[i]) == string::npos)
        {  
            if(index == l)
            {
                dp[index] = x;
                return dp[index];
            }      
            dp[index] = f2(dp,x,y,l,i+1,m) + x;
        }
        else
        {
            dp[index] = f3(dp,x,y,l,i,m);
        }
        
    }
    return dp[index];  
}

int the_messenger_implementation::f3(vector<int> &dp,int x,int y,int l,int i, string m)
{
    int index = min((l+1) - (l-i),l);
    if(dp[index] == 0)
    {
        if(index == l)
        {
            dp[index] = min(x,y);
            return dp[index];
        }
        int r1 = f2(dp,x,y,l,i+1,m) + x;
        int r2;
        int j = min(i + i - 1,l-1);
        string s = m;
        s.erase(i);
        while(j >= i)
        {
            string f = m;
            if(l != j+1)
            {
                f.erase(j+1);
            }
            f.erase(0,i);
            if(s.find(f) != string::npos)
            {
                r2 = f2(dp,x,y,l,j+1,m) + y;
                break;
            }
            j--;
        }
        dp[index] = min(r1,r2);
    }
    return dp[index];
}