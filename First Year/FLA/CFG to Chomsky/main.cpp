#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

ifstream f("CFG.in");
ofstream g("CFG.out");

int N;
map<string, int> m, word[100];
vector<string> CFG[100];
int HasL[100];
vector<string> Namemap;
map<string, string> twoc;
string l;

void Step1()
{
    int i, j, k;

    for(int i = 1; i <= N; i++)
        if(CFG[i].size() == 1 && CFG[i][0][0] == '_')
            HasL[i] = 2;

    for(i = 1; i <= N; i++)
        for(j = 0; j < (int)CFG[i].size(); j++)
            if(CFG[i][j].size() == 1 && HasL[ m[ CFG[i][j] ] ])
                    HasL[ m[Namemap[i]] ] = HasL[ m[ CFG[i][j] ] ];

    for(i = 1; i <= N; i++)
    {
        for(j = 0; j < (int)CFG[i].size(); j++)
        {
                for(k = 0; k < (int)CFG[i][j].size(); k++)
                {
                string c;
                c += CFG[i][j][k];

                if(HasL[m[c]] == 2)
                {
                    word[i][CFG[i][j]] = 0;
                    CFG[i][j].erase(CFG[i][j].begin() + k, CFG[i][j].begin() + k + 1);
                    k--;
                }
                if(HasL[m[c]] == 1)
                {
                    string d;
                    d += CFG[i][j];
                    d.erase(d.begin() + k, d.begin() + k + 1);

                    if(word[i][d] != 1)
                        {
                            CFG[i].push_back(d);
                            word[i][d] = 1;
                        }
                }
            }
        }
    }

    for(i = 1; i <= N; i++)
        if(HasL[i] == 2)
        {
            CFG[i].clear();
            m[Namemap[i]] = 0;
        }
        else if(HasL[i] == 1)
            for(j = 0; j < (int)CFG[i].size(); j++)
                if(CFG[i][j].size() == 1 && CFG[i][j].find('_') != string::npos)
                {
                    CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                    j--;
                }
}

void Step2()
{
    int i, j, k;

    for(i = 1; i <= N; i++)
        for(j = 0; j < (int)CFG[i].size(); j++)
            if(CFG[i][j] == Namemap[i])
            {
                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                j--;
            }
            else
            if(CFG[i][j].size() == 1 && CFG[i][j][0] == toupper(CFG[i][j][0]))
            {
                int index = m[CFG[i][j]];
                for(k = 0; k < (int)CFG[index].size(); k++)
                    if(word[i][CFG[index][k]] == 0)
                    {
                        CFG[i].push_back(CFG[index][k]);
                        word[i][CFG[index][k]] = 1;
                    }

                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                j--;
            }
}

void Step3()
{
    int i, j;
    l += 'A';

    for(i = 1; i <= N; i++)
        for(j = 0; j < (int)CFG[i].size(); j++)
            if(CFG[i][j].size() > 2)
            {
                string s;

                string aux;
                aux += CFG[i][j][0];
                aux += CFG[i][j][1];

                if(twoc[aux].size() == 0)
                {
                    s += l;
                    s += &CFG[i][j][2];
                    N++;
                    CFG[N].push_back(aux);
                    word[N][aux] = 1;
                    Namemap.push_back(l);
                    twoc[aux] = l;
                    l[0] = l[0] + 1;
                }
                else
                {
                    s += twoc[aux];
                    s += &CFG[i][j][2];
                }

                word[i][s] = 1;
                word[i][CFG[i][j]] = 0;
                CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                CFG[i].push_back(s);

            }

    /*for(i = 1; i <= N; i++)
    {
        if(CFG[i].size() != 0)
        {
            cout << Namemap[i] << ". ";
            for(j = 0; j < (int)CFG[i].size(); j++)
                cout << CFG[i][j] << " ";
            cout << "\n";
        }
    }
    cout << "\n";
    */
}

void Step4()
{
    int i, j, k;

    for(i = 1; i <= N; i++)
        for(j = 0; j < (int)CFG[i].size(); j++)
            if(CFG[i][j].size() == 2)
            for(k = 0; k < 2; k++)
                if(CFG[i][j][k] == tolower(CFG[i][j][k]))
                {
                    string aux;
                    aux += CFG[i][j][k];

                    if(twoc[aux].size() == 0)
                    {
                        twoc[aux] = l;
                        N++;
                        CFG[N].push_back(aux);
                        m[l] = N;
                        Namemap.push_back(l);
                        word[N][aux] = 1;

                        string t;
                        if(k == 0)
                        {
                            t = Namemap[m[l]] + t;
                            t += CFG[i][j][k + 1];
                        }
                        else
                        {
                            t += CFG[i][j][0];
                            t += Namemap[m[l]];
                        }

                        l[0] = l[0] + 1;

                        CFG[i].push_back(t);
                        CFG[i].erase(CFG[i].begin() + j, CFG[i].begin() + j + 1);
                        j--;
                        break;
                    }
                    else
                    {
                        CFG[i][j][k] = twoc[aux][0];
                    }
                }

    for(i = 1; i <= N; i++)
    {
        if(CFG[i].size() != 0)
        {
            g << Namemap[i] << ". ";
            for(j = 0; j < (int)CFG[i].size(); j++)
                g << CFG[i][j] << " ";
            g << "\n";
        }
    }
}

int main()
{
    string var, letter;

    f >> var >> letter;
    Namemap.push_back(var);
    while(f)
    {
        if(m[var] == 0)
        {
            N++;
            m[var] = N;
            Namemap.push_back(var);
            CFG[N].push_back(letter);
            word[N][letter] = 1;
        }
        else
        {
            CFG[m[var]].push_back(letter);
            word[m[var]][letter] = 1;
        }

        if(letter.find('_') != string::npos)
            HasL[m[var]] = 1;

        f >> var >> letter;
    }

    Step1();
    Step2();
    Step3();
    Step4();

    return 0;
}
