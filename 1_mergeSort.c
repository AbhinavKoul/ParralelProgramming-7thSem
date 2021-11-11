#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void merge(int a[] , int low, int mid, int high)
{
    int i,j,k,c[1000];
    // int p = x1, q = x2, k = 0, temp[1000], i, j;
    //new array
    k = low;
    //old ones
    i = low;
    j = mid + 1;

    while(i<=mid && j<=high)
    {
      if(a[i] <= a[j])
        c[k++] = a[i++];
      else
        c[k++] = a[j++];
    }
    
    while(i<=mid)
      c[k++] = a[i++];
    
    while(j<=high)
      c[k++] = a[j++];

    //put temp back in old array
    for(k = low;k<=high;k++)
        a[k] = c[k];
}

void mergesort(int a[],int low ,int high)
{
  int mid = 0;
  if(low < high)
  {
      mid = (low + high)/2;
      
      #pragma omp parallel sections
      {
        #pragma omp section
        {
            printf("Process handing left recursion is %d\n",omp_get_thread_num());
            mergesort(a,low,mid);
        }
        #pragma omp section
        {
            printf("Process handing right recursion is %d\n",omp_get_thread_num());
            mergesort(a,mid+1,high);
        }
      }
      
      merge(a,low,mid,high);
  }
}

int main(){
  int n = 0, i=0;
  printf("Enter the number of elements for sorting\n");
  scanf("%d",&n);

  int a[n];
  for(i = 0; i < n; i++ ){
    a[i] = rand()%100;
  }

  printf("Unsorted array is\n");
  for(i = 0; i < n; i++ ){
    printf("%d\n",a[i]);
  }

  mergesort(a,0,n-1);
  
  printf("Sorted array is\n");
  for(i = 0; i < n; i++ )
    printf("%d\n",a[i]);
  
  return 0;
}