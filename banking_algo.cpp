#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int processes, int resources, vector<vector<int>> allocation, vector<vector<int>> max, vector<int> available) {
    vector<vector<int>> need(processes, vector<int>(resources, 0));
    vector<bool> finish(processes, false);
    vector<int> safeSeq(processes, 0);
    int count = 0;

    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < resources; j++)
                    if (need[i][j] > available[j])
                        break;
                if (j == resources) {
                    for (int k = 0; k < resources; k++)
                        available[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    cout << "Safe sequence is: ";
    for (int i = 0; i < processes - 1; i++)
        cout << "P" << safeSeq[i] << " -> ";
    cout << "P" << safeSeq[processes - 1] << endl;
    return true;
}

int main() {
    int processes, resources;

    cout << "Enter the number of processes: ";
    cin >> processes;
    cout << "Enter the number of resources: ";
    cin >> resources;

    vector<vector<int>> allocation(processes, vector<int>(resources));
    cout << "Enter the allocation matrix: " << endl;
    for (int i = 0; i < processes; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < resources; j++)
            cin >> allocation[i][j];
    }

    vector<vector<int>> max(processes, vector<int>(resources));
    cout << "Enter the max matrix: " << endl;
    for (int i = 0; i < processes; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < resources; j++)
            cin >> max[i][j];
    }

    vector<int> available(resources);
    cout << "Enter the available vector: ";
    for (int i = 0; i < resources; i++)
        cin >> available[i];

    if (isSafe(processes, resources, allocation, max, available))
        cout << "The system is in a safe state" << endl;
    else
        cout << "The system is not in a safe state" << endl;
    return 0;
}


