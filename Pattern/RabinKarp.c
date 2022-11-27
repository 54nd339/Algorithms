#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void rabinkarp(char *text, char *pattern, int q) {
    int m = strlen(pattern);
    int n = strlen(text);
    int p, t, h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * 256) % q;
    // Calculate the hash value of pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (256 * p + pattern[i]) % q;
        t = (256 * t + text[i]) % q;
    }
    // Slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j])
                j++;
            // if p == t and pat[0...m-1] = txt[i, i+1, ...i+m-1]
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if (i < n - m) {
            t = (256 * (t - text[i] * h) + text[i + m]) % q;
            // We might get negative value of t, converting it to positive
            if (t < 0) t += q;
        }
    }
}

int main() {
    printf("Enter the string: ");
    char str[MAX]; gets(str);
    printf("Enter the pattern: ");
    char pat[MAX]; gets(pat);
    rabinkarp(str, pat, 101);
    return 0;
}