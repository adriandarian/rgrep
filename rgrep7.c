#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire
  return 0;
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int pIndex;
int lIndex;
int plus;
int slash;
int question;
int rgrep_matches(char *line, char *pattern) {
    //
    // Implement me
    //
    switch (pattern[pIndex]) {
      case '+':
        if (line[lIndex] == pattern[pIndex + 1]) {
          if (pattern[pIndex + 2] == '\0') {
            lIndex = 0;
            pIndex = 0;
            plus = 1;
          } else {
            pIndex++;
            plus = 2;
          }
        } else if ( pattern[pIndex + 1] == '\0') {
          pIndex++;
          if (pattern[pIndex] == '\0') {
            pIndex = 0;
            lIndex = 0;
            plus = 1;
          }
        } else if (line[lIndex + 1] == pattern[pIndex - 1]) {
          lIndex++;
          plus = 2;
        } else if ((line[lIndex + 1] == '\0') && (line[lIndex] != pattern[pIndex - 1])) {
          pIndex++;
          if (line[lIndex] == pattern[pIndex]) {
            lIndex = 0;
            pIndex = 0;
          } else {
            pIndex = 0;
            plus = 2;
          }
        } else if (line[lIndex + 1] != pattern[pIndex - 1]) {
          lIndex++;
          pIndex++;
          if ((line[lIndex] == pattern[pIndex]) && (pattern[pIndex + 1] == '\0')) {
            lIndex = 0;
            pIndex = 0;
            plus = 1;
          }
        } else {
          pIndex = 0;
          plus = 0;
        }
        if (plus == 1) {
          lIndex = 0;
          pIndex = 0;
          printf("%s\n", line);
          return 1;
        } else if (plus == 2) {
          rgrep_matches(line, pattern);
        } else {
          return 0;
        }
        break;
      case '.':
        if (line[lIndex] != '\n') {
          pIndex++;
          lIndex++;
          rgrep_matches(line, pattern);
        } else {
          return 0;
        }
        break;
      case '\\':
        if (line[lIndex] == pattern[pIndex + 1]) {
          if (line[lIndex + 1] != '\0') {
            pIndex++;
            slash = 1;
          } else {
            pIndex = 0;
          }
        } else {
          lIndex++;
          slash = 1;
        }
        if (slash == 1) {
          rgrep_matches(line, pattern);
        }
        break;
      case '?':
        if ()
        break;
      default:
        if (pattern[pIndex] == '\0' || pattern[pIndex] == '\n') {
          pIndex = 0;
          lIndex = 0;
          printf("%s\n", line);
          return 1;
        } else if (line[lIndex] == '\0' || line[lIndex] == '\n') {
          pIndex = 0;
          lIndex = 0;
          return 0;
        }else if (line[lIndex] != pattern[pIndex]) {
          if ( pattern[pIndex + 1] == '?') {
            pIndex++;
            rgrep_matches(line, pattern);
          } else {
            lIndex++;
            pIndex = 0;
            rgrep_matches(line, pattern);
          }
        } else if (line[lIndex] == pattern[pIndex]) {
          lIndex++;
          pIndex++;
          rgrep_matches(line, pattern);
        } else {
          return 0;
        }
        lIndex = 0;
        pIndex = 0;
    }
  return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
