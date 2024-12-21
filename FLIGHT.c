//Program to implement flight information system
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int countuser=10;
//creating a structure to store flight details
struct Flight 
{
    char flightID[10];
    char source[20];
    char arrivalTime[10];
    char destination[20];
    char departureTime[10];
    float flightTime;
    float fare;
}flights[20];
//creating a structure to store cities
struct city
{
    char cities[20]; 
}city_list[7];
struct userdetails
{
    char username[20];
    char email[20];
    char password[20];
}user[20];
//Creating prototypes for function
void userdata();
void files();
void createnewaccount();
void login();  
void userlogin();
void displayallflights();
void displaysource();    
void displaysourcetodesination();   
int check();
//Main function
int main()
{
    int flightn=20,choice;
    //fetching all files
    files();
    userdata();
    //user login
    userlogin();

    //Asking user to select option
    
    do
    {
        printf("Select a option\n");
        printf("1.To check all the flights available.\n");
        printf("2.To check all the flights from once place.\n");
        printf("3.To check all the flights from one place to another place.\n");
        printf("4.To exit\n");
    //To verify user is giving option in intergers
        while((scanf("%d",&choice)!=1))
        {
            while(getchar()!='\n');
            printf("Error in option ,Please type respective option.\n");
        }
        switch(choice)
        {
            case 1:displayallflights();
                   break; 
            case 2:displaysource();       
                   break; 
            case 3:displaysourcetodesination(); 
                   break;      
            case 4:return 0;       
            default:printf("Invalid choice\n");
                    break;    
        }
    } while (choice!=4);
    return 0;   
}
void files()
{
    FILE *fp,*fp2;
    int i=0;
    //opening FLIGHT DETAILS csv file
    fp = fopen("FLIGHTDETAILS.csv", "r");
    if (fp == NULL) 
    {
        printf("Error opening file FLIGHT DETAILS");
        return ;
    }
    //opening LOCATION csv file
    fp2 = fopen("PLACES.csv", "r");
    if (fp2 == NULL) 
    {
        printf("Error opening file PLACES");
        return ;
    }
    
    //reading flight details from csv file
    char line1[60];
    while (fgets(line1, sizeof(line1), fp)){
        if(sscanf(line1, "%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f", &flights[i].flightID, &flights[i].source, &flights[i].arrivalTime, &flights[i].destination, &flights[i].departureTime, &flights[i].flightTime, &flights[i].fare) == 7) 
        {
            i++;
        }
    }
    i=0;
    char line2[60];
    //reading city details from csv file
     while (fscanf(fp2, "%s", city_list[i].cities) == 1) 
    {
        i++;
        if (i == 7) 
        {
            break;
        }
    } 
    //closing files
    fclose(fp);
    fclose(fp2);
}
void userdata()
{
    FILE *fp3;   
    fp3 = fopen("PLACES.csv", "r");
    if (fp3 == NULL) 
    {
        printf("Error opening user files");
        return ;
    } 
    int i=0;
    //reading user details
    char line3[60];
    while (fgets(line3, sizeof(line3), fp3))
    {
        if(sscanf(line3, "%[^,],%[^,],%[^,]", user[i].username,&user[i].email,&user[i].password)==3)
         {
            i++;
            countuser=i;
        }
    }
    //closing file
    fclose(fp3);
}
//function to display all flights
void displayallflights()
{
    //Displaying all flights
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int i=0;i<75;i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < 20; i++) 
    {
        printf("%-10s %-10s %-10s %-10s %-10s %-10.2f  %-10.2f\n",
               flights[i].flightID, flights[i].source, flights[i].arrivalTime,
               flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
    }
      for(int i=0;i<75;i++)
    {
        printf("-");
    }
    printf("\n");
}
//function to display a flight from user given source
void displaysource()
{
    int option;
    //Asking user to select a source
    jump_here1:
    printf("Select the source\n");
    for(int i=0;i<7;i++)
    {
        printf("%d.%s\n",i+1,city_list[i].cities);
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    if(option>=8)
    {
        printf("Please Enter different source\n");
        goto jump_here1;
    }
    printf("%s\n",city_list[option-1].cities);
    //Displaying all flights from selected source
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0)
        {
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }           
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
        printf("\n");
}    
//function to display flights from user given source and destination
void displaysourcetodesination()
{
    int option,option1,verify=0;
    float totaltime,totalfare;
    //Asking user to select the source
    jump_here2:
    printf("Select the source\n");
    for(int i=0;i<7;i++)
    {
        printf("%d.%s\n",i+1,city_list[i].cities);
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    printf("%s\n",city_list[option-1].cities);
    //Asking user to select destination
    printf("Select the destination\n");
    for(int i=0;i<7;i++)
    {
        if(strcmp(city_list[option-1].cities,city_list[i].cities)==0)
        {
            continue;
        }
        printf("%d.%s\n",i+1,city_list[i].cities);   
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option1)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    printf("%s\n",city_list[option1-1].cities);
    //Asking user to select different destination 
    if(city_list[option-1].cities==city_list[option1-1].cities||option1>=8||option>=8)
    {
        printf("Please Enter different destination\n");
        goto jump_here2;
    }
    //printing direct flights from source to destintation
    printf("%40s\n","DIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0 && strcmp(city_list[option1-1].cities,flights[i].destination)==0)
        {
            verify=1;
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }   
    //Displaying no direct files if not available
    if(verify==0)
    {
        printf("\t\t\tNO DIRECT FLIGHTS ):\n");
    }        
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n\n");
    verify=0;
    //Displaying Indirect flights
    printf("%40s\n","INDIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0 && strcmp(flights[j].source,flights[i].destination)==0 && strcmp(city_list[option1-1].cities,flights[j].destination)==0)
        {
            verify=1;
            printf("%s","**FLIGHT 1**\n\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
            printf("%s","\n**FLIGHT 2**\n\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[j].flightID, flights[j].source, flights[j].arrivalTime,
                    flights[j].destination, flights[j].departureTime, flights[j].flightTime, flights[j].fare);        
            totalfare=flights[i].fare+flights[j].fare;      
            totaltime=flights[i].flightTime+flights[j].flightTime;  
            printf("\n");
            printf("TOTAL TIME = %0.2f hours\n",totaltime);
            printf("TOTAL FARE = Rs. %0.2f\n",totalfare);
            for(int j=0;j<75;j++)
            {
                printf("-");
            }
        printf("\n");
        }
    }     
    //Displaying no Indirect files if not available
    if(verify==0)
    {
        printf("\t\t\tNO INDIRECT FLIGHTS ):\n");
        for(int j=0;j<75;j++)
        {
            printf("-");
        }
    }      
    printf("\n");
}
void userlogin()
{
    char option;
    for(int j=0;j<50;j++)
        {
            printf("-");
        }
    printf("\n");
    printf("%40s","Welcome to Flight Finder\n");
    printf("%5s","Do you have a travel account with us? [Y/N]\n");
    scanf("%c",&option);
    do
    {
            if (option == 'y' || option == 'Y') 
            {
                login();    
                return;               
            }
            else if(option == 'n'|| option == 'N')
            {
                createnewaccount();
                return;
            }
            else
            {
                printf("\nERROR: Please type [y/Y] or [n/N]: ");
            }    
    }while(1);     

}
void login()
{
    char name[20],password[20],option;
    int error,i=-1;
    here:
    if(i==2)
    {
        printf("10%s","All attempts are over :(\n");
        printf("Do you want to create new account\n");
        scanf("%c",&option);
        do
        {
            if (option == 'y' || option == 'Y') 
            {
                createnewaccount();    
                return;               
            }
            else if(option == 'n'|| option == 'N')
            {
                printf("10%s","Account signin Failed :(");
                    exit(0);
            }
            else
            {
                printf("\nERROR: Please type [y/Y] or [n/N]: \n");
            }    
        }while(1);     
        
    }
    i++;
    if(i==0)
    {
        printf("10%s","Please type the following details\n");
    }
    else
    {
    printf("Attempt %d\n",i);
    }
    printf("%s","Enter your username or email address.\n");
    scanf("%s",name);
    here1:
    printf("%s","Enter your password\n");
    scanf("%s",password);
    error=check(name,password);
    if(error==1)
    {
        goto here1;
    }
    else if(error==2)
    {
        goto here;
    }
    for(int j=0;j<50;j++)
    {
        printf("-");
    }
    printf("\n");
} 
int check(char name[20],char password[20])
{
    for(int i=0;i<countuser;i++)
    {
        //checking if given username or email is valid or not
        if( strcmp(name,user[i].username)==0||strcmp(name,user[i].email)==0)
        {
            if(strcmp(password,user[i].password)==0)
            {
                printf("%10s","Welcome Back!!  ");
                printf("s\n",user[i].username);
                return 0;
            }
            else
            {
                printf("Wrong password!! Please try again\n");
                return 1;
            }
        }
        else
        {
            printf("10%s","Please Enter valid username");
            return 2;
        }
    }
}    
void createnewaccount()
{
    char username[20],email[20],password[20];
    FILE *fp;
    fp = fopen("userdetails.csv", "a");
    if (fp == NULL) 
    {
        printf("Error opening file.\n");
        return ;
    }
    for(int i=0;i<50;i++)
        {
            printf("-");
        }
    printf("\n\n%10s","Lets create your new account :)\n");
    //asking user to enter details for their new account
    printf("%10s","Enter Your Username\n");
    scanf("%s",&username);
    printf("%10s","Enter your Email Adress\n");
    scanf("%s",&email);
    printf("%10s","Enter your password\n");
    scanf("%s",&password);
    fprintf(fp, "%s,%s,%s\n", username, email, password);
    for(int j=0;j<50;j++)
    {
        printf("-");
    }
    // Close the file
    fclose(fp);
    userdata();
    printf("\n%10s%s\n","Welcome!! ",username);
    printf("10%s","How may i help you\n");
}
    