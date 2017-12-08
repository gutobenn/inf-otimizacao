#include <iostream>
#include <string>
#include <climits>

using namespace std;

static int INF = INT_MAX;

int main(){

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
        precedence[j][i] = false;
      } else { // -1
        distance[i][j] = INF;
        precedence[j][i] = true; // J precede I
      }
		}
	}

  cout << "data;" << endl << "set N:= ";





	/*

  Cada linha possui N valores inteiros separados por espaço. Dada uma linha i
  # qualquer, e uma coluna j qualquer, se o valor v presente na posição (i,j) for
  # tal que v >=0 , então v é a distância entre os vértices i e j no grafo. Caso
  # v = -1, então quer dizer que o vértice i só pode ser visitado após o vértice j
  # e NÃO antes. Em outras palavras, o vértice j deve preceder i na solução.
  #



	NAME: ESC07.sop
	TYPE: SOP
	COMMENT: Received by Norbert Ascheuer / Laureano Escudero
	DIMENSION: 9
	EDGE_WEIGHT_TYPE: EXPLICIT
	EDGE_WEIGHT_FORMAT: FULL_MATRIX
	EDGE_WEIGHT_SECTION
	0    0    0    0    0    0    0    0 1000000
	-1    0  100  200   75    0  300  100    0
	-1  400    0  500  325  400  600    0    0
	-1  700  800    0  550  700  900  800    0
	-1   -1  250  225    0  275  525  250    0
	-1   -1  100  200   -1    0   -1   -1    0
	-1   -1 1100 1200 1075 1000    0 1100    0
	-1   -1    0  500  325  400  600    0    0
	-1   -1   -1   -1   -1   -1   -1   -1    0
	EOF


	*/





	return 0;
}
