#include<omp.h>
#include<stdio.h>

int main()
{
    int num;
    printf("Enter number to calc fact \n");
    scanf("%d",&num);

    int fact1 = 1;
    #pragma omp parallel for firstprivate(num)
    for(int i = 2;i<=num;i++)
        fact1 *=  i; 
    
    printf("when first private is not used \t : %d\n",fact1);
    
    int fact2 = 1;
    #pragma omp parallel for firstprivate(num,fact2)
    for(int i = 2;i<=num;i++)
        fact2 *= i;
    printf("when first private is  used \t : %d\n",fact2);
    return 0;
}