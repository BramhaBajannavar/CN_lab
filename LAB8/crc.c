#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char rem[50], a[50], s[50], c, msg[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generator polynomial: ");
    fgets(gen, sizeof(gen), stdin);
    gen[strcspn(gen, "\n")] = '\0';
    printf("Generator polynomial is CRC: %s\n", gen);

    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message: ");
    n = 0;
    while ((c = getchar()) != '\n') {
        msg[n] = c;
        n++;
    }
    msg[n] = '\0';

    for (i = 0; i < n; i++) {
        a[i] = msg[i];
    }
    for (i = 0; i < k; i++) {
        a[n + i] = '0';
    }
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    for (i = 0; i < n; i++) {
        if (a[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++) {
                a[t] = (a[t] == gen[j]) ? '0' : '1';
                t++;
            }
        }
    }

    for (i = 0; i < k; i++) {
        rem[i] = a[n + i];
    }
    rem[k] = '\0';

    printf("The checksum appended:\n");
    puts(rem);
    printf("\nThe message with checksum appended:\n");
    for (i = 0; i < n; i++) {
        a[i] = msg[i];
    }
    for (i = 0; i < k; i++) {
        a[n + i] = rem[i];
    }
    a[n + k] = '\0';
    puts(a);

    n = 0;
    printf("Enter the received message: ");
    while ((c = getchar()) != '\n') {
        s[n] = c;
        n++;
    }
    s[n] = '\0';
    for (i = 0; i < n; i++) {
        if (s[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++, t++) {
                s[t] = (s[t] == gen[j]) ? '0' : '1';
            }
        }
    }

    for (i = 0; i < k; i++) {
        rem[i] = s[n + i];
    }
    rem[k] = '\0';
    for (i = 0; i < k; i++) {
        if (rem[i] == '1') {
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("Received polynomial is error-free.\n");
    } else {
        printf("Received polynomial has an error.\n");
    }

    return 0;
}
