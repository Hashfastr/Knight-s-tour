#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//declarations
int **map, size, moves=0, padsize;
clock_t begin;

void endtour();
void knight();
void printout();

int main(int argc, char **argv) {
    //make sure we have the right argument #
    if (argc != 2) {
        printf("Usage: knight [board size]\n");
        return 0;
    }

    size=atoi(argv[1]);
    padsize=floor(log10(abs(size*size))) + 2;

    //allocate memory for the 2D array
    map=malloc(size * sizeof(int *));
    for (int i=0; i < size; i++)
        map[i]=malloc(size * sizeof(int));

    //zero out the array
    for (int i=0; i<size; i++) {
        for (int n=0; n<size; n++) {
            map[i][n]=0;
        }
    }

    begin = clock();
    knight(0, 0);

    printf("no solutions found...\n");
    return 0;
}

void knight(int x, int y) {
    if (x<size && y<size && y>=0 && x>=0) { //make sure we aren't going out of bounds
        if (map[x][y]==0) { //if spot is unused set it as used, if not, return
            //printf("good move...\n");
            moves++;
            map[x][y]=moves;
        }
        else return;
    }
    else return;

    //check to see if the tour is finished
    if (moves==(size*size)) endtour();

    knight(x+1, y-2);
    knight(x+1, y+2);
    knight(x-1, y-2);
    knight(x-1, y+2);
    knight(x+2, y-1);
    knight(x+2, y+1);
    knight(x-2, y-1);
    knight(x-2, y+1);

    //if all checked spots fail set reset spot, and return
    map[x][y]=0;
    moves--;
    return;
}

void printout() {
    for (int i=0; i<size; i++) { //rows
        for (int n=0; n<size; n++) { //collumns
            printf("%*d", padsize, map[i][n]);
        }
        printf("\n"); //reset row
    }
    printf("\n");
}

void endtour() {
    printout(); //print out solution
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time taken: %f secs\n", time_spent);

    exit(0); //   and exit
}
