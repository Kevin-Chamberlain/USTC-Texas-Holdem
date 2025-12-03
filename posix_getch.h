#ifndef POSIX_GETCH_H
#define POSIX_GETCH_H
#ifndef _WIN32
/* 立即读取，无缓冲回显，Linux */
int posix_getch(void);
#endif
#endif /* POSIX_GETCH_H */
