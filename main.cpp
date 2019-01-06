#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

char tic[4][4] = {}, playerOne[23], playerTwo[23];
int x_rowCount=0, x_colCount=0, o_rowCount=0, o_colCount=0, x_wins, o_wins, allCellsFilled, giliran;

void cetakHeader() {
	system("cls");
	printf("##################################################################################\n");
	printf("#                    Tic Tac Toe by Putu Prema (Early Access)                    #\n");
	printf("##################################################################################\n\n");	
}			

void init() {
	x_rowCount=0, x_colCount=0, o_rowCount=0, o_colCount=0, x_wins=0, o_wins=0, allCellsFilled=0, giliran=1;
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			tic[i][j] = '_';
		}
	}
}

void cetakTic() {
	printf("  ");
	for (int i=1; i<=3; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (int i=0; i<3; i++) {
		printf("%d|", i+1);
		for (int j=0; j<3; j++) {
			printf("%c|", tic[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void masukin(int a, int b) {
	switch (giliran) {
		case 1 : tic[b][a] = 'X'; break;
		case 2 : tic[b][a] = 'O'; break;
	}	
}

void cekMenang() {
	switch (giliran) {
		case 1 :
			/* ####### CEK MENANG PLAYER 1 ####### */
			for (int i=0; i<3; i++) {
				for (int j=0; j<3; j++) {
					if (tic[i][j] == 'X') {
						x_rowCount++;
						if (x_rowCount == 3) {
							x_wins = 1;
							break;
						}
					}
				}
				if (x_wins == 1) {
					break;
				}
				x_rowCount = 0;
			}
			
			for (int j=0; j<3; j++) {
				for (int i=0; i<3; i++) {
					if (tic[i][j] == 'X') {
						x_colCount++;
						if (x_colCount == 3) {
							x_wins = 1;
							break;
						}
					}
				}
				if (x_wins == 1) {
					break;
				}
				x_colCount = 0;
			}
			
			x_rowCount = 0;
			x_colCount = 0;	
		break;
		case 2 :
			/* ####### CEK MENANG PLAYER 2 ####### */
			for (int i=0; i<3; i++) {
				for (int j=0; j<3; j++) {
					if (tic[i][j] == 'O') {
						o_rowCount++;
						if (o_rowCount == 3) {
							o_wins = 1;
							break;
						}
					}
				}
				if (o_wins == 1) {
					break;
				}
				o_rowCount = 0;
			}
			
			for (int j=0; j<3; j++) {
				for (int i=0; i<3; i++) {
					if (tic[i][j] == 'O') {
						o_colCount++;
						if (o_colCount == 3) {
							o_wins = 1;
							break;
						}
					}
				}
				if (o_wins == 1) {
					break;
				}
				o_colCount = 0;
			}
			
			o_rowCount = 0;
			o_colCount = 0;	
		break;			
	}
}

void cekDraw() {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (tic[i][j] != '_') {
				allCellsFilled = 1;
			} else {
				allCellsFilled = 0;
				break;
			}			
		}
		if (allCellsFilled == 0) {break;}
	}
}

void randomize() {
	time_t t;
	srand((unsigned) time(&t));
	
	giliran = (rand() % 2) + 1;
}

void playerName() {
	cetakHeader();
	
	do {
		printf("Player One (5-20 characters) : ");
		gets(playerOne); //getchar();		
	} while (strlen(playerOne) < 5 || strlen(playerOne) > 20);

	do {
		printf("Player Two (5-20 characters) : ");
		gets(playerTwo); //getchar();		
	} while (strlen(playerTwo) < 5 || strlen(playerTwo) > 20);
}

void goPlay() {
	int x,y;

	init();
	playerName();
	randomize();
	
	while (true) {
		cetakHeader();
		cetakTic();
	
		if ((x_wins == 1) && (o_wins == 0)) {
			printf("%s WINS!\n", playerOne); break;
		} else if ((x_wins == 0) && (o_wins == 1)){
			printf("%s WINS!\n", playerTwo); break;
		} else if ((allCellsFilled == 1) && (x_wins == o_wins)) {
			printf("DRAW!\n"); break;		
		} else {
			if (giliran == 1) {
				printf("%s\'s turn [\'X\']\n", playerOne, giliran);
			} else if (giliran == 2) {
				printf("%s\'s turn [\'O\']\n", playerTwo, giliran);
			}
		}
		
		inputCoordinate:
		do {
			printf("Input X Coordinate [1 - 3]: "); scanf("%d", &x);	
		} while (x < 1 || x > 3);
		
		do {
			printf("Input Y Coordinate [1 - 3]: "); scanf("%d", &y);
		} while (y < 1 || y > 3);
	
		if (tic[y-1][x-1] != '_') {
			printf("Coordinate X and Y has been taken!!\n");
			goto inputCoordinate;
		}
		
		masukin(x-1,y-1);
		cekMenang();	
		cekDraw();
		
		switch (giliran) {
			case 1 : giliran = 2; break;
			case 2 : giliran = 1; break;
		}	

		system("pause");			
	}
}

void goHow() {
	cetakHeader();
	printf("How To Play :\n");
	printf("1. The program will randomly generate which player start first\n");
	printf("2. The player who have the turn will have to choose X and Y coordinates on the board\n");
	printf("3. The program will change the player each turn\n\n");
	printf("How To Win :\n");
	printf("One of the player must have 3 X\'s or O\'s in a row vertically or horizontally\n\n");
}

int main() {
	int menuInput;
	
	mainMenu:
	cetakHeader();
	
	printf("1. Play Game\n");
	printf("2. How To Play\n");
	printf("3. Exit\n\n");
	printf("Your Choice: ");
	
	scanf("%d", &menuInput); getchar();

	switch (menuInput) {
		case 1: goPlay(); system("pause"); goto mainMenu; break;
		case 2: goHow(); system("pause"); goto mainMenu; break;
		case 3: goto exit; break;
		default: printf("\nInvalid input.\n"); system("pause"); goto mainMenu; break;
	}
	
	exit:
	cetakHeader();
	printf("Thanks for playing :)\n");	
	system("pause");
	
	return 0;
}
