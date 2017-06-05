#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;


ifstream f("ldfa.in");
ifstream ff("tests.in");
ofstream g("ldfa.out");

struct nod
{
    int cs, ns, pos;
    char c;
};

int fstate[100];
vector<nod> v[100];

int ldfa(char cuvant[])
{
    stack<nod> s;
    nod t;
    t.pos = 0;
    t.cs = 0;

    s.push(t);

    while(!s.empty())
    {
        t = s.top();
        s.pop();

        for(int i = 0; i < (int)v[t.cs].size(); i++)
        {
            if(v[t.cs][i].c == cuvant[t.pos])
            {
                nod y;
                y.pos = t.pos + 1;
                y.cs = v[t.cs][i].ns;
                s.push(y);

                if(y.pos == (int)strlen(cuvant) && fstate[y.cs])
                    return 1;
            }
            else if(v[t.cs][i].c == '_')
            {
                nod y;
                y.pos = t.pos;
                y.cs = v[t.cs][i].ns;
                s.push(y);

                if(y.pos == (int)strlen(cuvant) && fstate[y.cs])
                    return 1;
            }
        }
    }

    return 0;
}

int main()
{
    char cuvant[100];
    string t;
    int i;
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
        nod x;
        x.ns = b;
        x.c = c;

        v[a].push_back(x);

        f >> a >> c >> b;
    }

    ff >> cuvant;

    while(ff)
    {
        g << ldfa(cuvant) << "\n";
        ff >> cuvant;
    }

    return 0;
}
