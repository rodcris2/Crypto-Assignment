#ifndef CRYPTO_H
#define CRYPTO_H
#include <iostream>
#include <string>
using namespace std;

class Crypto {
private:
	char InputDataBuffer[129];
	char CryptoKey[9];
	char CryptoMatrix[129];
	char ClearMatrix[129];
	short InputDataCount;

public:
	void InputData();
	void Encrypt();
	void Decrypt();
	void DisplayCryptoMatrix();
	void DisplayClearMatrix();
};
#endif