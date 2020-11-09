#include<bits/stdc++.h>
using namespace std;

//Substitution matrix cost for replacements for alphabets
int subs[26][26] = {{0,0,7,1,342,0,0,2,118,0,1,0,0,3,76,0,0,1,35,9,9,0,1,0,5,0},
                    {0,0,9,9,2,2,3,1,0,0,0,5,11,5,0,10,0,0,2,1,0,0,8,0,0,0},
                    {6,5,0,16,0,9,5,0,0,0,1,0,7,9,1,10,2,5,39,40,1,3,7,1,1,0},
                    {1,10,13,0,12,0,5,5,0,0,2,3,7,3,0,1,0,43,30,22,0,0,4,0,2,0},
                    {388,0,3,11,0,2,2,0,89,0,0,3,0,5,93,0,0,14,12,6,15,0,1,0,18,0},
                    {0,15,0,3,1,0,5,2,0,0,0,3,4,1,0,0,0,6,4,12,0,0,2,0,0,0},
                    {4,1,11,11,9,2,0,0,0,1,1,3,0,0,2,1,3,5,13,21,0,0,1,0,3,0},
                    {1,8,0,3,0,0,0,0,0,0,2,0,12,14,2,3,0,3,1,11,0,0,2,0,0,0},
                    {103,0,0,0,146,0,1,0,0,0,0,6,0,0,49,0,0,0,2,1,47,0,2,1,15,0},
                    {0,1,1,9,0,0,1,0,0,0,0,2,1,0,0,0,0,0,5,0,0,0,0,0,0,0},
                    {1,2,8,4,1,1,2,5,0,0,0,0,5,0,2,0,0,0,6,0,0,0,4,0,0,3},
                    {2,10,1,4,0,4,5,6,13,0,1,0,0,14,2,5,0,11,10,2,0,0,0,0,0,0},
                    {1,3,7,8,0,2,0,6,0,0,4,4,0,180,0,6,0,0,9,15,13,3,2,2,3,0},
                    {2,7,6,5,3,0,1,19,1,0,4,35,78,0,0,7,0,28,5,7,0,0,1,2,0,2},
                    {91,1,1,3,116,0,0,0,25,0,2,0,0,0,0,14,0,2,4,14,39,0,0,0,18,0},
                    {0,11,1,2,0,6,5,0,2,9,0,2,7,6,15,0,0,1,3,6,0,4,1,0,0,0},
                    {0,0,1,0,0,0,27,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,14,0,30,12,2,2,8,2,0,5,8,4,20,1,14,0,0,12,22,4,0,0,1,0,0},
                    {11,8,27,33,35,4,0,1,0,1,0,27,0,6,1,7,0,14,0,15,0,0,5,3,20,1},
                    {3,4,9,42,7,5,19,5,0,1,0,14,9,5,5,6,0,11,37,0,0,2,19,0,7,6},
                    {20,0,0,0,44,0,0,0,64,0,0,0,0,2,43,0,0,4,0,0,0,0,2,0,8,0},
                    {0,0,7,0,0,3,0,0,0,0,0,1,0,0,1,0,0,0,8,3,0,0,0,0,0,0},
                    {2,2,1,0,1,0,0,2,0,0,1,0,0,0,0,7,0,6,3,3,1,0,0,0,0,0},
                    {0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
                    {0,0,2,0,15,0,1,7,15,0,0,0,2,0,6,1,0,7,36,8,5,0,0,1,0,0},
                    {0,0,0,7,0,0,0,0,0,0,0,7,5,0,0,0,0,2,21,3,0,0,0,0,3,0}};

//This algorithm finds the minimum cost for converting an incorrect word to correct word.

int EditDistance(string input1,string input2,int n,int m,vector<vector<int>> &dp)
{
  int i,j;
  for(i=0;i<=n;i++)
    dp[i][0]=i;
  for(j=0;j<=m;j++)
    dp[0][j]=j;
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=m;j++)
    {
        if(input1[i-1]==input2[j-1])
        {
          dp[i][j] = dp[i-1][j-1];
        }
        else
        {
          dp[i][j] = min(dp[i-1][j-1]+subs[input1[i-1]-'a'][input2[j-1]-'a'],min(dp[i-1][j]+1,dp[i][j-1]+1));
        }
    }
  }
  return dp[n][m];
}

//Backtracking the dp matrix for finding insertions, deletions and replacements.

void FindChanges(string input1,string input2,int n,int m,vector<vector<int>> &dp)
{
  int i,j;
  i = n;
  j = m;
  while(i > 0 || j > 0)
  {
    if(i!=0 && dp[i][j] == dp[i-1][j] + 1)
    {
      cout<<"Delete "<<input1[i-1]<<": Cost is "<<"1"<<endl;
      i--;
    }
    else if(j!=0 && dp[i][j] == dp[i][j-1] + 1)
    {
      cout<<"Insert "<<input2[j-1]<<": Cost is "<<"1"<<endl;
      j--;
    }
    else if(i!=0 && j!=0 && input1[i-1] == input2[j-1])
    {
      i--;
      j--;
    }
    else if(i!=0 && j!=0 && dp[i][j] == dp[i - 1][j - 1] + subs[input1[i-1]-'a'][input2[j-1]-'a'])
    {
      cout<<"Replace "<<input1[i-1]<<" with "<<input2[j-1]<<": Cost is "<<subs[input1[i-1]-'a'][input2[j-1]-'a']<<endl;
      i--;
      j--;
    }
  }
}

int main()
{
  ifstream fin;
  string input1,input2;
  fin.open("Input2.txt");
    getline(fin,input1);
    getline(fin,input2);
    fin.close();
    int n = input1.size();
    int m = input2.size();
    vector<vector<int>> dp;
    dp.resize(n+1,vector<int>(m+1));
    int editDistance = EditDistance(input1,input2,n,m,dp);
    cout<<"The edit distance is "<<editDistance<<endl;
    cout<<"The changes required are  : "<<endl;
    FindChanges(input1,input2,n,m,dp);
    return 0;
}


