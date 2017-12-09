#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

static int INF = INT_MAX;

int main(int argc, const char * argv[]) {

  if (! argv[1]) {
    cerr << "Usage: " << argv[0] << " <instance_file.sop>" << endl;
		return -1;
	}

  ifstream ifs;
	ifs.open(argv[1], ifstream::in);
  if (!ifs) {
    cerr << "Erro ao abrir arquivo";
    return -1;
  }

	string initialInfo;

  // Get irrelevant information from the instance
	for (int i = 0; i < 3; i++) {
		getline(ifs, initialInfo);
    cout << "linha: " << initialInfo << endl;
	}

	// Get dimensions
	getline(ifs, initialInfo);
	int dimension = stoi(initialInfo.substr(11,initialInfo.length()));

  // Create matrices
  int distance[dimension][dimension];
  int precedence[dimension][dimension];

	// Get more irrelevant information from the instance
	for (int i = 0; i < 3; i++) {
		getline(ifs, initialInfo);
	}

	// Read vertices
	int v;
	for (size_t i = 0; i < dimension; i++) {
		for (size_t j = 0; j < dimension; j++) {
			ifs >> v;
      if (v >= 0) {
        distance[i][j] = v;
        precedence[i][j] = false;
      } else { // -1
        distance[i][j] = INF;
        precedence[i][j] = true; // J precedes I
      }
		}
	}

	ifs.close();

  return 0;
}
