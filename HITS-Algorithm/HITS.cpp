#include <iostream>
#include <bits/stdc++.h>
using namespace std;
double threshold = 0.15;
vector<vector<int>> graph;
vector<vector<int>> graphTrans;
int nodes;
map<int,double> hub;
map<int,double> auth;
//Transpose of the matrix
vector<vector<int> > transpose(vector<vector<int> > b)
{
  if (b.empty())
    return b;
  vector<vector<int> > trans_vec(b[0].size(), vector<int>());
  for(auto & i : b)
  {
    for(int j = 0; j < i.size(); j++)
    {
      trans_vec[j].push_back(i[j]);
    }
  }
  return trans_vec;
}

//Multiplication of n*n graph with n*1 vector

vector<int> matrixMultiplication(vector<vector<int>> g,vector<int> u)
{
  int n = g.size(),i,j,sum;
  vector<int> v;
  for(i=0;i<n;i++)
  {
    sum=0;
    for(j=0;j<n;j++)
    {
      sum+=g[i][j]*u[j];
    }
    v.push_back(sum);
  }
  return v;
}

//ComputeHits function is a recursive function to find authority and hub scores

void computeHITS()
{
  vector<double> h(nodes),a(nodes);
  int i;
  static int j=2;
  //Taking a limit of 20 iterations
  if(j>20)
  {
    return;
  }
  else {
    double hSum = 0, aSum = 0;
    //sum of squares of authority and hub vales
    for (i = 0; i < nodes; i++) {
      hSum += (hub[i + 1] * hub[i + 1]);
      aSum += (auth[i + 1] * auth[i + 1]);
    }
    //Taking square-root
    hSum = sqrt(hSum);
    aSum = sqrt(aSum);
    cout << "For iteration " << j << " :" << endl;
    //Normalize the scores
    for (i = 0; i < nodes; i++) {
      h[i] = hub[i + 1] / hSum;
      a[i] = auth[i + 1] / aSum;
      cout << "For node " << i + 1 << ", Hub score is : " << h[i] << " Authority score is : " << a[i] << endl;
    }
    //Verifying with previous iteration if its converging and the difference is below some threshold
    int k = 0;
    for (i = 0; i < nodes; i++) {
      if ((abs(auth[i + 1] - a[i]) <= threshold) && (abs(hub[i + 1] - h[i]) <= threshold)) {
        k++;
      }
    }
    //If all the nodes converge
    if (k == nodes) {
      cout
          << "The scores for previous iteration and current iteration are approximately close, so the above scores are final and the orders are : "
          << endl;
      vector<pair<double, int>> hu, au;
      for (i = 0; i < nodes; i++) {
        hu.push_back(make_pair(h[i], i + 1));
        au.push_back(make_pair(a[i], i + 1));
      }
      sort(hu.rbegin(), hu.rend());
      sort(au.rbegin(), au.rend());
      cout << "Hub order of nodes is : ";
      for (i = 0; i < nodes; i++) {
        cout << hu[i].second << " ";
      }
      cout << endl;
      cout << "Authority order of nodes is : ";
      for (i = 0; i < nodes; i++) {
        cout << au[i].second << " ";
      }
      cout << endl;
      return;
    }
    else
    {
      //Update the hub and authority map with the latest scores
      for (i = 0; i < nodes; i++) {
        auth[i + 1] = a[i];
        hub[i + 1] = h[i];
      }
      j++;
      computeHITS();
    }
  }
}

int main() {

  //Taking input from file.
  ifstream fin;
  fin.open("input2.txt");
  int flag=0,data,i=-1;
  while(fin)
  {
    string line;
    getline(fin,line);
    stringstream ss(line);
    int j = 0;
    while(ss>>data) {
      if (flag == 0) {
        nodes = data;
        graph.resize(nodes);
        flag = 1;
      } else {
          graph[i][j++] = data;
      }
    }
    i++;
    if(i<nodes)
      graph[i].resize(nodes);
  }
  for(i=0;i<nodes;i++)
  {
    for(int j=0;j<nodes;j++)
    {
      if(graph[i][j])
        hub[i+1]++;
      if(graph[j][i])
        auth[i+1]++;
    }
  }
  graphTrans = transpose(graph);
  //Step 1 :
  vector<int> v,h;
  vector<int> u(nodes);
  //Unit vector
  for(i=0;i<nodes;i++)
  {
    u[i]=1;
  }
  //Transpose of graph multiplied with unit vector gives authority vector
  v = matrixMultiplication(graphTrans,u);
  //Authority vector multiplied with graph gives hub vector
  h = matrixMultiplication(graph,v);
  cout<<"After iteration 1 : "<<endl;
  for(i=0;i<nodes;i++)
  {
    auth[i+1] = v[i];
    hub[i+1] = h[i];
    cout<<"For node "<<i+1<<" Hub score is : "<<hub[i+1]<<" Authority score is : "<<auth[i+1]<<endl;
  }
  computeHITS();
  return 0;
}
