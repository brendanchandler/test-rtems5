/* Hello World Example */
#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

rtems_task Init(rtems_task_argument ignored)
{
  printf("Hello World!\n");
  exit(0);
}
