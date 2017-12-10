#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

static int INF = INT_MAX;
static int MAX_ITERATIONS = 40; // TODO how many?

/* VECTOR UTILITIES */
void printBidimensionalVector(vector<vector<int> > v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

bool vectorHasElement(vector<int> v, int x) {
    return find(v.begin(), v.end(), x) != v.end();
}


/* TABU SEARCH */
vector<pair<int, int> > tabuList;
unsigned int maxTabuListSize;

void printTabuList() {
    cout << "Tabu List:" << endl;
    for (size_t i = 0; i < tabuList.size(); i++) {
        cout << "(" << tabuList[i].first << ", " << tabuList[i].second << ")" << " ";
    }
}

//TODO ver se ta funcionando essa funcao
bool isTabu(int i, int j) {
    return find(tabuList.begin(), tabuList.end(), make_pair(i,j)) != tabuList.end();
}

void addRestrictionToTabuList(int i, int j) {
    if(!isTabu(i,j)) {
        tabuList.push_back(make_pair(i,j));
    }
    if(tabuList.size() == maxTabuListSize) {
        tabuList.erase(tabuList.begin());
    }
}

/* Path utilities */
int getPathCost(vector<int> path, vector<vector<int> > costs) {
    int total = 0;
    for (size_t i = 0; i < path.size()-1; i++) {
        total += costs[path[i]-1][path[i+1]-1];
    }
    return total;
}

void twoOptMove(vector<int> *path, int i, int j) {
    // Based on https://stackoverflow.com/questions/33043991/trouble-with-the-implementation-of-2-opt-and-3-opt-search-in-the-resolution-of-t

    vector<int> helpPath;
    helpPath.resize(path->size());

    // compute new tour
    for(int k = 0; k <= i; k++) {
        helpPath[k] = (*path)[k];
    }
    for(int k = 0; k < j - i; k++) {
        helpPath[a+k+1] = (*path)[b-k];
    }
    for(int k = j + 1; k < size; k++) {
        helpPath[k] = (*path)[k];
    }

    // update tour
    /*for(int i = 0; i < size; i++){
        cities[i] = help_cities[i];
    }*/
    (*path) = helpPath; // TODO testar, talvez esteja errado
}

/* STARTING CURRENT SOLUTION */
int getStartingCurrentSolution(vector<int> *tempPath, int dimension, vector<vector<int> > costs) {
    vector<int> waitingForPrecedent; // Store nodes waiting for a precedent node still not visited
    int currentNodeIndex = 0, minCostFound, nextNodeIndex, totalCost = 0;
    bool foundNextNode, validNextNode;

    tempPath->push_back(1);

    for (size_t i = 1; i < dimension - 1; i++) {
        foundNextNode = false;
        minCostFound = INF;
        nextNodeIndex = 0;

        while (!foundNextNode) {

            for (size_t j = 1; j < dimension - 1; j++) {
                if (costs[currentNodeIndex][j] != -1 && !vectorHasElement(waitingForPrecedent, j+1) && !vectorHasElement(*tempPath, j+1)) {
                    if (costs[currentNodeIndex][j] < minCostFound) {
                        minCostFound = costs[currentNodeIndex][j];
                        nextNodeIndex = j;
                    }
                }
            }

            validNextNode = true;

            // If the chosen node has an unvisited precedent node, it can't be visited now.
            for (size_t j = 1; j < dimension - 1; j++) {
                if(costs[nextNodeIndex][j] == -1 && !vectorHasElement(*tempPath, j+1)) {
                    validNextNode = false;
                    break;
                }
            }

            if (validNextNode) {
                tempPath->push_back(nextNodeIndex+1);
                foundNextNode = true;
                waitingForPrecedent.clear();
                currentNodeIndex = nextNodeIndex;
            } else {
                minCostFound = INF;
                waitingForPrecedent.push_back(nextNodeIndex+1);
            }

        }
        totalCost += minCostFound;
    }

    tempPath->push_back(dimension);

    cout << "PATH: ";
    printVector(*tempPath);
    cout << endl;

    return totalCost;
}

int main(int argc, const char * argv[]) {
    string initialInfo;
    int iterationsCounter = MAX_ITERATIONS;

    if (! argv[1]) {
        cerr << "Usage: " << argv[0] << " <instance_file.sop>" << endl;
        return -1;
    }

    // Open file
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    if (!ifs) {
        cerr << "Erro ao abrir arquivo";
        return -1;
    }

    // Get irrelevant information from the instance
    for (int i = 0; i < 3; i++) {
        getline(ifs, initialInfo);
    }

    // Get dimensions
    getline(ifs, initialInfo);
    int dimension = stoi(initialInfo.substr(11,initialInfo.length()));

    // Create matrices
    vector<vector<int> > costs(dimension);
    for (size_t i = 0; i < dimension; i++) {
        costs[i].resize(dimension);
    }


    // Get more irrelevant information from the instance
    for (int i = 0; i < 3; i++) {
        getline(ifs, initialInfo);
    }

    // Read vertices
    int v;
    for (size_t i = 0; i < dimension; i++) {
        for (size_t j = 0; j < dimension; j++) {
            ifs >> costs[i][j];
        }
    }

    // Close file
    ifs.close();

    maxTabuListSize = int(dimension / 4);

    vector<int> bestPath;
    vector<int> tempPath;
    int bestCost = getStartingCurrentSolution(&bestPath, dimension, costs);
    int tempCost = bestCost;
    tempPath = bestPath;

    cout << "Costs:" << endl;
    printBidimensionalVector(costs);
    cout << endl << "Starting Current Solution:" << endl;
    printVector(tempPath);
    cout << "has cost " << bestCost << endl;


    while(iterationsCounter--) {
        /* TODO Fazer e renomear!!
        pair<int, int> maxMove = twoOptSearch(costs, tempPath);
        if(maxMove.first == -1){
            break;
        }

        twoOptMove(&tempPath, maxMove.i, maxMove.j);
        tempCost = getPathCost(tempPath, costs);

        addRestrictionToTabuList(maxMove); */

        if(tempCost < bestCost) {
            bestCost = tempCost;
            bestPath = tempPath;
            iterationsCounter = MAX_ITERATIONS;
        }
    }

    cout << "Reached iteration " << MAX_ITERATIONS - iterationsCounter << endl;
    cout << "Best Solution:";
    printVector(bestPath);
    cout << "with cost " << bestCost;

    return 0;
}
