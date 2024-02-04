#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

void
xargs(char* command, char** argv)
{ 

//get a line, read and add to word until \n
//create a child with the command, line as arguments
//use exec to run the command on the line arguments
  char arguments[MAXARG*64]; 
  char* word[MAXARG];
  for (int i = 0; i < MAXARG; i++) {
  	word[i] = 64*i+arguments;
  	}
  memset(arguments, 0 , MAXARG*64);
  char new_char;
  int charp = 0;
  int wordp = 1;
  for (int i = 2; argv[i] != 0; i++) {
  	int j = 0;
  	for (j = 0; argv[i][j] != 0; j++) {
  	 word[i-1][j] = argv[i][j];
  	}
  	word[i-1][j] = '\0';
  	wordp++;
  }
  while (read(0, &new_char, 1) == 1) {
  if (new_char == '\n') {
  	if (fork() > 0) {
  		wait(0);
  		charp = 0;
  		wordp = 1;
  		memset(word, 0 , MAXARG*64);
  		for (int i = 0; i < MAXARG; i++) {
  			word[i] = 64*i+arguments;
  		}
  		 for (int i = 2; argv[i] != 0; i++) {
  			int j = 0;
  			for (j = 0; argv[i][j] != 0; j++) {
  			 word[i-1][j] = argv[i][j];
  			}
  			word[i-1][j] = '\0';
  			wordp++;
  		}
  		}
  	else {
  		word[++wordp] = 0;
  		exec(command, word);
  	}
  } else {
  	if (new_char == ' ') {
  	charp = 0;
  	wordp++;
  	}
  	else {
  		word[wordp][charp++] = new_char;
  		}
  } 
}
}

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(1,"error: not enough arguments\n");
        exit(0);
    }
    xargs(argv[1], argv);
    exit(0);
}
