#include <bits/stdc++.h>
using namespace std;

vector<int> Tree;

int N;

int Op;

int main() {
	ios::sync_with_stdio(false);
	
	cin >> N;
	
	while(N--) {
	
		int Op;
		int X;
		
		cin >> Op >> X;
		
		switch(Op) {
			case 1:
				Tree.insert(upper_bound(Tree.begin() , Tree.end() , X) , X);
				break;
			case 2:
				Tree.erase(lower_bound(Tree.begin() , Tree.end() , X));
				break;
			case 3:
				cout << lower_bound(Tree.begin() , Tree.end() , X) - Tree.begin() + 1 << endl;
				break;
			case 4:
				cout << Tree[X - 1] << endl;
				break;
			case 5:
				cout << *--lower_bound(Tree.begin() , Tree.end() , X) << endl;
				break;
			case 6:
				cout << *upper_bound(Tree.begin() , Tree.end() , X) << endl;
		}
	}
	
	return 0;
}