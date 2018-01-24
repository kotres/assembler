#include "label.h"

int labelInitialize(struct Label *label, uint32_t address, char fixed, char *name){
    label=(struct Label*)malloc(sizeof(struct Label));
    if(label==NULL){
	printf("error: label %s malloc failed\n",name);
	return -1;
    }
    label->address=address;
    label->fixed=fixed;
    label->name=malloc(strlen(name)*sizeof(char));
    if(label->name==NULL){
	printf("error: label %s name malloc failed\n",name);
	return -1;
    }
    strcpy(label->name,name);
    label->next=NULL;
    return 0;
}

int labelPushBack(struct Label *label, uint32_t address, char fixed, char *name){
    return labelInitialize(label->next,address,fixed,name);
}

void labelDestroy(struct Label *label){
    struct Label *next_label;
    while(label!=NULL){
	next_label=label->next;
	free(label->name);
	free(label);
	label=next_label;
    }
}
