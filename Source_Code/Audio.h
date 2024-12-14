#ifndef AUDIO
#define AUDIO

#include <fstream>
//class Login_Account_Features;  // forward declaration
class Sound
{
    
    public:
    Sound() { }  // Constructor

    virtual void play_sound_only( string mp3, string user_id_name) = 0 ;// Plays Audio Only

    virtual void play_sound_progress_bar(string mp3, string message, string user_id_name) = 0; // Plays Audio and Display Progress Bar

};
class Audio : public Sound
{
    string temp_file;  // hold sound file setting location
    int temp_setting;  // read sound 0 or 1
    public:
    Audio() { }  // Constructor

    void play_sound_only(string mp3, string user_id_name) ; // Plays Audio Only

    void play_sound_progress_bar(string mp3, string message, string user_id_name); // Plays Audio and Display Progress Bar


    ~Audio() { } // destructor
};
void Audio:: play_sound_only( string mp3, string user_id_name)
{
     if( user_id_name == "Default")
    {
        PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
        
    }
    else 
    {
        
        temp_file = user_id_name + "\\" + user_id_name + "_sound.txt";
        fstream mysound3(temp_file.c_str(), ios::in);
        if(!mysound3)
        {
            system("cls");
            cout << "\nUnable to open sound file\n";
            Sleep(2000);
            system("cls");
        }
        mysound3 >> temp_setting;
        mysound3.close();
        if (temp_setting == 1)
        { 
            PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
        }
        else
        {
            ; // Play nothing
        }
    }
    
}
void Audio:: play_sound_progress_bar( string mp3, string message, string user_id_name)
{
    system("cls");
       // Initialize char for printing loading bar
    char a = 177, b = 219;
    cout << "\n\n\n\n";
        cout << "\n\n\n\n\t\t\t\t\t\t"<< message << "\n\n";
        cout << "\t\t\t\t\t\t";

        // Print initial loading bar
        for (int i = 0; i < 50; ++i)
        cout << a;

        // Set the cursor again starting point of loading bar
        cout << "\r";
        cout << "\t\t\t\t\t\t";


    if( user_id_name == "Default")
    {
        PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
        
    }
    else 
    {
        
        temp_file = user_id_name + "\\" + user_id_name + "_sound.txt";
        fstream mysound2(temp_file.c_str(), ios::in);
        if(!mysound2)
        {
            system("cls");
            cout << "\nUnable to open sound file\n";
            Sleep(2000);
            exit(0);
        }
        mysound2 >> temp_setting;
        mysound2.close();
        if (temp_setting == 1)
        { 
            PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
        }
    }

            // Print loading bar progress
            for (int i = 0; i < 50; ++i) 
            {
                cout << b;  
                Sleep(16);
            }
            system("cls");
}
#endif // end of declaration