#include "Cursor.h"
#include "Password_Security.h"
#include "Encryption_and_Decryption.h"
#include "Audio.h"
#include "Create_Account.h"
#include "Login_Account.h"
#include "Login_Menu_Option.h"
#include "Login_Account_Features.h"
using namespace std;

int main()
{
    system("cls");
    Audio A;  // Audio class
    A.Play_Sound_Progress_Bar("Audio\\System_Login.wav", "Loading...");   
    while (1)
   {
    first_menu:
        system("cls"); // clearing all warning
        
        int command = menu_key_movement();
        
     switch (command)
     {
        case 1:
        {
            
            system("cls"); // Consider replacing with a cross-platform solution
            int password_counter = 0;
            Login_Account LA;
           LA.Get_User_ID();
            
             if(LA.User_ID_Check() == 0)
             {
                A.Play_Sound_Only("Audio\\Error_1.wav");
                Sleep(1500);
                goto first_menu;
             }
            int password_check = LA.User_Password_Check();
            password_ok: // label for re_entered password
            if (password_check == 1)
            {
                A.Play_Sound_Progress_Bar("Audio\\Login.wav", "Logging In...");
                Login_Menu_Option LMO;

                login_menu_again: // goto label
                int login_option_choose = LMO.Login_Menu_List(A);
              

                Login_Account_Features LAF;
                if (login_option_choose == 1)
                {
                    again_update: // label for again_update;
                    system("cls"); // clearing menus
                    int login_status = LAF.Update_Journal_Status(LA, A);
                    if (login_status == 1)
                    {
                        goto again_update;
                    }
                    else if(login_status == 0)
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");
                        Sleep(1500);
                        system("cls");
                        goto login_menu_again;
                    }
                    else 
                    {
                        A.Play_Sound_Only("Audio\\Back.wav");  
                        system("cls"); 
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 2)
                {
                    int add_task = LAF.Add_New_Task( LA, A);
                    if (add_task == 1)
                    { 
                        goto login_menu_again;
                    }
                    else
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");
                        goto first_menu;
                    }
                }
                else if (login_option_choose == 3)
                {
                    again_delete: // Label for delete;
                    system("cls");
                    int delete_task_status = LAF.Delete_User_Task(LA, A);
                    if (delete_task_status == 1)
                    {
                       
                        goto again_delete;
                    }
                    else
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 4)
                {
                    system("cls");
                   
                    int view_task = LAF.View_User_Task(LA, A);
                    {
                        if (view_task == 1)
                        {
                            goto login_menu_again;
                        }
                        else 
                        {
                            A.Play_Sound_Only("Audio\\Error_1.wav");
                            goto login_menu_again;
                        }
                    }
                }
                else if (login_option_choose == 5)
                {
                    system("cls");
                    again_status: // label
                    
                    int task_status = LAF.Task_Status_Report(LA, A);
                    
                    if (task_status == 1 || task_status == 0)
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 6)
                {
                    int delete_status = LAF.Delete_Account(LA, A);
                    if(delete_status == 1)
                    {
                        
                        goto first_menu;
                    }
                    else
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 7)
                {
                     A.Play_Sound_Progress_Bar("Audio\\Report.wav", "Exiting...");
                     return 0;
                }
                else 
                {
                    goto login_menu_again;
                }
            }
            else
            {
                again_enter_pass: // label from again_enter_pass
                system("cls");
                A.Play_Sound_Only("Audio\\Error_1.wav");
                cout << "\n\nIncorrect Password\n\n";
                Sleep(1500);

                string temp_password;
                
                password_counter++;

                if (password_counter == 3)
                {
                    string temp_name;
                    cout << "\n\nDo You Want To Reset Password (Yes/No): ";
                    cin >> temp_name;

                    if (temp_name == "Yes" || temp_name == "yes" || temp_name == "Y" || temp_name == "y")
                    {
                        password_counter = LA.Reset_Password();
                        if (password_counter == 1)
                        {
                            password_check = 1;
                            cout << "\n\nPassword Reset Sucessfull\n\n";
                            A.Play_Sound_Only("Audio\\Update.wav");
                            Sleep(1500);
                            goto first_menu;
                        }
                        else
                        {
                            
                            A.Play_Sound_Only("Audio\\Error_1.wav");
                            Sleep(1500);
                        }
                    }
                    else
                    {
                        A.Play_Sound_Only("Audio\\Error_1.wav");

                       goto first_menu;
                    }
                }
                else
                {
                    cout << "Re-Type Password: ";
                    cin >> temp_password;
                    if (temp_password == LA.Return_Password())
                    {
                        // goto login menu label
                        password_check = 1;
                        goto password_ok;
                    }
                    else
                    {
                        //A.Play_Sound_Only("Audio\\Error_1.wav");
                        goto again_enter_pass;
                    }
                }
            }
            break;
        }
        case 2:
        {
            int account_status = 1;
            system("cls"); 
            Create_Account CA;
            if ((account_status = CA.Get_Details()) == 0)
            {
                break;
            }
            // Opening user individual file
            if ((account_status = CA.Individual_Details_File()) == 0)
            {
                break;
            }
            // Opening user excel file
            if (account_status = CA.Opening_User_Excel_File() == 0)
            {
                break;
            }

            // Opening user security details
            if (CA.Get_Security_Details() == 0)
            {
                break;
            }

            if (CA.Open_File() == 4)
            {
               A.Play_Sound_Progress_Bar("Audio\\Sign.wav", "Creating Account...");
            }
            else
            {
                // DIsplay error
                break;
            }
            
        }
        break;
        case 3:
        {
            A.Play_Sound_Progress_Bar("Audio\\Report.wav", "Exiting...");
            return 0;
        }
        default:
        {
            A.Play_Sound_Only("Audio\\Error_1.wav");
            cout << "\n\nAn Unexpected Error Occured\n\n";
            Sleep(2500);
            return 0;
        }
     }
   }

    return 0;
}

