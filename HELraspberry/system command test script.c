/*
Auteur: Kaya Hartwig 2019
Dit programma is bedoeld om op een raspberry pi te draaien bij HEL Shooter.
Het vraagt om een wachtwoord en laat een filmpje zien.
Vereisten zijn dat de videospeler geïnstalleerd is (nog even kijken welke).
Wachtwoord is case sensitive

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> 


#define PWLENGTH 12
#define FALSE 0
#define TRUE 1

char inputstring[PWLENGTH+1];
char password[] = "O23 M18 S56 K94";
char passwordNoSpace[] = "O23M18S56K94";
int i, j;

int passwordCheck()
{
    printf( "\n>insert_password<\n"
            " ___ ___ ___ ___\r");
            
    for (i = 0; i<PWLENGTH; i++)
    {
        if(i%3 == 0) printf(" ");
        inputstring[i] = getche(); //getch() vereist geen enter
        if(inputstring[i] == '\b') return FALSE;
        if(inputstring[i] == '\r') {printf("\n\n>Access denied<");return FALSE;}
        
    }
    passwordNoSpace[PWLENGTH+1] = '\0';
    getchar(); //wordt gebruikt om te wachten op enter
    
    if(!strcmp(inputstring, password)|!strcmp(inputstring, passwordNoSpace)) {printf("\n>Acces granted<\n"); return TRUE;}
    else printf("\n>Access denied<");
}

int main()
{
    printf( "System_request_acces\n"
            "Connected_to_main_server_\n"
            "IP_34.47.201.9\n\n"
            "Boot device USB Authorisation required.\n");
    getch(); //getch wordt hier gebruikt om te wachten op any key
    printf( "Admin_GRU_Directorate\n"
            "User_Name_Pompstok2002\n");
            
    while(1)
    {
        int passreturn = passwordCheck();
        if(passreturn == FALSE) continue;
        if(passreturn == TRUE) break;
                    
    }
    
    system("figlet welcome_Pompstok2002");  
    //system("sudo apt -y install fortune");
    system("fortune [-s]");
    
    printf("Downloading files...\n");
    
    printf("\n");
    int percentage;
    for(percentage = 0; percentage <= 100; percentage += rand()%3)
    {
        clock_t wait_time = clock()+ rand()%100;
        while (clock() < wait_time);
        printf("Download at %d%%\r", percentage);
    }
    printf("Download at 100%%\n");

    system("pause");
        
    return 0;
}
