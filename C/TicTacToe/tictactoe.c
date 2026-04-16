#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_SIZE 3
#define TITLE_DELAY 750000
#define AI_THINK_DELAY 500000


typedef struct {
    int x;
    int o;
    int draw;
} Score;

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    char player;
    Score score;
} Game;

void initializeGame(Game *game) {

    char initialBoard[BOARD_SIZE][BOARD_SIZE] = { 
        { '1', '2', '3' }, 
        { '4', '5', '6' }, 
        { '7', '8', '9' } 
    };

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
           game->board[i][j]=initialBoard[i][j];
        }
    }

} 

void printTitle() {

	printf("\033[H\033[J");
	printf("\033[31m");

	printf(
		"\n\n████████╗██╗ ██████╗\n"
		    "╚══██╔══╝██║██╔════╝\n"
		    "   ██║   ██║██║     \n"
		    "   ██║   ██║██║     \n"
		    "   ██║   ██║╚██████╗\n"
		    "   ╚═╝   ╚═╝ ╚═════╝\n"
	);

	usleep(TITLE_DELAY);
	printf("\033[H\033[J");

	printf("\033[32m");

	printf(
		"\n\n████████╗██╗ ██████╗              ████████╗ █████╗  ██████╗\n"
		    "╚══██╔══╝██║██╔════╝              ╚══██╔══╝██╔══██╗██╔════╝\n"
		    "   ██║   ██║██║         █████╗       ██║   ███████║██║     \n"
		    "   ██║   ██║██║         ╚════╝       ██║   ██╔══██║██║     \n"
		    "   ██║   ██║╚██████╗                 ██║   ██║  ██║╚██████╗\n"
		    "   ╚═╝   ╚═╝ ╚═════╝                 ╚═╝   ╚═╝  ╚═╝ ╚═════╝\n"
	);

	usleep(TITLE_DELAY);
	printf("\033[H\033[J");

	printf("\033[36m");

	printf(
		"\n\n████████╗██╗ ██████╗              ████████╗ █████╗  ██████╗              ████████╗ ██████╗ ███████╗\n"
		    "╚══██╔══╝██║██╔════╝              ╚══██╔══╝██╔══██╗██╔════╝              ╚══██╔══╝██╔═══██╗██╔════╝\n"
		    "   ██║   ██║██║         █████╗       ██║   ███████║██║         █████╗       ██║   ██║   ██║█████╗  \n"
		    "   ██║   ██║██║         ╚════╝       ██║   ██╔══██║██║         ╚════╝       ██║   ██║   ██║██╔══╝  \n"
		    "   ██║   ██║╚██████╗                 ██║   ██║  ██║╚██████╗                 ██║   ╚██████╔╝███████╗\n"
		    "   ╚═╝   ╚═╝ ╚═════╝                 ╚═╝   ╚═╝  ╚═╝ ╚═════╝                 ╚═╝    ╚═════╝ ╚══════╝\n"
	);

	usleep(TITLE_DELAY);
	printf("\033[H\033[J");
	printf("\033[0m");

}

void printBoard(Game *game) {
    printf("\033[H\033[J");
	printf("+---------------+---------------+-----------+\n");
    printf("| \033[1mX\033[0m's Score: %02d | \033[1mO\033[0m's Score: %02d | draws: %02d |\n", game->score.x, game->score.o, game->score.draw);
	printf("+---------------+---------------+-----------+\n");

    for(int i=0;i<BOARD_SIZE;i++){
        
        printf("\n\t+---+---+---+\n\t|");
        for(int j=0;j<BOARD_SIZE;j++){
            if( game->board[i][j] == 'X' )
                printf("\033[36;1m %c \033[0m|",game->board[i][j]);
            else if( game->board[i][j] == 'O' )
                printf("\033[31;1m %c \033[0m|",game->board[i][j]);
            else
            printf("\033[2m %c \033[0m|",game->board[i][j]);
        }

    }
    printf("\n\t+---+---+---+\n\n");

}

void userInput(Game *game) {

    int input;
    printf("Press zero to quit\n");
    printf("🗣 Where do you want to place your %c (1-9): ", game->player);
    while(1){
        if(scanf("%d",&input) != 1) {
            printf("🗣 Invalid input. Please enter a number between 1 and 9: ");
            while(getchar() != '\n');
        }
        else if(input>9 || input<0) {
            printf("🗣 Invalid input. Please enter a number between 1 and 9: ");
        }
        else if(input == 0){
            
            printf("🗣 Thanks for playing.\n");
            printf("🗣 Final Score\nX: %02d | O: %02d | Draws: %02d \n", game->score.x, game->score.o,game->score.draw);
            exit(0);

        }
        else {
            int row = (input - 1) / BOARD_SIZE;
            int column = (input - 1) % BOARD_SIZE;
        
            if(game->board[row][column] != 'X' && game->board[row][column] != 'O' ) {
                game->board[row][column] = game->player; 
                break;
            }
            else {
                printf("🗣 The block is already taken! Please try another block: ");
            }
        }
    }

    printBoard(game);
}

void switchPlayers(Game *game) {

    game->player = (game->player == 'X') ? 'O' : 'X';

}

int checkWinner(char Player, char Board[BOARD_SIZE][BOARD_SIZE]) {
    for(int i=0; i<BOARD_SIZE; i++){
        if (
            Board[i][0] == Player &&
            Board[i][1] == Player &&
            Board[i][2] == Player 
        )
            return 1;
        if (
            Board[0][i] == Player &&
            Board[1][i] == Player &&
            Board[2][i] == Player 
            )
            return 1;
    }

    if (
        Board[0][0] == Player &&
        Board[1][1] == Player &&
        Board[2][2] == Player 
    )
        return 1;

    if (
        Board[0][2] == Player &&
        Board[1][1] == Player &&
        Board[2][0] == Player 
    )
        return 1;

    return 0;


}

int checkDraw(char Board[BOARD_SIZE][BOARD_SIZE]) {

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){  
            if(Board[i][j] != 'X' && Board[i][j] != 'O' ) {
                 return 0;
            }
        }
    }
    return 1;
}

void updateScore(Game *game,char result) {

    if(result == 'X')
        game->score.x++;
    else if(result == 'O')
        game->score.o++;
    else if(result == 'D')   
        game->score.draw++;
    
}

void makePriorityMove(Game *game,int* row, int* col) {

    int priorityOrder[9][2] = {
        {1,1},                   //centre
        {0,0},{0,2},{2,2},{2,0}, //corners
        {0,1},{1,2},{2,1},{1,0}  //edges
    };

    for(int i=0;i<9;i++){
        
        int r = priorityOrder[i][0];
        int c = priorityOrder[i][1];

        if(game->board[r][c] != 'X' && game->board[r][c] != 'O' ) {
            *row = r;
            *col = c;
            return;
        }

        
    }

}

int evaluateGame(Game *game) {

    if(checkWinner('O', game->board))
        return +10;
    else if(checkWinner('X', game->board))
        return -10;
    else
        return 0;

}

int miniMax(Game *game, int depth, int isMaxing) {

    int score = evaluateGame(game);

    if (score == 10 || score == -10 )
        return score - depth;

    if (checkDraw(game->board)) 
        return 0;
    
    if(isMaxing) {

        int best = -1000;

        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){  
                if(game->board[i][j] != 'X' && game->board[i][j] != 'O' ) {
                    char backUp = game->board[i][j];

                    game->board[i][j] = 'O';
                    int score = miniMax(game,depth + 1,0);
                    best = (score > best) ? score : best;

                    game->board[i][j] = backUp;
                }
            }
        }

        return best;
    }

    else {
        int best = 1000;

        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){  
                if(game->board[i][j] != 'X' && game->board[i][j] != 'O' ) {
                    char backUp = game->board[i][j];

                    game->board[i][j] = 'X';
                    int score = miniMax(game,depth + 1,1);
                    best = (score < best) ? score : best;

                    game->board[i][j] = backUp;
                }
            }
        }

        return best;

    }

}

void bestMoveUsingMiniMax(Game *game,int* bestRow,int* bestCol) {

    int bestVal = -1000;

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){  
            if(game->board[i][j] != 'X' && game->board[i][j] != 'O' ) {
                 char backUp = game->board[i][j];
                 game->board[i][j] = 'O';

                int moveScore = miniMax(game,0,0);

                game->board[i][j] = backUp;

                if (moveScore > bestVal) {

                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveScore;

                }
            }
        }
    }


    
}

void aiPlayer(Game *game) {

    int row,col;

    int empty = 0;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){  
            if(game->board[i][j] != 'X' && game->board[i][j] != 'O' ) 
                 empty++;
        }
    }

    if(empty > 6) 
        makePriorityMove(game,&row,&col);
    else
        bestMoveUsingMiniMax(game,&row,&col);

    game->board[row][col] = game->player;

}

int quitOption(int scoreX,int scoreO, int draw, char* startingPlayer) {

    char choice;
    printf("🗣 Press \033[1mq\033[0m to quit press any other key to continue: ");
    scanf(" %c",&choice);
    if (choice == 'q' || choice == 'Q'){
        printf("🗣 Thanks for playing.\n");
        printf("🗣 Final Score\nX: %02d | O: %02d | Draws: %02d\n",scoreX, scoreO, draw);
        return 1;
    }
    else {
        *startingPlayer = (*startingPlayer == 'X') ? 'O' : 'X';
        return 0;
    }
}


int main() {

    Game game;
    char startingPlayer;
    char choice;

    game.score.x = 0;
    game.score.o = 0;
    game.score.draw = 0;

    printTitle();

    printf("Do you wanna play first? (y/n): ");
    scanf(" %c",&choice);

    if(choice == 'y' || choice == 'Y') 
        startingPlayer = 'X';
    else
        startingPlayer = 'O';


    while(1) {

        game.player = startingPlayer;
        initializeGame(&game);

        int gameOver = 0;

        while(!gameOver) {

            if(game.player == 'X') {
                printBoard(&game);
                userInput(&game);
            }
            else {
                printf("🗣 I'm thinking...\n");
                usleep(AI_THINK_DELAY);
                aiPlayer(&game);
                printBoard(&game);
            }

            if(checkWinner(game.player,game.board)) {

                updateScore(&game,game.player);
                printBoard(&game);
                printf("🗣 Player \033[1m%c\033[0m wins.\n", game.player);

                gameOver = 1;
                
            }
            else if(checkDraw(game.board)) {
                
                updateScore(&game,'D');
                printBoard(&game);
                printf("🗣 It's a draw game.\n"); 
                
                gameOver = 1;
                
            }

            if(!gameOver) {
                switchPlayers(&game);
            }
        }

        if(quitOption(game.score.x, game.score.o, game.score.draw, &startingPlayer)) 
                    return 0;

    }
   
    return 0;
}
