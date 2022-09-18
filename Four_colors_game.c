#include <stdio.h>
#include <stdlib.h>

struct node{
    char data;
    struct node *next;
} *first = NULL;


//ListAdd for the path
void listAdd(char selection){
    
    struct node *nn, *temp;
    nn = (struct node *)malloc(sizeof(struct node));
    nn->data = selection;
    nn->next = NULL;
    
    if(first == NULL) first=nn;
    else{
        temp = first;
        
        while(temp->next != NULL)
            temp = temp->next;
        
        temp->next = nn;
    }
}


//isFull implementation to know if the space is filled.
int isFull(int rounds_played, int MAX_ROUNDS){
    if(rounds_played==MAX_ROUNDS) return 1;
    return 0;
}

void print_board(int **board, int rows, int cols){
    int i,j,letter=65;
    
    printf("   ");
    for(int i=0; i<cols; i++) 
        printf("%c  ",letter++);
    printf("\n");
    
    for(i=rows-1; i>=0; i--){
        printf("%d  ", i+1);
        
        for(j=0; j<cols; j++){
            
            if(board[i][j]==-1) printf(".  ");
            else if(board[i][j]) printf("O  ");
            else printf("X  ");
            
        }
        printf("\n");
    }
}

int check_row(int** board, int row, int col, int cols) {
    int cnt=0,mx=0,find=board[row][col];
    for(int i=0; i<cols; i++){
        if(board[row][i]==find) cnt++;
        else{
            mx= mx>cnt ? mx: cnt ;
            cnt=0;
        }
        
    }
    mx= mx>cnt ? mx: cnt ;
    return mx>=4;    
}

int check_col(int** board, int row, int col, int rows) {
    int cnt=0,mx=0,find=board[row][col];
    for(int i=0; i<rows; i++){
        if(board[i][col]==find) cnt++;
        else{
            mx= mx>cnt ? mx: cnt;
            cnt=0;
        }
    }
    mx= mx>cnt ? mx: cnt;
    return mx>=4;    
}

int check_diag(int** board, int row, int col, int rows, int cols) {
    int cnt=0,mx=0,find=board[row][col];
    int m= row<col ? row : col ;
    int i=row-m,j=col-m;
    
    
    while(i<rows && j<cols) {
        if(board[i][j]==find) cnt++;
        else{
            mx= mx>cnt ? mx: cnt;
            cnt=0;
        }
        i++;
        j++;
    }
    mx= mx>cnt ? mx: cnt;
    
    m= (rows-row-1)>col ? col: rows-row-1 ;
    i=row+m;
    j=col-m;
    cnt=0;
    
    while(i>=0 && j<cols) {
        if(board[i][j]==find) cnt++;
        else{
            mx= mx>cnt ? mx: cnt;
            cnt=0;
        }
        i--;
        j++;
    }
    mx= mx>cnt ? mx: cnt;
    
    return mx>=4;
}

int is_player_winner(int** board, int row, int col, int rows, int cols) {
   
     return check_col(board,row,col,rows) || check_row(board,row,col,cols) || check_diag(board,row,col,rows,cols) ;
}

int is_valid(int* filled, int rows, int col){
    
    return filled[col] != rows;
    
}

void update_board(int** board, int row, int col, int current_player){
    
    board[row][col]=current_player;
    
}

void update_player(int *current_player){
    *(current_player)^=1;
}

int** initialize_board(int rows, int cols)
{
    int** board = malloc(sizeof *board * rows);
    for (int i = 0;  i < rows;  i++) {
        board[i] = malloc(sizeof *board[i] * cols);
        for (int j = 0;  j < cols;  j++) {
            board[i][j] = -1;
        }
    }
    return board;
}

void print_instructions(int **board, int rows, int cols){
    
  printf("\t\t\t\tWelcome to my Connect Four game\n\n");
  printf("\t\t\tWhen prompted to make a move, simply enter the Column\n\t\t\t     corresponding to a tile of your choosing\n");
  printf("\t\t\t\tThe board will initalize as below: \n");
  printf("\t\t\t\t    Hit ENTER to start playing.\n");
  print_board(board, rows, cols);
  
}

void freeboard(int** board, int rows){
    
    for(int i=0; i<rows; i++)
        free(board[i]);
        
    free(board);
}

int main(){
    
    int** board, *filled;
    
    int rows, cols, rounds_played=0, MAX_ROUNDS, X_PLAY=0, O_PLAY=1;
    char selection;
    
    printf("Enter rows: ");
    scanf("%d",&rows);
    
    printf("Enter columns: ") ;
    scanf("%d",&cols);
    
    printf("\n");
  
    MAX_ROUNDS=rows*cols;
    board = initialize_board(rows,cols);
    filled= malloc(sizeof *filled *cols);
    
    for(int i=0; i<cols; i++) filled[i]=0;
    
    int current_player=X_PLAY;
    
    print_instructions(board, rows, cols);
    
    while(!isFull(rounds_played, MAX_ROUNDS)){
        
        //Stops when all the spaces are occupied.
        //Have to hit the enter to start the game.
        while((selection = getchar()) != '\n' && selection != EOF);
        
        //Column selection by the player
        printf("Player %d, please make a move: ", 1+current_player);
        scanf("%c", &selection);
        
        
        //Exact row in the column in question
        int col=(int)selection-65;

        if( is_valid(filled,rows,col)==1){
            //If the row is plausible..

            //To store the path in linked-lists
            listAdd(selection);
    
            //Board is updated based on the valid choice made.
            update_board(board, filled[col], col, current_player);
            
            print_board(board, rows, cols);
            
            //When rounds_played becomes equal to max the loop is bound to break
            rounds_played++;
            
                        
            //WHen a win is acheived
            if(is_player_winner(board, filled[col], col, rows, cols)){
                
                //Declare the winner and stop the game.
                printf("Player %d wins the game\n",1+current_player);
                break;
            }
            
            //Players are swapped
            update_player(&current_player);
            
            
            //Filled is a container keeping the size occupied in the particular column.
            filled[col]++;
            printf("\n");
        }
        else{
            
            //Overflow condition
            printf("That move is not valid, please try again...\n");
            continue;
            
        }
        
    }
    if(isFull(rounds_played, MAX_ROUNDS))
        printf("Game Over with no champion.\n");
            
    struct node *temp;
    temp = first;
    
    printf("BEGIN -> ");
    while(temp != NULL){
            
        printf("%c -> ",temp->data);
        temp = temp->next;
    }
    printf("END\n");
    
    //Frees the space
    freeboard(board, rows);
    
    return 0;
}