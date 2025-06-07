#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 20
#define MAX_SEATS 30
#define MAX_PASSENGERS 200

struct Seat {
    int seatNumber;
    int isBooked;
    char seatClass[15];
    float price;
};

struct Flight {
    char flightNo[10];
    char source[20];
    char destination[20];
    char date[15];
    char time[10];
    char type[15];
    struct Seat seats[MAX_SEATS];
};

struct Passenger {
    char name[50];
    int age;
    char gender;
    char flightNo[10];
    int seatNumber;
    char seatClass[15];
    float price;
};

struct Flight flights[MAX_FLIGHTS];
struct Passenger passengers[MAX_PASSENGERS];
int totalPassengers = 0;

void initFlights() {
    char *flightNos[20] = {
        "KB111", "DN112", "MH113", "CH114", "BL115",
        "GA211", "HY212", "AD213", "PN214", "LK215",
        "LN311", "DB312", "PR313", "NY314", "SF315",
        "FR316", "TK317", "HK318", "SG319", "OS320"
    };
    char *sources[20] = {
        "Kolkata", "Delhi", "Mumbai", "Chennai", "Bangalore",
        "Goa", "Hyderabad", "Ahmedabad", "Pune", "Lucknow",
        "Kolkata", "Mumbai", "Delhi", "Chennai", "Hyderabad",
        "Kolkata", "Goa", "Mumbai", "Delhi", "Bangalore"
    };
    char *destinations[20] = {
        "Delhi", "Mumbai", "Chennai", "Bangalore", "Goa",
        "Pune", "Ahmedabad", "Lucknow", "Bhubaneswar", "Jaipur",
        "London", "Dubai", "Paris", "New York", "San Francisco",
        "Frankfurt", "Tokyo", "Hong Kong", "Singapore", "Osaka"
    };
    char *dates[20] = {
        "2025-06-10", "2025-06-11", "2025-06-12", "2025-06-13", "2025-06-14",
        "2025-06-10", "2025-06-11", "2025-06-12", "2025-06-13", "2025-06-14",
        "2025-06-15", "2025-06-16", "2025-06-17", "2025-06-18", "2025-06-19",
        "2025-06-20", "2025-06-21", "2025-06-22", "2025-06-23", "2025-06-24"
    };
    char *times[20] = {
        "08:00", "09:30", "10:45", "12:15", "13:00",
        "14:20", "15:30", "16:40", "17:50", "18:30",
        "19:00", "20:10", "21:15", "22:30", "23:45",
        "00:50", "01:30", "02:15", "03:00", "04:45"
    };

    for (int i = 0; i < MAX_FLIGHTS; i++) {
        strcpy(flights[i].flightNo, flightNos[i]);
        strcpy(flights[i].source, sources[i]);
        strcpy(flights[i].destination, destinations[i]);
        strcpy(flights[i].date, dates[i]);
        strcpy(flights[i].time, times[i]);
        strcpy(flights[i].type, i < 10 ? "Domestic" : "International");

        for (int j = 0; j < MAX_SEATS; j++) {
            flights[i].seats[j].seatNumber = j + 1;
            flights[i].seats[j].isBooked = 0;

            if (j < 5) {
                strcpy(flights[i].seats[j].seatClass, "First");
                flights[i].seats[j].price = (strcmp(flights[i].type, "Domestic") == 0) ? 5000.0f : 15000.0f;
            }
            else if (j < 15) {
                strcpy(flights[i].seats[j].seatClass, "Business");
                flights[i].seats[j].price = (strcmp(flights[i].type, "Domestic") == 0) ? 3000.0f : 10000.0f;
            }
            else {
                strcpy(flights[i].seats[j].seatClass, "Economy");
                flights[i].seats[j].price = (strcmp(flights[i].type, "Domestic") == 0) ? 1500.0f : 5000.0f;
            }
        }
    }
}

void viewFlights() {
    printf("\nAvailable Flights:\n");
    printf("Flight\tType\tFrom\tTo\t\tDate\t\tTime\n");
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        printf("%s\t%s\t%s\t%s\t%s\t%s\n",
               flights[i].flightNo,
               flights[i].type,
               flights[i].source,
               flights[i].destination,
               flights[i].date,
               flights[i].time);
    }
}

void bookTicket() {
    char flightNo[10];
    printf("Enter Flight Number: ");
    scanf("%s", flightNo);

    int index = -1;
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (strcmp(flights[i].flightNo, flightNo) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Flight not found.\n");
        return;
    }

    char desiredClass[15];
    printf("Enter Seat Class (Economy/Business/First): ");
    scanf("%s", desiredClass);

    for (int i = 0; i < MAX_SEATS; i++) {
        if (!flights[index].seats[i].isBooked && strcasecmp(flights[index].seats[i].seatClass, desiredClass) == 0) {
            flights[index].seats[i].isBooked = 1;

            printf("Enter Name: ");
            scanf(" %[^\n]", passengers[totalPassengers].name);
            printf("Enter Age: ");
            scanf("%d", &passengers[totalPassengers].age);
            printf("Enter Gender (M/F): ");
            scanf(" %c", &passengers[totalPassengers].gender);

            strcpy(passengers[totalPassengers].flightNo, flightNo);
            passengers[totalPassengers].seatNumber = flights[index].seats[i].seatNumber;
            strcpy(passengers[totalPassengers].seatClass, flights[index].seats[i].seatClass);
            passengers[totalPassengers].price = flights[index].seats[i].price;

            totalPassengers++;

            printf("Booking successful. Seat Number: %d, Class: %s, Price: Rs %.2f\n",
                   flights[index].seats[i].seatNumber,
                   flights[index].seats[i].seatClass,
                   flights[index].seats[i].price);
            return;
        }
    }

    printf("No available seats in %s class on this flight.\n", desiredClass);
}

void cancelTicket() {
    char name[50];
    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < totalPassengers; i++) {
        if (strcmp(passengers[i].name, name) == 0 && passengers[i].seatNumber != -1) {
            for (int j = 0; j < MAX_FLIGHTS; j++) {
                if (strcmp(flights[j].flightNo, passengers[i].flightNo) == 0) {
                    for (int k = 0; k < MAX_SEATS; k++) {
                        if (flights[j].seats[k].seatNumber == passengers[i].seatNumber) {
                            flights[j].seats[k].isBooked = 0;
                            break;
                        }
                    }
                }
            }
            passengers[i].seatNumber = -1;
            printf("Ticket cancelled.\n");
            return;
        }
    }
    printf("Passenger not found.\n");
}

void viewPassengers() {
    printf("\nPassenger List:\n");
    printf("Name\tFlight\tSeat\tClass\tPrice\n");
    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].seatNumber != -1) {
            printf("%s\t%s\t%d\t%s\tRs %.2f\n",
                   passengers[i].name,
                   passengers[i].flightNo,
                   passengers[i].seatNumber,
                   passengers[i].seatClass,
                   passengers[i].price);
        }
    }
}

void searchPassenger() {
    char keyword[50];
    printf("Enter Passenger Name or Flight Number to search: ");
    scanf(" %[^\n]", keyword);

    int found = 0;
    for (int i = 0; i < totalPassengers; i++) {
        if (passengers[i].seatNumber != -1 &&
           (strstr(passengers[i].name, keyword) || strcmp(passengers[i].flightNo, keyword) == 0)) {
            printf("Found: %s, Flight: %s, Seat: %d, Class: %s, Price: Rs %.2f\n",
                   passengers[i].name, passengers[i].flightNo,
                   passengers[i].seatNumber, passengers[i].seatClass,
                   passengers[i].price);
            found = 1;
        }
    }

    if (!found) printf("No matching passenger found.\n");
}

void filterFlights() {
    char type[20];
    printf("Enter type to filter (Domestic/International): ");
    scanf("%s", type);

    printf("\nFiltered Flights:\n");
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (strcasecmp(flights[i].type, type) == 0) {
            printf("%s\t%s\t%s to %s at %s on %s\n",
                   flights[i].flightNo, flights[i].type, flights[i].source,
                   flights[i].destination, flights[i].time, flights[i].date);
        }
    }
}

int main() {
    initFlights();
    int choice;

    do {
        printf("\n--- Airline Reservation System ---\n");
        printf("1. View Flights\n2. Book Ticket\n3. Cancel Ticket\n4. View Passengers\n");
        printf("5. Search Passenger\n6. Filter Flights\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewFlights(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: viewPassengers(); break;
            case 5: searchPassenger(); break;
            case 6: filterFlights(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}

