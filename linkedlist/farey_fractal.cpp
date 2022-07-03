#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> generate_fractal(int n)
{
    vector<pair<int, int>> f = {
        {0, 1},
        {1, 1}};

    auto it = f.begin();
    for (int i = 0; i < f.size() - 1; i++)
    {
        // it++;
        f.insert(
            it,
            {(f[i].first + f[i + 1].first),
             (f[i].second + f[i + 1].second)});
    }

    return f;
}

int main()
{
    int n = 5;
    vector<pair<int, int>> fractal = generate_fractal(n);
    for (auto &p : fractal)
    {
        cout << p.first << ", " << p.second << '\n';
    }
    return EXIT_SUCCESS;
}
