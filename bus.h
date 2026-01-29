#ifndef BUS_H
#define BUS_H

#include<unistd.h>
#define TOTAL_SEATS 40
#define FILE_NAME "bus.dat"

struct Seat {
    int seat_no;
    int is_booked;
    char name[50];
    char phone[15];
    char time[30];
};

void current_time(char *c_time, size_t size);
void seat_layout(void);
void initialize_seats(void);
void view_seats(void);
void book_seat(void);
void cancel_booking(void);
void view_passengers(void);

#endif