#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 10
#define COLOURS 7

typedef struct MastermindCombination {
    int slot[4];
} MastermindCombination;

MastermindCombination generate() {
    MastermindCombination combination;
    srand(time(NULL));
    for(int i = 0; i < 4; i++) {
        do combination.slot[i] = rand() % COLOURS; while(combination.slot[i] == 0);
    }
    return combination;
}

char letters[COLOURS] = {'#', 'Y', 'G', 'B', 'P', 'M', 'O'};

void print(MastermindCombination combination);

int getNumberFromLetter(char letter) {
    for(int i = 0; i < COLOURS; i++) {
        if(letters[i] == letter) {
            return i;
        }
    }
    return -1;
}

char get(int number) {
    return letters[number];
}

void print(MastermindCombination combination) {
    for(int i = 0; i < 4; i++) {
        printf("%c", get(combination.slot[i]));
    }
    printf("\n");
}

MastermindCombination saisir() {
    MastermindCombination combination;
    char letter;
    for(int i = 0; i < 4; i++) {
        do {
            printf("Saisir la lettre %d: \n", i + 1);
            scanf(" %c", &letter);
            getchar();
        } while(getNumberFromLetter(letter) == -1);
        combination.slot[i] = getNumberFromLetter(letter);
    }
    return combination;
}

int compareCombinations(MastermindCombination secret, MastermindCombination player) {
    int red = 0, white = 0;
    for (int i = 0; i < 4; i++) {
        if (secret.slot[i] == player.slot[i]) {
            red++;
        } else {
            for (int j = 0; j < 4; j++) {
                if(i == j) continue;
                if (secret.slot[i] == player.slot[j]) {
                    white++;
                    break;
                }
            }
        }
    }

    if(red == 4) {
        printf("Bravo, vous avez gagne!\n");
        return 1;
    }

    for(int i = 0; i < red; i++) {
        printf("R");
    }
    for(int i = 0; i < white; i++) {
        printf("W");
    }
    int none = 4 - red - white;
    for(int i = 0; i < none; i++) {
        printf("#");
    }

    printf("\n");
    return 0;
}

int main() {
    MastermindCombination mastermindCombination = generate();
    print(mastermindCombination);
    int tries = 0;
    do {
        tries++;
        printf("Essai %d\n", tries);
        MastermindCombination playerCombination = saisir();
        int valid = compareCombinations(mastermindCombination, playerCombination);

        if(valid == 1) break;

    } while(tries < MAX_TRIES);
    return 0;
}