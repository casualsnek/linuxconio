#include <conio.h>
int main()
{
    char input;
    char *password;
    int row, col;
    
    while(!kbhit())
    {
        printf("Press any key!\n");
    }
    input=getche();
    printf("You just pressed --> %c \n", input);
    
    
    printf("Press any key to clear the screen\n");
    getch();
    
    
    clrscr();
    printf("The screen successfully cleared\n");
    
    password = getpass("Enter Password: ");
    printf("The password is : %s\n",password);

    printf("Getting location of cursor for this line !");
    wherexy(&row, &col);
    printf("\nYou were on Row: %d and Column: %d \n", row, col);
    
    printf("Press any key to move to Row: 9 Column 4 and edit the line: ");
    getch();
    gotoxy(9, 4);
    printf("You now see that it is edited .. Press any key to clear the screen and continue!");
    getch();
    clrscr();
    
    printf("Now changing background color to green and text color to black \n");
    textbackground(GREEN);
    textcolor(BLACK);
    printf("Some colorful text here \n");
    
    
    printf("Press any key to delete last line (This line)");
    getch();
    delline();

    printf("\nFinished ! Press any key to exit..");	
    getch();
 
    return 0;
}
