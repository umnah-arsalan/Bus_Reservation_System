#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "bus.h"

void Current_time(char *c_time, size_t size) {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    strftime(c_time, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void initialize_seats() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int i;

    if (fp) {
        fclose(fp);
        return;
    }

    fp = fopen(FILE_NAME, "wb");

    for (i = 1; i <= TOTAL_SEATS; i++) {
        s.seat_no = i;
        s.is_booked = 0;
        strcpy(s.name, "EMPTY");
        strcpy(s.phone, "-");

        fwrite(&s, sizeof(struct Seat), 1, fp);
    }
    fclose(fp);
}

void view_seats() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (!fp) {
        printf("\nFile doesn't exist!\n\n");
        return;
    }

    printf("\nSeat No  Status\n");
    printf("---------------\n\n");

    while (fread(&s, sizeof(struct Seat), 1, fp)) {
        printf("%-8d %s\n", s.seat_no, s.is_booked ? "Booked" : "Available");
    }

    fclose(fp);
}

void book_seat() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb+");
    int seat_no;

    if (!fp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter seat number: ");
    scanf("%d", &seat_no);

    if (seat_no < 1 || seat_no > TOTAL_SEATS) {
        printf("\nInvalid seat number!\n\n");
        return;
    }

    while (fread(&s, sizeof(struct Seat), 1, fp)) {
        if (seat_no == s.seat_no) {

            if (s.is_booked) {
                printf("\nSeat already booked!\n");
                fclose(fp);
                return;
            }

            printf("Enter name of passenger: ");
            scanf(" %[^\n]", s.name);

            printf("Enter contact number: ");
            scanf(" %[^\n]", s.phone);

            s.is_booked = 1;
            Current_time(s.time, sizeof(s.time));

            fseek(fp, -sizeof(struct Seat), SEEK_CUR);
            fwrite(&s, sizeof(struct Seat), 1, fp);

            printf("\nSeat booked successfully!\n\n");
            break;
        }
    }
    fclose(fp);
}

void cancel_booking() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb+");
    int seat_no;

    if (!fp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter seat number to cancel: ");
    scanf("%d", &seat_no);

    if (seat_no < 1 || seat_no > TOTAL_SEATS) {
        printf("\nInvalid seat number!\n\n");
        return;
    }

    while (fread(&s, sizeof(struct Seat), 1, fp)) {
        if (seat_no == s.seat_no) {

            if (!s.is_booked) {
                printf("\nSeat is not booked!\n\n");
                fclose(fp);
                return;
            }

            strcpy(s.name, "EMPTY");
            strcpy(s.phone, "-");

            s.is_booked = 0;
            strcpy(s.time, "");

            fseek(fp, -sizeof(struct Seat), SEEK_CUR);
            fwrite(&s, sizeof(struct Seat), 1, fp);

            printf("\nBooking cancelled!\n\n");
            break;
        }
    }
    fclose(fp);
}

void view_passengers() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (!fp) {
        printf("\nFile doesn't exist!\n\n");
        return;
    }

    printf("\nSeat No  Status     Passenger Name  Contact      Date\n");
    printf("---------------\n\n");

    while (fread(&s, sizeof(struct Seat), 1, fp)) {
        printf("%-8d %-10s %-15s %-12s %s\n", s.seat_no, s.is_booked ? "Booked" : "Available", s.name, s.phone, s.time);
    }

    printf("\n");
    fclose(fp);
}

void seat_layout() {
    struct Seat s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int count = 0;

    if (!fp) {
        printf("\nNo seat data to print!\n\n");
        return;
    }

    printf("\n-----------------Bus Seat Layout-----------------\n\n");

    while (fread(&s, sizeof(struct Seat), 1, fp)) {
        if (s.is_booked)
            printf("[XX] ");
        else
            printf("[%02d] ", s.seat_no);

        count++;

        if (count % 10 == 0)
            printf("\n");
    }

    printf("\n");
    fclose(fp);
}