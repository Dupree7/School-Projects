#include <stdio.h>
#include <stdlib.h>

#define maxim(a , b) a > b ? a : b;

void Afisare(char **M, int n, int m, FILE *g) // functia de afisare in fisier a unei matrice
{
    int i, j;

    for(i = 1; i < n + 1; i++)
        {
        for(j = 1; j < m + 1; j++)
            fprintf(g, "%c ", M[i][j]);
        fprintf(g, "\n");
        }
}

int VerifCelula(char **M, int i, int j) // functia care verifica cate celelue vecine sunt in viata
{
    int c = 0, t;

    for(t = j - 1; t < j + 2; t++)
        {
        if(M[i - 1][t] == '1')
            c++;
        if(M[i + 1][t] == '1')
            c++;
        }

    if(M[i][j - 1] == '1')
        c++;
    if(M[i][j + 1] == '1')
        c++;

    return c;
}

char** Transformare(char **a, int n, int m, float *max)
{
    int i, j, nr = 0, nr2 = 0; // prin nr contorizam celulele vii ca sa calculam gradul de populare pe care il salvam in variabila max trimisa ca parametru

    char **b = (char **) malloc((n + 2) * sizeof(char *));
    for(i = 0; i < n + 2; i++)
        b[i] = (char *) malloc((m + 2) * sizeof(char));

    for(i = 1; i < n + 1; i++)
        for(j = 1; j < m + 1; j++)
        {
            int c = VerifCelula(a, i, j); // c = numarul de celule vecine celulei de pe poz i si j

            if(a[i][j] == '0') // celula este moarta si verificam daca invie
            {
                if(c == 3)
                    {
                    b[i][j] = '1';
                    nr2++;
                    }
                else
                    b[i][j] = '0';
            }
            else // celula e vie si verificam daca traieste
            {
                nr++; // incrementam numarul de aparitii al nr de celule vii
                if(c == 2 || c == 3)
                    {
                    b[i][j] = '1';
                    nr2++;
                    }
                else
                    b[i][j] = '0';
            }
        }
    nr = maxim(nr, nr2);

    if(nr > *max)
        *max = nr;

    return b;
}

void Bordare(char **a, int n, int m, char c) // completez marginile cu vecinii de pe partile celelalte
{
    int i;

    if(n < 3 && m < 3)
    {
        for(i = 0; i < m + 2; i++) // bordarea pe linii daca nr de linii si coloane este mai mic sau egal cu 2
        {
            a[0][i] = 'x'; // le bordam cu x pentru ca in orice reprezentare nu au vecini de pe alte margini
            a[n + 1][i] = 'x';
        }
        for(i = 1; i < n + 1; i++)
        {
            a[i][0] = 'x';
            a[i][m + 1] = 'x';
        }
    }
    else if((n == 2 || n == 1) && m > 2) // cazul in care avem doua linii si mai multe coloane. Bordam doar pe coloane cu vecini
    {
        for(i = 0; i < m + 2; i++)
        {
            a[0][i] = 'x';
            a[n + 1][i] = 'x';
        }

        a[1][0] = (c == 'T') ? a[1][m] : 'x';
        a[2][0] = (c == 'T') ? a[2][m] : 'x';
        a[1][m + 1] = (c == 'T') ? a[1][1] : 'x';
        a[2][m + 1] = (c == 'T') ? a[2][1] : 'x';
    }
    else if(n > 2 && (m == 2 || m == 1)) // cazul in care avem doar doua coloane si mai multe linii. Bordam doar pe linii cu vecini
    {
        for(i = 0; i < n + 2; i++)
        {
            a[i][0] = 'x';
            a[i][m + 1] = 'x';
        }

        a[0][1] = (c == 'T') ? a[n][1] : 'x';
        a[0][2] = (c == 'T') ? a[n][2] : 'x';
        a[n + 1][1] = (c == 'T') ? a[1][1] : 'x';
        a[n + 1][2] = (c == 'T') ? a[1][2] : 'x';
    }
    else // cazul in care n > 2 si m > 2 bordam conform T sau P    {
    {
        for(i = 1; i < n + 1; i++) // bordarea pe prima si ultima coloana
        {
            a[i][0] = (c == 'T') ? a[i][m] : 'x';
            a[i][m + 1] = (c == 'T') ? a[i][1] : 'x';
        }
        for(i = 1; i < m + 1; i++) // bordarea pe prima si ultima linie
        {
            a[0][i] = (c == 'T') ? a[n][i] : 'x';
            a[n + 1][i] = (c == 'T') ? a[1][i] : 'x';
        }
        // bordarea colturilor
        a[0][0] = (c == 'T') ? a[n][m] : 'x';
        a[0][m + 1] = (c == 'T') ? a[n][1] : 'x';
        a[n + 1][0] = (c == 'T') ? a[1][m] : 'x';
        a[n + 1][m + 1] = (c == 'T') ? a[1][1] : 'x';
    }
}

int main()
{
    char c; // variabila in care se retine tipul reprezentarii
    int m, n, i, j, t, k; // variabilele citite cu seminificatia din enunt. i si j sunt iteratori
    FILE *f, *g;
    float procentaj_populare = 0.0;

    f = fopen("date.in", "r");
    g = fopen("date.out", "w");

    fscanf(f, "%c %d %d %d", &c, &n, &m, &k);

    char **a = (char **) malloc((n + 2) * sizeof(char *));
    for(i = 0; i < n + 2; i++)
        a[i] = (char *) malloc((m + 2) * sizeof(char));

    for(i = 1; i < n + 1; i++)
        for(j = 1; j < m + 1; j++)
            {
                fscanf(f, "%d", &t);
                a[i][j] = t + '0';
            }

    Bordare(a, n, m, c);

    for(i = 0; i < k; i++)
    {
        a = Transformare(a, n, m, &procentaj_populare);
        Bordare(a, n, m, c);
    }

    procentaj_populare = procentaj_populare / (n * m) * 100;

    Afisare(a, n, m, g);
    fprintf(g, "%.3f", procentaj_populare);

    for(i = 0; i < n + 2; i++)
        free(a[i]);
    free(a);

    return 0;
}
