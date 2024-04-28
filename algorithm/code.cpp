#include<iostream>
#include<vector>
#include<stack>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

int foldingAlgorithm(string rna, vector<vector<int>>& dp) 
{
    int n = rna.size();
    vector<vector<int>> OPT(n, vector<int>(n, 0));

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
            dp[i][j] = splitPoint;
        }
    }
    return OPT[0][n - 1];
}

pair<vector<pair<pair<int, int>, pair<char, char>>>, string> generateStructure(string rna, vector<vector<int>> dp) {
    int n = rna.size();
    stack<pair<int, int>> segments;
    vector<pair<pair<int, int>, pair<char, char>>> pairs;
    string dotBracket(n, '.');

    segments.push(make_pair(0, n - 1));
    while (!segments.empty()) 
    {
        int i = segments.top().first;
        int j = segments.top().second;
        segments.pop();

        if (i >= j) continue;

        int splitPoint = dp[i][j];

        if (splitPoint == -1)
            segments.push(make_pair(i, j-1));
        else
        {
            dotBracket[splitPoint] = '(';
            dotBracket[j] = ')';
            pairs.push_back(make_pair(make_pair(splitPoint, j),make_pair(rna[splitPoint],rna[j])));
            segments.push(make_pair(i, splitPoint-1));
            segments.push(make_pair(splitPoint+1, j-1));
        }
    }
    return make_pair(pairs,dotBracket);
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
    vector<vector<int>> dp(n, vector<int>(n, -1));

    int ans = foldingAlgorithm(rna, dp);
    pair<vector<pair<pair<int, int>, pair<char, char>>>, string> folding = generateStructure(rna, dp);

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
        optimalPairs <<"(" <<x.first.first<<" "<<x.first.second << ")"<< ", " << "(" <<x.second.first<<" "<<x.second.second << ")"<<endl;
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
