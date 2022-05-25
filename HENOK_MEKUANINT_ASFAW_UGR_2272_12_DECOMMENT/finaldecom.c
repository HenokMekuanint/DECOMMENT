#include <stdio.h>
#include <stdlib.h>
enum POSSIBLE_STATE_OF_COMMENT
{
    NORMAL,
    SLASH, 
    FORWARD_SLASH, 
    END_STAR, 
    DOUBLE_QOUTE, 
    SINGLE_QOUTE, 
    BACK_SLASH, 
    BACK_SLASH_BETWEEN_DOUBLE_QOUTE,
    BACK_SLASH_BETWEEN_SINGLE_QOUTE, 
    BACK_SLASH_BETWEEN_SLASH 
};
void BACK_SLASH_STATE_HANDLER(int string_read, enum POSSIBLE_STATE_OF_COMMENT *state,int *line){
        
        if(string_read =='n'){
        *state = NORMAL;
        putchar('\n');
        (*line)++;
    }
    else{
        *state = NORMAL;
        putchar('\\');
        putchar(string_read);
    };
}
void SINGLE_QOUTE_STATE_HANDLER(int string_read,enum POSSIBLE_STATE_OF_COMMENT *state){

    if(string_read == '\''){
        *state = NORMAL;
        putchar(string_read);
    }
    else if(string_read == '\\'){
        *state = BACK_SLASH_BETWEEN_SINGLE_QOUTE;
    }
    else{
        *state = SINGLE_QOUTE;
        putchar(string_read);
    };
}
void DOUBLE_QOUTE_STATE_HANDLER(int string_read,enum POSSIBLE_STATE_OF_COMMENT *state){
    
    if(string_read == '"'){
    *state = NORMAL;
    putchar(string_read);
    }
    else if(string_read == '\\'){
        *state = BACK_SLASH_BETWEEN_DOUBLE_QOUTE;
    }
    else{
        *state = DOUBLE_QOUTE;
        putchar(string_read);
        
    };
}
void ENDING_STAR_STATE_HANDLER(enum POSSIBLE_STATE_OF_COMMENT *state,int string_read){

if(string_read == '/'){
        *state = NORMAL;
    }
    else if(string_read == '*'){
        *state = END_STAR;
    }
    else{
        *state = FORWARD_SLASH;
    };
}

void BEGGINING_STAR_STATE_HANDLER(int string_read,enum POSSIBLE_STATE_OF_COMMENT *state){

    if(string_read == '*'){
        *state = END_STAR;
    }
    else if(string_read == '\\'){
        *state = BACK_SLASH_BETWEEN_SLASH;
    }
    else{
        *state = FORWARD_SLASH;
    };
}

void STATE_TO_BE_HANDLED(int string_read,enum POSSIBLE_STATE_OF_COMMENT *state){
     if(string_read  =='/'){
        *state = SLASH;
    }
    else if(string_read  == '"'){
        *state = DOUBLE_QOUTE;
        putchar(string_read);
    }
    else if(string_read  == '\''){
        *state = SINGLE_QOUTE;
        putchar(string_read);
    }
    else if(string_read  == '\\'){
        *state = BACK_SLASH;
    }
    else{
        *state = NORMAL;
        putchar(string_read);
    };
}

void SLASH_STATE_HANDLER(enum POSSIBLE_STATE_OF_COMMENT *state,int string_read){

        if(string_read == '*'){
        *state = FORWARD_SLASH;
        putchar(' ');
    }
    else if(string_read == '/'){
        *state = SLASH;
        putchar(string_read);
    }
    else{
        *state = NORMAL;
        putchar('/');
        putchar(string_read);
    };
}


int comment_remover(int string_read,enum POSSIBLE_STATE_OF_COMMENT *state, int *line){
    if(string_read =='\n'){ 
            (*line)++;
    }
    if(*state == NORMAL){
    
STATE_TO_BE_HANDLED(string_read,state);
    }
    else if(*state == SLASH){
    
    SLASH_STATE_HANDLER(state,string_read);

    }
    else if(*state == FORWARD_SLASH){

    BEGGINING_STAR_STATE_HANDLER(string_read,state);

    }
    else if(*state == END_STAR){

ENDING_STAR_STATE_HANDLER(state,string_read);

    }
    else if(*state == DOUBLE_QOUTE){
DOUBLE_QOUTE_STATE_HANDLER(string_read,state);

    }
    else if(*state == SINGLE_QOUTE){

SINGLE_QOUTE_STATE_HANDLER(string_read,state);

    }
    else if(*state == BACK_SLASH){

BACK_SLASH_STATE_HANDLER(string_read,state,line);


    }
    else if(*state == BACK_SLASH_BETWEEN_DOUBLE_QOUTE){
    if(string_read =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(string_read);
    };
    *state = DOUBLE_QOUTE;
    }
    else if(*state == BACK_SLASH_BETWEEN_SINGLE_QOUTE){
        if(string_read =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(string_read);
    }
    *state = SINGLE_QOUTE;

    }
    else if(*state == BACK_SLASH_BETWEEN_SLASH){
     if(string_read =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(string_read);
    }
    *state = FORWARD_SLASH;
}

    
}

int main(int argc, char *argv[]){
    enum POSSIBLE_STATE_OF_COMMENT state;
    FILE  *file;
    int string_read;
    state=NORMAL;
    int line = 0;
    if(argc==1) {
		while ((string_read=getchar())!=EOF){
            comment_remover(string_read,&state, &line);
        }
	} 
    else if(argc==2) {
		file = fopen(argv[1], "r");
		if(file == NULL) {
            fprintf(stderr, "Cannot open the file\n");
            exit(-1);
		}
        while ((string_read=getc(file))!=EOF){
            comment_remover(string_read,&state, &line);
        }
        fclose(file);
    }   
        if(state == FORWARD_SLASH || state == END_STAR){
            fprintf(stderr, "Error: line %d: unterminated comment\n",line);
            exit(-1);     
  }
  return 0;
}