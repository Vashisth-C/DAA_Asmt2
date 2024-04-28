#include<iostream>
#include<vector>
#include<stack>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

int solve(string rna, vector<vector<int>>& traceback) 
{
    int n = rna.size();
    vector<vector<int> > OPT(n, vector<int>(n, 0));

    for (int k=4; k<n; k++) 
    {
        for (int i=0; i<n-k; i++) 
        {
            int j=i+k;
            int max = OPT[i][j-1];
            int splitPoint = -1;
            
            for (int t=i; t<j-4; t++) 
            {
                if ((rna[t] == 'A' && rna[j] == 'U') || (rna[t] == 'U' && rna[j] == 'A') || (rna[t] == 'C' && rna[j] == 'G') || (rna[t] == 'G' && rna[j] == 'C')) 
                {
                    int c = 1;
                    if (t > i)
                        c += OPT[i][t-1];
                    if (t + 1 < j)
                        c += OPT[t+1][j-1];
                    if (c > max) 
                    {
                        max = c;
                        splitPoint = t;
                    }
                }
            }
            OPT[i][j] = max;
            traceback[i][j] = splitPoint;
        }
    }
    return OPT[0][n - 1];
}

pair<vector<pair<int, int>>, string> tracebackSecondaryStructure(string rna, vector<vector<int>> traceback) {
    int n = rna.size();
    stack<pair<int, int>> segments;
    vector <pair<int, int> > pairs;
    string structure(n, '.');

    segments.push(make_pair(0, n - 1));
    while (!segments.empty()) 
    {
        int i = segments.top().first;
        int j = segments.top().second;
        segments.pop();

        if (i >= j) continue;

        int splitPoint = traceback[i][j];

        if (splitPoint == -1)
            segments.push(make_pair(i, j-1));
        else
        {
            structure[splitPoint] = '(';
            structure[j] = ')';
            pairs.push_back(make_pair(splitPoint, j));
            segments.push(make_pair(i, splitPoint-1));
            segments.push(make_pair(splitPoint+1, j-1));
        }
    }
    return make_pair(pairs,structure);
}

int main() {
    string rna;

    ifstream inputFile("./static/data/input.txt");
    string line;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            cout << line << endl;
            rna = line;
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }

    int n = rna.size();
    vector<vector<int>> traceback(n, vector<int>(n, -1));

    int ans = solve(rna, traceback);
    pair<vector<pair<int, int>>, string> folding = tracebackSecondaryStructure(rna, traceback);

    ofstream foldingOutput("./static/data/folding.txt");
    if (!foldingOutput.is_open()) {
        cerr << "Failed to open the file!" << endl;
        return 1;
    }
    foldingOutput << rna << endl;
    foldingOutput << folding.second << endl;
    foldingOutput.close();

    ofstream optimalPairs("./static/data/output.txt");
    optimalPairs <<"Optimal pairs: " << ans << endl;
    for(auto x: folding.first){
        optimalPairs << x.first<<" "<<x.second<<endl;
    }
    optimalPairs.close();

    ofstream dotBrac("./static/data/dotBracNotation.txt");
    if (!dotBrac.is_open()) {
        cerr << "Failed to open the file!" << endl;
        return 1;
    }
    dotBrac << folding.second << endl;
    dotBrac.close();

    system("./static/shell/run1.sh");
    
    return 0;
}
