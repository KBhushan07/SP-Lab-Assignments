#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_LEN 100
#define MAX_CODE_LEN 100
#define MAX_OPERAND_LEN 100
#define MAX_ALA_LEN 100
#define MAX_TEMP_LEN 100

struct stack {
    char data[MAX_ALA_LEN][MAX_TEMP_LEN];
    int sp;
};

FILE *f1, *f2, *f3, *f4;
char label[MAX_LABEL_LEN], code[MAX_CODE_LEN], operand[MAX_OPERAND_LEN], du_label[MAX_LABEL_LEN], du_code[MAX_CODE_LEN], du_operand[MAX_OPERAND_LEN], ala1[MAX_ALA_LEN], temp[MAX_TEMP_LEN];
int mdtc = 1, mntc = 1, mdlc = 0, mdtp = 0, flag = 0, n = 0, t;

struct stack s;

void READ();
void SUBSTIUTE_ALA2();
void SEARCH_IN_MNT();
void PREPARE_ALA2();
int PREPARE_ALA1();
void SUBSTITUTE_ALA1(int len_ala1);

int main()
{
    int len_ala1 = 0;
    s.sp = -1;
    f1 = fopen("input4.txt", "r");
    if (f1 == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }
    f2 = fopen("mnt_table.txt", "w+");
    f3 = fopen("mdt_table.txt", "w+");
    f4 = fopen("output_file_nested.txt", "w+");

    do {
        label1:
        READ();
        flag = 0;
        SEARCH_IN_MNT();
        if (flag == 1) {
            sprintf(temp, "%d", s.sp + 48);
            strcpy(s.data[s.sp + n + 2], temp);
            s.sp = s.sp + n + 2;
            sprintf(temp, "%d", mdtp + 48);
            strcpy(s.data[s.sp + 1], temp);

            PREPARE_ALA2();
            READ();
            fseek(f3, 0, SEEK_SET);
        }
        if (strcmp(code, "MACRO") == 0) {
            mdlc++;
            READ();
            flag = 0;
            SEARCH_IN_MNT();
            if (flag == 1) {
                while (strcmp(code, "MEND") != 0)
                    READ();
                printf("\nouter code = %s", code);
                mdlc--;
                printf("\nmdlc = %d", mdlc);
                if (mdlc == 0) {
                    strcpy(temp, s.data[s.sp]);
                    t = atoi(temp) - 48;
                    n = s.sp - 2 - t;
                    s.sp = t;
                }
                goto label1;
            }
            mdtc++;
            mdtp++;
        }
        else {
            SUBSTITUTE_ALA1(len_ala1);
            fprintf(f4, "%s\t%s\t%s\n", label, code, operand);
        }
    } while (strcmp(code, "END") != 0);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);


    return 0;

}

void READ()
{
    fscanf(f1, "%s%s%s", label, code, operand);
}

void SUBSTIUTE_ALA2()
{
    int i, j, len_ala1;
    char temp_operand[MAX_OPERAND_LEN];
    len_ala1 = PREPARE_ALA1();
    for (i = 0, j = 0; operand[i] != '\0'; i++) {
    if (operand[i] == ',') {
    temp_operand[j] = '\0';
    SUBSTITUTE_ALA1(len_ala1);
    fprintf(f4, "%s, ", ala1);
    j = 0;
    }
    else
    temp_operand[j++] = operand[i];
    }
    temp_operand[j] = '\0';
    SUBSTITUTE_ALA1(len_ala1);
    fprintf(f4, "%s\n", ala1);
}

void SEARCH_IN_MNT()
{
    int i = 0;
    char mname[MAX_LABEL_LEN];
    while (fscanf(f2, "%d%s%s%d", &i, mname, du_code, &t) != EOF) {
    if (strcmp(mname, code) == 0) {
    flag = 1;
    break;
    }
    }
    fseek(f2, 0, SEEK_SET);
}

void PREPARE_ALA2()
{
    int i, j, len_ala1;
    char temp_operand[MAX_OPERAND_LEN];
    len_ala1 = PREPARE_ALA1();
    for (i = 0, j = 0; operand[i] != '\0'; i++) {
    if (operand[i] == ',') {
    temp[j] = '\0';
    SUBSTITUTE_ALA1(len_ala1);
    strcpy(ala1, temp);
    s.sp++;
    j = 0;
}
else
    temp[j++] = operand[i];
}
    temp[j] = '\0';
    SUBSTITUTE_ALA1(len_ala1);
    strcpy(ala1, temp);
    s.sp++;
}

int PREPARE_ALA1()
{
    int i, j, k, len_ala1;
    char temp[MAX_OPERAND_LEN];
    len_ala1 = 0;
    for (i = 0, j = 0; operand[i] != '\0'; i++) {
    if (operand[i] == '&' && operand[i + 1] == ' ') {
        i = i + 2;
        for (k = 0; operand[i] != ',' && operand[i] != '\0'; i++, k++)
            temp[k] = operand[i];
            temp[k] = '\0';
            len_ala1++;
            strcpy(s.data[s.sp + len_ala1], temp);
            j = 0;
    }
    else
        temp[j++] = operand[i];
    }
    temp[j] = '\0';
    return len_ala1;
}

void SUBSTITUTE_ALA1(int len_ala1) {
    int i, k, m, counter, check;
    i = counter = k = m = 0;

    if (flag == 0 && mdlc == 1) {
        while (operand[i] != '\0') { 
            if (operand[i] == '&') {
                counter = 0;
                m = i;
                check = 0;
                ++i;
                for (k = 0; k < len_ala1; k++) {
                    if (ala1[k] == operand[i]) {
                        check = 1;
                        i++;
                    }
                    if (check == 0) {
                        if (ala1[k] == ' ') {
                            counter++;
                        }
                    }
                }
                if (check == 1) {
                    operand[m] = '#';
                    operand[++m] = ((char)counter) + 48;
                    operand[++m] = '\0';
                    i = m;
                }
            }
            else {
                i++;
            }
        }
    }
    else {
        while (code[i] != '\0') {
            if (code[i] == '&') {
                counter = 0;
                m = i;
                check = 0;
                ++i;
                for (k = 0; k < len_ala1; k++) {
                    if (ala1[k] == code[i]) {
                        check = 1;
                        i++;
                    }
                    if (check == 0) {
                        if (ala1[k] == ' ') {
                            counter++;
                        }
                    }
                }
                if (check == 1) {
                    code[m] = '#';
                    code[++m] = ((char)counter) + 48;
                    code[++m] = '\0';
                    i = m;
                }
            }
            else {
                i++;
            }
        }
    }
}

