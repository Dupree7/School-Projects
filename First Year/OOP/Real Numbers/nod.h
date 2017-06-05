#ifndef nod_h
#define nod_h

class nod
{
    char val;
    nod *urm, *ant;

    public:
        char get_val();
        nod* get_urm();
        nod* get_ant();
        bool set_val(char a);
        bool set_urm(nod *p);
        bool set_ant(nod *p);
};

char nod::get_val()
{
    return val;
}
nod* nod::get_urm()
{
    return urm;
}
nod* nod::get_ant()
{
    return ant;
}

bool nod::set_val(char a)
{
    return (val = a);
}

bool nod::set_urm(nod* p)
{
    return (urm = p);
}

bool nod::set_ant(nod *p)
{
    return (ant = p);
}

#endif
