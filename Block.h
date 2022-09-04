#ifndef BLOCK
#define BLOCK

#include <bitset>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "math.h"
#include "Hex.h"
using namespace std;

class Block
{
public:
    Hex mat[4][4]; // String hexadecimales
    void print();

    Block(){};
    Block(string s); // Construcotr
    Block(Hex init_mat[4][4]);
    void swapCol(int i, int j); // i y j entre 0 y 3
    void swapRow(int i, int j);

    void sumCol(int i, int x); // i y j entre 0 y 3
    void sumRow(int i, int x);
    void subsCol(int i, int x); // i y j entre 0 y 3
    void subsRow(int i, int x);

    void rotation();
    void invRotation();

    void transpuestaDifusion();
    //void revertirBinarioConfusion();
    //void multiplicacionClaveConfusion();

    void sumBlock(Block b);
    void subsBlock(Block b);
    void xorBlock(Block b);

    string translate();
    string translateInt();

private:
    void swap(int x1, int y1, int x2, int y2);
    void sum(int i, int j, int x);
    void sum(int i, int j, Hex h);
    void subs(int i, int j, int x);
    void subs(int i, int j, Hex h);
};

Block ::Block(string s)
{
    for (int i = 0; i < 16; ++i)
    {
        Hex x(s[i]);
        mat[i / 4][i % 4] = x;
    }
    /*
    stringstream ss;
    for (int i = 0; i < 16; ++i)
    {
        ss << hex << (int)s[i];
        mat[i / 4][i % 4] = ss.str();

    }
    */
}

Block ::Block(Hex init_mat[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat[i][j] = init_mat[i][j];
        }
    }
}

void Block::swap(int x1, int y1, int x2, int y2)
{
    Hex t = mat[x1][y1];
    mat[x1][y1] = mat[x2][y2];
    mat[x2][y2] = t;
}

void Block::sum(int i, int j, int x)
{
    // x = x % 256;
    mat[i][j] = (mat[i][j])+x;
}

void Block::subs(int i, int j, int x)
{
    // x = x % 256;
    mat[i][j] = (mat[i][j])-x;
}

void Block::sum(int i, int j, Hex h)
{
    mat[i][j] = (mat[i][j]) + h;
}

void Block::subs(int i, int j, Hex h)
{
    mat[i][j] = (mat[i][j]) - h;
}

void Block::swapCol(int i, int j)
{
    for (int k = 0; k < 4; k++)
    {
        swap(k, i, k, j);
    }
}

void Block::swapRow(int i, int j)
{
    for (int k = 0; k < 4; k++)
    {
        swap(i, k, j, k);
    }
}

void Block::sumCol(int i, int x)
{
    for (int k = 0; k < 4; k++)
    {
        sum(i, k, x);
    }
}

void Block::subsCol(int i, int x)
{
    for (int k = 0; k < 4; k++)
    {
        subs(i, k, x);
    }
}

void Block::sumRow(int i, int x)
{
    for (int k = 0; k < 4; k++)
    {
        sum(k, i, x);
    }
}

void Block::subsRow(int i, int x)
{
    for (int k = 0; k < 4; k++)
    {
        subs(k, i, x);
    }
}


void Block::rotation()
{
    Hex aux = mat[1][1];
    mat[1][1] = mat[2][1];
    mat[2][1] = mat[2][2];
    mat[2][2] = mat[1][2];
    mat[1][2] = aux;

    aux = mat[0][0];
    mat[0][0] = mat[0][1];
    mat[0][1] = mat[0][2];
    mat[0][2] = mat[0][3];
    mat[0][3] = mat[1][3];
    mat[1][3] = mat[2][3];
    mat[2][3] = mat[3][3];
    mat[3][3] = mat[3][2];
    mat[3][2] = mat[3][1];
    mat[3][1] = mat[3][0];
    mat[3][0] = mat[2][0];
    mat[2][0] = mat[1][0];
    mat[1][0] = aux;
}

/*      0    1   2   3
    0   x <- x <-x <-x
    1   x    x <-x   x
    2   x    x ->x   x
    3   x -> x ->x ->x


*/
void Block::invRotation()
{
    Hex aux = mat[2][1];
    mat[2][1] = mat[1][1];
    mat[1][1] = mat[1][2];
    mat[1][2] = mat[2][2];
    mat[2][2] = aux;

    aux = mat[0][0];
    mat[0][0] = mat[1][0];
    mat[1][0] = mat[2][0];
    mat[2][0] = mat[3][0];
    mat[3][0] = mat[3][1];
    mat[3][1] = mat[3][2];
    mat[3][2] = mat[3][3];
    mat[3][3] = mat[2][3];
    mat[2][3] = mat[1][3];
    mat[1][3] = mat[0][3];
    mat[0][3] = mat[0][2];
    mat[0][2] = mat[0][1];
    mat[0][1] = aux;
}

void Block::print()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << mat[i][j].getHex() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string Block::translate()
{
    string s;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            s.push_back((char)(int)strtol(mat[i][j].getHex().c_str(), NULL, 16));
        }
    }
    cout << s;
    return s;
}

string Block::translateInt()
{
    string s;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout<<mat[i][j].hex_to_int()<<" ";
            s=mat[i][j].hex_to_int()+" ";
        }
        s+="\n";
    }
    s+="\n";;
    cout << s<<endl;
    return s;
}

void Block::sumBlock(Block b){
     for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           mat[i][j] = mat[i][j] + b.mat[i][j];
        }
    
    }
}

void Block::subsBlock(Block b){
     for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           mat[i][j] = mat[i][j] - b.mat[i][j];
        }
    
    }
}

void Block::xorBlock(Block b){
     for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           mat[i][j] = mat[i][j] ^ b.mat[i][j];
        }
    
    }
}

void Block::transpuestaDifusion() {
	Hex db[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			db[i][j] = mat[j][i];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = db[i][j];
		
		}
	}
}


#endif
