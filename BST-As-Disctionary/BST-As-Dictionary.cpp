#include <iostream>
#include<bits/stdc++.h>
using namespace std;
//Global dp matrix for storing cost and root of subtrees
vector<vector<pair<int,int>>> dp;
//Node for tree
struct  Node{
    int key;
    string word;
    Node *left,*right;
};

Node *CreateNode(int key,vector<pair<string,int>> v)
{
  Node *node = (Node*)malloc(sizeof(Node));
  node->key = key;
  node->word = v[key].first;
  node->left = nullptr;
  node->right = nullptr;
  return node;
}
//Building the tree using the dp matrix
Node* MakeTree(int curr,int l,int h,vector<pair<string,int>> v)
{
  cout<<v[curr].first<<" ";
  Node *newNode = CreateNode(curr,v);
  if(curr > l)
  {
    newNode->left = MakeTree(dp[l][curr-1].second,l,curr-1,v);
  }
  if(curr < h)
  {
    newNode->right = MakeTree(dp[curr+1][h].second,curr+1,h,v);
  }
  return newNode;
}

//Utility function for calculating sum of costs of all nodes once irrespective of what root is and at which level the node is.
int Total(vector<pair<string,int>> v,int i,int j)
{
  int sum=0;
  for(int k=i;k<=j;k++)
  {
    sum+=v[k].second;
  }
  return sum;
}
//Function for finding out optimal cost of the tree and the root of subtrees using this we can build the optimal tree.
Node* buildOptimalTree(vector<pair<string,int>> v,int n)
{
  int i,j,k,l,b;
  for(i=0;i<n;i++)
  {
    dp[i][i].first = v[i].second;
    dp[i][i].second = i;
  }
  for(l=2;l<=n;l++)
  {
    for(i=0;i<n-l+1;i++)
    {
      j = i+l-1;
      k = Total(v,i,j);
      dp[i][j].first = INT_MAX;
      for(b=i;b<=j;b++)
      {
        int cost = k;
        if(b>i)
          cost+=dp[i][b-1].first;
        else
          cost+=0;
        if(b<j)
          cost+=dp[b+1][j].first;
        else
          cost+=0;
        if(cost < dp[i][j].first)
        {
          dp[i][j].first = cost;
          dp[i][j].second = b;
        }
      }
    }
  }

  cout<<" Root :"<<dp[0][n-1].second<<" "<<"Total Cost : "<<dp[0][n-1].first<<endl;
  cout<<"Pre-order traversal of tree is : ";
 Node *head = MakeTree(dp[0][n-1].second,0,n-1,v);
 cout<<endl;
  return head;
}

//Searching the word in the root and giving at which level it was found
void Search(Node *root,Node **temp,int key,int level,int &finalLevel)
{
  if(!root)
    return;
  if(root->key == key)
  {
    finalLevel = level;
    *temp = root;
    return;
  }
  if(root->key > key)
  {
    Search(root->left,temp,key,level+1,finalLevel);
  }
  else
  {
    Search(root->right,temp,key,level+1,finalLevel);
  }
}


int main() {
  int n,i,key=-1;
  vector<pair<string,int>> v;
  map<string,int> mp;
  ifstream fin;
  string str;
  fin.open("input.txt");
  while(fin)
  {
    string line;
    getline(fin,line);
    stringstream ss(line);
    while(ss>>str)
    {
      mp[str]++;
    }
  }
  string find = str;
  mp[find]--;
  for(auto itr=mp.begin();itr!=mp.end();itr++)
  {
    v.push_back({itr->first,itr->second});
  }
  sort(v.begin(),v.end());
  n = v.size();
  for(i=0;i<n;i++)
  {
    cout<<v[i].first<<" "<<v[i].second<<endl;
    if(v[i].first == find)
    {
      key = i;
    }
  }
  dp.resize(n,vector<pair<int,int>>(n));
  Node *root = buildOptimalTree(v,n);
  int finalLevel = -1;
  Node *temp = nullptr;
  if(key!=-1) {
    Search(root, &temp, key, 0, finalLevel);
    if (temp) {
      cout << "Word is " << temp->word << " Found at level " << finalLevel << endl;
    }
  }
  else
  {
    cout<<"Word not found"<<endl;
  }
  return 0;
}
