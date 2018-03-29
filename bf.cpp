#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;


int INF= std::numeric_limits<int>::max();

int vertices;
int edges;


std::vector<int> dist;
std::vector<bool> visited;
std::vector<int> pi;

std::vector<string> edgeLists;

std::vector<std::vector<int>> adjacencyMatrix;

void INITIALIZE()
{
    for(int i=0;i<vertices;i++)
	dist.push_back(INF), visited.push_back(false),pi.push_back(-1);
}

void RELAX(int u, int v, int w)
{
  if((dist[v]> dist[u] + w) && (dist[u]!=INF))
    {
      dist[v] = dist[u] + w;
      pi[v]=u;
    }
}

bool bellmanFord(int src)
{
  INITIALIZE();
  dist[src]=0;
  string line;
  string token;
  int sdc[3];
  int r=0;
  //for V-1 times
  for(int i=1;i<=vertices-1;i++)
    {
      //for all edges in the graph
      for(int j=0;j<edges;j++)
	{
	  istringstream iss(edgeLists[j+2]);
	  while(getline(iss,token,' '))
	    sdc[r]=stoi(token),r++;
	  RELAX(sdc[0],sdc[1],sdc[2]);
	  r=0;
	}
    }
  //Detect negative weighted cycle
  for(int i=0;i<edges;i++)
    {
      istringstream iss(edgeLists[i+2]);
      while(getline(iss,token,' '))
	  sdc[r]=stoi(token),r++;
      r=0;
      if((dist[sdc[1]] > dist[sdc[0]] + sdc[2]) && (dist[0]!=INF))
	return false;
    }
  return true;
}

void print_result()
{
  cout<<" To      Distance"<<endl<<"-----------------"<<endl;
  for(int i=0;i<vertices;i++)
    cout<<" "<<i<<"          "<<dist[i]<<endl;
}

int main(int argc, char * argv[])
{
  string line;
  ifstream myfile(argv[1]);
  if(myfile.is_open())
    {
      cout<<"Reading graph from the file..."<<endl;
      while(getline(myfile,line))
	edgeLists.push_back(line);
      cout<<"Done reading"<<endl<<"Adjacency Matrix of the graph is"<<endl;
      vertices=stoi(edgeLists[0]);
      edges=stoi(edgeLists[1]);
      for(int i=0;i<vertices;i++)
	{
	  adjacencyMatrix.push_back(std::vector<int>());
	  for(int j=0;j<vertices;j++)
	    adjacencyMatrix[i].push_back(0);
	}
      int sdc[3];
      int r=0;
      string token;
      for(int i=2;i<edgeLists.size();i++)
	{
	  istringstream iss(edgeLists[i]);
	  while(getline(iss,token,' '))
	    {
	      sdc[r]=stoi(token);
	      r++;
	    }
	  r=0;
	  adjacencyMatrix[sdc[0]][sdc[1]]=sdc[2];
	}
      for(int i=0;i<vertices;i++)
	{
	  for(int j=0;j<vertices;j++)
	    {
	      cout<<adjacencyMatrix[i][j]<<" ";
	    }
	  cout<<endl;
	}

      cout<<"Enter the source vertex"<<endl;
      int src;
      cin>>src;
      bool res=bellmanFord(src);
      if(res==false)
	cout<<"Graph contains negative weighted cycle. SSP cannot be obtained"<<endl;
      else
	{
	  cout<<"Calculated Min distance from source vertex "<<src<<" is "<<endl;
	  print_result();
	}
      myfile.close();
    }
  else
    cout<<"Input file does not exists"<<endl;
  return 0;
}
