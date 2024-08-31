#include "Crypto.h"

char Cezar(bool encrypt, char letter, short key)
{
    if (isalpha(letter))
    {
        char base = isupper(letter) ? 'A' : 'a';
        key = key % Length_Eng_Alp;
        if (encrypt)
        {
            letter = base + ((letter - base + key) % Length_Eng_Alp);
        }
        else
        {
            letter = base + ((letter - base - key + Length_Eng_Alp) % Length_Eng_Alp);
        }
    }
    return letter;
}

string ProcessStringForCezar(const string& text, short key, bool encrypt) {
    string result;
    result.reserve(text.size());
    for (char letter : text) {
        result += Cezar(encrypt, letter, key);
    }
    return result;
}

string Vigenere(const string& text, const string& key, bool encrypt)
{
    string result;
    int keyLength = key.length();

    for (int i = 0; i < text.length(); ++i) {
        char letter = text[i];

        char keyChar = key[i % keyLength];

        if (isupper(letter)) {
            keyChar = toupper(keyChar);
        }
        else {
            keyChar = tolower(keyChar);
        }

        int keyShift = (isupper(keyChar) ? keyChar - 'A' : keyChar - 'a');

        if (isalpha(letter)) {
            char base = isupper(letter) ? 'A' : 'a';
            if (encrypt) {
                letter = (letter - base + keyShift) % Length_Eng_Alp + base;
            }
            else {
                letter = (letter - base - keyShift + Length_Eng_Alp) % Length_Eng_Alp + base;
            }
        }
        result += letter;
    }
    return result;
}

//For RSA
//greatest common divisor - gcd;
long long CalculateGreatestCommonDivisor(long long a, long long b) // function for 2 numbers 
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long ModInverse(long long key_publ_e, long long phi)
{
    long long m0 = phi, t, q;
    long long x0 = 0, x1 = 1;

    // If a and m are not mutually simple, then there is no modular inverse
    if (CalculateGreatestCommonDivisor(key_publ_e, phi) != 1)
        return -1;

    while (key_publ_e > 1) {
        // q - quotient 
        q = key_publ_e / phi;

        // Updating phi and e
        t = phi;
        phi = key_publ_e % phi;
        phi = t;

        // Updating x0 and x1
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}
long long ModExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod; // for working with the lower numbers
    while (exp)
    {
        if (exp & 0x01)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void GenerateKeys(long long& key_n, long long& key_publ_e, long long& key_priv_d)
{
    long long p = 4877;
    long long q = 5147;
    key_n = p * q;
    long long phi = (p - 1) * (q - 1); //Eiler function 

    key_publ_e = 2;
    while (key_publ_e < phi) // looking for a public key, but it must be mutually prime numbers with phi
    {
        if (CalculateGreatestCommonDivisor(key_publ_e, phi) == 1)
            break;
        else
            key_publ_e++;
    }

    key_priv_d = ModInverse(key_publ_e, phi); // the number d is a private key and is such that d is a multiplicative inverse modulo phi

}

vector<long long> EncryptionRSA(const string& message, long key_publ_e, long key_n) {
    vector<long long> encryptedMessage;
    for (char ch : message) {
        long long m = static_cast<long long>(ch);
        encryptedMessage.push_back(ModExp(m, key_publ_e, key_n));
    }
    return encryptedMessage;
}
vector<long long> SplitStringToNumbers(const string& message) {
    vector<long long> clearText;
    string number;

    for (char ch : message) {
        if (ch == ' ') {
            if (!number.empty()) {
                clearText.push_back(stoll(number));
                number.clear();
            }
        }
        else {
            number += ch;
        }
    }

    if (!number.empty()) {
        clearText.push_back(stoll(number));
    }

    return clearText;
}

string DecryptionRSA(const vector<long long>& encryptedMessage, long key_priv_d, long key_n) {
    string decryptedMessage{};
    for (long long c : encryptedMessage) {
        long long m = ModExp(c, key_priv_d, key_n);
        decryptedMessage.push_back(static_cast<char>(m));
    }
    return decryptedMessage;
}

