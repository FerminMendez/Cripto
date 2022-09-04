#include <bitset>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "math.h"
#include "Hex.h"
#include "Block.h"

using namespace std;

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
	// //cout << "TRANSLATE" << endl;
	for (auto it : blocks)
	{
		it->translate();
	}
	//cout << endl;
}

void translateBlocksInt(vector<Block *> &blocks)
{
	// //cout << "TRANSLATE" << endl;
	for (auto it : blocks)
	{
		it->translateInt();
	}
	//cout << endl;
}

void alg1(vector<Block *> &blocks)
{
	//cout << "Algoritmo 1" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// Initial
		// //cout << "Bloque " << i << endl;
		// it->print();

		// Encrypt
		// it->swapCol(0, 1);
		// it->print();

		it->sumRow(1, 253);
		// it->print();
		//  Decrypt

		i++;
	}
}

void decryptalg1(vector<Block *> &blocks)
{
	//cout << "Decrypt 1: ";
	//cout << "" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// Initial
		// //cout << "Bloque " << i << endl;
		// it->print();

		it->sumRow(1, 256 - 253);
		// it->print();

		// it->swapCol(0, 1);
		//  it->print();

		i++;
	}
}

void alg2(vector<Block *> &blocks)
{
	//cout << "Algoritmo 2: ";
	//cout << "Rotar" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// INITIAL
		// //cout << "Bloque " << i << endl;
		// it->print();
		//  Encrypt
		// //cout << "Rotada" << endl;
		it->rotation();
		// it->print();
		i++;
	}
}

void decryptalg2(vector<Block *> &blocks)
{
	//cout << "Decrypt 2" << endl;

	int i = 1;
	for (auto it : blocks)
	{
		// INITIAL
		// //cout << "Bloque " << i << endl;
		// it->print();
		//  Encrypt
		it->invRotation();
		// it->print();

		i++;
	}
}

void alg3(vector<Block *> &blocks, Block clave)
{
	//cout << "Algoritmo 3: ";
	//cout << "Sumar clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// INITIAL
		// //cout << "Bloque " << i << endl;
		// it->print();
		//  Encrypt
		it->sumBlock(clave);
		// it->print();
		i++;
	}
}

void decryptalg3(vector<Block *> &blocks, Block clave)
{
	//cout << "Decrypt 3: ";
	//cout << "Restar clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// INITIAL
		// //cout << "Bloque " << i << endl;
		// it->print();
		//  Encrypt

		it->subsBlock(clave);
		// it->print();
		i++;
	}
}

void alg4(vector<Block *> &blocks, Block clave)
{
	//cout << "Algoritmo 4: ";
	//cout << "XOR clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		// INITIAL
		// //cout << "Bloque " << i << endl;
		// it->print();
		//  Encrypt
		it->xorBlock(clave);
		// it->print();
		i++;
	}
}

void decryptalg4(vector<Block *> &blocks, Block clave)
{
	//cout << "Decrypt 4: ";
	//cout << "XOR clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		it->xorBlock(clave);
		i++;
	}
}


void alg5(vector<Block *> &blocks)
{
	//cout << "Algoritmo 5: ";
	//cout << "XOR clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		it->transpuestaDifusion();
		i++;
	}
}

void decryptalg5(vector<Block *> &blocks)
{
	//cout << "Decrypt 4: ";
	//cout << "XOR clave" << endl;
	int i = 1;
	for (auto it : blocks)
	{
		it->transpuestaDifusion();
		i++;
	}
}

void roundEncrypt(vector<Block *> &blocks, Block clave){
	alg1(blocks);
	alg2(blocks);
	alg3(blocks,clave);
	alg4(blocks,clave);
	alg5(blocks);
}

void roundDesencrypt(vector<Block *> &blocks, Block clave){
	decryptalg5(blocks);
	decryptalg4(blocks, clave);
	decryptalg3(blocks, clave);
	decryptalg2(blocks);
	decryptalg1(blocks);
	
}

int main()
{
	// Blocks es una clase para manejar las matrices de bytes que nos piden

	// Mensaje que se va a mandar
	string texto = "hola soy yo";
	string str_clave = "UnoDosTresCuatr"; // Tiene que ser de 16 caracteres
	Block clave(str_clave);
	vector<Block *> blocks; // Vector de apuntado de bloques de 128 bytes
	createBlocks(blocks, texto);
	
	cout<<"Mensaje original: ";
	translateBlocks(blocks);
	cout<<endl;
	for (int i=0;i<10;i++){
		roundEncrypt(blocks,clave);
	}
	cout<<"Mensaje Encriptado en texto: ";
	translateBlocks(blocks);
	cout<<endl;
	cout<<"Mensaje Encriptado en enteros:"<<endl;
	translateBlocksInt(blocks);

	for (int i=0;i<10;i++){
		roundDesencrypt(blocks,clave);
	}
	cout<<"Mensaje Desencriptado: ";
	translateBlocks(blocks);


	deleteBlocks(blocks); // Es para liberar el espacio de la memoria dinamica wuu

	return 0;
}

// Arreglar suma
