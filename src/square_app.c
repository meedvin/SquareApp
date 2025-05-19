
#include <stdio.h>

// FUNCTION PROTOTYPES
int run_app(void);
int calc_squares(int);

// Function that wrapps the I/O and calculations.
int run_app(){

    int n = 0;
    int res = 0;

    printf("\n----Square Calculator Application----\n");
    printf("To exit the application, input n=0\n\n");
    printf("---------------------\n");

    while (1)
    {

        printf("Input the value of n (int): ");

        // Make sure scanf is successfull
        if (!scanf("%d", &n)){
            printf("ERROR! Scanf was unsuccessfull!\n");
            return -1;
        }

        // Check that a valid number was received
        if (n < 0){
            printf("ERROR! Invalid problem size!\n");
            return -1;
        }

            // Check if we should exit on user request
        if (n == 0){
            printf("Exiting application.\n");
            return 1;
        }

        res = calc_squares(n);

        printf("Result: %d\n", res);
        printf("---------------------\n");
    }

    return 0;
} 


// Recursively calculates the number of individual squares 
// for n*n squares.
int calc_squares(int n){
    int res = 0;
    
    if (n > 1)
        res = calc_squares(n-1);

    res += n*n;

    return res;
}