#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps) {
    // length of the previous longest prefix suffix
    int len = 0;
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpSearch(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int *lps = (int *)malloc(sizeof(int) * m);
    
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pattern, m, lps);
    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while ((n-i) >= (m-j)) {
        if (pattern[j] == text[i]) {
            j++; i++;
        }
        if (j == m) {
            printf("Found pattern at index %d\n", i - j);
            j = lps[j - 1];
        }
        // mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    printf("Enter the string: ");
    char str[MAX]; gets(str);
    printf("Enter the pattern: ");
    char pat[MAX]; gets(pat);
    kmpSearch(str, pat);
    return 0;
}