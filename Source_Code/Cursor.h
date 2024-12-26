 #ifndef CURSOR  // checks cursor is define or not
 #define CURSOR  // define cursor

 #include <iostream>
 #include <windows.h>
 #include <conio.h>

 using namespace std;
 
 int checker = 0;
 void gotoxy(int x, int y)
{
     COORD c;
     c.X=x;
     c.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void color(int color)
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
void clearLine(int x, int y, int length = 120) 
{
    gotoxy(x, y);
    cout << string(length, ' ');
    gotoxy(x, y);
}
void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int menu_key_movement()
{
	 menu:
     static int Set[] = {7,7,7}; // DEFAULT COLORS
     static int counter = 0;
     static int backspace_counter = 0;
     static char key;
     printf("\e[?25l"); // Hide curosr blinking
	 while(1)
	 {
		 gotoxy(60,10);
         color(Set[0]);
         cout<<"Login";

         gotoxy(60,12);
         color(Set[1]);
         cout<<"Sign up";

         gotoxy(60,14);
         color(Set[2]);
         cout<<"Exit";

        // gotoxy(40,18);

         key =_getch();
             if(key == 72 || key == 80)
             {
                     if(key == 80 && counter <3)
                     {
                    	 counter++;
			            	 }
			            	if(key == 72 && counter > 1)
                     {
                    	 counter--;
                     }
		         }
		         else if(key == 13)//carriage return
             {
                	 color(7);
                   for(int i=0; i<3; i++)
                   {
                       if(counter == i + 1)
                       {
                         return (counter);
                       } 
                   }
                     
              }
              else
              {
                	 if(key == 8 && counter>0)
                	 {
                		    backspace_counter++;
                		    system("cls");
                		    if(backspace_counter == 2)
                		    {
                		       	 cout << backspace_counter;
                		      	 goto menu;
						            }
				           }
			      	}
                 Set[0] = 7;
                 Set[1] = 7;
                 Set[2] = 7;

                 for(int i=0; i<3; i++)
                 {
                     if(counter == (i + 1))
                     {
                        Set[i] = 2;
                     }
                 }
                 
 	  }
}
 #endif // end of defination
