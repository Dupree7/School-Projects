#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

ifstream f("real.in");
ofstream g("real.out");

#include "nod.h"
#include "intreg.h"

class real
{
    intreg a, b;

    public:
        bool set_a(intreg x);
        bool set_b(intreg x);
        intreg get_a();
        intreg get_b();
        real operator+ (real &y);
        real operator* (real &y);
        ifstream &operator >> (ifstream &stream);
        ofstream &operator << (ofstream &stream);
        real maxim(real x);
};

bool real::set_a(intreg x)
{
    nod *it = x.get_ul();
    a.set_semn(x.get_semn());
    a.set_cifre(x.get_cifre());

    while(it)
    {
        a.adauga_cifra(it -> get_val());
        it = it -> get_ant();
    }

    return 1;
}

bool real::set_b(intreg x)
{
    nod *it = x.get_ul();
    b.set_semn(x.get_semn());
    b.set_cifre(x.get_cifre());

    while(it)
    {
        b.adauga_cifra(it -> get_val());
        it = it -> get_ant();
    }
    return 1;
}

intreg real::get_a()
{
    return a;
}

intreg real::get_b()
{
    return b;
}

ifstream &operator >> (ifstream &stream, real &p)
{
    intreg x, y;

    stream >> x;
    stream >> y;

    int c = x.sterge_zero();
    y.aduna_constanta(c);

    p.set_a(x);
    p.set_b(y);

    return stream;
}

ofstream &operator << (ofstream &stream, real &p)
{
    intreg x = p.get_a(), y = p.get_b();

    stream << x << " ";// << " " << x.get_cifre() << "\n";
    stream << y;// << " " << y.get_cifre();
    stream << "\n";
    return stream;
}

real real::operator* (real &y)
{
    if((*this).a.get_ul() -> get_val() == '0' || y.get_a().get_ul() -> get_val() == '0')
    {
        intreg a, b;
        a.adauga_cifra('0');
        b.adauga_cifra('0');
        a.set_cifre(1);
        b.set_cifre(1);
        a.set_semn('+');
        b.set_semn('+');
        real r;
        r.set_a(a);
        r.set_b(b);
        return r;
    }

    real z;
    intreg A1 = (*this).a, B1 = (*this).b;
    intreg A2 = y.get_a(), B2 = y.get_b();

    intreg p = A1 * A2;
    intreg s = B1 + B2;

    z.set_a(p);
    z.set_b(s);

    return z;
}

real real::operator+ (real &y)
{
    if((*this).a.get_ul() -> get_val() == '0')
        return y;
    if(y.get_a().get_ul() -> get_val() == '0')
        return (*this);
    intreg A1, A2, B1, B2;
    intreg diferenta;
    B1 = (*this).b;
    B2 = y.get_b();

    char s1 = B1.get_semn(), s2 = B2.get_semn();
    if(s1 == s2 && s1 == '+')
    {
        diferenta = B1 - B2;
        if(diferenta.get_semn() == '-')
            return y + (*this);
    }
    else if(s1 == s2 && s1 == '-')
    {
        diferenta = B1 - B2;
        if(diferenta.get_semn() == '-')
            return y + (*this);
    }
    else
    {
        if(B1.get_semn() == '-')
            return y + (*this);
        diferenta = B1 - B2;
    }

    int nr_cif = 0;
    nod *itA = (*this).a.get_pr();

    while(itA)
    {
        A1.adauga_cifra_final(itA -> get_val());
        nr_cif++;
        itA = itA -> get_urm();
    }

    s1 = (*this).a.get_semn();
    s2 = y.get_a().get_semn();

    if(s1 != s2)
    {
        while(diferenta.get_ul() -> get_val() != '0')
        {
            A1.adauga_cifra('0');
            diferenta.aduna_constanta(-1);
            nr_cif++;
        }
    }
    else if(s1 == s2 && s1 == '+')
    {
        while(diferenta.get_ul() -> get_val() != '0')
        {
            A1.adauga_cifra('0');
            diferenta.aduna_constanta(-1);
            nr_cif++;
        }
        A2 = y.get_a();
    }
    else
    {
        A2 = y.get_a();
        while(diferenta.get_ul() -> get_val() != '0')
        {
            A1.adauga_cifra('0');
            diferenta.aduna_constanta(-1);
            nr_cif++;
        }
    }

    A1.set_semn(s1);
    A2.set_semn(s2);
    intreg nou;
    nou.set_semn(A1.get_semn());
    nou.set_cifre(nr_cif);

    A2 = y.get_a();
    nou = A1 + A2;
    real r;
    r.set_a(nou);
    r.set_b(B2);

    return r;
}

real real::maxim(real x)
{
    if(x.get_a().get_ul() -> get_val() == '0')
        {
            if((*this).a.get_semn() == '+')
                return (*this);
            else
                return x;
        }
    if((*this).a.get_ul() -> get_val() == '0')
        {
            if(x.get_a().get_semn() == '+')
                return x;
            else
                return (*this);
        }

    intreg a1 = (*this).get_a(), b1 = (*this).get_b();
    intreg a2 = x.get_a(), b2 = x.get_b();

    a1.set_semn('+');
    a2.set_semn('+');

    b1.aduna_constanta(a1.get_cifre());
    b2.aduna_constanta(a2.get_cifre());

    if(b1.get_semn() == b2.get_semn() && b1.get_semn() == '+')
    {
        intreg rezultat = b1 - b2;

        if(rezultat.get_semn() == '-')
            {
                b2.aduna_constanta(-a2.get_cifre());
                    return x;
            }
        else
        {
            if(rezultat.get_ul() -> get_val() != '0')
                {
                    b1.aduna_constanta(-a1.get_cifre());
                    return (*this);
                }
            else
            {
                intreg rezultat2 = a1 - a2;
                if(rezultat2.get_semn() == '+')
                    {
                        b1.aduna_constanta(-a1.get_cifre());
                        return (*this);
                    }
                else
                    {
                        b2.aduna_constanta(-a2.get_cifre());
                        return x;
                    }
            }
        }
    }
    else if(b1.get_semn() == b2.get_semn() && b1.get_semn() == '-')
    {
        intreg rezultat = b1 - b2;

        if(rezultat.get_semn() == '-')
            {
                b2.aduna_constanta(-a2.get_cifre());
                return x;
            }
        else
        {
            if(rezultat.get_ul() -> get_val() != '0')
                {
                    b1.aduna_constanta(-a1.get_cifre());
                    return (*this);
                }
            else
            {
                intreg rezultat2 = a1 - a2;
                if(rezultat2.get_semn() == '+')
                    {
                        b2.aduna_constanta(-a2.get_cifre());
                        return x;
                    }
                else
                    {
                        b1.aduna_constanta(-a1.get_cifre());
                        return (*this);
                    }
            }
        }
    }
    else if(b1.get_semn() != b2.get_semn())
    {
        if(b1.get_semn() == '+')
            {
                b1.aduna_constanta(-a1.get_cifre());
                return (*this);
            }
        else
            {
               b2.aduna_constanta(-a2.get_cifre());
                return x;
            }
    }

    return x;
}

int main()
{
    real r1, r2;

    f >> r1 >> r2;
    g << "r1 = ";
    g << r1;
    g << "r2 = ";
    g << r2;
    real produs, suma, maxim;
    produs = r1 * r2;
    g << "produs = ";
    g << produs;
    suma = r1 + r2;
    g << "suma = ";
    g << suma;
    maxim = r1.maxim(r2);
    g << "maxim = ";
    g << maxim;
    return 0;
}
