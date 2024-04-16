#include "../includes/nm.h"

int ft_strlen(const char *s) {
  size_t i;
  i = 0;
  while (s[i])
    i++;
  return (i);
}

char *ft_strdup(const char *s) {
  size_t len = ft_strlen(s);
  char *dst = (char *)malloc(len + 1);
  if (!dst) {
    return NULL;
  }
  return ft_strcpy(dst, s);
}

int ft_strcasecmp(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    int diff = tolower(*s1) - tolower(*s2);
    if (diff != 0) {
      return diff;
    }
    s1++;
    s2++;
  }
  return (int)(tolower(*s1) - tolower(*s2));
}

char *ft_strScpy(char *dst, const char *src, int start) {
  int i = 0;
  while (src[start]) {
    dst[i] = src[start];
    start++;
    i++;
  }
  dst[i] = '\0';
  return dst;
}
char *ft_strcpy(char *dst, const char *src) {
  size_t i;

  i = 0;
  while (src[i]) {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  return (dst);
}

int ft_strcmp(const char *s1, const char *s2) {
  size_t i;

  i = 0;
  while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] != '\0' &&
         s2[i] != '\0')
    i++;
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strchr(const char *str, int c) {
  size_t i;

  i = 0;
  while (str[i]) {
    if (str[i] == c)
      return ((char *)str + i);
    i++;
  }
  if (str[i] == c)
    return ((char *)str + i);
  return (NULL);
}
void ft_bzero(void *s, size_t n) {
  unsigned char *ps;

  ps = (unsigned char *)s;
  while (n > 0) {
    *ps++ = '\0';
    n--;
  }
}
