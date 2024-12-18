#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    printf("*******************************\n");
    printf("* Welcome to the guessing game*\n");   
    printf("*******************************\n");

    // Making the numbers random
    int seconds = time(0);
    srand(seconds);
    int bigNum = rand(); 

    int secret = bigNum % 100;
    printf("secret!: %d\n", secret);

    int tries = 1;
    int guess;
    double points = 1000;
    int isright = 0;

    int level;
    printf("Game difficulty?\n");
    printf("(1) Easy (2) Medium (3) Hard\n\n");
    printf("Choice: ");
    scanf("%d", &level);

    int triesAmmount;
    switch(level){
        case 1:
            triesAmmount = 20;
            break;
        case 2:
            triesAmmount = 15;
            break;
        case 3:
            triesAmmount = 6;
            break;
        default:
            printf("Invalid option\n");
            break;
    }

    for (int i = 1; i <= triesAmmount; i++) {

        printf("Guess %d\n", tries);

        printf("What's your guess? ");
        scanf("%d",&guess);

        if (guess < 0){
            printf("Negative numbers not allowed!\n");

            continue;
        }

        isright = (guess == secret);

        if (isright) {
            break;
        }
        if (guess > secret){
            printf("Number too high\n");
        }
        else{
            printf("Number too low\n");
        }

        tries ++;

        double lostNumbers = abs(guess - secret) / (double)2;
        points = points - lostNumbers;

    }

    if (isright){
        printf("You won!\n");
        printf("You made it with %d tries\n", tries);
        printf("Total points scored: %.1f\n", points);
    } else{
        printf("You lost! Try again!\n");

    }
}
