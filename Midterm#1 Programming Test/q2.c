#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>

#define MASK (1 + 2 + 4 + 8 + 16 + 32)
// #define MASK 16

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

char buffer[20971527];
#define BUF_SIZE 32

int main(int argc, char* argv[]) {
    FILE* fin = fopen("source2", "r");

    // fread/fwrite 1
    if(MASK >> 0 & 1) {
        rewind(fin);
        int buf_size = 1;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output1", "w+");

        int cnt;
        int total = 0;
        while(true) {
            cnt = fread(fout, 1, buf_size, fin);
            total += cnt;
            if(cnt != buf_size) {
                break;
            }
        }
        while(true) {
            fwrite(fout, 1, min(total, buf_size), of);
            total -= buf_size;
            if(total <= 0) {
                break;
            }
        }
        chmod("output1", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    // fread/fwrite 32
    if(MASK >> 1 & 1) {
        rewind(fin);
        int buf_size = 32;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output2", "w+");

        int cnt;
        int total = 0;
        while(true) {
            cnt = fread(fout, 1, buf_size, fin);
            total += cnt;
            if(cnt != buf_size) {
                break;
            }
        }
        while(true) {
            fwrite(fout, 1, min(total, buf_size), of);
            total -= buf_size;
            if(total <= 0) {
                break;
            }
        }
        chmod("output2", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    // fread/fwrite 1024
    if(MASK >> 2 & 1) {
        rewind(fin);
        int buf_size = 1024;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output3", "w+");

        int cnt;
        int total = 0;
        while(true) {
            cnt = fread(fout, 1, BUF_SIZE, fin);
            total += cnt;
            if(cnt != BUF_SIZE) {
                break;
            }
        }
        while(true) {
            fwrite(fout, 1, min(total, BUF_SIZE), of);
            total -= BUF_SIZE;
            if(total <= 0) {
                break;
            }
        }
        chmod("output3", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    // fread/fwrite 4096
    if(MASK >> 3 & 1) {
        rewind(fin);
        int buf_size = 4096;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output4", "w+");

        int cnt;
        int total = 0;
        while(true) {
            cnt = fread(fout, 1, BUF_SIZE, fin);
            total += cnt;
            if(cnt != BUF_SIZE) {
                break;
            }
        }
        while(true) {
            fwrite(fout, 1, min(total, BUF_SIZE), of);
            total -= BUF_SIZE;
            if(total <= 0) {
                break;
            }
        }
        chmod("output4", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    // fgets/fputs 4096
    if(MASK >> 4 & 1) {
        rewind(fin);
        int buf_size = 4096;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output5", "w+");

        int total = 0;
        while(true) {
            char* cc = fgets(buffer, BUF_SIZE, fin);
            if(strlen(cc) == 0L) {
                break;
            }
            fputs(cc, of);
        }
        // while(true) {
        //     fwrite(fout, 1, min(total, buf_size), of);
        //     total -= buf_size;
        //     if(total <= 0) {
        //         break;
        //     }
        // }
        chmod("output5", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    if(MASK >> 4 & 1) {
        rewind(fin);
        int buf_size = 4096;
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output5", "w+");

        int cnt;
        int total = 0;
        while(true) {
            cnt = fread(fout, 1, BUF_SIZE, fin);
            total += cnt;
            if(cnt != BUF_SIZE) {
                break;
            }
        }
        while(true) {
            fwrite(fout, 1, min(total, BUF_SIZE), of);
            total -= BUF_SIZE;
            if(total <= 0) {
                break;
            }
        }
        chmod("output5", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    // fgetc/fputc
    if(MASK >> 5 & 1) {
        rewind(fin);
        FILE* fout = fmemopen(buffer, sizeof(buffer), "w+");
        FILE* of = fopen("output6", "w+");

        int cnt = 0;
        int total = 0;
        while(true) {
            int c = fgetc(fin);
            if(c == EOF || fputc(c, of) == EOF) {
                break;
            }
            total++;
        }
        // while(true) {
        //     fwrite(fout, 1, min(total, 1024), of);
        //     total -= 1024;
        //     if(total <= 0) {
        //         break;
        //     }
        // }
        chmod("output6", (1 << 9) - 1);
        fclose(fout);
        fclose(of);
    }
    return 0;
}
