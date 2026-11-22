#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;

    int i, roomNo, nights;
    int storedRoom, storedNights;

    int rooms[10];

    char status;
    char guest[21];
    char guests[10][21];
    char searchName[21];

    float rate;

    fp = fopen("hotel.txt", "wb");

    for (i = 0; i < 10; i++)
    {
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                101 + i, 'F', "-", 0, 8000.0);
    }

    fclose(fp);

    fp = fopen("hotel.txt", "rb+");

    printf("Check-in room: ");
    scanf("%d", &roomNo);

    printf("Name: ");
    scanf("%20s", guest);

    printf("Nights: ");
    scanf("%d", &nights);

    if (roomNo >= 101 && roomNo <= 110 && nights > 0)
    {
        fseek(fp, (roomNo - 101) * 39L, SEEK_SET);

        fscanf(fp, "%d %c %20s %d %f",
               &storedRoom, &status,
               guests[0], &storedNights, &rate);

        if (status == 'F')
        {
            fseek(fp, (roomNo - 101) * 39L, SEEK_SET);

            fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                    roomNo, 'B', guest, nights, 8000.0);

            printf("Room %d booked\n", roomNo);
        }
        else
        {
            printf("Room already booked\n");
        }
    }

    rewind(fp);

    for (i = 0; i < 10; i++)
    {
        fscanf(fp, "%d %c %20s %d %f",
               &rooms[i], &status,
               guests[i], &storedNights, &rate);

        if (status == 'F')
            strcpy(guests[i], "-");
    }

    printf("Search name: ");
    scanf("%20s", searchName);

    for (i = 0; i < 10; i++)
    {
        if (strcmp(guests[i], searchName) == 0)
        {
            printf("%s is in room %d\n",
                   searchName, rooms[i]);
            break;
        }
    }

    if (i == 10)
        printf("Guest not found\n");

    printf("Check-out room: ");
    scanf("%d", &roomNo);

    if (roomNo >= 101 && roomNo <= 110)
    {
        fseek(fp, (roomNo - 101) * 39L, SEEK_SET);

        fscanf(fp, "%d %c %20s %d %f",
               &storedRoom, &status,
               guest, &nights, &rate);

        if (status == 'B')
        {
            printf("Bill: %d x %.2f = %.2f\n",
                   nights, rate, nights * rate);

            fseek(fp, (roomNo - 101) * 39L, SEEK_SET);

            fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                    roomNo, 'F', "-", 0, 8000.0);
        }
        else
            printf("Room is already free\n");
    }

    fclose(fp);

    return 0;
}