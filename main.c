#include<stdio.h>
#include<stdlib.h>
#include "bus.h"

int main() {
    int choice;

    initialize_seats();

    while (1) {
        printf("---Bus Reservation System---\n\n");
        printf("1. View seat status\n");
        printf("2. Book a seat\n");
        printf("3. Cancel booking\n");
        printf("4. View passengers\n");
        printf("5. View seat layout\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: view_seats(); break;
            case 2: book_seat(); break;
            case 3: cancel_booking(); break;
            case 4: view_passengers(); break;
            case 5: seat_layout(); break;
            case 6: exit(0);
            default: printf("\nInvalid option!\n\n");
        }
    }
    return 0;
}