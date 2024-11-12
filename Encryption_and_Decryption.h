#ifndef Encryption_Decryption  // checks if Encryption_Decryption is defined or not
#define Encryption_Decryption  // define Encryption_Decryption

class Encryption_and_Decryption
{
 protected:
    Encryption_and_Decryption(){ }

    void encrypt(string &password);

    void decrypt(string &password);

    ~Encryption_and_Decryption(){ } // Destructor of Encryption and Decryption
};
void Encryption_and_Decryption:: encrypt(string &password)
{
        int len = password.length();
        for (int i = 0; i < len; i++)
        {
            if (i % 2 == 1)
            {
                password[i] += -10;
            }
            else
            {
                password[i] += -11;
            }
        }
}
void Encryption_and_Decryption:: decrypt(string &password)
{
        int len = password.length();
        for (int i = 0; i < len; i++)
        {
            if (i % 2 == 1)
            {
                password[i] += 10;
            }
            else
            {
                password[i] += 11;
            }
        }
}
#endif  // end of definition