
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{

  time_t a, b;

  time(&a);
  time(&b);

  if(a != b)
    printf("a and b are different.\n");
  else
    printf("a and b are the same.\n");

  if(difftime(a, b) != 0)
    printf("a and b are different.\n");
  else
    printf("a and b are the same.\n");

  // time_t is just an unsigned interger of some sort


  return 0;
}
