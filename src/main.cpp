#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

static int INF = INT_MAX;
static int MAX_ITERATIONS = 10;

/*; VECTOR UTILITIES */
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

bool isValidPath(vector<int> path, vector<vector<int> > costs){
    vector<int> waitingForPrecedent; // Store nodes waiting for a precedent node still not visited
    int nodeIndex;

    for (size_t i = 0; i < path.size() - 1; i++) {
        waitingForPrecedent.push_back(path[i]);
        nodeIndex = path[i]-1;
        for (size_t j = 0; j < path.size(); j++) {
            if(costs[nodeIndex][j] == -1 && !vectorHasElement(waitingForPrecedent, j+1)){
                return false;
            }
        }
    }
    return true;
}


int twoOptMove(vector<int> *path, vector<vector<int> > costs, int i, int j) {
    // i e j são os indices dos vértices no vetor path
    // Based on https://stackoverflow.com/questions/33043991/trouble-with-the-implementation-of-2-opt-and-3-opt-search-in-the-resolution-of-t

    vector<int> helpPath;
    helpPath.resize(path->size());
    int cost = 0;

    // compute new tour
    for(int k = 0; k <= i; k++) {
        helpPath[k] = (*path)[k];
    }
    for(int k = 0; k < j - i; k++) {
        helpPath[i+k+1] = (*path)[j-k];
    }
    for(int k = j + 1; k < path->size(); k++) {
        helpPath[k] = (*path)[k];
    }

    (*path) = helpPath;

    return getPathCost((*path),costs);
}


pair<int, int> twoOptSearch(vector<int> path, vector<vector<int> > costs, int pathCost){
    // Based on https://stackoverflow.com/questions/33043991/trouble-with-the-implementation-of-2-opt-and-3-opt-search-in-the-resolution-of-t

    int iMin = -1, jMin = -1, iMinK=-1, jMinK=-1, change, oldCost, newCost, maxSaving = 0, probability;
    bool foundBetterSolution = false;
    vector<pair<int, int> > bestFounds;
    // repeat until there are not new improvement
    for(int i = 1; i < path.size() - 3; i++){
        for(int j = i + 1; j < path.size() - 2; j++){
            probability = rand() % 10 + 1; // random number between 1 and 10
            //cout << "PROBABILITY " << probability << endl;
            //cout << "isTabu " << isTabu(i,j) << endl;
            if(isTabu(i,j) && probability > 8){ // accept tabu 20% of times
                break;
            }

            oldCost = pathCost;

            vector<int> newPath = path;
            newCost = twoOptMove(&newPath, costs, i, j);

            change = newCost - oldCost;

            if(isValidPath(newPath, costs)){
                if(change < maxSaving){
                    iMin = i;
                    jMin = j;
                    maxSaving = change;
                    foundBetterSolution = true;
                    bestFounds.clear();
                } else if(change == maxSaving){
                    bestFounds.push_back(make_pair(i,j));
                } else if(j-i > 3){ // Diversifying
                    iMinK = i;
                    jMinK = j;
                }
            }
        }
    }

    if(!foundBetterSolution){
        iMin = iMinK;
        jMin = jMinK;
    } else {
        if(bestFounds.size() > 1){
            //cout << "ENTROU IF BESTBOUND" << endl;
            //for (size_t i = 0; i < bestFounds.size(); i++) {
            //  cout << bestFounds[i].first << " " << bestFounds[i].second << " )" << endl;
            //}
            //cout << endl;
            int random_index = rand() % bestFounds.size();
            iMin = bestFounds[random_index].first;
            jMin = bestFounds[random_index].second;
        }
    }

    addRestrictionToTabuList(iMin, jMin);
    return make_pair(iMin, jMin);

}


/* STARTING CURRENT SOLUTION */
int getStartingCurrentSolution(vector<int> *tempPath, int dimension, vector<vector<int> > costs) {
	// TODO comentar essa função
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

    //cout << "PATH: ";
    //printVector(*tempPath);
    //cout << endl;

    return totalCost;
}

int main(int argc, const char * argv[]) {
    string initialInfo;
    int iterationsCounter = MAX_ITERATIONS;
    long int randomSeeds[10] = {419281046, 927195464, 483380767, 771002500, 398382839, 379984894, 635420729, 979478050, 239064709, 157236716};

    if (! argv[2]) {
        cerr << "Usage: " << argv[0] << " <instance_file.sop> <random_seed_id>" << endl;
        return -1;
    }

    if(stoi(argv[2]) > 10 || stoi(argv[2]) < 1){
        cerr << "Argument 'random seed' must be in interval [1,10]" << endl;
        return -1;
    }

    // Initialize srand with specified random seed
    long int randomSeed = randomSeeds[stoi(argv[2])-1];
    srand(randomSeed);
    //cout << "Random seed #" << argv[2] << ": " << randomSeed << endl;


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

    //cout << "Costs:" << endl;
    //printBidimensionalVector(costs);
    //cout << endl << "Starting Current Solution:" << endl;
    //printVector(tempPath);
    cout << bestCost << ";";

    clock_t begin = clock();

    while(iterationsCounter--) {
        pair<int, int> bestMove = twoOptSearch(tempPath, costs, tempCost);
        if(bestMove.first == -1){
            break;
        }

        tempCost = twoOptMove(&tempPath, costs, bestMove.first, bestMove.second);

        if(tempCost < bestCost) {
            bestCost = tempCost;
            bestPath = tempPath;
            iterationsCounter = MAX_ITERATIONS;
        }
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    //cout << "Reached iteration " << MAX_ITERATIONS - iterationsCounter << endl;
    //cout << "Best Solution:";
    //printVector(bestPath);
    cout << bestCost << ";";

    cout << elapsed_secs << ";" << endl;

    return 0;
}
