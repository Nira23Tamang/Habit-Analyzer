#ifndef AUDIO
#define AUDIO

//class Login_Account_Features;  // forward declaration
class Sound
{
    public:
    Sound() { }  // Constructor

    virtual void play_sound_only( string mp3) = 0 ;// Plays Audio Only

    virtual void play_sound_progress_bar(string mp3, string message) = 0; // Plays Audio and Display Progress Bar

    
};
class Audio : public Sound
{
    public:
    Audio() { }  // Constructor

    void play_sound_only(string mp3) ; // Plays Audio Only

    void play_sound_progress_bar(string mp3, string message); // Plays Audio and Display Progress Bar

    friend class Login_Account_Features ;// making  login_account_features friend class of Sound classs

    ~Audio() { } // destructor
};
void Audio:: play_sound_only( string mp3)
{
    PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
    
}
void Audio:: play_sound_progress_bar( string mp3, string message)
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
    PlaySound(TEXT( mp3.c_str() ),NULL,SND_ASYNC);
    // Print loading bar progress
    for (int i = 0; i < 50; ++i) 
    {
        cout << b;  
        Sleep(16);
    }
    system("cls");
}
#endif // end of declaration