#ifndef CRYPTO_H
#define CRYPTO_H
using namespace std;

#include <string>
#include <vector>
#include <cctype>
#include <iostream>

enum UniCode
{
	Length_Eng_Alp = 26
};
char Cezar(bool encrypt, char letter, short key);

string ProcessStringForCezar(const string& text, short key, bool encrypt);
string Vigenere(const string& text, const string& keyword, bool encrypt);

void GenerateKeys(long long& n, long long& e, long long& d);

long long Calculate_greatest_common_divisor(long long a, long long b);
long long ModInverse(long long e, long long phi);
long long ModExp(long long base, long long exp, long long mod);

string DecryptionRSA(const vector<long long>& encryptedMessage, long d, long n);
vector<long long> EncryptionRSA(const string& message, long e, long n);
vector<long long> SplitStringToNumbers(const string& message);
#endif
