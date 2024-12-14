#ifndef PASSWORD_SECURITY
#define PASSWORD_SECURITY

#include <vector>

class Password_Security
{
    string password;

 public:
    Password_Security(){ }
    
    Password_Security(string pas)
    {
        password = pas;
    }

    void get_password(string& password);

    string get_password_data();

    bool security();
};
void Password_Security:: get_password(string& password)
{
        char ch;
        password.clear();

        while (true)
        {
            ch = _getch();
            if (ch == 13) // Enter key to stop
            {
                break;
            }
            else if (ch == 8) // Backspace key to delete a character
            {
                if (!password.empty())
                {
                    password.resize(password.size() - 1); // Remove the last character
                    cout << "\b \b"; // Move back one space, overwrite with space, and move back again
                }
            }
            else if (ch >= 32 && ch <= 126) // Valid password characters
            {
                password.push_back(ch);
                cout << '*'; // Mask the password character
            }
        }
}
string Password_Security:: get_password_data()
{
         pass_mark: // Mark
        cout << "Password: ";
        get_password(password);

        if (!security())
        {
            cout << "\nPassword is weak\n\n";
            goto pass_mark;
        }
        else
        {
            return password;
        }
}
bool Password_Security:: security()
{
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

        for (size_t i = 0; i < password.length(); ++i)
        {
            char c = password[i];
            if (isupper(c)) 
                hasUpper = true;
            else if (islower(c)) 
                hasLower = true;
            else if (isdigit(c)) 
                hasDigit = true;
            else if (!isalnum(c)) 
                hasSpecial = true;

            // If all conditions are met and length is greater than 8
            if (hasUpper && hasLower && hasDigit && hasSpecial && password.length() > 8)
            {
                return true;
            }
        }

        return false;
}
#endif // end of definition
