#include<stdio.h>
#include<string.h>
#define MAXLENGTH 20
#define MAXENTRIES 1000

int LC = 1000;
int Sym_T_cnt=0;
int dsflag=0;

//struct for MOT
struct MOT{
    char instruction[MAXLENGTH];
    int opcode;
    int no_operands;
    int length_instr;
};

//struct for POT
struct POT{
    char pseudo_opcode[MAXLENGTH];
    int no_operands;
};

//struct for instruction table
struct Sym_Table{
    char token[MAXLENGTH];
    char type[MAXLENGTH];
    int value;
    int address;
};

struct MOT MOT[MAXENTRIES];
struct POT POT[MAXENTRIES];
struct Sym_Table Sym_Table[MAXENTRIES];


void initializeMOT(){

    strcpy(MOT[1].instruction,"ADD");
    strcpy(MOT[2].instruction,"SUB");
    strcpy(MOT[3].instruction,"MUL");
    strcpy(MOT[4].instruction,"JMP");
    strcpy(MOT[5].instruction,"JNEG");
    strcpy(MOT[6].instruction,"JPOS");
    strcpy(MOT[7].instruction,"JZ");
    strcpy(MOT[8].instruction,"READ");
    strcpy(MOT[9].instruction,"WRITE");
    strcpy(MOT[10].instruction,"LOAD");
    strcpy(MOT[11].instruction,"STORE");
    strcpy(MOT[12].instruction,"HLT");

    MOT[1].opcode=1;
    MOT[2].opcode=2;
    MOT[3].opcode=3;
    MOT[4].opcode=4;
    MOT[5].opcode=5;
    MOT[6].opcode=6;
    MOT[7].opcode=7;
    MOT[8].opcode=8;
    MOT[9].opcode=9;
    MOT[10].opcode=10;
    MOT[11].opcode=11;
    MOT[12].opcode=12;
    
    MOT[1].no_operands=1;
    MOT[2].no_operands=1;
    MOT[3].no_operands=1;
    MOT[4].no_operands=1;
    MOT[5].no_operands=1;
    MOT[6].no_operands=1;
    MOT[7].no_operands=1;
    MOT[8].no_operands=1;
    MOT[9].no_operands=1;
    MOT[10].no_operands=1;
    MOT[11].no_operands=1;
    MOT[12].no_operands=0;

    MOT[1].length_instr=2;
    MOT[2].length_instr=2;
    MOT[3].length_instr=2;
    MOT[4].length_instr=2;
    MOT[5].length_instr=2;
    MOT[6].length_instr=2;
    MOT[7].length_instr=2;
    MOT[8].length_instr=2;
    MOT[9].length_instr=2;
    MOT[10].length_instr=2;
    MOT[11].length_instr=2;
    MOT[12].length_instr=2;

    for(int i=13; i<MAXENTRIES; i++){
        strcpy(MOT[i].instruction,"\0");
        MOT[i].opcode = -1;
    }

}


void initializePOT(){

    strcpy(POT[1].pseudo_opcode,"START:");
    strcpy(POT[2].pseudo_opcode,"ORG:");
    strcpy(POT[3].pseudo_opcode,"DB");
    strcpy(POT[4].pseudo_opcode,"DW");
    strcpy(POT[5].pseudo_opcode,"CONST");
    strcpy(POT[6].pseudo_opcode,"ENDP");
    strcpy(POT[7].pseudo_opcode,"END");
    
    POT[1].no_operands=0;
    POT[2].no_operands=1;
    POT[3].no_operands=2;
    POT[4].no_operands=2;
    POT[5].no_operands=2;
    POT[6].no_operands=0;
    POT[7].no_operands=0;
    
}


void initializeSym_Table(){

    for(int i=0; i<MAXENTRIES; i++){
        strcpy(Sym_Table[i].token,"\0");
        Sym_Table[i].address = 0;
        Sym_Table[i].value = -1;
        strcmp(Sym_Table[i].type ," VAR ");
    }
}

int IsInMOT(char *input){
    for(int i=1; i<13; i++){
        if(strcmp(input , MOT[i].instruction)==0){

            return 1;
        }
    }
    return 0;
}

int IsInPOT(char *input){
    for(int i=1; i<=7; i++){
        if(strcmp(input , POT[i].pseudo_opcode)==0){
            return 1;
        }
    }
    return 0;
}

int getopc(char* input){
    for(int i=1; i<13; i++){
        if(strcmp(input , MOT[i].instruction)==0){
            return MOT[i].opcode;
        }
    }
}

int isconst(char* input){
    int i=1;
    while((strcmp(Sym_Table[i].token,"\0")!=0) && (i<MAXENTRIES)){
        if(strcmp(input , Sym_Table[i].token)==0){
            if(strcmp(Sym_Table[i].type,"CONST")==0){
                return Sym_Table[i].value;
            }
        }
        i++;
    }
    return -1;
}

int getadd(char *input){
    int i=1;
    while((strcmp(Sym_Table[i].token,"\0")!=0) && (i<MAXENTRIES)){
        if(strcmp(input , Sym_Table[i].token)==0){
            if(strcmp(Sym_Table[i].type,"CONST")==1){
                return Sym_Table[i].address;
            }
        }
        i++;
    }
    return 0;
}

int IsInSymTab(char *input){
    int i=1;
    while((strcmp(Sym_Table[i].token,"\0")!=0) && (i<MAXENTRIES)){
        if(strcmp(input , Sym_Table[i].token)==0){
            return 1;
        }
        i++;
    }
    return 0;
}

int get_idx_in_ST(char *input){
    int i=1;
    while((strcmp(Sym_Table[i].token,"\0")!=0) && (i<MAXENTRIES)){
        if(strcmp(input , Sym_Table[i].token)==0){
            return i;
        }
        i++;
    }
    return 0;
}


void addEntryinST(struct Sym_Table item){
    int i=1;
    while((strcmp(Sym_Table[i].token,item.token)!=0)&&(strcmp(Sym_Table[i].token,"\0")!=0) && (i<MAXENTRIES))
        i++;

    if(strcmp(Sym_Table[i].token , "\0") == 0){
        strcpy(Sym_Table[i].token, item.token);
        strcpy(Sym_Table[i].type,item.type);
        Sym_Table[i].value=item.value;
        Sym_Table[i].address=item.address;
    }
}

char* substring(char *destination, const char *source, int beg, int n){
    while (n > 0){
        *destination = *(source + beg);
        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return destination;
}

void Parse_Line(char* line , int l){
    char* token;
    char* rest = line;
    char* arg[100][100];
    int i=0;

    while ((token = strtok_r(rest, " ", &rest))){
        strcpy(arg[i],token);
        i++;
    }

    if(dsflag==1){
        if(i==2){
            if(IsInSymTab(arg[0])==1){
                int idx = get_idx_in_ST(arg[0]);
                if(idx!=0){
                    char destination[25];
                    int start = 0;
                    int len = strlen(arg[1])-1;
                    substring(destination, arg[1], start, len);
                    strcpy(Sym_Table[idx].type ,destination);
                }
            }
        }
        else if(i==3){
            if(IsInSymTab(arg[0])==1){
                int idx = get_idx_in_ST(arg[0]);
                if(idx!=0){
                    strcpy(Sym_Table[idx].type ,arg[1]);
                    Sym_Table[idx].value = atoi(arg[2]);
                }
            }
        }

        if(IsInSymTab(arg[0])==1){
            int idx = get_idx_in_ST(arg[0]);
            if(idx!=0){
                Sym_Table[idx].address = LC;
            }
            else if(idx==0){
                struct Sym_Table item;
                strcpy(item.token,arg[0]);
                strcpy(item.type,"DIR");
                item.value=-1;
                item.address=LC;
                addEntryinST(item);
            }
        }
        LC = LC + 2;
    }

    if(i!=1 && IsInMOT(arg[0])==1){
        LC = LC+2;
        if(i>2){
            printf("%s %d" , arg[0] , i);
            printf("Incorrect Number of Operands");
            exit(0);
        }
        else if(i==2){
            int c=0;
            struct Sym_Table item;
            char destination[25];
            int start = 0;
            int len = strlen(arg[1])-1;
            substring(destination, arg[1], start, len);
            strcpy(item.token,destination);
            strcpy(item.type,"VAR");
            item.value=-1;
            item.address=0;
            if(IsInSymTab(destination)==0){
                addEntryinST(item);
            }
        }
    }
    else if(i==1){
        char destination[25];
        int start = 0;
        int len = strlen(arg[0])-1;
        substring(destination, arg[0], start, len);
        if(strcmp(destination , "ENDP")==0){
            dsflag=1;
        }
        else if(strcmp(destination , "HLT")==0){
            LC=LC+2;
        }

        if(IsInPOT(destination)==0 && IsInMOT(destination)==0 && destination[strlen(destination)-1]==58){
            if(IsInSymTab(destination)==1){
                int idx = get_idx_in_ST(destination);
                if(idx!=0){
                    Sym_Table[idx].address = LC;
                    strcpy(Sym_Table[idx].type,"DIR");
                }
            }
            else{
                struct Sym_Table item;
                strcpy(item.token,destination);
                strcpy(item.type,"DIR");
                item.address=LC;
                item.value=-1;
                addEntryinST(item);
            }
        }
    }
}

void printST(){
    int j=1;
    while((strcmp(Sym_Table[j].token,"\0")!=0) && (j<MAXENTRIES)){
        printf("Token=%s      Type=%s      Value=%d      Address=%d\n" , Sym_Table[j].token ,Sym_Table[j].type , Sym_Table[j].value , Sym_Table[j].address) ;
        j++;
    }
}

void output(char* line , int l , FILE*f){
    char* token;
    char* rest = line;
    int i=0;

    while ((token = strtok_r(rest, " ", &rest))){
        if(IsInMOT(token)==1){
            int op = getopc(token);
            //printf("%s -> %d\n" , token , op);
            fprintf(f, "%s -> %d\n", token , op);
            //fprintf(f, "%d", op);
        }
        else if(IsInPOT(token)){

        }
        else{
            char destination[25];
            int start = 0;
            int len = strlen(token)-1;
            substring(destination, token, start, len);
            int c = isconst(destination);
            int d = getadd(destination);
            int e = IsInMOT(destination);
            int g = IsInPOT(destination);

            if(e==1){
                int go = getopc(destination);
                //printf("%s -> %d\n" , destination , go);
                fprintf(f, "%s -> %d\n", token , go);
                //fprintf(f, "%d", go);
            }
            else if(g==1 && strcmp("ENDP" , destination)==0){
                exit(0);
            }
            else if(c!=-1){
                //printf("%s -> %d\n" , destination , c);
                fprintf(f, "%s -> %d\n", token , c);
                //fprintf(f, "%d", c);
            }
            else{
                //printf("%s -> %d\n" , destination , d);
                fprintf(f, "%s -> %d\n", token, d);
                //fprintf(f, "%d", d);
            }
        }
    }
}

int main(){

    struct MOT item1;
    initializeMOT();

    struct POT item2;
    initializePOT();

    struct Sym_Table item3;
    initializeSym_Table();

    FILE* fp = fopen("pgm.asm" , "r");
    char line[1000];
    int l=0;
    if(fp==NULL){
        printf("Could not open the file");
    }

    while(fgets(line, 1000, fp)){
        Parse_Line(line,l);
        l++;
    }

    //printST();
    close(fp);

    FILE* fp1 = fopen("pgm.asm" , "r");
    FILE* f = fopen("output.obj", "a+");

    char line1[1000];
    int ll=0;
    if(fp1==NULL){
        printf("Could not open the file");
    }

    while(fgets(line1, 1000, fp1)){
        output(line1,ll,f);
        ll++;
    }
    close(fp1);
    return 0;
}
