#include <stdio.h>
#include <windows.h>
#include <string.h>

/***************
 * @file project.c
 * @author Nischal Baral
 * @brief It allows to create edit and cancel flights by admin and also reserve seat by users
*/

int loginid;
int log_in();
void admin();
void passenger();
void flight_status();
void flightstats_create();
void flightstats_change();
void cancel();
void reserve();
void reserve_check();
void txtadd(char []);
void txtadd_name(char []);//Declaring all the functions
void setcolor(int ForgC){//function to initialize the setcolor function
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
    }
 return;
}//refrence https://stackoverflow.com/questions/29574849/how-to-change-text-color-and-console-color-in-codeblocks

/***********
 * @brief The main function
 * Entry point of the function
 * 
 * @return 0
*/
int main(){
    top:
    loginid = log_in();//calling the login function
    if (loginid == 0){
        printf("Thank you for your valuable time");
        goto exit;//Condition for exiting the program
    }else if(loginid<=100){//Condition for entering admin pannel
        admin(loginid);//calling admin function
        goto top;
        }else{
        passenger();//calling the passenger function
        goto top;
    }
    exit:
    return 0;
}

/**
 * @brief login finction
 * function to take login id from user 
 * 
 * @return the user entered login id
 */
int log_in(){
    int id;
    printf("****************************************************************\n");
    printf("Enter your ID number \n");
    printf("To exit enter 0\n");
    printf("****************************************************************\n");
    scanf("%d",&id);
    return id;
}

/**
 * @brief admin function
 * function to display the admin options and and send to its respective module
 * 
 */
void admin(){
    int choice;
    selectadmin:
    printf("****************************************************************\n");
    printf("1. Check flight status\n");
    printf("2. Add flight\n");
    printf("3. Change flight status\n");
    printf("4. Cancel the flight\n");
    printf("5. Log out\n");
    printf("****************************************************************\n");
    //printing the options
    scanf("%d",&choice);//taking input of option choice
    switch(choice){
        case 1:
        flight_status();//calling flight_status()
        break;
        case 2:
        flightstats_create();//calling flightstats_create()
        break;
        case 3:
        flightstats_change();//calling flightstats_change()
        break;
        case 4:
        cancel();//calling cancel()
        break;
        case 5:
        printf("Successfully logged out\n");
        return;//exiting the function
        break;
        default:
        printf("Invalid choice\n");//default choice
        break;
    }
    goto selectadmin;
}
/**
 * @brief passenger finction
 * function to display passenger options and send to its respective module
 * 
 */

void passenger(){
    int choice;
    selectpassenger:
    printf("****************************************************************\n");
    printf("1. Check flight status\n");
    printf("2. Reserve a seat\n");
    printf("3. Check your reservations\n");
    printf("4. Log out\n");
    printf("****************************************************************\n");//printing the options
    scanf("%d",&choice);//taking input of option choice
    switch(choice){
        case 1:
        flight_status();//calling flight_status()
        break;
        case 2:
        reserve();//calling reserve()
        break;
        case 3:
        reserve_check();//calling reserve_check()
        break;
        case 4:
        printf("Successfully logged out\n");
        return;//exiting the function
        break;
        default:
        printf("Invalid choice\n");//default choice
        break;
    }
    goto selectpassenger;
}

/**
 * @brief function to print the status of entred flight
 * accessed from both admin and passenger pannel
 */
void flight_status(){
    char flight[6],statusprint[50],seat[40];
    printf("****************************************************************\n");
    printf("Enter the flight name\n");
    scanf("%s",&flight);//taking input of the user entred flight name
    txtadd(flight);//calling txtadd
    FILE *status = fopen(flight,"r");//opening the user entred file
    fscanf(status,"%s %s",&statusprint,&seat);//reading data from the opened file
    printf("%s\n\n",statusprint);//printing status
    if (statusprint[0] == 'C'&&statusprint[1] == 'A'&&statusprint[2] == 'N'&&statusprint[3] == 'C'){
        fclose(status);
        return;//checking if the flight is cancled
    }
    int count = 0,letter=65;
    printf(" 12345678910\n");
    for (int i = 0; i < 40; i++)
    {
        if( i%10==0){
            printf("%c",letter);
        }
        if (seat[i]=='0'){
            setcolor(2);
            printf("%c",240);
            setcolor(15);
        }else{
            setcolor(4);
            printf("%c",240);
            setcolor(15);
        }
        count++;
        if (count%10==0 && i>0){
            printf("\n");
            letter++;
        }
    }//printing the availabe seat in the required format
    printf("\n*****************************************************************\n");
    fclose(status);
    return;
}

/**
 * @brief function to change the flight status
 * accessed from admin pannel only
 * 
 */
void flightstats_change(){
    char flight[6],statusprint[50],seat[40];
    printf("****************************************************************\n");
    printf("Enter the flight name\n");
    scanf("%s",&flight);//taking input of name of flight
    txtadd(flight);//calling txtadd
    FILE *status = fopen(flight,"r");//opening the file of the entred flight
    fscanf(status,"%s %s",&statusprint,&seat);//reading the data
    fclose(status);//closing the file
    FILE *statuschange = fopen(flight,"w");//opening  the same file in write mode
    printf("\nEnter the flight status\n");
    scanf("%s",&statusprint);//asking for new status
    fprintf(statuschange,"%s %s",statusprint,seat);//storing the new data in the file
    fclose(statuschange);//closing the file
}

/**
 * @brief function to add .txt to the flight array 
 * required to change the user entred word into .txt file name
 * @param flight 
 * the user entred name of flight
 */
void txtadd(char flight[]){
    flight[3]='.';
    flight[4]='t';
    flight[5]='x';
    flight[6]='t';
    flight[7]='\0';
    return;
}

/**
 * @brief function to add .txt to the name array 
 * required to change the user entred word into .txt file name
 * @param name1
 * the user entred name of flight
 */
void txtadd_name(char name1[]){
    name1[3]='.';
    name1[4]='t';
    name1[5]='x';
    name1[6]='t';
    name1[7]='\0';
    return;
}

/**
 * @brief function to create new flight
 * 
 */
void flightstats_create(){
    char flight[6],newstatus[50],seat[40];
    for(int i=0;i<40;i++){seat[i]='0';};//loop for initializing all seats as empty
    printf("****************************************************************\n");
    printf("Enter the flight name\n");
    scanf("%s",&flight);//Asking the user for the name of the new flight
    txtadd(flight);//calling txtadd
    FILE *status = fopen(flight,"w");//opening new file for the flight
    printf("\nEnter the flight status\n");//asking the user for the initial status
    scanf("%s",&newstatus);
    fprintf(status,"%s %s",newstatus,seat);
    fclose(status);//closing the file
}

/**
 * @brief function to cancel the flight
 * can be accessed only through admin pannel
 * 
 */
void cancel(){
    char flight[6];
    printf("Enter the flight name\n");
    scanf("%s",&flight);//asking the user for the flight name
    txtadd(flight);//calling txtadd
    FILE *status = fopen(flight,"w");//opening the file
    fprintf(status,"CANCLED");//adding status as CANCLED
    fclose(status);//closing the file
}

/**
 * @brief function ot reserve the seat
 * can be accessed only throug passenger pannel
 * 
 */
void reserve(){
    char flight[6],statusprint[50],seat[40],seatchar,seatchar1,name1[6];
    int seatno,flag;
    printf("****************************************************************\n");
    printf("Enter the flight name\n");
    scanf("%s%*c",&flight);//asking for user input
    txtadd(flight);//calling txtadd
    
    
    FILE *status = fopen(flight,"r");//opening the file
    fscanf(status,"%s %s",&statusprint,&seat);//reading the file
    printf("%s",name1);
    printf("%s\n\n",statusprint);//printing the status
    if (statusprint[0] == 'C'&&statusprint[1] == 'A'&&statusprint[2] == 'N'&&statusprint[3] == 'C'){
        return;//checking if the flight is cancled
    }
    int count = 0,letter=65;
    printf(" 12345678910\n");
    for (int i = 0; i < 40; i++){
        if( i%10==0){
            printf("%c",letter);
        }
        if (seat[i]=='0'){
            setcolor(2);
            printf("%c",240);
            setcolor(15);
        }else{
            setcolor(4);
            printf("%c",240);
            setcolor(15);
        }
        count++;
        if (count%10==0 && i>0){
            printf("\n");
            letter++;//printing the available seats of the flight
        }
    }
    printf("\n****************************************************************\n");
    fclose(status);//closing the file
    FILE *reserve = fopen(flight,"w");//opening the same file in write mode
    selectagain:
    printf("Enter the seat\n");
    scanf("%c,%d",&seatchar,&seatno);//asking user for the seat selection
    if(seatchar=='A'){
        if (seat[seatno-1]=='0'){
            seat[seatno-1]='1';
            flag=1;
        }else{
            printf("Seat already taken\n");
            goto selectagain;
        }
    }
    if(seatchar=='B'){
        if (seat[seatno-1+10]=='0'){
            seat[seatno-1+10]='1';
            flag=2;
        }else{
            printf("Seat already taken\n");
            goto selectagain;
        }
    }
    if(seatchar=='C'){
        if (seat[seatno-1+20]=='0'){
            seat[seatno-1+20]='1';
            flag=3;
        }else{
            printf("Seat already taken\n");
            goto selectagain;
        }
    }
    if(seatchar=='D'){
        if (seat[seatno-1+30]=='0'){
            seat[seatno-1+30]='1'; 
            flag=4;
        }else{
            printf("Seat already taken\n");
            goto selectagain;
        }
    }//booking the seat after checking whether it is booked or not
    fprintf(reserve,"%s %s",statusprint,seat);//storing the data in the file
    fclose(reserve);//closing the file
    
    printf("\nEnter your reservation code\n");
    scanf("%s%*c",&name1);//asking for reservation code to store the reservation for later use
    txtadd_name(name1);//calling txtadd_name
    seatchar1=seatchar;
    FILE *passenger_file = fopen(name1,"a");//opening the file
    if (flag == 1){
        seatchar1 ='A';
    }else if(flag == 2){
        seatchar1 = 'B';
    }else if(flag == 3){
        seatchar1 = 'C';
    }else if(flag == 4){
        seatchar1 = 'D';
    }//checking the condition and setting the respective row
    fprintf(passenger_file,"%c %d\n",seatchar1,seatno);//storing the data in the file
    fclose(passenger_file);//closing the file
    printf("\nSeat Booked\n");//printing the seat booking was a success
    return;
}

/**
 * @brief function to check the reservation of the user
 * 
 */
void reserve_check(){
    char name1[6],seatrow;
    int seatno,ch;
    printf("Enter your reservation code\n");
    scanf("%s",&name1);//asking for reservation code
    txtadd_name(name1);//calling txtadd_name
    FILE *passenger_file = fopen(name1,"r");//opening the file
    printf("The reserved seats are :\n");
    while((ch=fgetc(passenger_file))!=EOF)
    {    
        printf("%c",ch);
    }//printing the data of the file
    printf("\n");
    fclose(passenger_file);//closing the file
    return;
}