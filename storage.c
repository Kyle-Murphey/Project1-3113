#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
  int fd;
} STORAGE;

STORAGE * init_storage(char * name)
{
    STORAGE * file = malloc(sizeof(STORAGE));
    file->fd = open(name, O_CREAT | O_RDWR | S_IRWXU);

    if (file->fd == -1)
    {
      fprintf(stderr, "Could not open or create file\n");
      return NULL;
    }
    return file;
}

/* REMEMBER TO ERROR CHECK IN MAIN */
int close_storage(STORAGE *storage)
{
  int isClosed = close(storage->fd);
  return isClosed;
}

int get_bytes(STORAGE *storage, unsigned char *buf, int location, int len)
{
  int setStart = lseek(storage->fd, location, SEEK_SET);

  if (setStart < 0)
  {
    fprintf(stderr, "error setting offset\n");
    return setStart;
  }

  int readBytes = read(storage->fd, buf, len);

  if (readBytes < 0) 
  {
    fprintf(stderr, "error reading file\n");
  }

  return readBytes;
}

int put_bytes(STORAGE *storage, unsigned char *buf, int location, int len)
{
  int setStart = lseek(storage->fd, location, SEEK_SET);

  if (setStart < 0)
  {
    fprintf(stderr, "error setting offset\n");
    return setStart;
  }

  int writeBytes = write(storage->fd, buf, len);

  if (writeBytes < 0)
  {
    fprintf(stderr, "error writing to file\n");
  }

  return writeBytes;
}