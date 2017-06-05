#ifndef intreg_h
#define intreg_h

#include <string>
#include <math.h>

class intreg
{
    nod *pr, *ul;
    char semn;
    int cifre;

    public:
        intreg();
        char get_semn();
        nod* get_pr();
        nod* get_ul();
        int get_cifre();
        bool set_cifre(int d);
        bool set_semn(char c);
        bool set_ul(nod *a);
        int sterge_zero();
        bool aduna_constanta(int c);
        bool adauga_cifra(char c);
        bool adauga_cifra_final(char c);
        intreg operator* (intreg &x);
        intreg operator+ (intreg &x);
        intreg operator- (intreg &x);
        ifstream &operator >> (ifstream &stream);
        ofstream &operator << (ofstream &stream);
};

intreg::intreg()
{
    pr = NULL;
    ul = NULL;
    semn = 'x';
    cifre = 0;
}

bool intreg::set_ul(nod *a)
{
    return (ul = a);
}

char intreg::get_semn()
{
    return semn;
}

nod* intreg::get_pr()
{
    return pr;
}

nod *intreg::get_ul()
{
    return ul;
}

int intreg::get_cifre()
{
    return cifre;
}

bool intreg::set_cifre(int d)
{
    return (cifre = d);
}
bool intreg::set_semn(char c)
{
    return (semn = c);
}

bool intreg::adauga_cifra(char c)
{
    if(!ul)
    {
        ul = new nod;
        ul -> set_val(c);
        ul -> set_urm(NULL);
        ul -> set_ant(NULL);
        pr = ul;
        cifre++;
    }
    else
    {
        nod *nou = new nod;
        pr -> set_ant(nou);
        nou -> set_val(c);
        nou -> set_ant(NULL);
        nou -> set_urm(pr);
        pr = nou;
        cifre++;
    }
    return 1;
}

bool intreg::adauga_cifra_final(char c)
{
    if(!ul)
    {
        ul = new nod;
        ul -> set_val(c);
        ul -> set_urm(NULL);
        ul -> set_ant(NULL);
        pr = ul;
        cifre++;
    }
    else
    {
        nod *nou = new nod;
        nou -> set_urm(NULL);
        nou -> set_ant(ul);
        nou -> set_val(c);
        ul -> set_urm(nou);
        ul = nou;
        cifre++;
    }
    return 1;
}

int intreg::sterge_zero()
{
    int nr = 0;

    if(pr -> get_val() == '0' &&  pr -> get_urm() == NULL)
        return 0;

    if(pr -> get_urm() != NULL)
        while(pr -> get_val() == '0')
        {
            nod *nou = pr;
            pr = pr -> get_urm();
            pr -> set_ant(NULL);
            delete nou;
            nr++;
            cifre--;
        }

    return nr;
}


intreg intreg::operator*(intreg &x)
{
    intreg z;
    int t, nr_cif = 1;

    nod *itA = (*this).pr;

    z.adauga_cifra('0');
    nod *itC = z.get_pr();

    while(itA != NULL)
    {
        t = 0;
        int a = itA -> get_val() - '0';
        nod *itCC = itC;
        nod *itB = x.get_pr();

        while(itB)
        {
            int b = itB -> get_val() - '0';
            t += a * b;

            if(itCC)
            {
                t += (itCC -> get_val() - '0');
                itCC -> set_val(t % 10 + '0');
            }
            else
            {
                z.adauga_cifra_final(t % 10 + '0');
                itCC = z.get_ul();
                nr_cif++;
            }

            t /= 10;

            itB = itB -> get_urm();
            itCC = itCC -> get_urm();
        }

        if(t != 0)
            {
            z.adauga_cifra_final(t + '0');
            nr_cif++;
            }

        itA = itA -> get_urm();
        if(itC)
            itC = itC -> get_urm();
    }


    z.set_cifre(nr_cif);

    if((*this).semn != x.get_semn() && ((*this).ul -> get_val()) != '0' && (x.get_ul() -> get_val() != '0'))
        z.set_semn('-');
    else
        z.set_semn('+');

    return z;
}

intreg intreg::operator+(intreg &x)
{
    if(x.get_semn() == (*this).semn)
    {
        intreg z;
        int nr_cif = 0, t = 0;

        nod *it1 = x.get_pr();
        nod *it2 = (*this).pr;

        while(it1 && it2)
        {
            t += (it1 -> get_val() - '0') + (it2 -> get_val() - '0');
            z.adauga_cifra_final(t % 10 + '0');
            t /= 10;
            nr_cif++;
            it1 = it1 -> get_urm();
            it2 = it2 -> get_urm();
        }

        while(it1)
        {
            t += (it1 -> get_val() - '0');
            z.adauga_cifra_final(t % 10 + '0');
            t /= 10;
            nr_cif++;
            it1 = it1 -> get_urm();
        }

        while(it2)
        {
            t += (it2 -> get_val() - '0');
            z.adauga_cifra_final(t % 10 + '0');
            t /= 10;
            nr_cif++;
            it2 = it2 -> get_urm();

        }
        z.set_semn((*this).semn);
        z.set_cifre(nr_cif);

        return z;
    }
    else
    {
        if((*this).cifre < x.get_cifre())
                return x + (*this);
        else if((*this).cifre >= x.get_cifre())
        {
            if((*this).cifre == x.get_cifre())
            {
                nod *i2 = x.get_ul();
                nod *i1 = (*this).ul;

                while(i1 && (i1 -> get_val() == i2 -> get_val()))
                {
                    i1 = i1 -> get_ant();
                    i2 = i2 -> get_ant();
                }

                if(i1 == NULL)
                {
                    intreg z;
                    z.adauga_cifra('0');
                    z.set_semn('+');
                    z.set_cifre(0);
                    return z;
                }
                else
                    if(i1 -> get_val() < i2 -> get_val())
                                return x + (*this);
            }

            intreg z;
            int nr_cif = 0, t = 0;

            nod *it1 = (*this).pr;
            nod *it2 = x.get_pr();

            while(it2)
            {
                int a = it1 -> get_val() - '0';
                int b = it2 -> get_val() - '0';

                if(a >= b)
                {
                    z.adauga_cifra_final(a - b + '0');
                    t = 0;
                }
                else
                {
                    z.adauga_cifra_final(10 + a - b + '0');
                    t = -1;
                }

                it1 = it1 -> get_urm();
                it2 = it2 -> get_urm();
                nr_cif++;

                if(it1 && t == -1)
                {
                    nod *itA;
                    itA = it1;

                    while(itA && itA -> get_val() == '0')
                        {
                            itA -> set_val('9');
                            itA = itA -> get_urm();
                        }

                    int c = itA -> get_val() - '0';
                    itA -> set_val(c - 1 + '0');

                    t = 0;

                }
            }

            if(it1)
            {

                int a = it1 -> get_val() - '0';
                z.adauga_cifra_final(a + '0');
                it1 = it1 -> get_urm();
                nr_cif++;
                while(it1)
                {
                    z.adauga_cifra_final(it1 -> get_val());
                    it1 = it1 -> get_urm();
                    nr_cif++;
                }
            }
            it1 = z.get_ul();
            while(it1 -> get_val() == '0')
            {
                nod *nou = it1;
                it1 = it1 -> get_ant();
                it1 -> set_urm(NULL);
                delete nou;
                nr_cif--;
            }

            z.set_ul(it1);
            z.set_semn((*this).semn);
            z.set_cifre(nr_cif);
            return z;
        }
    }
    return x;
}

intreg intreg::operator- (intreg &x)
{
    intreg a = x;

    if(a.get_semn() == '-')
    {
        a.set_semn('+');
        return ((*this) + a);
    }
    else
    {
        a.set_semn('-');
        return ((*this) + a);
    }
}

ifstream &operator >> (ifstream &stream, intreg &p)
{
    string s;
    getline(stream, s);
    int i, nr_cif = 0;

    if(int(s.size()) < 2 || (((s[0] == '+') ^ (s[0] == '-')) != 1))
    {
        g << "Datele de intrare nu sunt valide!";
        exit(0);
    }
    else
    {
        p.set_semn(s[0]);
        for(i = 1; i < int(s.size()); i++)
            {
                if(!isdigit(s[i]))
                {
                    g << "Datele de intrare nu sunt valide!";
                    exit(0);
                }
                p.adauga_cifra(s[i]);
                nr_cif++;
            }
    }

    p.set_cifre(nr_cif);

    return stream;
}

ofstream &operator <<(ofstream &stream, intreg &p)
{
    nod *it = p.get_ul();

    stream << p.get_semn();
    while(it != NULL)
    {
        stream << it -> get_val();
        it = it -> get_ant();
    }
    //stream << "\n";

    return stream;
}

bool intreg::aduna_constanta(int c)
{
    intreg aux, aux2;

    if(c >= 0)
        aux.set_semn('+');
    else
        aux.set_semn('-');

    while(c != 0)
    {
        aux.adauga_cifra(c % 10 + '0');
        c /= 10;
    }

    aux2 = (*this) + aux;
    (*this) = aux2;

    return 1;
}

#endif
