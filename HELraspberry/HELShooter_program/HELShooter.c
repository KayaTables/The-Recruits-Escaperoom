/*
Kaya Hartwig 2019
This program asks for a password (hardcoded) and continues with a login animation.
Password is case sensitive.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define PWLENGTH 12
#define FALSE 0
#define TRUE 1

char inputstring[PWLENGTH+1];
char password[] = "O23 M18 S56 K94";
char passwordNoSpace[] = "O23M18S56K94";
int i, j;

int passwordCheck()
{
    
    printf( "\n\r>insert_password<\n\r"
            " ___ ___ ___ ___\r");
            
    for (i = 0; i<PWLENGTH; i++)
    {
        if(i%3 == 0) printf(" ");
        
        inputstring[i] = getchar(); 
        if(inputstring[i] == '\b') return FALSE;
        if(inputstring[i] == '\r') {printf("\n\n\r>Access denied<");return FALSE;}
        
    }
    passwordNoSpace[PWLENGTH+1] = '\0';
    getchar(); //wait for enter
    
    if(!strcmp(inputstring, password)|!strcmp(inputstring, passwordNoSpace)) {printf("\n\r>Acces granted<\n\r"); return TRUE;}
    else printf("\n\r>Access denied<");
}

int main()
{
    system("clear");
    printf( "System_request_acces\n\r"
            "Connected_to_main_server_\n\r"
            "IP_34.47.201.9\n\n\r"
            "Insert USB Authorisor to log in, press CTRL + ALT + DEL to reboot or press 'g' for GUI.\n\r");
    if(getchar() == 'g') {system("startx"); return 0;} //wait for enter (go to GUI on 'g')
    
    system("figlet -t -f banner Admin_GRU_Directorate");
    printf( //"Admin_GRU_Directorate\n\r"
            "User_Name_Pompstok2002\n\r");
            
    while(1)
    {
        system ("/bin/stty raw"); //tijdens wachtwoord check niet wachten op enter
        int passreturn = passwordCheck();
        system ("/bin/stty cooked"); //nu weer wel wachten op enter
        //break;
        if(passreturn == FALSE) continue;
        if(passreturn == TRUE) break;
        
                    
    }
    
      
    //system("sudo apt -y install fortune");
    printf("\n\r");
    system("fortune -s");
    
    printf("\nDownloading files...\n\r");
    
    printf("\n\r");
    
    volatile int percentage;
    for(percentage = 0; percentage < 100; percentage += random()%5)
    {
        printf("Download at %d%%\r", percentage);
        fflush(stdout);
        usleep(random()%100000);
    }
    printf("Download at 100%%\n\r");
    
    
    //print source 
  
    int i;
    char c;FILE *f;
	f=fopen("/home/pi/Documents/HELShooter_program/HELShooter.c","r");
	for (i=0;i<2655;i++)
    {
        c=fgetc(f);
        usleep(random()%10000);
        putchar(c);
    }
    
    system("omxplayer /home/pi/Documents/HELShooter_program/video.mp4");
    
    return 0;
}
