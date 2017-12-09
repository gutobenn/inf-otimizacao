#include <iostream>
#include <string>
#include <climits>

using namespace std;

static int INF = INT_MAX;

int main(){
	string initialInfo;

	// Get irrelevant information from the instance
	for (int i = 0; i < 3; i++) {
		getline(cin, initialInfo);
	}

	// Get dimensions
	getline(cin, initialInfo);
	int dimension = stoi(initialInfo.substr(11,initialInfo.length()));

  // Create matrices
  int distance[dimension][dimension];
  int precedence[dimension][dimension];

	// Get more irrelevant information from the instance
	for (int i = 0; i < 3; i++) {
		getline(cin, initialInfo);
	}

	// Read vertices
	int v;
	for (size_t i = 0; i < dimension; i++) {
		for (size_t j = 0; j < dimension; j++) {
			cin >> v;
      if (v >= 0) {
        distance[i][j] = v;
        precedence[i][j] = false;
      } else { // -1
        distance[i][j] = INF;
        precedence[i][j] = true; // J precede I
      }
		}
	}

  // Output "data" info
  cout << "data;" << endl << "param n := " << dimension;

  cout << ";" << endl << "set E := ";
  for (size_t i = 1; i < dimension; i++) { // TODO verificar se ta certo esses valores e a variavel
    cout << i << " ";
  }

	cout << ";" << endl << "param c:" << endl;
  for (size_t i = 0; i < dimension; i++) {
    cout << i << " ";
  }
  cout << ":=" << endl;

	for (size_t i = 0; i < dimension; i++) {
		cout << i << " ";
		for (size_t j = 0; j < dimension; j++) {
			cout << distance[i][j] << " ";
		}
		cout << endl;
	}

	cout << ";" << endl << "param p:" << endl;
  for (size_t i = 0; i < dimension; i++) {
    cout << i << " ";
  }
  cout << ":=" << endl;

	for (size_t i = 0; i < dimension; i++) {
		cout << i << " ";
		for (size_t j = 0; j < dimension; j++) {
			cout << precedence[i][j] << " ";
		}
		cout << endl;
	}

	cout << ";" << endl << endl << "end;" << endl;

	return 0;
}
