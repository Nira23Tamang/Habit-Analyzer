#ifndef LOGIN_ACCOUNT
#define LOGIN_ACCOUNT

#include <sstream>

using namespace std;

class Login_Account_Features; // forward declaration for login menu features

class Login_Account : public Create_Account  // Handle only allowing to enter to login account
{
 protected:
    string user_id_2;
    string str_line, storedPassword;
    bool userIDExists = false;
    int commaCounter = 0;

 public:
    friend class Login_Account_Features; // forward declaration for login menu features

    Login_Account() {}

    void get_user_id();

    int user_id_check();

    int user_password_check();

    string return_password();

    int reset_password();

    string return_user_id()
    {
        return user_id_2;
    }
    
};
void Login_Account::  get_user_id()
{
        cout << "\n\nUser ID: ";
        cin >> user_id_2;
}
int Login_Account:: user_id_check()
{
        temp = "User_ID_List.csv";
        ifstream myfile(temp.c_str());

        if (!myfile)
        {
            system("cls");
            cout << "\n\nUnable to Check User Account Availability\n\n";
            return 0;
        }

        encrypt(user_id_2);

        while (getline(myfile, str_line))
        {
            if (str_line == user_id_2)
            {
                userIDExists = true;
                break;
            }
        }

        myfile.close();

        if (!userIDExists)
        {
            decrypt(user_id_2);
            system("cls");
            cout << "\n\nUser ID: " << user_id_2 << " Does Not Exist\n\n";
            return 0;
        }
        return 1;
}
int Login_Account:: user_password_check()
{
        cout << "\n\nPassword: ";
        get_password(password);

        temp = user_id_2 + "\\" + user_id_2 + "_Details.csv";
        ifstream myfile(temp.c_str());

        if (!myfile)
        {
            system("cls");
            cout << "\n\nUnable to Open Individual File to Check Password\n\n";
            return 0;
        }
         commaCounter = 0;
        while (getline(myfile, str_line))
        {
            commaCounter ++;
            if(commaCounter == 3)
            {
                commaCounter = 0;
                stringstream pp_object(str_line);
                while(getline(pp_object, storedPassword, ','))
                {
                    commaCounter ++;
                    if(commaCounter == 2)
                    {
                        break;
                    }
                    
                }
            }
        }

        myfile.close();

        decrypt(storedPassword);
        if (storedPassword == password)
        {
            return 1;
        }
        
        return 0;
        
}
string Login_Account:: return_password()
{
    return storedPassword;
}
int Login_Account:: reset_password()
{
        temp.clear();
        temp = user_id_2 + "\\" + user_id_2 + "_Security.csv";
        fstream my_pass_reset(temp.c_str(), ios::in | ios::out);

        if (!my_pass_reset)
        {
            system("cls");
            cout << "\n\nUnable to Open Security File to Check Password\n\n";
            return 0;
        }
        else
        {
            compare = 0;
            do
            {
                getline(my_pass_reset, security_question, ',');
                cout << "\n" << security_question << " : ";
                getline(my_pass_reset, storedPassword);
                decrypt(storedPassword);
                cin >> temp;
                if (storedPassword == temp)
                {
                    compare++;
                }
                else
                {
                    system("cls");
                    cout << "\n\nIncorrect Answer\n\n";
                    Sleep(2000);
                    my_pass_reset.close();
                    return 0;
                }
            } while (compare != 3);

            my_pass_reset.close();
            system("cls");

            temp = user_id_2 + "\\" + user_id_2 + "_Details.csv";
            fstream my_pass_update(temp.c_str(), ios::in);
            if (my_pass_update.fail())
            {
                cout << "\n\nUnable to Reset Password\nUnable to Open User Detail File\n\n";
                return 0;
            }
            else
            {
                compare = 0;
                string update_array[3];
                while (getline(my_pass_update, temp))
                {
                    if (compare == 2)
                    {
                        cout << "\n\nNew ";
                        str_line = get_password_data();
                        encrypt(str_line);
                        name.clear();
                        name = name + "Password:" + "," + str_line + ",";
                        update_array[compare] = name;
                        break;
                    }
                    update_array[compare] = temp;
                    compare++;
                }
                my_pass_update.close();

                name = user_id_2 + "\\" + user_id_2 + "_Details.csv";
                fstream my_new_pass_update(name.c_str(), ios::out | ios::trunc);
                if (my_new_pass_update.fail())
                {
                    cout << "\n\nUnable to Reset Password\nError New File\n\n";
                    return 0;
                }

                for (int i = 0; i < 3; i++)
                {
                    my_new_pass_update << update_array[i] << "\n";
                }
                my_new_pass_update.close();
            }
        }
        system("cls");
        return 1;
}
#endif // LOGIN_ACCOUNT
