#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("lnfa.in");
ofstream g("nfa.out");

struct nod
{
    int ns;
    char c;
};

int fstate[100];
vector<nod> v[100], LLencl[100], NFA[100];
vector<int> Lencl[100];

void Lenclosure(int x)
{
    queue<int> q;
    q.push(x);
    int viz[100] = {0};

    Lencl[x].push_back(x);

    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        viz[t] = 1;

        for(int i = 0; i < (int)v[t].size(); i++)
            if(v[t][i].c == '_' && !viz[v[t][i].ns])
                {
                    if(fstate[v[t][i].ns] == 1)
                        fstate[t] = 1;

                    q.push(v[t][i].ns);
                    Lencl[x].push_back(v[t][i].ns);
                }
    }
}

void Transform(int n, char l)
{
    int i, j;
    const int lines = n, col = (l - 'a') + 1;
    vector<int> a[lines][col];

    for(i = 0; i < n; i++)
        Lenclosure(i);

    for(i = 0; i < lines; i++)
    {
        for(j = 0; j < col; j++)
        {
            char c = 'a' + j;

            for(int k = 0; k < (int)v[i].size(); k++)
                if(v[i][k].c == c)
                    a[i][j].push_back(v[i][k].ns);
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < (int)Lencl[i].size(); j++)
        {
            int cs = Lencl[i][j];

            for(int k = 0; k < col; k++)
            {
                char c = k + 'a';

                for(int u = 0; u < (int)a[cs][k].size(); u++)
                {
                    nod x;
                    x.ns = a[cs][k][u];
                    x.c = c;
                    LLencl[i].push_back(x);
                }
            }
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < LLencl[i].size(); j++)
        {
            int cs = LLencl[i][j].ns;
            for(int k = 0; k < Lencl[cs].size(); k++)
            {
                nod x;
                x.ns = Lencl[cs][k];
                x.c = LLencl[i][j].c;
                NFA[i].push_back(x);
            }
        }
    }
}

/*void RedundantStateRemoval(int &n)
{
    int i, j, k;
    int schimb[100];
    for(i = 0; i < n; i++)
        schimb[i] = i;

    for(i = 0; i < n; i++)
        if(schimb[i] == i)
            for(j = 0; j < n; j++)
            {
                if(NFA[i].size() == NFA[j].size())
                    {
                        int ok = 1;
                        for(k = 0; k < (int)NFA[j].size(); k++)
                            if(kNFA[i][k] != NFA[j][k])
                                ok = 0;
                        if(ok)
                            schimb[j] = schimb[i];
                    }
            }
}
*/

void ShowNFA(int n)
{
    int i, j;

    for(i = 0; i < n; i++)
        if(fstate[i])
            g << i << " ";

    g << "\n";

    for(i = 0; i < n; i++)
        for(j = 0; j < NFA[i].size(); j++)
            g << i << " " << NFA[i][j].c << " " << NFA[i][j].ns << "\n";
}

int main()
{
    string t;
    int i, nr = -1;
    char l = 'a';
    getline(f, t);

    for(i = 0; i < (int)t.size(); i++)
    {
        if(isdigit(t[i]))
            fstate[t[i] - '0'] = 1;
    }

    int a, b;
    char c;

    f >> a >> c >> b;

    while(f)
    {
        nr = max(nr, max(a,b));
        if(c != '_' && c > l)
            l = c;

        nod x;
        x.ns = b;
        x.c = c;

        v[a].push_back(x);

        f >> a >> c >> b;
    }

    nr++;

    Transform(nr, l);
    //RedundantStateRemoval(nr);
    ShowNFA(nr);

    return 0;
}
