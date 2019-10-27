#include "../include/survival_of_the_fittest.hpp"
#include <vector>
//#include <iostream>
using namespace std;


class survival_of_the_fittest_implementation : public survival_of_the_fittest
{
public:
    vector<double> solve(int, int, int);
    vector<double> memoize(vector<vector<vector<vector<double>>>> &dp,int,int,int);
};

vector<double> survival_of_the_fittest_implementation::solve(int a,int p, int k)
{
    vector<vector<vector<vector<double>>>> dp(a+1,vector<vector<vector<double>>>(p+1,vector<vector<double>>(k+1,vector<double>(3,0))));

    //base conditions
    // only one survivor
    for(int i=0;i<=a;i++)
    {
        dp[i][0][0][0] = 1;
    }

    for(int i=0;i<=p;i++)
    {
        dp[0][i][0][1] = 1;
    }

    for(int i=0;i<=k;i++)
    {
        dp[0][0][i][2] = 1;
    }
    // two surivors
    for(int i=0;i<=p;i++)
    {
        for(int j=0;j<=k;j++)
        {
            dp[0][i][j][1] = 1;
        }
    }

    for(int i=0;i<=a;i++)
    {
        for(int j=0;j<=k;j++)
        {
            dp[i][0][j][2] = 1;
        }
    }

    for(int i=0;i<=a;i++)
    {
        for(int j=0;j<=p;j++)
        {
            dp[i][j][0][0] = 1;
        }
    }

    memoize(dp,a,p,k);
    return dp[a][p][k];
}

vector<double> survival_of_the_fittest_implementation::memoize(vector<vector<vector<vector<double>>>> &dp,int a,int p, int k)
{
    vector<double> com(3,0);
    if(dp[a][p][k]==com)
    {
        //cout<<"solving for: "<<a<<" "<<p<<" "<<k;
        vector<double> f1 = memoize(dp,a-1,p,k);
        vector<double> f2 = memoize(dp,a,p-1,k);
        vector<double> f3 = memoize(dp,a,p,k-1);
        int den = (k*a) + (p*k) + (a*p);
        dp[a][p][k][0] = ((k*a*f1[0]) + (a*p*f2[0]) + (p*k*f3[0]))/den;
        dp[a][p][k][1] = ((k*a*f1[1]) + (a*p*f2[1]) + (p*k*f3[1]))/den;
        dp[a][p][k][2] = ((k*a*f1[2]) + (a*p*f2[2]) + (p*k*f3[2]))/den;
    }
    return dp[a][p][k];
}
