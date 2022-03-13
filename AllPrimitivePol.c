#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>

int num_setbits(long long int n) //this function count number of 1's in a binary representation of an integer
{
    int count = 0;
    while(n)
    {
        int val = n & (-n);
        n -= val;
        count++;
    }
    return count;
}

void lfsr(int n, long int bit, FILE *op)
{
    static int j = 1;
    long int lfsr = 0b1;//this is the seed of the lfsr
    long int padder = 0b1 << n-1;// this is the carry bit
    unsigned period = 0;
    do
    {
        long int temp = lfsr & bit;
        int counter = num_setbits(temp);
        if(counter % 2 == 0)
        {
            lfsr = lfsr >> 1;
        }
        else
        {
            lfsr = (lfsr >> 1) | padder;
        }
        period++;
    }
    while(lfsr != 0b1);

    if(period == (1 << n) - 1)
    {
        printf("%4d. 1 ", j);
        fprintf(op, "%4d. 1 ", j);
        for(int i = n - 1; i >= 0; i--)
        {
            if((bit >> i) & 1)
            {
                printf("+ x^%d ", n - i);
                fprintf(op, "+ x^%d ", n - i);
            }
        }
        printf("\n");
        fprintf(op, "\n");
        j++;
    }
}

void main()
{
    FILE *op;
    op = fopen("output.txt", "w+");
    long int i;
    int n;
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &n);
    printf("\nAll primitive polynomials of degree %d are:\n", n);
    fprintf(op, "\nAll primitive polynomials of degree %d are:\n", n);
    for(i = 1; i < (1 << n); i += 2)
    {
        lfsr(n, i, op);
    }
}