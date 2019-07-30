#include<stdio.h>
#include<unistd.h>
#include<sys/eventfd.h>

int main(int argc, char** argv) {
  int efd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  int count = 5;
  write(efd, &count, 8);
  write(efd, &count, 8);
  read(efd, &count, 8);
/*  eventfd_write(efd, count);
  eventfd_write(efd, count);
  eventfd_read(efd, &count);
  eventfd_read(efd, &count);*/
  printf("count: %d\n", count);
  read(efd, &count, 8);
  printf("count: %d\n", count);
/*  read(efd, &count, 4);
  printf("count: %d\n", count);*/
  return 1;
}
