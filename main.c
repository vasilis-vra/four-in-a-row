#include <stdio.h>
#include <stdlib.h>


//function initialization
int checkWinner();
void keyInput(int counter,int input);
void printTable();
int checkWinner();
void nextMove();
int evaluateMove(int row, int col);

//initialize table 7x7
char gameTable[7][7];


int main()
{
    //table initialization
    int i,j;

    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            gameTable[i][j]='-';
        }
    }

    int counter=0;
    int gameMode;

    printf("Choose Game Mode: \n 1. Player 1 vs Player 2\n 2. Player 1 vs Computer\n");
    while(scanf("%d", &gameMode) != 1 || (gameMode!=1 &&gameMode!=2)){  //scan for gameMode to be either 1 or 2, 1 to play against another player
            printf("Error: Wrong Input\n");                             //or 2 to play against a computer
			printf("Choose opponent: \n 1. Player 1 vs Player 2\n 2. Player 1 vs Computer\n\n");
			while( (getchar() !='\n') );
        	}
    //if gameMode==1 the player plays against another human player
    if(gameMode==1){
        while(!checkWinner()&&counter<49){
            printTable();
            int inp;
            printf("Choose table column(1-7): \n");
            if(counter%2==0) printf("Player 1(+): \n");
            else printf("Player 2(*): \n");
            while(scanf("%d", &inp) != 1 ||inp<1 ||inp>7){
                printf("Error: Wrong Input\n");
                printf("Choose table column(1-7): \n");
                while( (getchar() !='\n') );
            }
            if(gameTable[0][inp-1]!='-'){
                printf("The column is full, select another column\n");
                continue;
            }
            keyInput(counter,inp);
            counter++;
        }
        if(counter==49)printf("It's a draw!\n");
        if(checkWinner()==1) printf("Player 1 Wins! \n");
        else if(checkWinner()==2) printf("Player 2 Wins! \n");
    }
    //if gameMode==2 then the player plays against the computer
    else if(gameMode==2){
        while(checkWinner()==0&&counter<49){
            printTable();
            int inp;
            if(counter%2==0){
                printf("Choose table column(1-7): \n");
                printf("Player 1(+): \n");
                while(scanf("%d", &inp) != 1 ||inp<1 ||inp>7){
                    printf("Error: Wrong Input\n");
                    printf("Choose table column(1-7): \n");
                    while( (getchar() !='\n') );
                }
                if(gameTable[0][inp-1]!='-'){
                    printf("The column is full, select another column\n");
                    continue;
                }
                keyInput(counter,inp);
            }
            else{
                nextMove();
                printf("Computer has made a move! \n");
            }

            counter++;
        }
        if(counter==49)printf("It's a draw!\n");
        if(checkWinner()==1) printf("Player 1 Wins! \n");
        else if(checkWinner()==2) printf("Computer Wins! \n");
    }
    printTable();
    return 0;
}
//function that prints the table
void printTable(){
    int i,j;
    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            printf("%c\t",gameTable[i][j]);
        }
        printf("\n");
    }

}
//function that inputs the disk for each player, depending on the player's turn and input disk
void keyInput(int counter,int input){
    char c;
    int i;
    if(counter%2==0) c='+';
    else c='*';
    for(i=6; i>=0; i--){
        if(gameTable[i][input-1]=='-'){
            gameTable[i][input-1]=c;
            break;
        }
    }
}
//function that finds the winner, returns 0 for no winner, 1 for player 1, and 2 for player 2 or computer
int checkWinner(){
    int i,j;
    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            if(gameTable[i][j]!='-'){
                char c = gameTable[i][j];
                if(i<4){
                    if((gameTable[i+1][j]==c) &&(gameTable[i+2][j]==c)&&(gameTable[i+3][j]==c)){
                        if(c=='+') return 1;
                        else return 2;
                    }
                }
                if(j<4){
                    if(gameTable[i][j+1]==c&&gameTable[i][j+2]==c&&gameTable[i][j+3]==c){
                        if(c=='+') return 1;
                        else return 2;
                    }
                }
                if(i<4&&j<4){
                    if(gameTable[i+1][j+1]==c&&gameTable[i+2][j+2]==c&&gameTable[i+3][j+3]==c){
                        if(c=='+') return 1;
                        else return 2;
                    }
                }
                if(i<4&&j>2){
                    if(gameTable[i+1][j-1]==c&&gameTable[i+2][j-2]==c&&gameTable[i+3][j-3]==c){
                        if(c=='+') return 1;
                        else return 2;
                    }
                }
            }
        }
    }
    return 0;
}
//function that finds next computer turn
//for every possible column the computer checks if the input wins
//if it wins the computer selects this column as the input
//if there is not winner column the computer checks if there is
//a column for which the opponent wins and selects this column as input
//so that the opponent doesn't win. if there is also no such column then
//the computer selects the column that is evaluated to be the best.
void nextMove(){
    int i,j;
    //check if there is a winning column for the computer
    for(j=0; j<7; j++){
        if(gameTable[0][j]!='-') continue; //column is full
        for(i=6; i>=0; i--){
            if(gameTable[i][j]=='-'){
                gameTable[i][j]='*';
                if(checkWinner()==2) return;
                else gameTable[i][j]='-';
                break;
            }
        }
    }
    //checks if there is a winning column for the opponent
    for(j=0; j<7; j++){
        if(gameTable[0][j]!='-') continue; //column is full
        for(i=6; i>=0; i--){
            if(gameTable[i][j]=='-'){
                gameTable[i][j]='+';
                if(checkWinner()==1){
                    gameTable[i][j]='*';
                    return;
                }
                else gameTable[i][j]='-';
                break;
            }
        }
    }


                        //else for every possible column as input call the evaluating function to find the best move
    int value=-1;   //then if the value returned from the evaluating function is higher than the previous value
    int row,col;    //we store the row and column till we check all the possible columns. The last row and column
    for(j=0; j<7; j++){         //that we stored are the position that has returned the highest value.
        if(gameTable[0][j]!='-') continue; //column is full
        for(i=6; i>=0; i--){
            if(gameTable[i][j]=='-'){
               if(evaluateMove(i,j)>value){
                value = evaluateMove(i,j);
                row=i;
                col=j;
               }
               break;
            }
        }
    }
    //computer inputs the disk at the best possible position, the one that returned the highest value
    //from the evaluating function
    gameTable[row][col]='*';

}

//evaluating function to find the best move for the computer
//the function uses as input the row and column given by the nextMove function
//the function calculates and returns the value of the given position
//the higher the value the better the position to play.

int evaluateMove(int row, int col){
    int val=0;  //initialize value as 0
    //for the given position we increment the value +1 if there is another '*' next to the given position
    //so that we prefer to input the disk close to another disk of the same type.
    if(row>0){
        if(col>0){
            if(gameTable[row-1][col-1]=='*') val++;
        }
        if(gameTable[row-1][col]=='*') val++;
        if(col<6){
            if(gameTable[row-1][col+1]=='*') val++;
        }
    }
    if(row<6){
        if(col>0){
            if(gameTable[row+1][col-1]=='*') val++;
        }
        if(gameTable[row+1][col]=='*') val++;

        if(col<6){
            if(gameTable[row+1][col+1]=='*') val++;
        }
    }
    if(col>0){
        if(gameTable[row][col-1]=='*') val++;
    }
    if(col<6){
        if(gameTable[row][col+1]=='*') val++;
    }

    //middle col is the best column so the value has to be better
    //so we increment the value +1 if the col is the middle one.
    //also in the first round when the computer inputs the first disk
    //the computer will start at the middle column as it is the best start for this strategy.
    if(col==3)val++;

    //check if the opponent has two disks in a row in the middle columns
    //this is a dangerous combination because if the opponent forms three disks in a row with empty positions on both sides
    //then the opponent wins. As a result we increment the value by 2 to avoid this type of situation.
    if(col<4){
        if(gameTable[row][col+1]=='+'&&gameTable[row][col+2]=='+'){
            val=val+2;
        }
    }
    if(col>2){
        if(gameTable[row][col-1]=='+'&&gameTable[row][col-2]=='+'){
        val=val+2;
        }
    }


    //if there is a row above the row under evaluation check if the cell exactly above the cell
    //under evaluation gives a winner position for the opponent so that we exclude this cell
    //and avoid the opponent winning.
    if(row!=0){
        if(gameTable[row-1][col]=='-'){
            gameTable[row-1][col]='+';
            if(checkWinner()==1){
                    val=-1;
            }
            gameTable[row-1][col]='-';
        }
    }

    return val;
}
