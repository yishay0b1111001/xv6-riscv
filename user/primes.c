#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int
main(int argc, char* argv[]) 
{
	int pipes[32][2];
	int offset = 0;
	pipe(pipes[offset]);
	int pid = fork();
	if (pid > 0) {
		//parrent;
		close(pipes[offset][0]);
		for (char i = 2; i <= 32; i++) {
			write(pipes[offset][1], &i, 1);
			//fprintf(1, "wrote: %d\n", i);
		}
		wait(0);
		exit(0);
	}
	else if (pid == 0) {
		//child
		int flag = 0;
		char x = 2;
		int n = 0;
		int self_value = 2;
		fprintf(1, "prime %d\n", self_value);

		while (x != 32) {
			close(pipes[offset][1]);
			n = read(pipes[offset][0], &x, 1);
			if (n < 0) {
				fprintf(1, "read error, %d\n", n);
			}
			if (x == 32){
				if (flag){
					write(pipes[offset+1][1], &x, 1);
					wait(0);
				}
				return 0;
				
			}
			if (x % self_value != 0) {
				if (!flag) {
					pipe(pipes[offset+1]);
					if (fork() == 0) {
						self_value = x;
						offset += 1;
					
						close(pipes[offset][1]);
						
						
						flag = 0;
						fprintf(1, "prime %d\n", self_value);
					}
					else {
						close(pipes[offset+1][0]);
						flag = 1;
					}
				}
				else {
					write(pipes[offset+1][1], &x, 1);
				}
			}
		}
		wait(0);
		return 0;
		
	}	
	return 0;
}
