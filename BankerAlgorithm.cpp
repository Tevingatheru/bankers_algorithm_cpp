#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the need of each process
void calculateNeed(vector<vector<int>> &need, vector<vector<int>> &max, vector<vector<int>> &allocation, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(vector<int> &available, vector<vector<int>> &need, vector<vector<int>> &allocation, int n, int m)
{
    vector<int> work(available);
    vector<bool> finish(n, false);

    // Find an index i such that both
    // (i) Finish[i] == false
    // (ii) Need[i][j] <= Work[j] for all j
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }
                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

// Function to find the safe sequence
vector<int> safeSequence(vector<int> &available, vector<vector<int>> &need, vector<vector<int>> &allocation, int n, int m)
{
    vector<int> work(available);
    vector<bool> finish(n, false);
    vector<int> safeSeq(n);

    // Find an index i such that both
    // (i) Finish[i] == false
    // (ii) Need[i][j] <= Work[j] for all j
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }
                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    safeSeq[count] = i;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
        {
            return vector<int>();
        }
    }
    return safeSeq;
}


void executeSaftyCheck(vector<int> available, vector<vector<int>> need, vector<vector<int>> allocation, int processNumber, int resourceNumber)
{
    if (isSafe(available, need, allocation, processNumber, resourceNumber))
    {
        cout << "The system is in a safe state." << endl;
        vector<int> safeSeq = safeSequence(available, need, allocation, processNumber, resourceNumber);
        cout << "The safe sequence is: ";
        for (int i = 0; i < processNumber; i++)
        {
            cout << "P" << safeSeq[i];
            if (i != processNumber - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "The system is in an unsafe state." << endl;
    }
}

void safeExample()
{
    int processNumber = 5, resourceNumber = 3;
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2},
    };
    vector<int> available = {3, 3, 2};
    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};

    vector<vector<int>> need(processNumber, vector<int>(resourceNumber));
    calculateNeed(need, max, allocation, processNumber, resourceNumber);
    executeSaftyCheck(available, need, allocation, processNumber, resourceNumber);
}

void unsafeExample()
{
    int processNumber = 3, resourceNumber = 2;

    vector<vector<int>> allocation = {
        {0, 0},
        {0, 0},
        {0, 0},
    };
    vector<int> available = {3, 3, 2};
    vector<vector<int>> max = {
        {7, 5},
        {3, 2},
        {9, 0},
    };

    vector<vector<int>> need(processNumber, vector<int>(resourceNumber));
    calculateNeed(need, max, allocation, processNumber, resourceNumber);
    executeSaftyCheck(available, need, allocation, processNumber, resourceNumber);
}

int main()
{
    cout<< "Safe Example" << endl;
    safeExample();
    cout<< "Unsafe Example" << endl;
    unsafeExample();

    return 0;
}
