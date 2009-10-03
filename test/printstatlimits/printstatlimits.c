#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  printf("Some important types:\n");
  printf("  sizeof(dev_t)=%zu\n", sizeof(dev_t));
  printf("  sizeof(ino_t)=%zu\n", sizeof(ino_t));
  printf("  sizeof(mode_t)=%zu\n", sizeof(mode_t));
  printf("  sizeof(nlink_t)=%zu\n", sizeof(nlink_t));
  printf("  sizeof(uid_t)=%zu\n", sizeof(uid_t));
  printf("  sizeof(gid_t)=%zu\n", sizeof(gid_t));
  printf("  sizeof(off_t)=%zu\n", sizeof(off_t));
  printf("  sizeof(quad_t)=%zu\n", sizeof(quad_t));
  printf("  sizeof(u_long)=%zu\n", sizeof(u_long));
  printf("\n");
  
  struct stat st;
  printf("sizeof(struct stat)=%zu\n", sizeof(struct stat));

  return 0;
}
