#include <bits/stdc++.h>

using namespace std;

const int max_enemies = 11; // Total number of enemies in the Chakravyuha

int power; // Initial power of Abhimanyu

// dp[enemy][cur_power][skips][recharge] stores whether Abhimanyu can cross the Chakravyuha
vector<vector<vector<vector<int>>>> dp;

bool canCrossChakrvyuha(vector<int>& enemyPower, int enemy, int cur_power, int behind, int skips, int recharge) {
    // Base case: Abhimanyu successfully crossed the Chakravyuha
    if (enemy == max_enemies)
        return true;

    // If the state has been computed before, return the stored result
    if (dp[enemy][cur_power][skips][recharge] != -1)
        return dp[enemy][cur_power][skips][recharge];

    bool flag = false;

    // Option 1: Recharge if possible
    if (recharge > 0 && cur_power < power)
        flag |= canCrossChakrvyuha(enemyPower, enemy, power, behind, skips, recharge - 1);

    // Option 2: Fight from behind if there is an enemy attacking from behind
    if (cur_power >= behind) {
        cur_power -= behind;
        behind = 0;
    } else {
        return dp[enemy][cur_power][skips][recharge] = false;
    }

    // Option 3: Skip the current enemy if skips are available
    if (skips > 0)
        flag |= canCrossChakrvyuha(enemyPower, enemy + 1, cur_power, behind, skips - 1, recharge);

    // Option 4: Fight the current enemy
    if (cur_power >= enemyPower[enemy]) {
        if (enemy == 2 || enemy == 6)
            behind = enemyPower[enemy] / 2;

        flag |= canCrossChakrvyuha(enemyPower, enemy + 1, cur_power - enemyPower[enemy], behind, skips, recharge);
    }

    // Store the result in dp table and return
    return dp[enemy][cur_power][skips][recharge] = flag;
}

int main() {
    vector<int> enemyPower(max_enemies); // Powers of each enemy from 1-11.

    for (int i = 0; i < max_enemies; i++)
        cin >> enemyPower[i];

    int a, b; // a: Total number of skips Abhimanyu has, b: Number of times Abhimanyu can recharge himself
    cin >> power >> a >> b;

    // Initialize DP table with -1 (uncomputed state)
    dp = vector<vector<vector<vector<int>>>>(max_enemies + 1, vector<vector<vector<int>>>(power + 1, vector<vector<int>>(a + 1, vector<int>(b + 1, -1))));

    int behind = 0; // Power of regenerated enemy to attack from behind.

    if (canCrossChakrvyuha(enemyPower, 0, power, behind, a, b))
        cout << "Abhimanyu can cross the Chakrvyuha" << endl;
    else
        cout << "Abhimanyu cannot cross the Chakrvyuha" << endl;

    return 0;
}