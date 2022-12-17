#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

vector<vector<double>> Local_matrix(3), G_matrix(3), M_matrix(3);
vector<vector<int>> Elements, Conds1, Conds2;
vector<vector<double>> Global_A;
vector<vector<double>> Nodes;
vector<double> Local_B(3);
vector<double> ggl, diag;
vector<double> Global_B;
vector<int> ig, jg;
vector<int> jgV;
const long B = 1e+10;
int k, e;
const double Lyambda = 10;
const double Gamma = 4;

void Input() {
  ifstream f_Nodes, f_Elements, f_cond1, f_cond2;
  f_Nodes.open("Nodes.txt");
  f_Nodes >> k;
  Nodes.resize(k);
  for (int i = 0; i < k; i++) {
    Nodes[i].resize(2);
    f_Nodes >> Nodes[i][0] >> Nodes[i][1];
  }
  f_Nodes.close();
  f_Elements.open("Elems.txt");
  f_Elements >> e;
  Elements.resize(e);
  for (int i = 0; i < e; i++) {
    Elements[i].resize(4);
    f_Elements >> Elements[i][0] >> Elements[i][1] >> Elements[i][2] >>
        Elements[i][3];
  }
  f_Elements.close();
}

void Portait() {
  vector<set<int>> list(k);
  list.resize(k);
  // jg.resize(k + 6);
  ig.resize(k + 1);
  for (int d = 0; d < Elements.size(); d++) {
    for (int p = 0; p < 3; p++)
      for (int j = p + 1; j < 3; j++) {
        int ind_1 = Elements[d][p];
        int ind_2 = Elements[d][j];
        if (ind_1 < ind_2) {
          int h = ind_1;
          ind_1 = ind_2;
          ind_2 = ind_2;
        }
        list[ind_1].insert(ind_2);
      }
  }
  ig[0] = 0;

  for (size_t i = 0; i < k; i++) {
    ig[i + 1] = ig[i] + list[i].size();
    for (int j = 0; j < Nodes[i].size(); j++) {
      jg.push_back(Nodes[i][j]);
    }
  }
}

int main() {
  //	vector<double>x(3), y(3);
  Input();
  Portait();
  cout << " ig = ";
  for (int i = 0; i <= k; i++)
    cout << ig[i] << " ";
  cout << " jg = ";
  for (int i = 0; i < k; i++)
    cout << jg[i] << " ";
  cout << " list = ";
}
