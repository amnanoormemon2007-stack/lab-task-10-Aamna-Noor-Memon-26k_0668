#include <stdio.h>

int main()
{
    FILE *fp;
    int roll, lectures, leave;
    int r, lastLectures;
    char name[16];

    fp = fopen("attendance.txt", "wb");

    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);

    fclose(fp);

    fp = fopen("attendance.txt", "rb+");

    printf("Roll number: ");
    scanf("%d", &roll);

    if (roll >= 1 && roll <= 5)
    {
        fseek(fp, (roll - 1) * 24L, SEEK_SET);

        fscanf(fp, "%d %15s %d", &r, name, &lectures);

        printf("%s: %d / 20 (%.1f%%)",
               name, lectures, lectures * 100.0 / 20);

        if (lectures * 100.0 / 20 < 75)
            printf(" Short attendance");

        printf("\n");
    }

    printf("Roll number for leave: ");
    scanf("%d", &roll);

    printf("Lectures: ");
    scanf("%d", &leave);

    if (roll >= 1 && roll <= 5 && leave >= 0)
    {
        fseek(fp, (roll - 1) * 24L, SEEK_SET);

        fscanf(fp, "%d %15s %d", &r, name, &lectures);

        lectures += leave;

        if (lectures > 20)
            lectures = 20;

        fseek(fp, (roll - 1) * 24L, SEEK_SET);

        fprintf(fp, "%-3d %-15s %3d\n",
                r, name, lectures);

        printf("%s: now %d / 20 (%.1f%%)\n",
               name, lectures, lectures * 100.0 / 20);
    }

    fseek(fp, -24L, SEEK_END);

    fscanf(fp, "%d %15s %d", &r, name, &lastLectures);

    printf("Last record: %d %s %d\n",
           r, name, lastLectures);

    fclose(fp);

    return 0;
}