#include <stdio.h>

int main() {
    int n, i, j, k, mode, maxcount=0, count=-1, sum=1,  digit=0;
    int arr[100];

    for(int i=0; i<100; i++) {
        scanf("%d", &arr[i]);
        count++;
        sum = arr[i] + sum;
        if(arr[i] == -1)
        break;
     }    
     printf("sum %d\n", sum);
     printf("count %d\n", count);
     int mean = sum / count;
     printf("mean : %d\n", mean);
                                        //  0   1   2   3
     int midel = count/2 ;           //   1   2   6   4
     int mid = arr[midel];              //
     printf("mid : %d", mid);           //

     for(i=0; i<count; i++) {
        for(j=1; j<count; j++) {
           if(arr[i] == arr[j])
           digit++;
        }
        if(digit > maxcount)
         maxcount = digit;
        mode = arr[i];
     }
     printf("mode : %d", mode);
 return 0; 
}
                                       //code 2
// #include <stdio.h>

// int main() {
//    int n, i, j, mid, mode, count=-1, digit=0, maxcount = 0, sum=1;
//    int arr[100];

//    for(i=0; i<100; i++) {
//       scanf("%d", &arr[i]);
//       count++;
//       sum+=arr[i];
//       if(arr[i]==-1)
//       break;
//    }                                //for mean
//    printf("sum : %d\n", sum);
//    printf("count : %d\n", count);
//    int mean=sum/count;
//    printf("mean = %d\n", mean);
//                                     //for mean
//    if(count % 2 == 0) {
//       int a=count/2-1;
//       int b=count/2;
//       mid = (arr[a] + arr[b])/2;
//    }  else {
//    int mean=sum/count;
//    int a=count/2;
//    mid = arr[a];
//    }
//    printf("mid = %d", mid);
//                                    // mode for
//    for(i=0; i<count; i++) {
//       for(j=0; j<count; j++) {
//          if(arr[i]==arr[j])
//          digit++;
//       }
//       if(digit>maxcount)
//       maxcount = digit;
//       mode = arr[i];
//    }
//    printf("mode = %d", mode);
//   return 0; 
// }