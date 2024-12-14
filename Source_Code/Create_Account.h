#ifndef CREATE_ACCOUNT   // checks create_account define or not
#define CREATE_ACCOUNT  // define create_account

#include <cstdlib>
#include <fstream>

using namespace std;

class Create_Account : public Password_Security, public Encryption_and_Decryption, public Audio
{
 protected:
    string name, password, re_password, User_ID, temp, 
    temp_2[5], user_ask_list[3], user_excel_list[3], user_journal_list[1], Unique_ID[1];
    string security_question;
    double user_id;
    int compare;
    static int file_count;

 public:
    // Constructor to initialize default values
    Create_Account()
    {
        name = "Unknown";
        password = "Hello";
        re_password = "Hello";
        User_ID = "Unknown";
    }

    // Function to get user details
    int get_details();
    
    // Function to create and open individual details file
    int individual_details_file();

    // Function to create and open the user's Excel file for journal
    int opening_user_excel_file();

    // Function to get security details
    int get_security_details();

    // Open user all file
    int open_file();
    // Function to check whether all file opened or not
    static int account_check();
    // Function to open user sound setting file
    int sound_setting()
    {
        encrypt(User_ID);
         temp_2[4].clear(); 
         temp_2[4] = temp_2[4] + User_ID + "\\" + User_ID + "_sound.txt";
          decrypt(User_ID);
         return 1;
    }
    ~Create_Account(){ }// Create Account Destructor
};

int Create_Account::file_count;

int Create_Account::get_details()
{
    cout << "\n\nBasic Details\n\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "\n\n";

    cout << "User ID: ";
    cin >> User_ID;

    temp_2[0].clear();
    temp_2[0] = temp_2[0] + "User_ID_List.csv";

    // Check if the User ID is unique
    fstream myfile;
    myfile.open("User_ID_List.csv", ios::in);
    if (myfile.fail())
    {
        cout << "Unable to create account as the User ID list cannot be accessed.";
        Sleep(2500);
        system("cls");
        return 0;
    }
    while (getline(myfile, temp))
    {
        decrypt(temp);  // decrypting encrypted User_ID form file

        if (User_ID == temp)
        {
            cout << "\n\nUnable to Create Account \n\nUser ID already exists in the database.\n\n";
            Sleep(2500);
            system("cls");
            return 0;
        }
    }
    myfile.close(); 

    encrypt(User_ID);

    Unique_ID[0].clear();
    Unique_ID[0] = Unique_ID[0] + User_ID + "\n";

    cout << "\n\n";

    // Password Input From User
    cin.ignore();
    password.clear();
    password = get_password_data();
    system("cls");

    return 1;
}

// Creating user individual csv file having name, user id and password
int Create_Account::individual_details_file()
{ 
    // Don’t require to encrypt User_ID

    
    temp_2[1].clear();
    temp_2[1] =temp_2[1] + User_ID + "\\" + User_ID + "_Details.csv";;  // later user for deleting this file

    // Encrypting User Name
    encrypt(name);

     user_ask_list[0].clear();
     user_ask_list[0] =  user_ask_list[0] + "Name:" + "," + name + "," + "\n";
     
    user_ask_list[1].clear();
    user_ask_list[1] = user_ask_list[1] + "User ID:" + "," + User_ID + "," + "\n";

    encrypt(password);
    user_ask_list[2].clear();
    user_ask_list[2]  = user_ask_list[2] + "Password:" + "," + password + ",";

    decrypt(User_ID);
    system("cls");
    
    return 1;
}

// Function to create and open the user's Excel file
int Create_Account::opening_user_excel_file()
{

    encrypt(User_ID);

    temp_2[2].clear();
    temp_2[2] = temp_2[2] + User_ID + "\\" + User_ID + "_Journal.csv";  
    
    user_journal_list[0].clear();
    user_journal_list[0] = user_journal_list[0] + user_journal_list[0] + "MM/DD/YYYY" + ",";
    
    // Decrypting User_ID name;
    decrypt(User_ID);

    system("cls");
    return 1;
}

// Function to get user security details
int Create_Account::get_security_details()
{
    encrypt(User_ID);

    temp_2[3].clear();
    temp_2[3] = temp_2[3] + User_ID + "\\" + User_ID + "_Security.csv"; 

    cout << "\n\nSecurity Details\n\n";

    cout << "What's your Favourite Food? : ";
    cin >> security_question;
    encrypt(security_question);  // Encrypting security answer
    user_excel_list[0].clear();
    user_excel_list[0] = user_excel_list[0] + "What's your Favourite Food?" + "," + security_question + "\n";

    cout << "What's your Favourite Place? : ";
    cin >> security_question;
    encrypt(security_question);  // Encrypting security answer
     user_excel_list[1].clear();
     user_excel_list[1] = user_excel_list[1] + "What's your Favourite Place?" + "," + security_question + "\n";

    cout << "What's your Favourite Person? : ";
    cin >> security_question;
    encrypt(security_question);  // Encrypting security answer
    user_excel_list[2].clear();
    user_excel_list[2] = user_excel_list[2] + "What's your Favourite Person?" + "," + security_question + "\n";

    decrypt(User_ID);
    system("cls");
    return 1;
}
int Create_Account:: open_file()
{
    file_count = 0;
    for(int i=0; i<5; i++)
    {
                if( i == 0 )
                {
                    fstream myid;
                    myid.open( temp_2[i].c_str(), ios::app);
    
                    if (myid.fail())
                    {
                    cout << "Unable to Create Account\n\nUser ID List Cannot be Accessed.";
                     Sleep(2500);
                     
                     system("cls");
                      return 0;
                    }
                    
                    myid << Unique_ID[i];
                    myid.close();
                    file_count++;  // file Journal File opened successfully, counter up
                }
                if( i == 1)
                {
                    temp.clear();
                    encrypt(User_ID); // encrypting user id for opening folder

                    temp = temp + "mkdir " + User_ID;
                    system(temp.c_str());

                    temp.clear();
                    temp = temp + "mkdir C:\\Users\\niraj\\Documents\\Desktop\\Vs_Code\\Habit-Analyzer\\Source_Code\\"+ User_ID + "\\Task_List";
                    system(temp.c_str());
                    fstream mydetail(temp_2[i].c_str(), ios::out);
                    if (mydetail.fail())
                    {
                        system("cls");
                        cout << "\n\nUnable to open Individual Details File\n\n";
                        Sleep(2500);
                        return 0;
                    }
                    for(int i=0; i<3; i++)
                    {
                        mydetail << user_ask_list[i];
                    }
                    mydetail.close();
                    file_count++;  // file Journal File opened successfully, counter up
                }
                if( i == 2 )
                {
                    fstream myjournal(temp_2[i].c_str(), ios::out );

                    if (myjournal.fail())
                    {
                        system("cls");
                        cout << "\n\nUnable To Create Journal File\n\n";
                        Sleep(2500);
                        return 0;
        
                    }
                    myjournal << user_journal_list[0];
                    myjournal.close();
                    file_count++;  // file Journal File opened successfully, counter up
                }
                if( i == 3)
                {
                    fstream mycsv;
                    mycsv.open(temp_2[i].c_str(), ios::out);
                    if (mycsv.fail())
                    {
                        system("cls");
                        cout << "\n\nUnable to Open User's Security file\n\n";
                        Sleep(2500); 
                        return 0;
                    }
                    for(int i=0; i<3; i++)
                    {
                        mycsv << user_excel_list[i];
                    }
                    mycsv.close();
                    file_count++;  // file Journal File opened successfully, counter up
                }
                if(i == 4)
                {
                  
                   fstream mysound(temp_2[i].c_str(), ios::out);
                     if(!mysound)
                    {
                       system("cls");
                       cout << "Unable to open sound file\n";
                       Sleep(2500); 
                       return 0;
            
                    }
                    mysound << 1;
                     mysound.close();
                     file_count ++;
                }
    }
    return file_count;
}
int Create_Account:: account_check()
{
    system("cls");
    try
    {
        if (file_count == 5)
        {
            return file_count;
        }
        else
        {
            throw(file_count);
        }
    }
    catch (int file_count)
    {
        cout << "\n\nUnable to Open Account";
        Sleep(2500);
        system("cls");
        return 0;
    }
}

#endif  // end of declaration
