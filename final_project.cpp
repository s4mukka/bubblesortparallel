// Author: Samuel Henrique Ferreira Pereira
// Objective: Study the Bubble Sort Parallel
// University: Universidade Federal de São Carlos (UFSCar)
// Date: 03/07/2020


// Libraries
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>

// Constants
#define QTD_TEST 100
int SIZE = pow(2,13);

// Subroutines
int *createVector();
void swap(int *, int *);
void printVector(int *vector);

// Function Main
int main(int, char**) {
    // Seed
    srand( (unsigned) time(NULL) );

    // Set the number threads   
    omp_set_num_threads(8);

    // Initialize average
    double average = 0;

    // Initialize time
    clock_t start, stop;

    for(int n = 0; n < QTD_TEST; n++) {
        // Create a vector
        int *vector = createVector();

        // Start time
        start = clock();

        // Bubble Sort Sequential
        // for(int i = 0; i < SIZE; i++)
        //     for(int j = 1; j < SIZE; j++)
        //         if(vector[j - 1] > vector[j])
        //             swap(&vector[j - 1], &vector[ j ]);

        // Bubble Sort Parallel
        for(int i = 0; i < SIZE; i++) {
            int first = i % 2;

            #pragma omp parallel for default(none), shared(vector,first,SIZE)
            for(int j = first; j < SIZE; j+=2)
                if(vector[j - 1] > vector[j])
                    swap(&vector[j - 1], &vector[ j ]);
        }
        
        // printVector(vector);
        
        // Stop time
        stop = clock();

        // Increment time
        average += (stop - start) * 1000 / (double)CLOCKS_PER_SEC;

        // Delete a vector
        delete[] vector;
    }

    // Calculate arithmetic average
    average /= QTD_TEST;

    // Print average
    std::cout << "Average time: " << average << " ms" <<std::endl;

    return 0;
}

// Function that creates a vector with random values
int *createVector() {
    // Allocate vector
    int *vector = new int[SIZE];

    // Initialize with random values
    for(int i = 0; i < SIZE; i++)
        vector[i] = rand() % SIZE + 1;

    // return the vector
    return vector;
}

// Function that swap two variables
void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

// Function that print a vector
void printVector(int *vector) {

    for (int i = 0; i < SIZE; i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
}