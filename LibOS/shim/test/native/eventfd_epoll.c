#include <stdio.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <pthread.h>

int efd = -1;
void *read_thread(void *dummy)
{
    int ret = 0;
    uint64_t count = 0;
    int ep_fd = -1;
    struct epoll_event events[10];

    if (efd < 0)
    {
        printf("efd not inited.\n");
        goto fail;
    }

    ep_fd = epoll_create(1024);

    if (ep_fd < 0)
    {
        perror("epoll_create fail: ");
        goto fail;
    }


    struct epoll_event read_event;

    read_event.events =  EPOLLIN;
    read_event.data.fd = efd;

    ret = epoll_ctl(ep_fd, EPOLL_CTL_ADD, efd, &read_event);
    if (ret < 0)
    {
        perror("epoll ctl failed:");
        goto fail;
    }

    printf("adding %d eventfd to epoll list\n", efd);

    ret = epoll_wait(ep_fd, &events[0], 10, -1);
    if (ret > 0)
    {
        int i = 0;
        for (; i < ret; i++)
        {
           if (events[i].events & EPOLLIN)
           {
               int event_fd = events[i].data.fd;

               printf("going to read event_fd %d\n", event_fd);
               int read_ret = read(event_fd, &count, sizeof(count));
               if (read_ret < 0)
               {
                   perror("read fail:");
                   goto fail;
               }
               printf("read event_fd: %d\n", count);
           }
        }
    }

fail:
    if (ep_fd >= 0)
    {
        close(ep_fd);
        ep_fd = -1;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t pid = 0;
  uint64_t count = 0;
  efd = eventfd(0, EFD_CLOEXEC);
  printf("creating efd: %d\n", efd);
  int ret = pthread_create(&pid, NULL, read_thread, NULL);

  sleep(4);

  count = 4;
  ret = write(efd, &count, sizeof(count));
  if (ret < 0)
  {
     perror("write event fd fail:");
     goto fail;
  }

fail:
  pthread_join(pid, NULL);
  return ret;
}
