#include <stdio.h>

int main()
{
    FILE *fp;
    char city[5][20], name[20];
    float temp[5], newTemp, hottestTemp;
    int i, cityNo, found = 0;

    
    fp = fopen("temperature.txt", "wb");

    if (fp == NULL)
    {
        printf("File cannot be opened.");
        return 1;
    }

    for (i = 0; i < 5; i++)
    {
        printf("Enter city name: ");
        scanf("%19s", city[i]);

        printf("Enter temperature: ");
        scanf("%f", &temp[i]);

        fprintf(fp, "%-10s %5.1f\n", city[i], temp[i]);
    }

    fclose(fp);

    
    fp = fopen("temperature.txt", "rb+");

    if (fp == NULL)
    {
        printf("File cannot be opened.");
        return 1;
    }

    printf("\nCity number (1-5): ");
    scanf("%d", &cityNo);

    if (cityNo >= 1 && cityNo <= 5)
    {
        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fscanf(fp, "%10s %f", name, &newTemp);

        printf("%s %.1f\n", name, newTemp);
    }
    else
    {
        printf("Invalid city number.");
    }


    printf("\nCity number to correct (1-5): ");
    scanf("%d", &cityNo);

    if (cityNo >= 1 && cityNo <= 5)
    {
        printf("New temperature: ");
        scanf("%f", &newTemp);

        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fscanf(fp, "%10s", name);

        fseek(fp, (cityNo - 1) * 17L, SEEK_SET);

        fprintf(fp, "%-10s %5.1f\n", name, newTemp);

        printf("%s updated to %.1f\n", name, newTemp);
    }
    else
    {
        printf("Invalid city number.");
    }

    
    rewind(fp);

    hottestTemp = -999.0;

    for (i = 0; i < 5; i++)
    {
        fscanf(fp, "%10s %f", name, &temp[i]);

        if (temp[i] > hottestTemp)
        {
            hottestTemp = temp[i];

            for (int j = 0; name[j] != '\0'; j++)
                city[0][j] = name[j];

            city[0][strlen(name)] = '\0';
        }
    }

    printf("\nHottest city: %s (%.1f)\n",
           city[0], hottestTemp);

    fclose(fp);

    return 0;
}
