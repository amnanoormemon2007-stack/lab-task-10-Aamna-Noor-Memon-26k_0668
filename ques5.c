#include <stdio.h>

int main()
{
    FILE *fp;
    char category[13];
    float amount, total = 0;
    int i, entryNo;

    fp = fopen("expenses.txt", "wb");

    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);

    fclose(fp);

    printf("Category: ");
    scanf("%12s", category);

    printf("Amount: ");
    scanf("%f", &amount);

    fp = fopen("expenses.txt", "ab");

    fprintf(fp, "%-12s %9.2f\n", category, amount);

    fclose(fp);

    fp = fopen("expenses.txt", "rb+");

    printf("\nLatest two expenses:\n");

    fseek(fp, -2 * 23L, SEEK_END);

    for (i = 0; i < 2; i++)
    {
        fscanf(fp, "%12s %f", category, &amount);

        printf("%s %.2f\n", category, amount);
    }

    printf("\nEntry to fix: ");
    scanf("%d", &entryNo);

    printf("Correct amount: ");
    scanf("%f", &amount);

    if (entryNo >= 1 && entryNo <= 5)
    {
        fseek(fp, (entryNo - 1) * 23L, SEEK_SET);

        fscanf(fp, "%12s %f", category, &total);

        fseek(fp, (entryNo - 1) * 23L, SEEK_SET);

        fprintf(fp, "%-12s %9.2f\n", category, amount);
    }

    rewind(fp);

    total = 0;

    printf("\nAll expenses:\n");

    for (i = 0; i < 5; i++)
    {
        fscanf(fp, "%12s %f", category, &amount);

        printf("%s %.2f\n", category, amount);

        total += amount;
    }

    printf("Total: %.2f\n", total);

    fclose(fp);

    return 0;
}