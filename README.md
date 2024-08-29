# EnDeCryptor
#1 Installation
1) Open https://wxwidgets.org/downloads/
2) Download and unzip wxWidget to path EnDeCryptor/External/wxWidget
3) Open cmd in your root folder
4) Create build folder by "mkdir build"
5) Open build folder in cmd by command "cd build"
6) Print "cmake .."
7) Print "cmake --build"
8) After that you can find exe file in path/to/your/project/build/debug

#2 Abilities
The application can encrypt and decrypt messages in three different ways: the Caesar Cipher, the Vigener cipher, and using the Public Key (RSA).

#2.1 How to encrypt or decrypt by Caesar cipher:
1) Push "Encrypt" or "Decrypt" button
2) Push "Caesars" button
3) Enter the message you want to encrypt/decrypt
4) Enter the key, it must be a number or a digit
5) You will see your encrypted/decrypted message

#2.2
How to encrypt or decrypt by Vigener cipher:
1) Push "Encrypt" or "Decrypt" button
2) Push "Vigener" button
3) Enter the message you want to encrypt/decrypt
4) Enter the keyword
5) You will see your encrypted/decrypted message

#2.3
How to encrypt or decrypt by RSA cipher:
1) Push "Encrypt" or "Decrypt" button
2) Push "RSA" button
3) Enter the message you want to encrypt/decrypt
4) If you want to encrypt, you need enter your puclic key (e), if you want to decrypt you need enter your private key
5) Enter module (n)
5) You will see your encrypted/decrypted message