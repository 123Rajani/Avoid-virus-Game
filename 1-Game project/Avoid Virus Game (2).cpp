/*

INTE 11223 - Programming Concepts 

Mini Game Project - Y1S1

IM/2019/024 - Anupa Senevirathne
IM/2019/096 - Harini Jayasundara
IM/2019/098 - Dinithi Samaratunga
IM/2019/107 - Rajani Gunawardhana

                            ~ AVOID VIRUS GAME ~

Avoid Virus is a Command Prompt Console Game developed using C++ Programming language.  
It can be considered as an Obstacle Avoidance Game, where the man tries to avoid collisions with the virus. 
The man's movements are controlled by the spacebar.

*/

//Imported Header files
#include<iostream>
#include<conio.h>
#include <cstdlib>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

//Defined variables with values
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 90
#define MENU_WIDTH 20
#define v_SIZE 5
#define PIPE_DIF 45

using namespace std;
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	//Returns a handle for the standard input or output
COORD CursorPosition;								//Declaring cursor position variable

//Initiallizing global variables
int virusPos[3];
FILE *fptr;
int vPos[3];
int virusFlag[3];

//Draw "man" using array
char man[4][5] = { ' ','(','o',')',' ',
					' ','/','Ü','\\',' ',
					' ',' ','Ü',' ',' ',
					' ','/',' ','\\',' '};
					
int manPos = 6;		//Set the initial position of "man" array
int score = 0;      //Initialize the score to 0
int Lives =9;       //Initialize the Lives to 9
char p_name[100];   //Declare variable to store player name

void gotoxy(int x, int y)//This function takes x,y values an position the corresponding element
{
	CursorPosition.X = x;//Setting the X coordinate
	CursorPosition.Y = y;//Setting the Y coordinate
	SetConsoleCursorPosition(console, CursorPosition);//Setting position
}

//the function to customize the cursor
void setcursor(bool visible, DWORD size) 
{
	if(size == 0)//If condition to see whether size is equal to 0
		size = 20;	
	
	
	CONSOLE_CURSOR_INFO lpCursor;			//Declare cursor info structure
	lpCursor.bVisible = visible;			//Make the cursor visible
	lpCursor.dwSize = size;					//set the size of cursor to 20
	SetConsoleCursorInfo(console,&lpCursor);//Send the cursor info to the SetConsoleCursorInfo function
}

//Draws the borders in the game screen
void drawBorder(){ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Returns a handle for the standard input or output
    SetConsoleTextAttribute(hConsole, 9);			  //setting border colour as blue
			
	
	//Printing the horizontal border (Top and bottom borders)
	for(int i=0; i<=SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"±";//Printing a pattern the border 
		gotoxy(i,SCREEN_HEIGHT); cout<<"±";
	}
	
	//Printing the vertical borders
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
	
	//Printing the vertical borders
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"±";
	}
	SetConsoleTextAttribute(hConsole, 7);//set the text color to white
}

//Function to Generate new virus position 
void genVirus(int ind){
	vPos[ind] = 3 + rand()%14; 
}


//Function to draw the virus in the screen using cout statements
void drawVirus(int ind,int k){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Returns a handle for the standard input or output
    SetConsoleTextAttribute(hConsole, 10);			  //Printing the virus in green colour
    
	if( virusFlag[ind] == true ){
		int i=0;//Drawing the virus with positions in the screen
		    gotoxy(WIN_WIDTH-virusPos[ind]-10,k);     cout<<"  *   *  "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+1);   cout<<"   * *   "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+2);   cout<<"* * * * *";
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+3);   cout<<"   * *   "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+4);   cout<<"  *   *  ";
	} 
	SetConsoleTextAttribute(hConsole, 7);//Set txt color to white
}

//Function to erase the virus in the screen using cout statements
void eraseVirus(int ind,int k){
	if( virusFlag[ind] == true ){
		//Erasing the above drawn virus, using a for loop
		for(int i=0; i<virusPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k);   cout<<"         "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+1); cout<<"         "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+2); cout<<"         "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+3); cout<<"         "; 
			gotoxy(WIN_WIDTH-virusPos[ind]-10,k+4); cout<<"         "; 
		}		
	}
}


//Drawing the "man" on the screen using nested for loops
void drawMan(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+2,i+manPos); cout<<man[i][j];
		}
	}
}

//Erasing the above drawn "man" from the screen
void eraseman(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+2,i+manPos); cout<<" ";
		}
	}
}

//Invokes when the "man" and the "virus" collide
int collision(int k){
	//The if condition to check whether the "man" and the virus has the same position on the screen
	if( virusPos[0] >= 73  ){
		if( manPos>k-v_SIZE && manPos<k+v_SIZE){
				Lives=Lives-1;                 //Decrease the number of "Lives" the "man" has when collided with a virus
				return 1;
		}
	}
	return 0;
}

//The function to Print Game over message
void gameover(){
    
    cout<<""<<endl<<endl;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Returns a handle for the standard input or output
    SetConsoleTextAttribute(hConsole, 12);//Setting the colour of "GAME OVER" to red
    gotoxy(7,8) ;cout<<" --------------------------------------------------------------------------- "<<endl;
    gotoxy(7,9) ;cout<<" |    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    gotoxy(7,10);cout<<" |   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    gotoxy(7,11);cout<<" |   *  ****   *****   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    gotoxy(7,12);cout<<" |   *  *  *  *     *  *   *   * *           *    *    * *   *     * *     |"<<endl;
    gotoxy(7,13);cout<<" |    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    gotoxy(7,14);cout<<" ---------------------------------------------------------------------------"<<endl;
    gotoxy(7,15);cout<<""<<endl<<endl;
    SetConsoleTextAttribute(hConsole, 7);       //Reset colour to white
    gotoxy(7,16);cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<""<<endl<<endl;
	fptr=fopen("Scores.dat","a");               //Opening the Scores.dat file in append mode
	fprintf(fptr,"%s	%d \n",p_name,score);   //Printing the player name and score in the file
	fclose(fptr);								//close file
	
	getch();									//Get a character as user input
}

//Display the updated Player Score
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 6);cout<<"Score: "<<score<<endl;
}

//Display the updated Player Lives
void updateLives(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Lives: "<<Lives/3<<endl;
}

//Display game instructions
void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n ~ Press spacebar to make man jump     ~";
	cout<<"\n ~ Avoid viruses to earn points        ~";
	cout<<"\n ~ Each player has 3 lives             ~";
	cout<<"\n ~ Avoid touching borders              ~\n";
	cout<<"\n\nPress any key to go back to menu";
	getch();			//Getting character as user input
}


//Display all the usernames with their scores and highScore
void Highscore(){

	int max;
	char maxp[100];
	int s;
	char user[100];
	FILE * rptr;
	system("cls");
	cout<<"===========================HighScores===========================";
	cout<<"\n----------------------------------------------------------------\n\n";
		rptr=fopen("Scores.dat","r");       //Open Scores.dat file in read mode
		cout<<"\t\tName \t\t\t Score\n\n";  
		fscanf(rptr,"%s %d",user,&s);       //reading a line from the Scores.dat file
		max=s;								//Assign max to the first score
			while(!feof(rptr)){
				printf("\t\t%s \t\t\t %d\n",user,s);  //Print the name and score
				if(s>max){							  //check if the new score is higher than max
					max=s;							  //assign new maximum value to max variable
					strcpy(maxp,user);				  //copy the High scorer's name to "maxp" variable
				}
				fscanf(rptr,"%s %d",user,&s);		  //Read next line
			}
	cout<<"\n\t\tHigh Score :- ";	
	cout<<max<<"  (By "<<maxp<<")"<<"\n";			  //Print highscore with the player name
	cout<<"\n\nPress any key to go back to menu";
	getch();								//Getting character as user input
}


//The function to start the game
void play(){
	
	//Assigning values to variables
	manPos = 6;
	score = 0;
	virusFlag[0] = 1; 
	virusFlag[1] = 0;
	virusPos[0] = virusPos[1] = 4;
	
	system("cls"); 			//Clear the console
	drawBorder();			//Invoke drawBorder function
	genVirus(0);			//Generate a virus position
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//Returns a handle for the standard input or output
    SetConsoleTextAttribute(hConsole, 9);             	//change text colour to blue
	gotoxy(WIN_WIDTH + 9, 1);cout<<"Avoid Virus"; 		//Print the game name
	SetConsoleTextAttribute(hConsole, 7);				//Reset text colour to white

    SetConsoleTextAttribute(hConsole, 14);				//change text colour to Yellow
	gotoxy(WIN_WIDTH + 7, 4);cout<<"Player Name: "<<p_name; 	//Print playername
	SetConsoleTextAttribute(hConsole, 7);				//Reset text colour to white
	
	//Print statements
	gotoxy(WIN_WIDTH + 9, 7);cout<<"----------";
	gotoxy(WIN_WIDTH + 9, 9);cout<<"----------";
	gotoxy(WIN_WIDTH + 10, 15);cout<<"Control ";
	gotoxy(WIN_WIDTH + 9, 16);cout<<"--------- ";
	gotoxy(WIN_WIDTH + 5, 17);cout<<" Spacebar = jump";     	
	gotoxy(10, 5);cout<<"Press any key to start";
	
	getch();   			//Get any character as user input
	gotoxy(10, 5);cout<<"                      ";	//Clear the last instruction
	
	//Declare integer variables
	int k;
	int y;
	int l;
	
	//The while loop to keep the game running until terminated
	while(1){
		 
		//If condition to determine whether a key has been pressed or not
		if(kbhit()){
			char ch = getch();    //Take the user input character and store in "ch"
			
			//If condition to check whether the spacebar is pressed
			if(ch==32){
				if( manPos > 6 )  // If spacebar is pressed, set the new position of the man
					manPos-=6;
			} 
			
			//If condition to check whether the esc button is pressed
			if(ch==27){
				break;            //If esc is pressed, terminate the game
			}
		}
		
		drawMan();                //Draw the man icon
		
		//Check the while condition to see whether the random number 'k' is within the screen limit
		while(k>20 || k<1){
			k=rand();			  //generate a random number in order to print a virus
		}
		
		
		drawVirus(0,k);			  //Draw the virus icon
		
		//the if condition to see whether the man has collided with a virus
		if( collision(k) == 1 ){
		updateLives(); 			 //Update lifecount when collided with a virus
		
			//The if condition to check whether the lifecount is less than 0
			if(Lives<=0){
				gameover();		 //invoke game over function if the lifecount is less than 0
				Lives=9;		 //Re initialize Lifecount to 9
				return;			 //Terminate the game
			}
		}

		Sleep(60);				 //Pause the process temporarily for 60 miliseconds
		eraseman();				 //Erase the man icon
		eraseVirus(0,k);		 //Erase the virus
		manPos += 1;			 //Increase the position of the man icon
		
		//check if the man icon touches the bottom of the screen
		if( manPos > SCREEN_HEIGHT - 4 ){
			Lives=9;			//Re initialize lifecount to 9
			gameover();			//Invoke the gameover function
			return;				//terminate the game
		}
		
		//Change the virus position when the Flag value is equal to 1
		if( virusFlag[0] == 1 ){
			virusPos[0] += 2;
	    }
		
		//The if condition to check whether the position of the virus is in a specific range
		if( virusPos[0] >= 60 && virusPos[0] < 61 ){
			virusFlag[1] = 1;
			virusPos[1] = 4;
			genVirus(1);			//Generate a new virus position
		}
		
		//The if condition to check whether the position of the virus is in a specific range
		if( virusPos[0] > 79 ){
			k=rand();					//Generate the random number
			score++;					//Increment the score
			updateScore();				//set the new score
			virusFlag[1] = 0;
			virusPos[0] = virusPos[1];
		}		
	}
	
	
	 
}

//The function that invokes before the play function
void beforestart(){
	
	setcursor(0,0); 			  //Position the cursor
	srand((unsigned)time(NULL));  //generate random number using current time
	
	//Declaring file pointer and local variables
	FILE * rptr;
	int state=1,s;
	char user[100];
	
	system("cls");       		//Clearing the console
	
	//The do while loop for entering a player name
	do{
		state=1;				//Initializing state to 1
		system("cls");			//Clearing the console
		gotoxy(10,8); cout<<"Enter Player Name (Limit to 6 characters ) : "; //	Print statement
		
				cin>>p_name; 			//Take username as input
			
				rptr=fopen("Scores.dat","a"); //creating scores.dat file
				fclose(rptr);				  //Closing the file from append mode
				
				rptr=fopen("Scores.dat","r");//opening scores.dat file in read mode
				fscanf(rptr,"%s %d",user,&s);//reading a line from the file
			
				//The while loop to read all the content from the file
				while(!feof(rptr)){
					//Check if the user entered name is already there in the scores.dat file
					
					//The if condition to check whether the username is already existing
					if(!strcmp(p_name,user)){	
					
						//Printing error messages if the username is already there in the scores.dat file
						gotoxy(10,23); cout<<"-----------Name Already exist!!!--------";
						gotoxy(10,24); cout<<"-----------Please pick another name--------";
						gotoxy(10,25); cout<<"-----------Press any key to continue--------";
						getche();
						state=0; // Setting state variable to 0 if the usernames are duplicated
						break;
					}
					fscanf(rptr,"%s %d",user,&s);     //reading a line from the file
				}	
	}while(state==0);

	play();			//Invoking the play function
}


//The stating function of the game
int main()
{
	setcursor(0,0); 				//Position the cursor
	srand((unsigned)time(NULL)); 	//generate random number using current time

	//The do while loop to get user input as characters
	do{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    //Returns a handle for the standard input or output
            SetConsoleTextAttribute(hConsole, 9);				  //change text colour to blue
					
			system("cls");  			//Clearing the console
			
			//Printing the title
		    cout << "-----------------------------------------------------------------------------------------------------------------  " << endl;
    	    cout << "|                                                                                                               | " << endl;
    	    cout << "|       **    *         *  ********  *****  *******       *          *  *****  *******   *      * *******       | " << endl;
    	    cout << "|      *  *    *       *   *      *    *      *    *       *        *     *    *     *   *      * *             | " << endl;
    	    cout << "|     ******    *     *    *      *    *      *    *        *      *      *    *******   *      * *******       | " << endl;
            cout << "|    *       *   *   *     *      *    *      *    *         *    *       *    *   *     *      *       *       | " << endl;
	        cout << "|   *         *   * *      ********  *****  *******           * *       *****  *     *   ******** *******       | " << endl;
	        cout << "|                                                                                                         v 1.0 | " << endl;
	        cout << "----------------------------------------------------------------------------------------------------------------- " << endl;
	        cout << "" << endl << endl;

			SetConsoleTextAttribute(hConsole, 7);//Reset text colour to white
					
		gotoxy(10,11); cout<<"1. Start Game";
		gotoxy(10,12); cout<<"2. Instructions";	
		gotoxy(10,13); cout<<"3. High Scores";
		gotoxy(10,14); cout<<"4. Quit";
		gotoxy(10,15); cout<<"Select option: ";
		char op = getche();							//Getting character as user input
		SetConsoleTextAttribute(hConsole, 7);
		if( op=='1') beforestart();					//Invoke the "beforestart" function if the user press 1
		else if( op=='2') instructions();			//Invoke the "instructions" function if the user press 2
		else if( op=='3') Highscore();				//Invoke the "Highscore" function if the user press 3
		else if( op=='4') exit(0);					//Invoke the "exit" systemcall if the user press 4
		
	}while(1);				
	
	return 0;
}
