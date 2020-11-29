/* Carl Hjorth */
/* cshj20@student.aau.dk */
/* Software A408B */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DICE 5
#define DIE_SIDES 6
#define DIE_COMBINATIONS 16

int randmax(int max);

void clearDice(int diceReg[]);

void rollDice(int dice, int diceReg[]);

void printDice(int diceReg[]);

int bonus(int diceReg[], int score[]);

int ofKind(int kind, int diceReg[]);

int differentPairs(int diceReg[]);

int smallStraight(int diceReg[]);

int largeStraight(int diceReg[]);

int fullHouse(int diceReg[]);

int chance(int diceReg[]);

int total(int score[]);

int main() {
	int scoreboard[DIE_COMBINATIONS];

	int diceRegister[DIE_SIDES];

	int dice, i = 0;

	/* setup random number generator */
	/* seed with time */
	srand(time(NULL));

	/* ask for user input */
	printf("yatzy with how many dice? ");
	scanf("%d", &dice);
	printf("\n");

	/* headline */
	printf("Combinations    : 1 2 3 4 5 6 : Score\n");
	printf("-------------------------------------\n");

	/* sum of dice with ones, twos, ... and sixes */
	for (; i < 6; ++i) {
		/* clears and fills diceRegister with new rolls */
		rollDice(dice, diceRegister);

		/* print name of combination and dice rolls */
		printf("%d-ere          ", i + 1);
		printDice(diceRegister);

		/* calculate score */
		if (diceRegister[i] >= MAX_DICE) {
			scoreboard[i] = 5 * (1 + i);
		}
		else {
			scoreboard[i] = diceRegister[i] * (1 + i);
		}

		/* print score */
		printf(": %d\n", scoreboard[i]);
	}

	/* bonus */
	for (; i < 7; ++i) {
		clearDice(diceRegister);

		printf("Bonus          ");
		printDice(diceRegister);

		scoreboard[i] = bonus(diceRegister, scoreboard);

		printf(": %d\n", scoreboard[i]);
	}

	/* one pair */
	for (; i < 8; ++i) {
		rollDice(dice, diceRegister);

		printf("One Pair       ");
		printDice(diceRegister);

		scoreboard[i] = ofKind(2, diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* two different pairs */
	for (; i < 9; ++i) {
		rollDice(dice, diceRegister);

		printf("Two Pairs      ");
		printDice(diceRegister);

		scoreboard[i] = differentPairs(diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* three of a kind */
	for (; i < 10; ++i) {
		rollDice(dice, diceRegister);

		printf("Three of a Kind");
		printDice(diceRegister);

		scoreboard[i] = ofKind(3, diceRegister);
		printf(": %d\n", scoreboard[i]);
	}

	/* four of a kind */
	for (; i < 11; ++i) {
		rollDice(dice, diceRegister);

		printf("Four of a Kind ");
		printDice(diceRegister);

		scoreboard[i] = ofKind(4, diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* small straight */
	for (; i < 12; ++i) {
		rollDice(dice, diceRegister);

		printf("Small Straight ");
		printDice(diceRegister);

		scoreboard[i] = smallStraight(diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* large straight */
	for (; i < 13; ++i) {
		rollDice(dice, diceRegister);

		printf("Large Straight ");
		printDice(diceRegister);

		scoreboard[i] = largeStraight(diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* full house */
	for (; i < 14; ++i) {
		rollDice(dice, diceRegister);

		printf("Full House     ");
		printDice(diceRegister);

		scoreboard[i] = fullHouse(diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* chance */
	for (; i < 15; ++i) {
		rollDice(dice, diceRegister);

		printf("Chance         ");
		printDice(diceRegister);

		scoreboard[i] = chance(diceRegister);

		printf(": %d\n", scoreboard[i]);
	}

	/* yatzy */
	for (; i < 16; ++i) {
		rollDice(dice, diceRegister);

		printf("Yatzy          ");
		printDice(diceRegister);

		/* if 5 dice have the same number gives 50 else 0 */
		scoreboard[i] = ofKind(5, diceRegister) ? 50 : 0;

		printf(": %d\n", scoreboard[i]);
	}

	/* Total score */
	printf("\nTotal == %d", total(scoreboard));

	return 0;
}

/* return random number between 0 and max */
int randmax(int max) {
	return rand() % (max + 1);
}

void clearDice(int diceReg[]) {
	int i;

	for (i = 0; i < DIE_SIDES; ++i) {
		diceReg[i] = 0;
	}
}

void rollDice(int dice, int diceReg[]) {
	int i;

	/* clear diceRegister of previous rolls */
	clearDice(diceReg);

	/* roll dice and keep track of rolled die */
	for (i = 0; i < dice; ++i) {
		int randomRoll = randmax(DIE_SIDES - 1);
		++diceReg[randomRoll];
	}
}

void printDice(int diceReg[]) {
	int i;

	printf(" : ");

	for (i = 0; i < DIE_SIDES; ++i) {
		printf("%d ", diceReg[i]);
	}
}

int bonus(int diceReg[], int score[]) {
	int i, sum = 0;

	for (i = 0; i < DIE_SIDES; ++i) {
		sum += score[i];
	}

	if (sum >= 63) {
		return 50;
	}

	return 0;
}

int ofKind(int kind, int diceReg[]) {
	int i, mem = 0;

	for (i = 0; i < DIE_SIDES; ++i) {
		/* look for x kinds */
		if (diceReg[i] >= kind) {
			/* calculate score */
			mem = (i + 1) * kind;
		}
	}

	return mem;
}

int differentPairs(int diceReg[]) {
	int i, pair1 = -1, pair2 = -1, bool = 0;

	for (i = 0; i < DIE_SIDES; ++i) {
		if (diceReg[i] >= 2) {
			/* alternate with storing in pair1 and pair2 */
			if (bool == 0) {
				pair1 = i;
				bool = 1;
			}
			else {
				pair2 = i;
				bool = 0;
			}
		}
	}

	/* check if two pairs */
	if (pair1 != -1 && pair2 != -1) {
		return (pair1 + 1) * 2 + (pair2 + 1) * 2;
	}

	return 0;
}

int smallStraight(int diceReg[]) {
	int i, count = 0;

	/* offset for small straight 0-4 */
	for (i = 0; i < DIE_SIDES - 1; ++i) {
		/* count the numbers in correct order */
		if (diceReg[i] >= 1) {
			++count;
		}
	}

	if (count == 5) {
		return 15;
	}

	return 0;
}

int largeStraight(int diceReg[]) {
	int i, count = 0;

	/* offset for large straight 1-5 */
	for (i = 1; i < DIE_SIDES; ++i) {
		/* count the numbers in correct order */
		if (diceReg[i] >= 1) {
			++count;
		}
	}

	if (count == 5) {
		return 20;
	}

	return 0;
}

int fullHouse(int diceReg[]) {
	int i, pair = -1, set = -1;

	for (i = 0; i < DIE_SIDES; ++i) {
		/* first look for set then pair */
		if (diceReg[i] >= 3) {
			/* a set is always a pair so if "set" is higher replace "pair" with "set" */
			if (set > pair) {
				pair = set;
			}
			set = i;
		}
		else if (diceReg[i] >= 2) {
			pair = i;
		}
	}

	/* check if there is both a pair and set */
	if (pair != -1 && set != -1) {
		return (pair + 1) * 2 + (set + 1) * 3;
	}

	return 0;
}

int chance(int diceReg[]) {
	int i, sum = 0, count = 0;


	for (i = DIE_SIDES - 1; i > 0; --i) {
		/* sum "DIE_SIDES" numbers in diceReg starting from highest die */
		sum += diceReg[i] * (i + 1);

		/* keep track of how many dice has been used */
		count += diceReg[i];

		if (count >= MAX_DICE) {

			/* correct if it overshoots allowed number of dice */
			sum -= (count-MAX_DICE) * (i + 1);

			break;
		}
	}

	return sum;
}

int total(int score[]) {
	int i, sum = 0;

	for (i = 0; i < DIE_COMBINATIONS; ++i) {
		sum += score[i];
	}

	return sum;
}