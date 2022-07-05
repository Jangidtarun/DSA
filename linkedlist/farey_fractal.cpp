/*farey fractals using vector and pair objects.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


void printVec(const vector<pair<int, int>> &v)
{
    for (auto &it : v)
    {
        cout << it.first << "/" << it.second << ", ";
    }
    cout << endl;
}

vector<pair<int, int>> generate_fractal(int n)
{
    vector<pair<int, int>> base = {{0, 1}, {1, 1}};
    vector<pair<int, int>> ans;

    if (n == 0)
    {
        cout << "minimum n is 1\n";
    }
    if (n == 1)
    {
        return base;
    }

    int size = 2;
    // run for n-1 times
    while (size <= n)
    {
        // create a temporary vector.
        vector<pair<int, int>> tmp;
        // iterate over the prev temporary vec 
        // excluding the last index.
        for (int i = 0; i < base.size() - 1; i++)
        {

            int numer = base[i].first + base[i + 1].first;
            int denom = base[i].second + base[i + 1].second;
            tmp.push_back(base[i]);
            if (denom <= size)
            {
                tmp.push_back({numer, denom});
            }
        }
        tmp.push_back(base[base.size() - 1]);
        base = tmp;
        size++;
        ans = tmp;
    }

    return ans;
}

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        printVec(generate_fractal(i));
    }
    return EXIT_SUCCESS;
}
