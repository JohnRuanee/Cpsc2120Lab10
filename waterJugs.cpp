/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state> > nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void){
  int aCap = 3;
  int bCap = 4;
  int a = 0;
  int b = 0;


  for(a = 0; a <= 3; a++){
    for(b = 0; b <= 4; b++){
      state pair = make_pair(a, b);

      //Fill A
      state temp1 = pair;

      //check if a is full
      if(temp1.first != aCap){
        //set a to max capacity
        temp1.first = aCap;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp1);
        edge_label[make_pair(pair, temp1)] = actions[0];
      }

      //Fill B
      state temp2 = pair;

      //check if b is max capacity
      if(temp2.second != bCap){
        //set b to max
        temp2.second = bCap;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp2);
        edge_label[make_pair(pair, temp2)] = actions[1];
      }

      //Empty A
      state temp3 = pair;

      //check if a is empty
      if(temp3.first != 0){
        //set a to empty
        temp3.first = 0;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp3);
        edge_label[make_pair(pair, temp3)] = actions[2];
      }

      //Empty B
      state temp4 = pair;

      //check if b is empty
      if(temp4.second != 0){
        //set b to empty
        temp4.second = 0;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp4);
        edge_label[make_pair(pair, temp4)] = actions[3];
      }

      //Pour A
      state temp5 = pair;

      //check if a is empty and if not check if b + a is less than bs cap 
       if (temp5.first != 0) {
         if (temp5.first + temp5.second <= bCap) {
          //if it isnt set b to a + b
          temp5.second = temp5.first + temp5.second;
        }
        else {

          //if it is set b to bs cap
          temp5.second = bCap;
        }

        //set a to a - b
        temp5.first = temp5.first - temp5.second;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp5);
        edge_label[make_pair(pair, temp5)] = actions[4];
      }

      //Pour B
      state temp6 = pair;

      //check if b is empty and if it is check if a + b is less than acap
      if(temp6.second != 0){
        if(temp6.first + temp6.second <= aCap){
          //if it is set a to a + b
          temp6.first = temp6.first + temp6.second;
        }else{
          //if not set a to acap
          temp6.first = aCap;
        }

        //set b to b - a
        temp6.second = temp6.second - temp6.first;

        //add this pair to possible solutions then add its string to lable map
        nbrs[pair].push_back(temp6);
        edge_label[make_pair(pair, temp6)] = actions[5];
      }
    }
  }
}

/*
int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
*/