
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct operation_type{
	char optname[100];
	float commission;
	int optnum;
	struct operation_type *nextopt;
};

struct transaction{
	int optype;
	int tno;
	float amount;
	struct transaction *nexttr;
};

struct customer{
	char fname[100];
	char lname[100];
	int cno;
	float paid_commission;
	struct transaction *trans;
	struct customer *nextc;
};

struct branch{
	char bname[100];
	int bno;
	struct customer *custs;
	struct branch *nextb;
};

struct bank{
	struct branch *branches;
	struct operation_type *optypes;
} bank1;


void readOperationTypes(char file[]);
void printOperationTypes();

void readBranches(char file[]);
void printBranches();

void readCustomers(char file[]);
void printCustomers();

void readTransactions(char file[]);
void printTransactions();

void printPaidCommission();

int main(){
	while(true){
		int option = 0;
		char inputFile[100];
		
		printf("1) Read operation types from the file\n");
		printf("2) Read branches from the file\n");
		printf("3) Read customers from the file\n");
		printf("4) Read customer transactions from the file\n");
		printf("5) Calculate paid commission amount of each customers in each branches\n\n");
		
		printf("option : ");
		scanf("%d", &option);
		
		switch(option){
		case 1:
			printf("Please enter the name of the input file : \n");
			scanf("%99s", inputFile);
			readOperationTypes(inputFile);
			printOperationTypes();
			continue;
		case 2:
			printf("Please enter the name of the input file : \n");
			scanf("%99s", inputFile);
			readBranches(inputFile);
			printBranches();
			continue;
		case 3:
			printf("Please enter the name of the input file : \n");
			scanf("%99s", inputFile);
			readCustomers(inputFile);
			printCustomers();
			continue;
		case 4:
			printf("Please enter the name of the input file : \n");
			scanf("%99s", inputFile);
			readTransactions(inputFile);
			printTransactions();
			continue;
		case 5:
			printPaidCommission();
			continue;
		default:
			break;
		}
		break;
	}
	
	return 0;
}

void readOperationTypes(char file[]){
	FILE* ptr;
    char str[100];
    ptr = fopen(file, "a+");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    while (fgets(str, 100, ptr) != NULL) {
    	
    	if(bank1.optypes == NULL){
    		bank1.optypes = (operation_type*)malloc(sizeof(operation_type));
    		
    		char * token = strtok(str, "\t");
    		strcpy(bank1.optypes -> optname, token);
      		token = strtok(NULL, " ");
    		bank1.optypes -> commission = atof(token);
    		
    		
    		bank1.optypes -> optnum = 1;
    		bank1.optypes -> nextopt = NULL;
		}
		else{
			struct operation_type *tempPtr = bank1.optypes;

			while((tempPtr -> nextopt) != NULL)
				tempPtr = tempPtr -> nextopt;
					
			tempPtr -> nextopt = (operation_type*)malloc(sizeof(operation_type));
			
			char * token = strtok(str, "\t");
    		strcpy(tempPtr -> nextopt -> optname, token);
      		token = strtok(NULL, " ");
    		tempPtr -> nextopt -> commission = atof(token);
			
			tempPtr -> nextopt -> optnum = tempPtr -> optnum+1;
			tempPtr -> nextopt -> nextopt = NULL;
		}
        
    }
    
    printf("\n");
 
    fclose(ptr);
}

void printOperationTypes(){
	struct operation_type *tempPtr = bank1.optypes;
	
	printf("optypes linked list : \n");
	
	while(tempPtr != NULL){
		printf("--");
		printf("%d ", tempPtr->optnum);
		printf(tempPtr->optname);
		printf(" %.1f\n", tempPtr->commission);
		tempPtr = tempPtr->nextopt;
	}
	
	printf("\n");
	
}

void readBranches(char file[]){
	FILE* ptr;
    char str[100];
    ptr = fopen(file, "a+");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    while (fgets(str, 100, ptr) != NULL) {

    	if(bank1.branches == NULL){
    		bank1.branches = (branch*)malloc(sizeof(branch));
    		
    		char * token = strtok(str, "\n");
    		strcpy(bank1.branches -> bname, token);
    		 		
    		bank1.branches -> bno = 1;
    		bank1.branches -> nextb = NULL;
    		bank1.branches -> custs = NULL;
		}
		else{
			struct branch *tempPtr = bank1.branches;

			while((tempPtr -> nextb) != NULL)
				tempPtr = tempPtr -> nextb;
					
			tempPtr -> nextb = (branch*)malloc(sizeof(branch));
			
			char * token = strtok(str, "\n");
    		strcpy(tempPtr -> nextb -> bname, token);
			
			tempPtr -> nextb -> bno = tempPtr -> bno+1;
			tempPtr -> nextb -> nextb = NULL;
			tempPtr -> nextb -> custs = NULL;
		}
        
    }
 
    fclose(ptr);
}

void printBranches(){
	struct branch *tempPtr = bank1.branches;
	
	while(tempPtr != NULL){
		printf("Branch : ");
		printf("%d ", tempPtr->bno);
		printf(tempPtr->bname);
		printf("\n");
		tempPtr = tempPtr->nextb;
	}
	
	printf("\n\n");
	
}

void readCustomers(char file[]){
	FILE* ptr;
    char str[100];
    ptr = fopen(file, "a+");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    while ((fgets(str, 100, ptr) != NULL) && strlen(str) != 1) {

    	struct branch *tempPtr1 = bank1.branches;
    	
    	char * token = strtok(str, " ");
    	while(tempPtr1->bno != atoi(token))
    		tempPtr1 = tempPtr1->nextb;
    		
    	if(tempPtr1->custs == NULL){
    		tempPtr1->custs = (customer*)malloc(sizeof(customer));
    		
    		token = strtok(NULL, " ");
    		strcpy(tempPtr1->custs -> fname, token);
    		
    		token = strtok(NULL, " ");
    		strcpy(tempPtr1->custs -> lname, token);
    		
    		tempPtr1->custs -> cno = 1;
    		tempPtr1->custs -> nextc = NULL;
    		tempPtr1->custs -> trans = NULL;
    	}
		else{
			struct customer *tempPtr2 = tempPtr1->custs;

			while((tempPtr2 -> nextc) != NULL)
				tempPtr2 = tempPtr2 -> nextc;

			tempPtr2 -> nextc = (customer*)malloc(sizeof(customer));
			
			token = strtok(NULL, " ");
    		strcpy(tempPtr2->nextc -> fname, token);

    		token = strtok(NULL, " ");
    		strcpy(tempPtr2->nextc -> lname, token);
			
			tempPtr2 -> nextc -> cno = tempPtr2 -> cno+1;
			tempPtr2 -> nextc -> nextc = NULL;
			tempPtr2 -> nextc -> trans = NULL;
		}
        
    }

    printf("\n");
 
    fclose(ptr);
}

void printCustomers(){
	printf("****************************\n\n");
	
	struct branch *tempPtr1 = bank1.branches;
	
	while(tempPtr1 != NULL){
		printf("Branch : ");
		printf("%d ", tempPtr1->bno);
		printf(tempPtr1->bname);
		printf("\n");
		
		struct customer *tempPtr2 = tempPtr1->custs;
		
		tempPtr1 = tempPtr1->nextb;
		
		while(tempPtr2 != NULL){
			printf("  --%d ", tempPtr2->cno);
			printf(tempPtr2->fname);
			printf(" ");
			printf(tempPtr2->lname);
			tempPtr2 = tempPtr2->nextc;
		}
			
	}
	
	printf("\n\n");
	
}

void readTransactions(char file[]){
	FILE* ptr;
    char str[100];
    ptr = fopen(file, "a+");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    while ((fgets(str, 100, ptr) != NULL) && strlen(str) != 1) {

    	struct branch *tempPtr1 = bank1.branches;
    	
    	char * token = strtok(str, " ");
    	while(tempPtr1->bno != atoi(token))
    		tempPtr1 = tempPtr1->nextb;
    	
    	struct customer *tempPtr2 = tempPtr1->custs;
    	token = strtok(NULL, " ");
    	
    	while(tempPtr2->cno != atoi(token))
    		tempPtr2 = tempPtr2->nextc;
    		
    	if(tempPtr2->trans == NULL){
    		tempPtr2->trans = (transaction*)malloc(sizeof(transaction));
    		
    		token = strtok(NULL, " ");
    		tempPtr2->trans->optype = atoi(token);
    		
    		token = strtok(NULL, " ");
    		tempPtr2->trans->amount = atof(token);
    		
    		tempPtr2->trans->tno = 1;
    		tempPtr2->trans->nexttr = NULL;
    	}
		else{
			struct transaction *tempPtr3 = tempPtr2->trans;

			while((tempPtr3->nexttr) != NULL)
				tempPtr3 = tempPtr3 -> nexttr;

			tempPtr3 -> nexttr = (transaction*)malloc(sizeof(transaction));
			
			token = strtok(NULL, " ");
    		tempPtr3->nexttr->optype = atoi(token);
    		
    		token = strtok(NULL, " ");
    		tempPtr3->nexttr->amount = atof(token);
			
			tempPtr3 -> nexttr -> tno = tempPtr3 -> tno+1;
			tempPtr3 -> nexttr -> nexttr = NULL;
		}
        
    }

    printf("\n");
 
    fclose(ptr);
}

void printTransactions(){
	printf("****************************\n\n");
	
	struct branch *tempPtr1 = bank1.branches;
	
	while(tempPtr1 != NULL){
		printf("Branch : ");
		printf("%d ", tempPtr1->bno);
		printf(tempPtr1->bname);
		printf("\n");
		
		struct customer *tempPtr2 = tempPtr1->custs;
		
		tempPtr1 = tempPtr1->nextb;
		
		while(tempPtr2 != NULL){
			printf("  --%d ", tempPtr2->cno);
			printf(tempPtr2->fname);
			printf(" ");
			printf(tempPtr2->lname);
			
			struct transaction *tempPtr3 = tempPtr2->trans;
			
			tempPtr2 = tempPtr2->nextc;
			
			while(tempPtr3 != NULL){
				printf("\t++tno %d operation type (optype) %d amount %.2f", tempPtr3->tno, tempPtr3->optype, tempPtr3->amount);
				printf("\n");
				tempPtr3 = tempPtr3->nexttr;
			}
		}
			
	}
	
	printf("\n\n");
	
}

void printPaidCommission(){
		printf("****************************\n\n");
	
	struct branch *tempPtr1 = bank1.branches;
	
	while(tempPtr1 != NULL){
		printf("BRANCH : ");
		printf(tempPtr1->bname);
		printf("\n");
		
		struct customer *tempPtr2 = tempPtr1->custs;
		
		if(tempPtr2 == NULL)
			printf("\n(no customer in the branch %s)\n\n", tempPtr1->bname);
		else
			printf("\n\n");		
		
		tempPtr1 = tempPtr1->nextb;
		
		while(tempPtr2 != NULL){
			printf("--> cust id %d : %s %s", tempPtr2->cno, tempPtr2->fname, tempPtr2->lname);
			
			struct transaction *tempPtr3 = tempPtr2->trans;
			
			if(tempPtr3 == NULL)
				printf("  --(customer has no transaction)\n");
			
			float totalCommission = 0;
			
			while(tempPtr3 != NULL){
				struct operation_type *tempPtr4 = bank1.optypes;
				
				while(tempPtr4->optnum != tempPtr3->optype)
					tempPtr4 = tempPtr4->nextopt;
					
				float commissionRate = tempPtr4->commission;
				float amount = tempPtr3->amount;
				float paidCommission = commissionRate * amount / 100;
				totalCommission += paidCommission;
				
				printf("  -- tno %d optype %d commission rate %.2f amount %.2f paid commission %.2f total commission %.2f", tempPtr3->tno, tempPtr3->optype, commissionRate, amount, paidCommission, totalCommission);
				printf("\n");
				tempPtr3 = tempPtr3->nexttr;
			}
			
			printf("  ** paid commission %.2f", totalCommission);
			printf("\n\n");
			tempPtr2->paid_commission = totalCommission;
			tempPtr2 = tempPtr2->nextc;
		}
		
		printf("-------------------------------------------------------\n\n");
			
	}
	
	printf("\n\n");
}
