#include <stdio.h>
int main()
{
    int n, a, sum1 = 0, sum2 = 0, j, missingnum;
    printf("enter number : ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int l = 1; l < n; l++)
    {
        sum1 = sum1 + arr[l];
    }
    for (int k = 1; k <= n; k++)
    {
        sum2 = sum2 + k;
    }
    for (j = 1; j < n; j++)
    {
        if (arr[j] >= 1 && arr[j] <= n)
        {
            missingnum = sum2 - sum1;
        }
    }
    printf("%d", missingnum);
    return 0;
}