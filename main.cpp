#include <bitset>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Block
{
public:
	string mat[4][4]; // String hexadecimales
	void print();
	Block(string s); // Construcotr

	void swapCol(int i, int j); // i y j entre 0 y 3
	void swapRow(int i, int j);
	void sumCol(int i, int x); // i y j entre 0 y 3
	void sumRow(int i, int x);

	void rotation();
	void invRotation();

	void rotacionDiagnoalDifusion();
	void revertirBinarioConfusion();
	void multiplicacionClaveConfusion();

	string translate();

private:
	void swap(int x1, int y1, int x2, int y2);
	void sum(int i, int j, int x);
};

Block ::Block(string s)
{
	stringstream ss;
	for (int i = 0; i < 16; ++i)
	{
		ss << hex << (int)s[i];
		mat[i / 4][i % 4] = ss.str();
		ss.str("");
	}
}

void Block::swap(int x1, int y1, int x2, int y2)
{
	string t = mat[x1][y1];
	mat[x1][y1] = mat[x2][y2];
	mat[x2][y2] = t;
}

void Block::sum(int i, int j, int x)
{
	//x = x % 256;
	mat[i][j] = to_string(x) + (mat[i][j]);
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

void Block::sumRow(int i, int x)
{
	for (int k = 0; k < 4; k++)
	{
		sum(k, i, x);
	}
}

void Block::rotation()
{
	string aux=mat[1][1];
	mat[1][1]=mat[2][1];
	mat[2][1]=mat[2][2];
	mat[2][2]=mat[1][2];
	mat[1][2]=aux;

	aux=mat[0][0];
	mat[0][0]=mat[0][1];
	mat[0][1]=mat[0][2];
	mat[0][2]=mat[0][3];
	mat[0][3]=mat[1][3];
	mat[1][3]=mat[2][3];
	mat[2][3]=mat[3][3];
	mat[3][3]=mat[3][2];
	mat[3][2]=mat[3][1];
	mat[3][1]=mat[3][0];
	mat[3][0]=mat[2][0];
	mat[2][0]=mat[1][0];
	mat[1][0]=aux;

}

/*      0    1   2   3
	0   x <- x <-x <-x
	1   x    x <-x   x 
	2   x    x ->x   x
	3   x -> x ->x ->x


*/
void Block::invRotation()
{
	string aux=mat[2][1];
	mat[2][1]=mat[1][1];
	mat[1][1]=mat[1][2];
	mat[1][2]=mat[2][2];
	mat[2][2]=aux;
	

	aux=mat[0][0];
	mat[0][0]=mat[1][0];
	mat[1][0]=mat[2][0];
	mat[2][0]=mat[3][0];
	mat[3][0]=mat[3][1];
	mat[3][1]=mat[3][2];
	mat[3][2]=mat[3][3];
	mat[3][3]=mat[2][3];
	mat[2][3]=mat[1][3];
	mat[1][3]=mat[0][3];
	mat[0][3]=mat[0][2];
	mat[0][2]=mat[0][1];
	mat[0][1]=aux;
}



void Block::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << mat[i][j] << " ";
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
			s.push_back((char)(int)strtol(mat[i][j].c_str(), NULL, 16));
		}
	}
	cout << s;
	return s;
}

void createBlocks(vector<Block *> &blocks, string msg)
{
	int p = 0;
	int last = msg.size() - 1;
	while (last - p >= 16)
	{
		Block *newlBlock = new Block(msg.substr(p, 16));
		blocks.push_back(newlBlock);
		p += 16;
	}

	if (last - p > 0)
	{
		for (int i = 0; i < 16 - (last - p); i++)
		{
			msg += " ";
		}
		Block *newlBlock = new Block(msg.substr(p, 16));
		blocks.push_back(newlBlock);
	}
}

void deleteBlocks(vector<Block *> &blocks)
{
	for (auto it : blocks)
	{
		delete it;
	}
}

void translateBlocks(vector<Block *> &blocks)
{
	cout << "TRANSLATE" << endl;
	for (auto it : blocks)
	{
		it->translate();
	}
}

void alg1(vector<Block *> &blocks)
{
	int i = 1;
	for (auto it : blocks)
	{
		//Initial
		cout << "Bloque " << i << endl;
		it->print();

		//Encrypt
		it->swapCol(0, 1);
		it->print();
		
		it->sumRow(1,253);
		it->print();
		//Decrypt
	

		i++;
	}
}

void decryptalg1(vector<Block *> &blocks)
{
	int i = 1;
	for (auto it : blocks)
	{
		//Initial
		cout << "Bloque " << i << endl;
		it->print();

		it->sumRow(1,-253);
		it->print();

		it->swapCol(0, 1);
		it->print();

		i++;
	}
}

void alg2(vector<Block *> &blocks)
{
	int i = 1;
	for (auto it : blocks)
	{
		//INITIAL
		cout << "Bloque " << i << endl;
		it->print();
		//Encrypt
		cout<<"Rotada"<<endl;
		it->rotation();
		it->print();
		i++;
	}
}

void decryptalg2(vector<Block *> &blocks)
{
	int i = 1;
	for (auto it : blocks)
	{
		//INITIAL
		cout << "Bloque " << i << endl;
		it->print();
		//Encrypt
		it->invRotation();
		it->print();

		i++;
	}
}


int main()
{
	// Blocks es una clase para manejar las matrices de bytes que nos piden

	// Mensaje que se va a mandar
	string texto = "hola soy yo";
	vector<Block *> blocks; // Vector de apuntado de bloques de 128 bytes
	createBlocks(blocks,texto);
	// Separa la palabra en bloques de 16 caracteres y llena blocks

	//cout<<"Algoritmo 1"<<endl;
	//alg1(blocks);
	//cout<<"Decrypt Algoritmo 1"<<endl;
	//decryptalg1(blocks);
	cout<<"Algoritmo 2"<<endl;
	alg2(blocks);
	cout<<"Decrypt Algoritmo 2"<<endl;
	decryptalg2(blocks);


	translateBlocks(blocks); // Imprime el que esta guardado actualmente en Blocks

	deleteBlocks(blocks); // Es para liberar el espacio de la memoria dinamica wuu

	return 0;
}

//Arreglar suma