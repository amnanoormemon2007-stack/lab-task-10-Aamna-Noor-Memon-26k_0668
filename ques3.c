#include <stdio.h>

int main()
{
    FILE *fp;
    char city[11], hottestCity[11];
    float temp, newTemp, highest = -1000;
    int i, cityNo;

    fp = fopen("temperature.txt", "wb");

    for (i = 0; i < 5; i++)
    {
        printf("Enter city name and temperature: ");
        scanf("%10s %f", city, &temp);

        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }

    fclose(fp);

    fp = fopen("temperature.txt", "rb+");

    printf("City number: ");
    scanf("%d", &cityNo);

    if (cityNo >= 1 && cityNo <= 5)
    {
        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fscanf(fp, "%10s %f", city, &temp);

        printf("%s %.1f\n", city, temp);
    }

    printf("City number to correct: ");
    scanf("%d", &cityNo);

    printf("New temperature: ");
    scanf("%f", &newTemp);

    if (cityNo >= 1 && cityNo <= 5)
    {
        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fscanf(fp, "%10s %f", city, &temp);

        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fprintf(fp, "%-10s %5.1f\n", city, newTemp);

        printf("%s updated to %.1f\n", city, newTemp);
    }

    rewind(fp);

    for (i = 0; i < 5; i++)
    {
        fscanf(fp, "%10s %f", city, &temp);

        if (temp > highest)
        {
            highest = temp;
            sprintf(hottestCity, "%s", city);
        }
    }

    printf("Hottest city: %s (%.1f)\n",
           hottestCity, highest);

    fclose(fp);

    return 0;
}