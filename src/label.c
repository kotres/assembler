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

struct Label* labelFindLabel(struct Label *label,const char *name){
    unsigned int i=0;
    int match=0;
    if(name[0]==0){
	printf("error to find label: empty name given\n");
	return NULL;
    }
    if(name[1]==0){
	printf("error to find label: empty name given\n");
	return NULL;
    }
    if(label==NULL){
	printf("error to find label: NULL label pointer given\n");
	return NULL;
    }
    while(label!=NULL&&match==0){
	i=0;
	match=1;
	while(label->name[i]!=0&&name[i]!=0&&match==1){
	    if(label->name[i]!=name[i])
		match=0;
	    ++i;
	}
	if(match!=0){
	    if(label->name[i]!=0||name[i]!=0){
		match=0;
		label=label->next;
	    }
	}
	else{
	    label=label->next;
	}

    }
    return label;
}

struct Label* labelEnd(struct Label *label){
    if(label==NULL){
	return NULL;
    }
    while(label->next!=NULL){
	label=label->next;
    }
    return label;
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
