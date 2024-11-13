#ifndef LOGIN_ACCOUNT_FEATURES
#define LOGIN_ACCOUNT_FEATURES
#include <graphics.h>
#include <sstream>
#include "System_Time.h"
#include <conio.h> 
#include <cstring> 

class Login_Account_Features : public Login_Account, public System_Time
{
 protected:
    int menu_list_counter = 0, loop_counter = 0, loop_counter_2 = 0, num_zero = 0, temp_counter = 0;  // for counting loop and number of zeros
    string system_time, file_time, user_journal_list_slection;

 public:
    Login_Account_Features() {}

    int Count_Return(string& data1);

    int Add_New_Task(Login_Account& LA, Audio& A);

    int Update_Journal_Status(Login_Account& LA, Audio& A);

    int View_User_Task(Login_Account& LA, Audio& A);

    string User_Journal_Menu_List(string array[], int num);

    int Delete_User_Task(Login_Account& LA, Audio& A);

    int Task_Status_Report(Login_Account& LA, Audio& A);

    bool Check_Length(string sample);

    int Report_Graph(int heights[], string labels[], int numBars);
    
    int Delete_Account(Login_Account& LA, Audio& A);

    ~Login_Account_Features() { } // Destructor of Login_Account_Features
};

int Login_Account_Features::Report_Graph(int heights[], string labels[], int numBars)
{
    // Initialize the graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    if (graphresult() != grOk) 
    {
        system("cls");
        cout << "Graphics initialization failed: " << grapherrormsg(graphresult()) << endl;
        return 0;
    }

    // Clear the screen
    cleardevice();

    // Display the title
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(275, 0, "REPORT STATUS");

    // Draw X and Y axes
    line(60, 430, 60, 20);    // Y-axis
    line(40, 410, 620, 410);  // X-axis

    // Draw axis arrows
    line(60, 20, 55, 25);    // Y-axis
    line(60, 20, 65, 25);  // X-axis

    line(615, 405, 620, 410);  // X-axis arrow top
    line(615, 415, 620, 410);  // X-axis arrow bottom

    // Add labels for the axes
    outtextxy(65, 45, "Y");
    outtextxy(590, 415, "X");
    outtextxy(40, 420, "O");  // Origin

    // Draw bars and labels
    setfillstyle(LTBKSLASH_FILL, WHITE);  // Bar fill pattern and color
    for (int i = 0; i < numBars; i++)
    {
        int barX1 = 100 + i * 100;  // Starting X position of each bar
        int barX2 = barX1 + 50;     // Ending X position (width of 50)

        // Draw the 3D bar with height from the `heights` array
        bar3d(barX1, heights[i], barX2, 410, 15, 1);

        // Convert the label to a C-style string
        char label[7];
        strcpy(label, labels[i].c_str());

        // Display the label under each bar
        outtextxy(barX1, 420, label);
    }

    // Wait for the user to press a key before closing
    getch();

    // Close the graphics mode
    closegraph();
    return 1;
}

bool Login_Account_Features::Check_Length(string sample)
{
    if (strlen(sample.c_str()) <= 7)
    {
        return true;
    }
    else
    {
        system("cls");
        cout << "\nThe length of Task Shouldn't be Greater than 7\n";
        Sleep(2500);
        return false;
    }
}
int Login_Account_Features:: Update_Journal_Status(Login_Account& LA, Audio& A) 
{
    LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
    fstream journal_status(LA.temp.c_str(), ios::in | ios::out);
    if (!journal_status) 
    {
        system("cls");
        cout << "\n\nUnable to Open User Journal File 1ist\n\n";
        return 0;
    }
    journal_status.clear();
    journal_status.seekg(0, ios::beg);  // sets pointer to the first
    LA.temp.clear();
    getline(journal_status, LA.temp); // read user habitual task
    menu_list_counter = Count_Return(LA.temp);  // Number of Task in Journal
    if (menu_list_counter == 0) {
        cout << "\n\nUser Don't Have Any Daily Habitual Task\n\n";
        
        return  0;
    }
    journal_status.clear();
    journal_status.seekg(-(11 + (2 * menu_list_counter)), ios::end);
    getline(journal_status, file_time, ','); // getting current time from system
    system_time = Current_Time(system_time);
    if (file_time == system_time) 
    {
        loop_counter = 0; loop_counter_2 = 0, num_zero = 0;  // assigning all counters zero
        string task_status[menu_list_counter];  // to store task status
        journal_status.clear();
        journal_status.seekg(-(11 + (2 * menu_list_counter)), ios::end);
        while (getline(journal_status, LA.name, ',')) 
        {
            if (LA.name == "0" || LA.name == "1") 
            {
                task_status[loop_counter_2] = LA.name;
                loop_counter_2++;
                if (LA.name == "0") 
                {
                    num_zero++;
                }
            }
        }
        if (num_zero == 0) 
        {
            system("cls");
            cout << "\n\nYou Have Updated All Daily Challenge\n\n";
            return 0;
        }
        journal_status.clear();
        journal_status.seekp(11, ios::beg);
        getline(journal_status, LA.temp); // it holds task name;
        vector<string> array_of_task_3;
        stringstream pp(LA.temp);
        loop_counter_2 = 0;
        loop_counter = 0;  // using as counter in this loop
        string array_of_task_2[num_zero]; // arrays of string to be shown
        while (getline(pp, LA.name, ',')) 
        {
            array_of_task_3.push_back(LA.name);
            if (task_status[loop_counter] == "0") 
            {
                array_of_task_2[loop_counter_2] = array_of_task_3[loop_counter];
                loop_counter_2++;
            }
            loop_counter++;
        }
        // show menu of above new array
        user_journal_list_slection = User_Journal_Menu_List(array_of_task_2, loop_counter_2);
        if (user_journal_list_slection == "eight") 
        {
            return -1;
        }
        journal_status.clear();
        journal_status.seekp(-(2 * menu_list_counter + 1), ios::end);
        for (int i = 0; i < menu_list_counter; i++) 
        {
            if (array_of_task_3[i] == user_journal_list_slection) 
            {
                journal_status << "," << "1";
                continue;
            }
            journal_status << "," << task_status[i];
        }
    } 
    else 
    { // when system time and file time do not match
        journal_status.clear();
        journal_status.seekp(0, ios::end);
        journal_status << "\n" << system_time << ","; // inserting today time
        for (int i = 0; i < menu_list_counter; i++) 
        {
            journal_status << "0" << ",";
        }
        // Separate word from line
        {
            // Create a stringstream object for the data
            stringstream ss(LA.temp);
            string array_of_task[menu_list_counter]; // arrays of string
            while (getline(ss, LA.name, ',')) 
            {
                if (LA.name == "MM/DD/YYYY") 
                {
                    continue;
                }
                array_of_task[loop_counter] = LA.name;  // Store token in the array
                loop_counter++;  // Increment the count
            }
            user_journal_list_slection = User_Journal_Menu_List(array_of_task, menu_list_counter);
            if (user_journal_list_slection == "eight") 
            {
                return -1;
            }
            journal_status.clear();
            journal_status.seekp(-(2 * menu_list_counter), ios::end);
            for (int i = 0; i < menu_list_counter; i++) 
            {
                if (array_of_task[i] == user_journal_list_slection) 
                {
                    journal_status << (1) << ",";
                    break;
                }
                journal_status << "0" << ",";
            }
        }
    }
    journal_status.close();
    A.Play_Sound_Progress_Bar("Audio\\Update.wav", "Updating Task...");
    return 1;
}

int Login_Account_Features::Count_Return(string& data1) 
{
    vector<string> array1;
    stringstream ss(data1);
    string token;

    // Use a while loop to extract tokens
    while (getline(ss, token, ',')) 
    {
        if (token == "MM/DD/YYYY") 
        {
            continue;
        }
        array1.push_back(token);
    }
    return (array1.size());
}

int Login_Account_Features::Add_New_Task(Login_Account& LA, Audio& A) 
{
    string new_task;
    LA.temp.clear();
    LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
    fstream my_add_new_task(LA.temp.c_str(), ios::in | ios::out);

    if (!my_add_new_task) 
    {
        system("cls");
        cout << "\n\nUnable to Open User Journal File\n\n";
        return 0;
    } 
    else 
    {
        system("cls");
        LA.temp.clear();
        loop_counter = 0;
        
        while (getline(my_add_new_task, LA.temp)) 
        {
            loop_counter++;
        }
        
        bool b1;
        
        if (loop_counter == 1) 
        {
            bool_label: // label statement
            my_add_new_task.clear();
            my_add_new_task.seekp(0, ios::end);
            LA.compare = Count_Return(LA.temp);
            
            switch (LA.compare) 
            {
                case 0:
                    cout << "\n1st Habitual Task: ";
                    break;
                case 1:
                    cout << "\n2nd Habitual Task: ";
                    break;
                case 2:
                    cout << "\n3rd Habitual Task: ";
                    break;
                case 3:
                    cout << "\n4th Habitual Task: ";
                    break;
                case 4:
                    cout << "\n5th Habitual Task: ";
                    break;
                default:
                    cout << "\n\nYou Cannot Keep More than 5 Daily Habitual Task at a Time\n\n";
                    Sleep(2000);
                    return 0;
            }
            
            cin >> new_task;
            b1 = Check_Length(new_task);
            
            if (b1 == false) 
            {
                goto bool_label;
            }
            
            my_add_new_task << new_task << ",";
        
        }
        else 
        {
            bool_label_2:  // label statement
            // clearing file_pointer
            my_add_new_task.clear();
            my_add_new_task.seekg(0, ios::beg);
            getline(my_add_new_task, LA.temp);
            LA.compare = Count_Return(LA.temp);
            
            switch (LA.compare) 
            {
                case 0:
                    my_add_new_task.seekp(11, ios::beg);
                    cout << "\n1st Habitual Task: ";
                    cin >> new_task;
                    my_add_new_task << new_task; // first task in first row and second column
                    break;
                case 1:
                case 2:
                case 3:
                case 4: 
                {
                    if (LA.compare == 1) 
                    {
                        cout << "\n2nd Habitual Task: ";
                    } else if (LA.compare == 2) 
                    {
                        cout << "\n3rd Habitual Task: ";
                    } else if (LA.compare == 3) 
                    {
                        cout << "\n4th Habitual Task: ";
                    } else if (LA.compare == 4) 
                    {
                        cout << "\n5th Habitual Task: ";
                    } else 
                    {
                        cout << "\nAn Error Occurred\n\n";
                        Sleep(2000);
                        return 0;
                    }
                    
                    cin >> new_task;
                    b1 = Check_Length(new_task);
                    
                    if (b1 == false) 
                    {
                        goto bool_label_2;
                    }
                    
                    // Here check;
                    loop_counter = 0;
                    my_add_new_task.seekp(0, ios::beg);
                    // opening temporary file for shifting above file data
                    LA.temp = LA.User_ID + "\\" + "Temp" + "_Journal.csv";
                    fstream mytemp(LA.temp, ios::in | ios::out | ios::trunc);
                    
                    if (!mytemp) 
                    {
                        system("cls");
                        cout << "\n\nUnable to Add New Task\n\n";
                        return 0;
                    }
                    
                    while (getline(my_add_new_task, LA.name)) 
                    {
                        if (loop_counter == 0) 
                        {
                            mytemp << LA.name << new_task << ",";
                        } 
                        else 
                        {
                            mytemp << "\n" << LA.name << "0,";
                        }
                        loop_counter++;
                    }
                    
                    // transferring back to main file
                    my_add_new_task.clear();
                    mytemp.clear();
                    loop_counter = 0;
                    my_add_new_task.seekp(0, ios::beg);
                    mytemp.seekg(0, ios::beg);
                    
                    while (getline(mytemp, LA.name)) 
                    {
                        if (loop_counter == 0) 
                        {
                            my_add_new_task << LA.name;
                        } 
                        else 
                        {
                            my_add_new_task << "\n" << LA.name;
                        }
                        loop_counter++;
                    }
                    
                    mytemp.close();
                    my_add_new_task.close();
                    num_zero = remove(LA.temp.c_str());
                    
                    if (num_zero != 0) 
                    {
                        cout << "\nUnable to Add New Task";
                    }
                }
                break;
                default:
                    my_add_new_task.close();
                    cout << "\n\nYou Cannot Keep More than 5 Records at a Time\n\n";
                    Sleep(1500);
                    system("cls");
                    return 1;
            }
           
            my_add_new_task.close();
        }
        
    }
     A.Play_Sound_Progress_Bar("Audio\\Add.wav", "Adding " + (new_task) + " Task...");
     return 1;
}
int Login_Account_Features::View_User_Task(Login_Account& LA, Audio& A) 
{
    A.Play_Sound_Progress_Bar("Audio\\View.wav", "Viewing Task List...");
    LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
    fstream journal_status(LA.temp.c_str(), ios::in);

    if (!journal_status) 
    {
        system("cls");
        cout << "\n\nUnable to Open User Journal File\n\n";
        Sleep(1500);
        return 0;
    }

    journal_status.seekg(0, ios::beg);  // sets pointer to the first
    LA.temp.clear();
    getline(journal_status, LA.temp); // read user habitual task
    menu_list_counter = Count_Return(LA.temp);  // Number of Task in Journal

    if (menu_list_counter == 0) 
    {
         system("cls");
        cout << "\n\nUser Don't Have Any Daily Habitual Task\n\n";
        Sleep(1500);
       
        return 0;
    }

    stringstream ss(LA.temp);
    
    loop_counter = 0;
    string array_of_task[menu_list_counter]; // arrays of string

    while (getline(ss, LA.name, ',')) 
    {
        if (LA.name == "MM/DD/YYYY") 
        {
            continue;
        }
        array_of_task[loop_counter] = LA.name;  // Store token in the array
        loop_counter++;  // Increment the count
    }

    do 
    {
        user_journal_list_slection = User_Journal_Menu_List(array_of_task, loop_counter);
    } while (user_journal_list_slection == "Eight");
    A.Play_Sound_Only("Audio\\Back.wav");
    return 1;
}

string Login_Account_Features:: User_Journal_Menu_List(string array[], int num) 
{
    const int DEFAULT_COLOR = 7;
    int Set[num];

    for (int i = 0; i < num; i++) 
    {
        Set[i] = DEFAULT_COLOR;
    }

    static int counter = 0;
    static int temp_counter = 0;
    static char key;
    printf("\e[?25l");  // Hide cursor blinking

    while (1) {
        int X_coordinates = 60;
        int Y_coordinates = 10;

        for (int i = 0; i < num; i++) 
        {
            gotoxy(X_coordinates, Y_coordinates + (i * 2));
            setColor(Set[i]);
            cout << (i + 1) << ". "<< array[i];
        }

        key = _getch();  // Get user input

        if (key == 72 || key == 80) {  // Arrow keys: 72 (up), 80 (down)
            if (key == 80 && counter < num) 
            {
                counter++;
            }
            if (key == 72 && counter > 1) 
            {
                counter--;
            }
        } 
        else if (key == 13) 
        {
            system("cls");
            temp_counter = counter;
            counter = 0;
            setColor(DEFAULT_COLOR);
            return array[temp_counter - 1];
        } 
        else if (key == 8) 
        {  // Backspace
            //system("cls");
            return "eight";
        } 
        else 
        {
            ;
        }

        // Reset all options to default color
        for (int i = 0; i < num; i++) 
        {
            Set[i] = DEFAULT_COLOR;
        }

        // Highlight the selected option
        if (counter > 0) 
        {
            Set[counter - 1] = 2;
        }
    }
}

int Login_Account_Features::Task_Status_Report(Login_Account& LA, Audio& A)
{
    LA.temp.clear();
    LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
    fstream task_status(LA.temp.c_str(), ios::in);
    
    if (!task_status) 
    {
        system("cls");
        cout << "\n\nUnable to Display User Journal Report" << endl;
        Sleep(1500);
        return 0;
    }
    getline(task_status, LA.temp); // read user habitual task

    // Determining how many bars do we need
    menu_list_counter = Count_Return(LA.temp);  // Number of Task in Journal

    if (menu_list_counter == 0) 
    {
         system("cls");
        cout << "\n\nUser Don't Have Any Daily Habitual Task\n\n";
        Sleep(1500);
        return 0;
    }
    else
    {
        getline(task_status, LA.temp); // read user habitual task
        task_status.seekg(0, ios::beg);
        loop_counter = 0;
        while(getline(task_status, LA.name))
        {
            loop_counter ++;
            if(loop_counter > 1)
            {
                break;
            }
        }
        
        task_status.seekg(0, ios::beg);
        getline(task_status, LA.temp); // read user habitual task
        if(loop_counter <= 1)
        {
            system("cls");
            cout << "\n\nUser don't have updated any daily habitual task\n\n";
            Sleep(2000);
            system("cls");
            return 0;
        }
    }

    // To name bars
    stringstream ss(LA.temp);
    loop_counter = 0;
    string bars_name[menu_list_counter]; // arrays of string 

    while (getline(ss, LA.name, ',')) 
    {
        if (LA.name == "MM/DD/YYYY") 
        {
            continue;
        }

        bars_name[loop_counter] = LA.name; // Store token in the array
        loop_counter++;  // Increment the count

        LA.name.clear();
    }

    loop_counter = 0;

    // To get all number of rows for life time menu selection
    string report_menu[5] = { "One Month", "Three Month", "Six Month", "One Year", "Till Date" };
    user_journal_list_slection = User_Journal_Menu_List(report_menu, 5);
    int bar_height[menu_list_counter];

    if (user_journal_list_slection == "One Month") 
    {
        temp_counter = 30;
    } 
    else if (user_journal_list_slection == "Three Month") 
    {
        temp_counter = 90;
    } 
    else if (user_journal_list_slection == "Six Month") 
    {
        temp_counter = 180;
    } 
    else if (user_journal_list_slection == "One Year") 
    {
        temp_counter = 365;
    } 
    else if (user_journal_list_slection == "Till Date") 
    {
        loop_counter = 0;

        while (getline(task_status, LA.temp)) 
        {
            loop_counter++;
        }
        temp_counter = loop_counter;
    } 
    else if (user_journal_list_slection == "eight") 
    {
        return 0;
    }

    loop_counter = 0;
    loop_counter_2 = 0;
    task_status.clear();
    task_status.seekg(0, ios::beg);

    while (getline(task_status, LA.temp)) 
    {
        loop_counter++;
    }

    if (loop_counter > temp_counter || user_journal_list_slection == "Life Time") 
    {
        for (int i = 0; i < menu_list_counter; i++) 
        {
            bar_height[i] = 0;
        }

        task_status.clear();
        task_status.seekg(0, ios::beg);
        loop_counter_2 = loop_counter - temp_counter;

        if (user_journal_list_slection == "Life Time") 
        {
            goto life_time;
        }

        for (int i = 0; i < loop_counter_2; i++) 
        {
            getline(task_status, LA.temp);
        }

        life_time: // label of life_time
        while (getline(task_status, LA.temp)) 
        {
            stringstream s_object;
            s_object.str(LA.temp);

            for (int i = 0; i <= menu_list_counter; i++) 
            {
                getline(s_object, LA.name, ',');

                if (i == 0) 
                {
                    continue;
                } 
                else 
                {
                    if (LA.name == "1") 
                    {
                        bar_height[i - 1] = bar_height[i - 1] + 1;
                    }
                }
            }

            LA.temp.clear();
        }

        for (int i = 0; i < menu_list_counter; i++) 
        {
            bar_height[i] = 500 - ((bar_height[i] * 500) / temp_counter) + 100;

            if (bar_height[i] > 410) 
            {
                bar_height[i] = 410;
            }
        }
    } 
    else 
    {
        cout << "\n\nUser Don't Have Enough Record To Display Task Report\n\n";
        
        return 0;
    }
    A.Play_Sound_Progress_Bar("Audio\\Report.wav", ("Preparing " + (user_journal_list_slection) + " Report Graph...") );
    int report_status = Report_Graph(bar_height, bars_name, menu_list_counter);
    if (report_status == 1) 
    {
        return 1;
    } 
    return 0;
}
int Login_Account_Features:: Delete_Account(Login_Account& LA, Audio& A)
{
    system("cls");
    LA.temp.clear();
    //  User_ID already encrypted
    fstream myfile("User_ID_List.csv", ios::in);
    if (myfile.fail())
    {
        system("cls");
        cout << "\n\nUnable to Delete Account\n\n";
        Sleep(1500);
        return 0;
    }
    loop_counter = 0;
    while (getline(myfile, LA.temp))
    {
        loop_counter ++;
    }
   
    string id_list[loop_counter - 1];
    myfile.clear();
    myfile.seekg(0, ios::beg);
    loop_counter = 0;
     while (getline(myfile, LA.temp))
    {
        if(LA.temp == LA.User_ID )
        {
            continue;
        }
        id_list[loop_counter] = LA.temp;
        loop_counter ++;
        
    }
    myfile.close();
    myfile.open("User_ID_List.csv", ios::out | ios::trunc);
    if(!myfile)
    {
        system("cls");
        cout << "\n\nUnable to Delete User Account\n\n";
        Sleep(1500);
        return 0;
    }
    for(int i=0; i< loop_counter; i++)
    {
        myfile << id_list[i] << "\n";
    }
    myfile.close();
    LA.temp = LA.temp + "rmdir /S /Q " + LA.User_ID ;
    system(LA.temp.c_str());
    LA.decrypt(LA.User_ID);
    A.Play_Sound_Progress_Bar("Audio\\Error_2.wav", "Deleting "+ (LA.User_ID) + " Account...");
    return 1;
}
int Login_Account_Features::Delete_User_Task(Login_Account& LA, Audio& A)
{
    LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
    fstream journal_status(LA.temp.c_str(), ios::in);

    if (!journal_status)
    {
        system("cls");
        cout << "\n\nUnable to Open User Journal File\n\n";
        Sleep(1500);
        return 0;
    }

    journal_status.seekg(0, ios::beg);  // sets pointer to the first
    LA.temp.clear();
    getline(journal_status, LA.temp);  // read user habitual task
    menu_list_counter = Count_Return(LA.temp);  // Number of Task in Journal

    if (menu_list_counter == 0)
    {
        system("cls");
        cout << "\n\nUser Doesn't Have Any Daily Habitual Task\n\n";
        Sleep(1500);
        return 0;
    }

    stringstream ss(LA.temp);
    loop_counter = 0;
    string array_of_task[menu_list_counter];  // arrays of strings

    while (getline(ss, LA.name, ','))
    {
        if (LA.name == "MM/DD/YYYY")
        {
            continue;
        }
        array_of_task[loop_counter] = LA.name;  // Store token in the array
        loop_counter++;  // Increment the count
    }

    if (loop_counter == 0)
    {
        system("cls");
        cout << "\n\nYou Don't Have Any Habitual Task to Delete\n\n";
        Sleep(1500);
        return 0;
    }

    user_journal_list_slection = User_Journal_Menu_List(array_of_task, loop_counter);

    if (user_journal_list_slection == "eight")
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < menu_list_counter; i++)
        {
            if (array_of_task[i] == user_journal_list_slection)
            {
                temp_counter = i + 1;
            }
        }

        journal_status.seekg(0, ios::beg);
        loop_counter = 0;

        while (getline(journal_status, LA.temp))
        {
            loop_counter++;
        }

        if (loop_counter == 1)
        {
            journal_status.close();
            LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
            journal_status.open(LA.temp.c_str(), ios::out | ios::trunc);

            if (!journal_status)
            {
                cout << "\nUnable to Delete Task\n\n";
                Sleep(1500);
                return 0;
            }

            journal_status << "MM/DD/YYYY,";
            if (menu_list_counter > 1)
            {
                for (int i = 0; i < menu_list_counter; i++)
                {
                    if (user_journal_list_slection == array_of_task[i])
                    {
                        continue;
                    }
                    else
                    {
                        journal_status << array_of_task[i] << ",";
                    }
                }
            }
            journal_status.close();
        }
        else
        {
            if (menu_list_counter == 1)
            {
                journal_status.close();
                LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
                journal_status.open(LA.temp.c_str(), ios::out | ios::trunc);

                if (!journal_status)
                {
                    cout << "\nUnable to Delete Task\n\n";
                    Sleep(1500);
                    return 0;
                }
                else
                {
                    journal_status << "MM/DD/YYYY,";
                    journal_status.close();
                }
            }
            else
            {
                journal_status.clear();
                journal_status.seekg(0, ios::beg);
                string* temp_task = new string[loop_counter];

                if (temp_task == NULL)
                {
                    system("cls");
                    cout << "\n\nUnablt to Delete Task\n\n";
                    Sleep(1500);
                    return 0;
                }

                for (int i = 0; i < loop_counter; i++)
                {
                    getline(journal_status, LA.temp);
                    stringstream ss_object(LA.temp);  // string to stringstream object
                    loop_counter_2 = 0;
                    temp_task[num_zero].clear();

                    while (getline(ss_object, LA.name, ','))
                    {
                        loop_counter_2++;
                        if (loop_counter_2 == (temp_counter + 1))
                        {
                            continue;
                        }
                        temp_task[num_zero] = temp_task[num_zero] + LA.name + ",";
                    }
                    num_zero++;
                }

                journal_status.close();
                LA.temp = LA.User_ID + "\\" + LA.User_ID + "_Journal.csv";
                journal_status.open(LA.temp.c_str(), ios::out | ios::trunc);

                if (!journal_status)
                {
                    system("cls");
                    cout << "\n\nUnable to Delete Task\n\n";
                    Sleep(1500);
                    return 0;
                }

                for (int i = 0; i < loop_counter; i++)
                {
                    if (i == loop_counter - 1)
                    {
                        journal_status << temp_task[i];
                        break;
                    }
                    journal_status << temp_task[i] << "\n";
                }

                journal_status.close();
                delete[] temp_task;
                num_zero = 0;
                loop_counter = 0;
                loop_counter_2 = 0;
            }
        }
    }
    A.Play_Sound_Progress_Bar("Audio\\Delete.wav", "Deleting " + user_journal_list_slection + " Task...");
    return 1;
}
#endif // end of declaration