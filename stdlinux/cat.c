#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void do_cat(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]) {
  int i;
  // 引数がなければエラー
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }
  // 引数ごとにcat
  for (i = 1; i < argc; i++) {
    do_cat(argv[i]);
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const char *path) {
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int n;

  // ファイルを開く
  fd = open(path, O_RDONLY);

  // ファイルオープン失敗
  if (fd < 0) {
    die(path);
  }
  for (;;) {
    // ファイルディスクリプタから sizeof buf 分のデータを読み込み、bufに格納
    n = read(fd, buf, sizeof buf); // n = 読み込んだバイト数, buf = データ保存領域のポインタ
    if (n < 0)
      die(path);
    if (n == 0)
      break;
    if (write(STDOUT_FILENO, buf, n) < 0)
      die(path);
  }
  if (close(fd) < 0) {
    die(path);
  }
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
