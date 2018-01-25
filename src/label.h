#ifndef LABEL_H
#define LABEL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

struct Label
{
    uint32_t address;
    char name[256];
    struct Label *next;
};

int labelInitialize(struct Label **label,uint32_t address,const char* name);

int labelPushBack(struct Label *label, uint32_t address, const char *name);

void labelPrintLabels(struct Label *label);

void labelDestroy(struct Label *label);

#endif
