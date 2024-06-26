#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H



typedef struct {
    void (*fptr)(const char *);
    char* alias;
    char* help;
    char* usage;
} __attribute__ ((packed)) shellfunction;

shellfunction* TryGetCMD(char* cmdbuf);
int GetCMDLength();

#endif