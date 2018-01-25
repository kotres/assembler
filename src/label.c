#include "label.h"

int labelInitialize(struct Label **label, uint32_t address, const char *name){
    struct Label *initialized_label;
    if(*label!=NULL){
	printf("label initialize error: non NULL pointer given to labelInitialize");
	return -1;
    }
    *label=(struct Label*)malloc(sizeof(struct Label));
    if(*label==NULL){
	printf("label initialize error: malloc failed\n");
	return -1;
    }

    initialized_label=*label;

    initialized_label->name=(char*)malloc((strlen(name)+1)*sizeof(char));
    if(initialized_label->name==NULL){
	printf("label initialize error: name malloc failed\n");
	return -1;
    }

    initialized_label->address=address;
    strcpy(initialized_label->name,name);
    initialized_label->next=NULL;
    return 0;
}

int labelPushBack(struct Label *label, uint32_t address,const char *name){
    struct Label *initialized_label;
    if(label==NULL){
	printf("label push back error: NULL pointer given to labelPushBack");
	return -1;
    }
    label->next=(struct Label*)malloc(sizeof(struct Label));
    if(label->next==NULL){
	printf("label push back error: malloc failed\n");
	return -1;
    }

    initialized_label=label->next;

    initialized_label->name=(char*)malloc((strlen(name)+1)*sizeof(char));
    if(initialized_label->name==NULL){
	printf("label initialize error: name malloc failed\n");
	return -1;
    }

    initialized_label->address=address;
    strcpy(initialized_label->name,name);
    initialized_label->next=NULL;
    return 0;

}

void labelDestroy(struct Label *label){
    struct Label *next_label;
    while(label!=NULL){
	next_label=label->next;
	free(label->name);
	free(label);
	label=next_label;
    }
    printf("labels freed from memory\n");
}

void labelPrintLabels(struct Label *label){
    if(label==NULL){
	printf("no labels to print\n");
    }
    else{
	while(label!=NULL){
	    printf("label %s\n",label->name);
	    label=label->next;
	}
    }
}
