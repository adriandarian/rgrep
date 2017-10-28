#include <stdio.h>
#define MAXSIZE 4096

char next(char *pattern);
char previous(char *pattern);
int operator(char typeOfPattern);
int plus(char *pattern);
int question(char *pattern);
int escape(char *pattern);

/**
*  You can use this recommended helper function
*  Returns true if partial_line matches pattern, starting from
*  the first char of partial_line.
*/
int matches_leading(char *partial_line, char *pattern) {
    // Implement if desire
    if (*partial_line == *pattern && !operator(*pattern)) {
        return 1;
    } if (*pattern == '.' && !escape(pattern)) {
        return 1;
    } if (*partial_line == *pattern && operator(*pattern) && escape(pattern)) {
        return 1;
    } if (*pattern == '\\') {
        return matches_leading(partial_line, pattern + sizeof(char));
    } if (question(pattern)) {
        return 1;
    }
    return 0;
}

/**
*  You may assume that all strings are properly null terminated
*  and will not overrun the buffer set by MAXSIZE
*
*  Implementation of the rgrep matcher function
*/
int rgrep_matches(char *line, char *pattern) {
    //
// Implement me
//
    static in pIndex = 0;
    if (*pattern == '\0') {
        if (*line == '\n') {
            pattern -= pIndex * sizeof(char);
        }
        pIndex = 0;
        return 1;
    } if (*line == '\0') {
        return 0;
    } if (*line == '\n') {
        pattern -= pIndex + sizeof(char);
        pIndex -= pIndex;
        return 0;
    } if ((*pattern == '\\') && operator(next(pattern))) {
        pattern += sizeof(char);
        pIndex++;
    } if (matches_leading(line, pattern)) {
        if (plus(pattern)) {
            int previous = 1;
            if (*pattern == *(pattern + 2 * sizeof(char))) {
                previous = 2;
            } while (*(line + previous * sizeof(char)) == *pattern && !(*pattern == '.' && !escape(pattern))) {
                line += sizeof(char);
            } if (*pattern == '.' && escape(pattern)) {
                char card = *line;
                while (*(line +previous * sizeof(char)) == card) {
                    line += sizeof(char);
                }
            } if (*pattern == '.' && !escape(pattern)) {
                while (!matches_leading(line + previous * sizeof(char), pattern + 2 * sizeof(char))) {
                    line += sizeof(char);
                    if((*line == '\0' || *line == '\n') && *(pattern + 2 * sizeof(char)) != '\0') {
                        return 0;
                    }
                }
            }
            pattern += sizeof(char);
            pattern_depth++;
        } if(question_modified(pattern)) {
            if (*pattern == '.' && !escape_modified(pattern) && escape_modified(pattern + 3 * sizeof(char)) && *line == *(pattern + 3 * sizeof(char)) && *(line + sizeof(char)) != *(pattern + 3 * sizeof(char))) {
                pattern_depth += 4;
                return rgrep_matches(line + sizeof(char), pattern + 4 * sizeof(char));
            }  else if(*pattern == '.' && !escape_modified(pattern) && *line == *(pattern + 2 * sizeof(char))) {
                    pattern_depth += 2;
                    return rgrep_matches(line, pattern + 2 * sizeof(char));
                } else if(*pattern == '.' && !escape_modified(pattern) && *line != *(pattern + 2 * sizeof(char))) {
                        pattern_depth += 2;
                        return rgrep_matches(line + sizeof(char), pattern + 2 * sizeof(char));
                } else if(*line == *pattern && *line == *(pattern + 2 * sizeof(char))) {
                        pattern_depth += 2;
                        return rgrep_matches(line, pattern + 2 * sizeof(char));
                } else if(*line == *pattern && next_char(line) == *(pattern + 2 * sizeof(char))){

                } else if(*line == *pattern && next_char(line) != *(pattern + 2 * sizeof(char)) && *line != *(pattern + 2 * sizeof(char))) {

                } else if(*line != *pattern && *line != *(pattern + 2 * sizeof(char))) {
                    return 0;
                } else if(*line == *pattern && *pattern == '.' && escape_modified(pattern)){

                } else if(!(*pattern == '.' && !escape_modified(pattern)) || *line != *pattern) {
                    line -= sizeof(char);
                }
                pattern += sizeof(char);
                pattern_depth++;
            }
            pattern += sizeof(char);
            pattern_depth++;
        } else if(pattern_depth != 0 && *(pattern - pattern_depth * sizeof(char)) != '\0') {
                pattern -= pattern_depth * sizeof(char);
                pattern_depth -= pattern_depth;
        }
        line += sizeof(char);
        return rgrep_matches(line, patter);
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

char next(char *pattern) {
    return *(pattern + sizeof(char));
}

char previous(char *pattern) {
    return *(pattern - sizeof(char));
}

int operator(char typeOfPattern) {
    switch(typeOfPattern) {
        case '.':
            return 1;
        case '+':
            return 2;
        case '\?':
            return 3;
        case '\\':
            return 4;
        default:
            return 0;
    }
}

int plus(char *pattern) {
    (next(pattern) == '+') ? return 1 : return 0;
}

int question(char *pattern) {
    (next(pattern) == '\?') ? return 1 : return 0;
}

int escape(char *pattern) {
    (previous(pattern) == '\\') ? return 1 : return 0;
}