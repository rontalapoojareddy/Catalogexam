#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


unsigned long long decodeValue(int base, const char* value) {
    unsigned long long result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++) {
        char digit = value[length - 1 - i];
        int digitValue;
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else if (digit >= 'a' && digit <= 'z') {
            digitValue = digit - 'a' + 10;
        } else if (digit >= 'A' && digit <= 'Z') {
            digitValue = digit - 'A' + 10;
        } else {
            continue;
        }
        result += digitValue * pow(base, i);
    }
    return result;
}


unsigned long long lagrangeInterpolation(unsigned long long points[][2], int k) {
    unsigned long long c = 0;

    for (int i = 0; i < k; i++) {
        unsigned long long xi = points[i][0];
        unsigned long long yi = points[i][1];
        unsigned long long li = 1;

        for (int j = 0; j < k; j++) {
            if (j != i) {
                unsigned long long xj = points[j][0];
                li *= xi / (xi - xj); 
            }
        }
        c += yi * li;
    }
    return c;
}

int main() {
    // Example input (second test case)
    const char* inputJson = "{ \"keys\": { \"n\": 10, \"k\": 7 }, "
                            "\"1\": { \"base\": \"6\", \"value\": \"13444211440455345511\" }, "
                            "\"2\": { \"base\": \"15\", \"value\": \"aed7015a346d63\" }, "
                            "\"3\": { \"base\": \"15\", \"value\": \"6aeeb69631c227c\" }, "
                            "\"4\": { \"base\": \"16\", \"value\": \"e1b5e05623d881f\" }, "
                            "\"5\": { \"base\": \"8\", \"value\": \"316034514573652620673\" }, "
                            "\"6\": { \"base\": \"3\", \"value\": \"2122212201122002221120200210011020220200\" }, "
                            "\"7\": { \"base\": \"3\", \"value\": \"20120221122211000100210021102001201112121\" }, "
                            "\"8\": { \"base\": \"6\", \"value\": \"20220554335330240002224253\" }, "
                            "\"9\": { \"base\": \"12\", \"value\": \"45153788322a1255483\" }, "
                            "\"10\": { \"base\": \"7\", \"value\": \"1101613130313526312514143\" } }";

   
    int n = 10; 
    int k = 7;  

    // Prepare points array
    unsigned long long points[10][2]; // 

    points[0][0] = 1; points[0][1] = decodeValue(6, "13444211440455345511");
    points[1][0] = 2; points[1][1] = decodeValue(15, "aed7015a346d63");
    points[2][0] = 3; points[2][1] = decodeValue(15, "6aeeb69631c227c");
    points[3][0] = 4; points[3][1] = decodeValue(16, "e1b5e05623d881f");
    points[4][0] = 5; points[4][1] = decodeValue(8, "316034514573652620673");
    points[5][0] = 6; points[5][1] = decodeValue(3, "2122212201122002221120200210011020220200");
    points[6][0] = 7; points[6][1] = decodeValue(3, "20120221122211000100210021102001201112121");

    
    unsigned long long constantTermC = lagrangeInterpolation(points, k);
    
    printf("The constant term c is: %llu\n", constantTermC);
    
    return 0;
}