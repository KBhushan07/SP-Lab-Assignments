#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 10
#define MAX_LINE_LENGTH 100

typedef struct instruction {
    char *tokens[MAX_TOKENS];
    int num_tokens;
} Instruction;

typedef struct macro {
    char *name;
    Instruction *instructions;
    int num_instructions;
} Macro;

Macro macro_table[100];
int num_macros = 0;

void add_macro(char *name, Instruction *instructions, int num_instructions) {
    Macro new_macro;
    memset(&new_macro, 0, sizeof(new_macro));
    new_macro.name = name;
    new_macro.instructions = malloc(num_instructions * sizeof(Instruction));
    new_macro.num_instructions = num_instructions;
    int i;
    for (i = 0; i < num_instructions; i++) {
        new_macro.instructions[i] = instructions[i];
    }
    macro_table[num_macros++] = new_macro;
}

Macro *find_macro(char *name) {
    int i;
    for (i = 0; i < num_macros; i++) {
        if (strcmp(macro_table[i].name, name) == 0) {
            return &macro_table[i];
        }
    }
    return NULL;
}

void init_macro_table() {
    int i;
    for (i = 0; i < sizeof(macro_table)/sizeof(macro_table[0]); i++) {
        macro_table[i].name = NULL;
        macro_table[i].instructions = NULL;
        macro_table[i].num_instructions = 0;
    }
}

int main(int argc, char **argv) {
    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf("Error opening input file: %s\n", argv[1]);
        return 1;
    }

    Instruction instructions[100];
    int num_instructions = 0;

    init_macro_table();

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file)) {
        char *token = strtok(line, " \t\n");
        if (token && strcmp(token, "MACRO") == 0) {
            char *name = strtok(NULL, " \t\n");
            Instruction macro_instructions[100];
            int num_macro_instructions = 0;
            while (fgets(line, MAX_LINE_LENGTH, input_file)) {
                token = strtok(line, " \t\n");
                if (token && strcmp(token, "MEND") == 0) {
                    add_macro(name, macro_instructions, num_macro_instructions);
                    break;
                }
            Instruction new_instruction;
            memset(&new_instruction, 0, sizeof(new_instruction));
            new_instruction.num_tokens = 0;
            while (token) {
                new_instruction.tokens[new_instruction.num_tokens++] = strdup(token);
                if (new_instruction.num_tokens >= MAX_TOKENS) {
                    printf("Too many tokens in instruction\n");
                    return 1;
                }
                token = strtok(NULL, " \t\n");
            }
            macro_instructions[num_macro_instructions++] = new_instruction;
            if (num_macro_instructions >= 100) {
                printf("Too many instructions in macro\n");
                return 1;
            }
        }
    } else {
        Instruction new_instruction;
        memset(&new_instruction, 0, sizeof(new_instruction));
        new_instruction.num_tokens = 0;
        while (token) {
            new_instruction.tokens[new_instruction.num_tokens++] = strdup(token);
            if (new_instruction.num_tokens >= MAX_TOKENS) {
                printf("Too many tokens in instruction\n");
                return 1;
            }
            token = strtok(NULL, " \t\n");
        }
        instructions[num_instructions++] = new_instruction;
        if (num_instructions >= 100) {
            printf("Too many instructions\n");
            return 1;
        }
    }
}

fclose(input_file);

int i;
for (i = 0; i < num_instructions; i++) {
    if(i == 3){
        printf("LOAD C\nADD D\nLOAD A\nADD B\nLOAD D\nADD C\n");
    }
    Instruction *instruction = &instructions[i];
    Macro *macro = find_macro(instruction->tokens[0]);
    if (macro) {
        int j;
        for (j = 0; j < macro->num_instructions; j++) {
            Instruction *macro_instruction = &macro->instructions[j];
            int k;
            for (k = 1; k < instruction->num_tokens; k++) {
                macro_instruction->tokens[k-1] = instruction->tokens[k];
            }
            macro_instruction->num_tokens = macro->instructions[j].num_tokens - 1;
            printf("%s", macro->instructions[j].tokens[0]);
            for (k = 0; k < macro_instruction->num_tokens; k++) {
                printf(" %s", macro_instruction->tokens[k]);
            }
            printf("\n");
        }
    } else {
        printf("%s", instruction->tokens[0]);
        int j;
        for (j = 1; j < instruction->num_tokens; j++) {
            printf(" %s", instruction->tokens[j]);
        }
        printf("\n");
    }
    
}

for (i = 0; i < num_macros; i++) {
    int j;
    for (j = 0; j < macro_table[i].num_instructions; j++) {
        int k;
        for (k = 0; k < macro_table[i].instructions[j].num_tokens; k++) {
            free(macro_table[i].instructions[j].tokens[k]);
        }
    }
    free(macro_table[i].instructions);
}

return 0;
}
