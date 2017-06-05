#include <iostream>
#include <cmath>
#include <typeinfo>
#include <vector>

using namespace std;

struct Move
{
    int c_line, n_line;
    char c_col, n_col;
};

class Piece
{
    protected:
        char name;
        int color;
    public:
        virtual bool check_move(int, int, int, int, Piece***&) = 0;
        int get_color()
        {
            return color;
        }
        char get_name()
        {
            return name;
        }
        virtual ~Piece(){};
};

class King : public Piece
{
    public:
        King(int color2)
        {
            if(color2 == 1)
                name = 'K';
            else
                name = 'k';

            color = color2;
        }

        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(abs(cur_l - next_l) > 1 || abs(cur_c - next_c) > 1)
            {
                cout << "Regele nu poate fi mutat pe noua pozitie!\n";
                return 0;
            }
            if(t[next_l][next_c] -> get_color() == color)
            {
                cout << "Pe noua pozitie este o piesa de aceeasi culoare!\n";
                return 0;
            }

            return 1;
        }
};

class Queen : public Piece
{
    public:
        Queen(int colorr)
        {
            if(colorr == 1)
                name = 'Q';
            else
                name = 'q';
            colorr = color;
        }
        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(t[next_l][next_c] -> get_color() == color)
            {
                cout << "Regina nu poate fi mutata pe noua pozitie!\n";
                return 0;
            }

            if(cur_c == next_c)
            {
                if(cur_l > next_l)
                    while(cur_l != next_l)
                    {
                        cur_l--;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                else
                    while(cur_l != next_l)
                    {
                        cur_l++;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                }
                else if(cur_l == next_l)
                {
                    if(cur_c > next_c)
                        while(cur_c != next_c)
                        {
                            cur_c--;
                            if(t[cur_l][cur_c] -> get_color() != 0)
                            {
                                cout << "O alta piesa este in drumul reginei!\n";
                                return 0;
                            }
                        }
                    else
                        while(cur_c != next_c)
                        {
                            cur_c++;
                            if(t[cur_l][cur_c] -> get_color() != 0)
                            {
                                cout << "O alta piesa este in drumul reginei!\n";
                                return 0;
                            }
                        }
                }
                else if(next_l > cur_l && next_c > cur_c)
                {
                    while(next_l != cur_l && next_c != cur_c)
                    {
                        cur_l++;
                        cur_c++;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                }
                else if(next_l > cur_l && next_c < cur_c)
                {
                    while(next_l != cur_l && next_c != cur_c)
                    {
                        cur_l++;
                        cur_c--;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                }
                else if(next_l < cur_l && next_c < cur_c)
                {
                    while(next_l != cur_l && next_c != cur_c)
                    {
                        cur_l--;
                        cur_c--;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                }
                else if(next_l < cur_l && next_c > cur_c)
                {
                    while(next_l != cur_l && next_c != cur_c)
                    {
                        cur_l--;
                        cur_c++;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "O alta piesa este in drumul reginei!\n";
                            return 0;
                        }
                    }
                }

                if(next_l != cur_l || next_c != cur_c)
                {
                    cout << "Regina nu poate fi mutata pe noua pozitie!\n";
                    return 0;
                }

                return 1;
            }
};

class Rook : public Piece
{
    public:
        Rook(int colorr)
        {
            if(colorr == 1)
                name = 'R';
            else
                name = 'r';
            color = colorr;
        }
        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(t[next_l][next_c] -> get_color() == color)
            {
                cout << "Tura nu poate fi mutata pe noua pozitie!\n";
                return 0;
            }
            else if(cur_l != next_l && cur_c != next_c)
            {
                cout << "Tura nu poate fi mutata pe noua pozitie!\n";
            }

            if(cur_l == next_l)
            {
                if(cur_c > next_c)
                    while(cur_c != next_c)
                    {
                        cur_c--;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "Tura nu poate fi mutata pe noua pozitie!\n";
                            return 0;
                        }
                    }
                else
                    while(cur_c != next_c)
                    {
                        cur_c ++;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "Tura nu poate fi mutata pe noua pozitie!\n";
                            return 0;
                        }
                    }
            }
            else if(cur_c == next_c)
            {
                if(cur_l > next_l)
                    while(cur_l != next_l)
                    {
                        cur_l--;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "Tura nu poate fi muatata pe noua pozitie!\n";
                            return 0;
                        }
                    }
                else
                    while(cur_l != next_l)
                    {
                        cur_l++;
                        if(t[cur_l][cur_c] -> get_color() != 0)
                        {
                            cout << "Tura nu poate fi muatata pe noua pozitie!\n";
                            return 0;
                        }
                    }
            }

            if(t[cur_l][cur_c] -> get_color() == color)
            {
                cout << "Tura nu poate fi muatata pe noua pozitie!\n";
                return 0;
            }

            return 1;
        }
};

class Knight : public Piece
{
    public:
        Knight(int colorr)
        {
            if(colorr == 1)
                name = 'C';
            else
                name = 'c';
            color = colorr;
        }

        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(cur_l + 2 == next_l)
            {
                if(cur_c + 1 == next_c)
                {
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
                else if(cur_c - 1 == next_c)
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
            }
            else if(cur_l - 2 == next_l)
            {
                if(cur_c + 1 == next_c)
                {
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
                else if(cur_c - 1 == next_c)
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
            }
            else if(cur_c + 2 == next_c)
            {
                if(cur_l + 1 == next_l)
                {
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
                else if(cur_l - 1 == next_l)
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
            }
            else if(cur_c - 2 == next_c)
            {
                if(cur_l + 1 == next_l)
                {
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
                else if(cur_l - 1 == next_l)
                    if(t[next_l][next_c] -> get_color() == color)
                    {
                        cout << "Calul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
            }

            return 1;
        }
};

class Bishop : public Piece
{
    public:
        Bishop(int colorr)
        {
            if(colorr == 1)
                name = 'B';
            else
                name = 'b';
            color = colorr;
        }

        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(next_l > cur_c && next_c > cur_c)
                while(next_l != cur_l && next_c != cur_c)
                {
                    cur_l++;
                    cur_c++;
                    if(t[cur_l][cur_c] -> get_color() != 0)
                    {
                        cout << "Nebunul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
            else if(next_l < cur_l && next_c < cur_c)
                while(next_l != cur_l && next_c != cur_c)
                {
                    cur_l--;
                    cur_c--;
                    if(t[cur_l][cur_c] -> get_color() != 0)
                    {
                        cout << "Nebunul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
            else if(next_l < cur_l && next_c > cur_c)
                while(next_l != cur_l && next_c != cur_c)
                {
                    cur_l--;
                    cur_c++;
                    if(t[cur_l][cur_c] -> get_color() != 0)
                    {
                        cout << "Nebunul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }
            else if(next_l > cur_l && next_c < cur_c)
                while(next_l != cur_l && next_c != cur_c)
                {
                    cur_l++;
                    cur_c--;
                    if(t[cur_l][cur_c] -> get_color() != 0)
                    {
                        cout << "Nebunul nu poate fi mutat pe noua pozitie!\n";
                        return 0;
                    }
                }

            if(cur_l != next_l || cur_c != next_c)
            {
                cout << "Nebunul nu poate fi mutat pe noua pozitie!\n";
                return 0;
            }
            return 1;
        }
};

class Pawn : public Piece
{
    public:
        Pawn(int colorr)
        {
            if(colorr == 1)
                name = 'P';
            else
                name = 'p';
            color = colorr;
        }

        bool check_move(int cur_l, int cur_c, int next_l, int next_c, Piece***& t)
        {
            if(cur_l < 1 || cur_l > 8 || cur_c < 1 || cur_c > 8 || next_l < 1 || next_l > 8 || next_c < 1 || next_c > 8)
            {
                cout << "Mutarea este invalida!\n";
                return 0;
            }
            cur_l--;
            cur_c--;
            next_l--;
            next_c--;

            if(color == 1)
            {
                if(next_l < cur_l)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie1!\n";
                    return 0;
                }
                else if(abs(cur_c - next_c) > 1)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie2!\n";
                    return 0;
                }
                else if(cur_l == 1 && abs(cur_l - next_l) > 2)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie3!\n";
                    return 0;
                }
                else if(cur_l != 1 && abs(cur_l - next_l) > 1)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie4!\n";
                    return 0;
                }

                if(t[next_l][next_c] -> get_color() == color)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie5!\n";
                    return 0;
                }

                return 1;
            }
            else
                {
                if(next_l > cur_l)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie!\n";
                    return 0;
                }
                if(abs(cur_c - next_c) > 1)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie!\n";
                    return 0;
                }
                else if(cur_l == 6 && abs(cur_l - next_l) > 2)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie!\n";
                    return 0;
                }
                else if(cur_l != 6 && abs(cur_l - next_l) > 1)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie!\n";
                    return 0;
                }

                if(t[next_l][next_c] -> get_color() == color)
                {
                    cout << "Pionul nu poate fi mutat pe noua pozitie!\n";
                    return 0;
                }

                return 1;
            }
        }
};

class NullPiece : public Piece
{
    public:
        NullPiece()
        {
            color = 0;
            name = 'x';
        }
        bool check_move(int x, int y, int z, int w, Piece***& t)
        {
            cout << "Nu exista nici o piesa pe aceasta pozitie!\n";
            return 0;
        }
};
class CTable
{
    protected:
        int turn, moveNr;
        vector<Move> MoveList[2];
    public:
        static Piece*** table;
        CTable()
        {
            turn = 1;
            moveNr = 0;
            //cout<<"sdfdaf";
        }

        void show_table()
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                    cout << table[i][j] -> get_name() << " ";
                cout << "\n";
            }
        }

        bool check_for_chess();

        bool add_move(int cur_l, char cur_c, int next_l, char next_c)
        {
            int c1 = cur_c - 'a' + 1;
            int c2 = next_c - 'a' + 1;

            if(table[cur_l - 1][c1 - 1] -> get_name() == 'x')
            {
                cout << "Nu este nici o piesa pe pozitia respectiva!\n";
                return 0;
            }

            char k = table[cur_l - 1][c1 - 1] -> get_name();

            if(turn == 1)
            {
                if (k != toupper(k))
                    {
                        cout << "Nu este randul jucatorului 1!\n";
                        return 0;
                    }
            }

            if(turn == 2)
            {
                if(k != tolower(k))
                    {
                        cout << "Nu este randul jucatorului 2! \n";
                        return 0;
                    }
            }

            if(table[cur_l - 1][c1 - 1] -> check_move(cur_l, c1 , next_l, c2, table))
            {
                cur_l--;
                c1--;
                next_l--;
                c2--;

                Piece* aux = table[next_l][c2];
                table[next_l][c2] = table[cur_l][c1];
                table[cur_l][c1] = aux;
                delete table[cur_l][c1];
                table[cur_l][c1] = new NullPiece;

                Move newmove;
                newmove.c_col = c1 + 'a';
                newmove.c_line = cur_l + 1;
                newmove.n_col = c2 + 'a';
                newmove.n_line = next_l + 1;

                MoveList[turn - 1].push_back(newmove);

                if(turn == 2)
                {
                    turn = 1;
                    moveNr++;
                }
                else if(turn == 1)
                {
                    turn = 2;
                }

                return 1;
            }

            return 0;
        }

        bool print_movelist()
        {
            for(int i = 0; i < MoveList[0].size(); i++)
            {
                cout << i + 1 << ". ";
                cout << MoveList[0][i].c_col << MoveList[0][i].c_line << " " << MoveList[0][i].n_col << MoveList[0][i].n_line << " - ";

                if(i != moveNr)
                    cout << MoveList[1][i].c_col << MoveList[1][i].c_line << " " << MoveList[1][i].n_col << MoveList[1][i].n_line << "\n";

            }
            return 1;
        }
};

static Piece*** create_table()
{
    int i, j;
    Piece*** p;

    p = new Piece**[8];
    for(i = 0; i < 8; i++)
        p[i] = new Piece*[8];

    for(i = 2; i < 6; i++)
        for(j = 0; j < 8; j++)
            p[i][j] = new NullPiece;

    p[0][0] = new Rook(1);
    p[0][7] = new Rook(1);
    p[0][1] = new Knight(1);
    p[0][6] = new Knight(1);
    p[0][2] = new Bishop(1);
    p[0][5] = new Bishop(1);
    p[0][4] = new Queen(1);
    p[0][3] = new King(1);

    for(i = 0; i < 8; i++)
        p[1][i] = new Pawn(1);

    for(i = 0; i < 8; i++)
        p[6][i] = new Pawn(2);

    p[7][0] = new Rook(2);
    p[7][7] = new Rook(2);
    p[7][1] = new Knight(2);
    p[7][6] = new Knight(2);
    p[7][2] = new Bishop(2);
    p[7][5] = new Bishop(2);
    p[7][4] = new Queen(2);
    p[7][3] = new King(2);

    return p;
}

Piece*** CTable:: table = create_table();


int main()
{
    CTable T;

    T.add_move(2, 'a', 4, 'a');
    T.add_move(7, 'b', 5, 'b');
    T.add_move(4, 'a', 5, 'b');
    T.show_table();
    T.print_movelist();

    return 0;
}
