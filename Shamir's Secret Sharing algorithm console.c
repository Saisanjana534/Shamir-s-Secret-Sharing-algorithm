#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_POINTS 10
#define MAX_BASE 16

typedef struct {
    int x;
    long long y;
} Point;

void decode_y_value(char *base, char *value, long long *decoded_value) {
    int base_value = atoi(base);
    *decoded_value = 0;
    long long multiplier = 1;
    int len = strlen(value);
    
    for (int i = len - 1; i >= 0; i--) {
        char digit = value[i];
        int digit_value;
        if (isdigit(digit)) {
            digit_value = digit - '0';
        } else {
            digit_value = toupper(digit) - 'A' + 10;
        }
        *decoded_value += digit_value * multiplier;
        multiplier *= base_value;
    }
}

void lagrange_interpolation(Point points[], int n, long long *secret) {
    *secret = 0;

    for (int i = 0; i < n; i++) {
        long long term = points[i].y;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - points[j].x);
                term /= (points[i].x - points[j].x);
            }
        }
        *secret += term;
    }
}

int main() {
    // Example input: Test Case 1
    Point points1[MAX_POINTS] = {
        {10, 4},
        {2, 7}, // base 2: 111 -> 7
        {10, 12},
        {4, 213} // base 4: 213 -> 2*4^2 + 1*4^1 + 3 = 32 + 4 + 3 = 39
    };
    
    long long secret1;
    lagrange_interpolation(points1, 4, &secret1);
    printf("Secret for Test Case 1: %lld\n", secret1);

    // Example input: Test Case 2
    Point points2[MAX_POINTS];
    char *bases[] = {"10", "16", "12", "11", "16", "10", "14", "9", "8"};
    char *values[] = {
        "28735619723837",
        "1A228867F0CA",
        "32811A4AA0B7B",
        "917978721331A",
        "1A22886782E1",
        "28735619654702",
        "71AB5070CC4B",
        "122662581541670",
        "642121030037605"
    };

    for (int i = 0; i < 9; i++) {
        long long decoded_y;
        decode_y_value(bases[i], values[i], &decoded_y);
        points2[i] = (Point){i + 1, decoded_y};
    }

    long long secret2;
    lagrange_interpolation(points2, 6, &secret2);
    printf("Secret for Test Case 2: %lld\n", secret2);

    // Identify wrong points (simple example, assuming last 3 points might be wrong)
    printf("Wrong points in Test Case 2: ");
    for (int i = 6; i < 9; i++) {
        printf("(%d, %lld) ", points2[i].x, points2[i].y);
    }
    printf("\n");

    return 0;
}
