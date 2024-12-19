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
    A.play_sound_progress_bar("Audio\\System_Login.wav", "Loading...", "Default");   
    while (1)
   {
    first_menu:
        system("cls"); // clearing all warning
        
        int command = menu_key_movement();
        
     switch (command)
     {
        case 1:
        {
            login: // after signing in, user will redirect here
            system("cls"); // Consider replacing with a cross-platform solution
            int password_counter = 0;
            Login_Account LA;
           LA.get_user_id();
            
             if(LA.user_id_check() == 0)
             {
                A.play_sound_only("Audio\\Error_1.wav", "Default");
                Sleep(1500);
                goto first_menu;
             }
            int password_check = LA.user_password_check();
            password_ok: // label for re_entered password
            if (password_check == 1)
            {
                A.play_sound_progress_bar("Audio\\Login.wav", "Logging In...", LA.return_user_id() );
                Login_Menu_Option LMO;

                login_menu_again: // goto label
                int login_option_choose = LMO.login_menu_list(A, LA);
              

                Login_Account_Features LAF;
                if (login_option_choose == 1)
                {
                    again_update: // label for again_update;
                    system("cls"); // clearing menus
                    int login_status = LAF.update_journal_status(LA, A);
                    if (login_status == 1)
                    {
                        goto again_update;
                    }
                    else if(login_status == 0)
                    {
                        A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                        Sleep(1500);
                        system("cls");
                        goto login_menu_again;
                    }
                    else 
                    {
                        A.play_sound_only("Audio\\Back.wav", LA.return_user_id());  
                        system("cls"); 
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 2)
                {
                    int add_task = LAF.add_new_task( LA, A);
                    if (add_task == 1)
                    { 
                        goto login_menu_again;
                    }
                    else
                    {
                        A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                        goto first_menu;
                    }
                }
                else if (login_option_choose == 3)
                {
                    again_delete: // Label for delete;
                    system("cls");
                    int delete_task_status = LAF.delete_user_task(LA, A);
                    if (delete_task_status == 1)
                    {
                       
                        goto again_delete;
                    }
                    else
                    {
                        A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 4)
                {
                    system("cls");
                   
                    int view_task = LAF.view_user_task(LA, A);
                    {
                        if (view_task == 1)
                        {
                            goto login_menu_again;
                        }
                        else 
                        {
                            A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                            goto login_menu_again;
                        }
                    }
                }
                else if (login_option_choose == 5)
                {
                    system("cls");
                    again_status: // label
                    
                    int task_status = LAF.task_status_report(LA, A);
                    
                    if (task_status == 1 || task_status == 0)
                    {
                        A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                        goto login_menu_again;
                    }
                }
                else if (login_option_choose == 6)
                {
                    int delete_status = LAF.delete_account(LA, A);
                    if(delete_status == 1)
                    {
                        
                        goto first_menu;
                    }
                    else
                    {
                        A.play_sound_only("Audio\\Error_1.wav", LA.return_user_id());
                        goto login_menu_again;
                    }
                }
                else if(login_option_choose == 7)
                {
                    LAF.sound_file(LA, A);
                    goto login_menu_again;

                }
                else if (login_option_choose == 8)
                {
                     A.play_sound_progress_bar("Audio\\Report.wav", "Exiting...", LA.return_user_id());
                     return 0;
                }
                else 
                {
                    goto login_menu_again;
                }
            }
            else
            {
                Create_Account CA_1;
                again_enter_pass: // label from again_enter_pass
                system("cls");
                A.play_sound_only("Audio\\Error_1.wav","Default");
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
                        password_counter = LA.reset_password();
                        if (password_counter == 1)
                        {
                            password_check = 1;
                            cout << "\n\nPassword Reset Sucessfull\n\n";
                            A.play_sound_only("Audio\\Update.wav", "Default");
                            Sleep(1500);
                            goto first_menu;
                        }
                        else
                        {
                            
                            A.play_sound_only("Audio\\Error_1.wav", "Default");
                            Sleep(1500);
                        }
                    }
                    else
                    {
                        A.play_sound_only("Audio\\Error_1.wav", "Default");

                       goto first_menu;
                    }
                }
                else
                {
                    cout << "Re-Type Password: ";
                    CA_1.get_password(temp_password);
                    //cin >> temp_password;
                    if (temp_password == LA.return_password())
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
            if ((account_status = CA.get_details()) == 0)
            {
                break;
            }
            // Opening user individual file
            if ((account_status = CA.individual_details_file()) == 0)
            {
                break;
            }
            // Opening user excel file
            if (account_status = CA.opening_user_excel_file() == 0)
            {
                break;
            }

            // Opening user security details
            if (CA.get_security_details() == 0)
            {
                break;
            }
            if (CA.sound_setting() == 0)
            {
                break;
            }
            if (CA.open_file() == 5)
            {
               A.play_sound_progress_bar("Audio\\Sign.wav", "Creating Account...","Default");
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
            A.play_sound_progress_bar("Audio\\Report.wav", "Exiting...","Default");
            return 0;
        }
        default:
        {
            A.play_sound_only("Audio\\Error_1.wav", "Default");
            cout << "\n\nAn Unexpected Error Occured\n\n";
            Sleep(2500);
            return 0;
        }
     }
     goto login;  /// label for transfering to login section after creating account
   }

    return 0;
}

