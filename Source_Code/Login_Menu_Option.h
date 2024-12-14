#ifndef LOGIN_MENU_OPTION
#define LOGIN_MENU_OPTION

class Login_Menu_Option 
{
 public:
    Login_Menu_Option() { }

    int login_menu_list(Audio& A, Login_Account LA);

    friend class Audio;

    ~Login_Menu_Option() { } // Login_Menu_List Destructor
};

int Login_Menu_Option::login_menu_list(Audio& A, Login_Account LA)
{
    const int DEFAULT_COLOR = 7;
    const int HIGHLIGHT_COLOR = 2;
    static int Set[] = {7, 7, 7, 7, 7, 7, 7, 7};  // Default colors
    static int counter = 0;
    static int backspace_counter = 0;
    static char key;

    cout << "\e[?25l";  // Hide cursor blinking

    while (1) 
    {
        // Displaying menu options
        gotoxy(60, 10);
        color(Set[0]);
        cout << "Update Task Status";

        gotoxy(60, 12);
        color(Set[1]);
        cout << "Add New Task";

        gotoxy(60, 14);
        color(Set[2]);
        cout << "Delete User Task";

        gotoxy(60, 16);
        color(Set[3]);
        cout << "View Task List";

        gotoxy(60, 18);
        color(Set[4]);
        cout << "Task Status Report";

        gotoxy(60, 20);
        color(Set[5]);
        cout << "Delete Account";

        gotoxy(60, 22);
        color(Set[6]);
        cout << "Audio Settig";

        gotoxy(60, 24);
        color(Set[7]);
        cout << "Exit Application";
        here:  // goto label
        key = _getch();  // Get user input

        if (key == 72 || key == 80) 
        {  // Arrow keys: 72 (up), 80 (down)
            if (key == 80 && counter < 8) 
            {
                counter++;
            }
            if (key == 72 && counter > 1) 
            {
                counter--;
            }
        } 
        else if (key == 13) 
        {   A.play_sound_only("Audio\\Enter.wav", LA.return_user_id() );
            // Enter key (carriage return)
            color(7);
            switch (counter)
            {
                // Reset all options to default color
                // Reset counter to zero
                case 1:
                    Set[0] = 7;
                    counter = 0;
                    return 1;

                case 2:
                    Set[1] = 7;
                    counter = 0;
                    return 2;

                case 3:
                    Set[2] = 7;
                    counter = 0;
                    return 3;

                case 4:
                    Set[3] = 7;
                    counter = 0;
                    return 4;

                case 5:
                    Set[4] = 7;
                    counter = 0;
                    return 5;
                case 6:
                    Set[5] = 7;
                    counter = 0;
                    return 6;
                case 7:
                    Set[6] = 7;
                    counter = 0;
                    return 7;
                case 8:
                    Set[7] = 7;
                    counter = 0;
                    return 8;
                default:
                    return 0;
            }
        } 
        else 
        {
            goto here;
        }
        // Reset all menu options to default color
        for (int i = 0; i < 8; i++) 
        {
            Set[i] = 7;
        }

        // Highlight the selected option
        for (int i = 1; i <= 8; i++) 
        {
            if (counter == i) 
            {
                Set[i - 1] = 2;
            }
        }
    }
}

#endif // end of definition
