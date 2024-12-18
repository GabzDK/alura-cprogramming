#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hang.h"

char secret[WORD_SIZE];
char guesses[26];
int guess_count= 0;


void opening(){
    printf("*************\n");
    printf("*  hangman  *\n");
    printf("*************\n\n");
}

void add_word(){
    char want;
    printf("Do you want to add a new word word? Y/N \n");
    scanf(" %c", &want);

    if(want == 'Y'){

        char new_word[WORD_SIZE];
        printf("What is the new word?: ");
        scanf("%s", new_word);

        FILE* f;

        f = fopen("words.txt", "r+");

        if(f == 0){
            printf("Sorry database not found.\n");
            exit(1);
        }

        int lines;
        fscanf(f,"%d", &lines);
        lines++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", lines);


        fseek(f, 0, SEEK_END);
        fprintf(f,"\n%s", new_word);
        fclose(f);
    }

}

void get_guess() {

    char guess;
    scanf(" %c", &guess);
    guesses[guess_count] = guess;
    guess_count++;

}

int have_guessed(char letter) {
    int found = 0;

    for(int j = 0; j < guess_count; j++){
        if(guesses[j] == letter){
            found = 1;
            break;
        }
    }

    return found;

}

void draw() {
    int wrong = wrong_guesses();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (wrong>=1?'(':' '), 
           (wrong>=1?'_':' '), (wrong>=1?')':' '));
    printf(" |      %c%c%c  \n", (wrong>=3?'\\':' '), 
           (wrong>=2?'|':' '), (wrong>=3?'/': ' '));
    printf(" |       %c     \n", (wrong>=2?'|':' '));
    printf(" |      %c %c   \n", (wrong>=4?'/':' '), 
           (wrong>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(secret);i++){

        int found = have_guessed(secret[i]);

        if(found){
            printf("%c ", secret[i]);
        }
        else{
            printf("_ ");
        }

    }

    printf("\n");
}
int wrong_guesses(){

    int wrong = 0;

    for(int i = 0; i < guess_count; i++){
        int right = 0;

        if(have_guessed(secret[i])){
            right = 1;
            break;
        }

        if(!right) wrong++;
    }
    return wrong;

}

void choose_word() {

    FILE* f; 
    f = fopen("words.txt", "r");

    if(f == 0){
        printf("Sorry database not found.\n");
        exit(1);
    }

    int wordcount;
    fscanf(f, "%d", &wordcount);

    srand(time(0));
    int random = rand() % wordcount;

    for(int i = 0; i <= random; i++){
        fscanf(f, "%s", secret);
    }

    fclose(f);
}

int won(){
    for(int i = 0; i < strlen(secret); i++){
        if(!have_guessed(secret[i])){
            return 0;
        }
    }
    return 1;

}

int hanged(){
    return wrong_guesses()>=5;
}

int main(){

    choose_word();
    opening();

    do { 

        draw();
        get_guess();

    }while (!won() && !hanged());
    if(won()){
        printf("                YOU WON!           \n\n"),
        printf("              .-=========-.\n");
        printf("              '-=======-'/\n");
        printf("              _|   .=.   |_ \n");
        printf("             ((|  {{1}}  |))\n");
        printf("              \\|   /|\\   |/ \n");
        printf("               \\__ '`' __/\n");
        printf("                 _`) (`_ \n");
        printf("              _/_______\\_ \n");
        printf("              /___________\\\n");
    add_word();
        
    }else{
        printf("          LOSER!!!! \n");

    printf("        .-"      "-. \n");
    printf("       /            \\ \n");
    printf("      |              | \n");
    printf("      |,  .-.  .-.  ,| \n");
    printf("      | )(__/  \\__)( | \n");
    printf("      |/     /\\     \\| \n");
    printf("      (_     ^^     _) \n");
    printf("       \\__|IIIIII|__/ \n");
    printf("        | \\IIIIII/ | \n");
    printf("        \\          / \n");
    printf("         `--------` \n\n");

    }

}
