#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10
#define X 88 // Case non découverte
#define M 77 // Case minée


typedef char tab[N][N];

int a = 3;
int MINE = 0;
int cpt = 0;
void func(a);


void Ini(char a[N][N], char c[N][N]);
void niveauDeJeu(tab, tab);
void AfficheT(tab);
void placeM(tab);
void jeu(tab, tab);
void ClearInput();
char getInputChar(const char* message, const char* authorizedCharacter, int length);
int getInputInt(const char* message, int min, int max);
int isMine(tab T, int i, int j);
int getMineArround(tab TM, tab TJ, int i, int j);
void reavealCase(tab TM, tab TJ, int i, int j);


int main()
{


	tab TM; // Tableau des mines
	tab TJ; // Tableau de jeu
	char ON = 'o';
	while (ON == 'o') {
		srand((unsigned int)time(NULL));

		Ini(TM, TJ);

		niveauDeJeu(TM, TJ);

		placeM(TM); // Placement des mines (M)

		jeu(TM, TJ);

		ON = getInputChar("Voulez vous rejouez ? \n o : oui  n : non \n -> ", "on", 2);
		cpt = 0;

		system("cls");
	}
	if (ON == 'n') {
		printf("\nReessayer une autre fois\n");
	}
	return 0;

}
void Ini(tab TM, tab TJ) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			TM[i][j] = X;
			TJ[i][j] = X;
		}
	}
}

void AfficheT(tab T) {
	int i, j;
	int c = 0;

	printf("   ");
	for (c = 0; c < N; c++) {
		printf("%d  ", c);
	}
	c = 0;
	printf("\n\n");

	for (i = 0; i < N; i++) {
		printf("%d  ", c);
		c++;
		for (j = 0; j < N; j++) {
			printf("%c  ", T[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void placeM(tab TM) {
	int i, j;
	int cm;
	for (cm = 0; cm < MINE; cm++) {
		i = rand() % N;
		j = rand() % N;
		if (TM[i][j] == M) {
			while (TM[i][j] == M) {
				i = rand() % N;
				j = rand() % N;
			}
			TM[i][j] = M;
		}
		else {
			TM[i][j] = M;
		}
	}
}

void niveauDeJeu(tab TM, tab TJ) {
	int niveau;
	niveau = getInputInt("Quel niveau souhaitez-vous ? [1, 2, 3]", 1, 4);

	switch (niveau) {
	case 1:
		MINE = 10;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
		break;
	case 2:
		MINE = 20;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
		break;
	case 3:
		MINE = 30;
		printf("La difficulte est de %d et il y as %d mines dans tout le tableaux\n", niveau, MINE);
		break;
	}
}

void ClearInput()
{
	while (getchar() != '\n');
}

int getInputInt(const char* message, int min, int max)
{
	int value;
	int error;
	do {
		printf("%s", message);
		error = scanf_s("%d", &value);
		ClearInput();
	} while ((error == 0) || (value < min) || (value >= max));
	return value;
}

char getInputChar(const char* message, const char* authorizedCharacter, int length)
{
	int error_scan;
	int error_char;
	char caract;

	do {
		printf("%s", message);
		error_scan = scanf_s("%c", &caract);
		ClearInput();

		error_char = 0;
		for (int i = 0; i < length; ++i) {
			if (caract == authorizedCharacter[i]) {
				error_char = 1;
			}
		}
	} while ((error_scan == 0) || (error_char == 0));

	return caract;
}

void jeu(tab TM, tab TJ) {
	int CL;
	int CC;
	char CD = 'c';
	int perdu = -1;
	int nbcasesm = N * N - MINE; // Nombre de cases sans mine

	printf("\nJeu du demineur\n\n");

	while ((perdu == -1)) {
		AfficheT(TJ);
		//AfficheT(TM);
		CD = getInputChar("Voulez vous jouer : c ou poser un drapeau : d ou retirer un drapeau : r -> ", "cdr", 3);
		if (CD == 'd') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			if (TJ[CL][CC] != X) {
				printf("Vous avez deja rentre cette valeur.\n\n");
			}
			if (TJ[CL][CC] == 'X') {
				TJ[CL][CC] = 80;
			}

			printf("\n");
			system("cls");


		}
		if (CD == 'r') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			if (TJ[CL][CC] == 80) {
				TJ[CL][CC] = 88;
			}


			printf("\n");
			system("cls");
		}
		if (CD == 'c') {
			CL = getInputInt("\nEntrer le numero de la ligne : ", 0, N);

			CC = getInputInt("Entrer le numero de la colonne : ", 0, N);
			printf("\n");
			system("cls");
			if (TJ[CL][CC] != X && TJ[CL][CC] != 80) {
				printf("Vous avez deja rentre cette valeur.\n\n");
				continue;
			}

			if (TM[CL][CC] == M && TJ[CL][CC] != 80) {
				perdu = 1; // VOUS AVEZ PERDU!
				printf("C'est une mine :O\n\n");
				break;
			}
			reavealCase(TM, TJ, CL, CC); // Recherche du nombre de mines aux alentours
			if (cpt == nbcasesm)
			{
				perdu = 0;
				printf("Vous avez gagne!\n\n");
			}
		}
	}

	if (perdu == 1) {
		printf("Game Over\n\n");

	}

}

int isMine(tab T, int i, int j)
{
	if (i < 0 || i >= N)
		return 0;

	if (j < 0 || j >= N)
		return 0;

	if (T[i][j] != M)
		return 0;

	return 1;
}
int getMineArround(tab TM, tab TJ, int i, int j)
{
	int mineCount = 48;

	mineCount += isMine(TM, i - 1, j);
	mineCount += isMine(TM, i + 1, j);
	mineCount += isMine(TM, i - 1, j - 1);
	mineCount += isMine(TM, i - 1, j + 1);
	mineCount += isMine(TM, i + 1, j - 1);
	mineCount += isMine(TM, i + 1, j + 1);
	mineCount += isMine(TM, i, j - 1);
	mineCount += isMine(TM, i, j + 1);
	return mineCount;
}

void reavealCase(tab TM, tab TJ, int i, int j)//Il n'y a pas de mines autour donc detruire autour du 0
{
	if (i < 0 || i >= N)
		return;

	if (j < 0 || j >= N)
		return;

	if (TJ[i][j] != 'X')
		return;

	cpt++;
	TJ[i][j] = getMineArround(TM, TJ, i, j);
	if (TJ[i][j] != 48)
		return;

	reavealCase(TM, TJ, i - 1, j - 1);
	reavealCase(TM, TJ, i - 1, j);
	reavealCase(TM, TJ, i - 1, j + 1);

	reavealCase(TM, TJ, i, j + 1);
	reavealCase(TM, TJ, i, j - 1);

	reavealCase(TM, TJ, i + 1, j - 1);
	reavealCase(TM, TJ, i + 1, j);
	reavealCase(TM, TJ, i + 1, j + 1);
}