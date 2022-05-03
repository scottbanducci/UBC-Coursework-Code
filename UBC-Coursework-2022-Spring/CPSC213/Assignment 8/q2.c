#include <stdio.h>

int i, a, b,c;

int q2 (int i, int a, int b,int c) {
  switch (i) {
    case 10:  c=a+b; break;
   
    case 12:  c=a-b; break;
    
    case 14:  c=a>b; break;

    case 16:  c=b>a; break;
    
    case 18:  c=b==a; break;
    
    default:  c=0; break;
  
  
  }
  return c;
}