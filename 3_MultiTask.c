#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sines[1000];
int primes[1000];
//prime_num: no of prime numbers we want
void prime_table(int prime_num)
{

  int i = 2;  
  int p = 0;  //keep count

  while(p < prime_num)
  {
    int flag = 1;  //flag

    for (int j = 2; j <i; j++)
    {
      if ( i % j  == 0 )
      {
        flag = 0;
        break;
      }
    }
     
    
    if (flag)
      primes[p++] = i;
    
    i++;
  }

}

void sine_table(int sine_num)
{
  for (int i = 0; i<sine_num; i++)
    sines[i] = sin(i*M_PI/180);
}
  

int main()
{
	int size;
	printf("Enter the the number of primes and sine table values required : \n");
	scanf("%d", &size);
	
  #pragma omp parallel sections
	{
		#pragma omp section
		{
			prime_table(size);
			for( int i =0;i<size;i++)
				printf("%d \n",primes[i]);
		}
		#pragma omp section
		{
			sine_table(size);
			for(int i=0;i<size;i++)
				printf("%lf \n",sines[i]);
		}
	}
  return 0;
}