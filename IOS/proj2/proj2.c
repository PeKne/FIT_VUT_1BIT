/*
//                                                                    
// Author:		  PETR KNETL <xknetl00@stud.fit.vutbr.cz>             
// Project:		  2. projekt předmětu IOS - Synchronizace procesů     
// Date:		  20. 4. 2017                                         
// File:		  proj2.c                                             
// Dependencies:  proj2.h                                                     
//                                                                            
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
int A, C , AGT, CGT, AWT, CWT; // promenne pro argumenty
sem_t *mut, *qeue_A, *qeue_C, *leaving_all, *waiting_child, *waiting_adult; // promenne pro semafory
int *sh_count, *sh_adult_counter, *sh_child_counter, *sh_child_wait, *sh_adult_generate, *sh_to_leave, *sh_done,  //sdilene promenne
     sh_doneID,  sh_to_leaveID,sh_child_waitID, sh_countID, sh_adult_counterID, sh_child_counterID, sh_adult_generateID;

int set_semaphores(){
	if( (mut = sem_open("/IOS2_xknetl00_mut",O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'mut'\n");
		return 1;
	}
	if( (qeue_A = sem_open("/IOS2_xknetl00_qeueA",O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'qeueA'\n");
		return 1;
	}
	if( (qeue_C = sem_open("/IOS2_xknetl00_qeueC",O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'qeueC'\n");
		return 1;
	}
	if( (leaving_all = sem_open("/IOS2_xknetl00_leavingAll",O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'leaving_all'\n");
		return 1;
	}
	if( (waiting_adult = sem_open("/IOS2_xknetl00_waitingAdult",O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'waiting_adult'\n");
		return 1;
	}
	if( (waiting_child = sem_open("/IOS2_xknetl00_waitingChild",O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED){
		fprintf(stderr, "ERROR: unable to create semaphore 'waiting_child'\n");
		return 1;
	}
	return 0;
}

int set_sh_memory(){ //funkce pro inicializaci sdilenych pameti
	if((sh_countID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_count = (int *) shmat(sh_countID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
    (*sh_count)=0;
	if((sh_adult_counterID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_adult_counter = (int *) shmat(sh_adult_counterID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_adult_counter) = 0;
	if((sh_child_counterID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_child_counter = (int *) shmat(sh_child_counterID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_child_counter) = 0;
	if((sh_child_waitID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_child_wait = (int *) shmat(sh_child_waitID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_child_wait) = 0;
	if((sh_adult_generateID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_adult_generate = (int *) shmat(sh_adult_generateID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_adult_generate) = A;
	if((sh_to_leaveID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_to_leave = (int *) shmat(sh_to_leaveID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_to_leave) =0;
	if((sh_doneID =shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 1;
    }
    if ((sh_done = (int *) shmat(sh_doneID, NULL, 0)) == NULL){
        fprintf(stderr, "ERROR: unable to create shared memory\n");
        return 2;
    }
	(*sh_done) = 0;
	return 0;
		
}

void destroy_shared_vars(){
	shmctl( sh_doneID, IPC_RMID, NULL);
    shmctl( sh_to_leaveID, IPC_RMID, NULL);
    shmctl( sh_child_counterID, IPC_RMID, NULL);
    shmctl( sh_countID, IPC_RMID, NULL);
    shmctl( sh_adult_counterID, IPC_RMID, NULL);
    shmctl( sh_child_waitID, IPC_RMID, NULL);
    shmctl( sh_adult_generateID, IPC_RMID, NULL);
}
     
int destroy_semaphores(){
	if(sem_close(mut)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_mut");
	if(sem_close(qeue_A)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_qeueA");
	if(sem_close(qeue_C)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_qeueC");
	if(sem_close(leaving_all)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_leavingAll");
	if(sem_close(waiting_adult)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_waitingAdult");
	if(sem_close(waiting_child)){
		fprintf(stderr,"ERROR: unable to close semaphores\n");
		return 2;
	}
	sem_unlink("/IOS2_xknetl00_waitingChild");
	
	return 0;
}
	
     
int main(int argc, char* argv[])
{
	if (argc != 7){ // chyba spatny pocet pocet param.
		fprintf(stderr, "ERROR: wrong number of parameters\n");
		return 1;
	}
	int param[6]; //pole pro parametry prevedene do int
	char* strcont;//pomocna promena pro funkci strtol()
	for(int i=0; i<=5; i++){ //prevod parametru z typu char do int
		strcont = NULL;
		param[i] = strtol(argv[i+1],&strcont, 10);
		printf("%s",strcont);
		if (*strcont != '\0'){ // parametr obsahuje jiny znak nez cislo
			fprintf(stderr, "ERROR: parameter includes letters\n");
			return 1;
		}
	}
	A = param[0]; //pocet ADULTS
	if(A <= 0){
		fprintf(stderr,"ERROR: parameter A has to be greater than 0\n");
		return 1;
	}
	C = param[1]; // pocet CHILDS
	if(C <= 0){
		fprintf(stderr,"ERROR: parameter C has to be greater than 0\n");
		return 1;
	}
	AGT = param[2]; //ADULT GENERATION TIME
	if(AGT < 0 || AGT >= 5001){
		fprintf(stderr,"ERROR: parameter AGT has to be greater than 0 and lower than 5001\n");
		return 1;
	}
	CGT = param[3]; //CHILD GENERATION TIME
	if(CGT < 0 || CGT >= 5001){
		fprintf(stderr,"ERROR: parameter CGT has to be greater than 0 and lower than 5001\n");
		return 1;
	}
	AWT = param[4]; //ADULT WORK TIME
	if(AWT < 0 || AWT >= 5001){
		fprintf(stderr,"ERROR: parameter AWT has to be greater than 0 and lower than 5001\n");
		return 1;
	}
	CWT = param[5]; //CHILD WORK TIME
	if(CWT < 0 || CWT >= 5001){
		fprintf(stderr,"ERROR: parameter CWT has to be greater than 0 and lower than 5001\n");
		return 1;
	}
	
	int total = A + C; //celkem procesu
	
	FILE *file;
	if( (file = fopen("proj2.out", "w")) == NULL) {//otevre soubor, pri neuspechu vraci 2 a konci
		fprintf(stderr, "ERROR: unable to open file proj2.out");
		return 2;
	}
	setbuf(file, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	
	srandom(time(0));
	
	if(set_semaphores() != 0) return 2; //inicializace semaforu
	if(set_sh_memory() != 0) return 2;// inicializace sdilene pameti
	
	pid_t child_generator; // vytvoreni procesu pro generovani precesu adult
	child_generator = fork();
	if(child_generator == 0){ //jsme uvnitr generatoru CHILD
		int z = 0;
		while(z < C){
			z++;
			if(CGT) usleep( 1000 * (rand() % CGT)); // spanek 0 az 5000
			pid_t child_process;
			child_process = fork();
			int child_id = z;
			if(child_process == 0){ // jsme uvnitr procesu CHILD
				sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: C %d	: started\n",*sh_count,child_id);
					
				if((((*sh_adult_counter) - (*sh_child_wait))*3) > (*sh_child_counter)){
					(*sh_child_counter)++;
					(*sh_count)++;
					fprintf(file,"%d	: C %d	: enter\n",*sh_count,child_id);
					sem_post(mut);
				}
				else{
					(*sh_child_wait)++;
					if((*sh_adult_generate) != 0){
						(*sh_count)++;
						fprintf(file, "%d	: C %d	: waiting	%d: %d\n",*sh_count, child_id, (*sh_adult_counter), (*sh_child_counter));
						sem_post(mut);
					}
					if(A != 0) sem_wait(qeue_C);
					sem_wait(mut);
						sem_post(waiting_child);
						(*sh_count)++;
						fprintf(file,"%d	: C %d	: enter\n",*sh_count, child_id);
					sem_post(mut);
				}
					
				if(CWT != 0) usleep(1000* (random()%CWT));
				
				sem_wait(mut);
					(*sh_child_counter)--;
					(*sh_count)++;
					fprintf(file, "%d	: C %d	: trying to leave\n", *sh_count, child_id);
					(*sh_count)++;
					fprintf(file, "%d	: C %d	: leave\n", *sh_count, child_id);
					
					if ((*sh_to_leave) && (3 * ((*sh_adult_counter) - 1) >= *sh_child_counter)){
							(*sh_adult_counter)--;
							(*sh_to_leave)--;
							sem_post(qeue_A);
							sem_post(mut);
								sem_wait(waiting_adult);
							sem_wait(mut);
						}
						
						(*sh_done)++;
						if((*sh_done) == total) sem_post(leaving_all);
						
						sem_post(mut);
						sem_wait(leaving_all);
						sem_post(leaving_all);
						
						sem_wait(mut);
							(*sh_count)++;
							fprintf(file, "%d	: C %d	: finished\n", *sh_count, child_id);
						sem_post(mut);
						exit(0);
			}
			else if(child_process < 0){ //nepovedlo se vygenerovat CHILD
				fprintf(stderr, "ERROR: Unable to fork process");
				return 2;
			}
		}
		int i = 0;
		while(i < C){
		wait(NULL);
		i++;
			}
		exit(0); // ukonceni GENERATORU CHILD
		}
	else if(child_generator < 0){
		fprintf(stderr, "ERROR: Unable to fork process");
		return 2;
	}
	
	pid_t adult_generator; // vytvoreni procesu pro generovani precesu adult
	adult_generator = fork();
	if(adult_generator == 0){ //jsme uvnitr generatoru ADULT
		int t = 0;
		while(t < A){
			t++;
			if(AGT) usleep( 1000 * (rand() % AGT)); // spanek 0 az 5000
			pid_t adult_process;
			adult_process = fork();
			int adult_id = t;
			if(adult_process == 0){ // jsme uvnitr procesu ADULT
				sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: A %d	: started\n",(*sh_count), adult_id);
				sem_post(mut);
					
				sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: A %d	: enter\n",(*sh_count), adult_id);
					(*sh_adult_generate)--;
					(*sh_adult_counter)++;
					if((*sh_child_wait) != 0){
						int pass = ((*sh_child_wait) > 3) ? 3 : (*sh_child_wait);
						int count = 0;
						while(count < pass){
							sem_post(qeue_C);
							count++;
						}
						(*sh_child_wait) -= pass;
						(*sh_child_counter) += pass;
						sem_post(mut);
						count = 0;
						while (count < pass){
							sem_wait(waiting_child);
							count++;
						}
						sem_wait(mut);
					}
				sem_post(mut);
					
				if(AWT != 0) usleep(1000* (random()%AWT)); //simulace prace v centru;
				sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: A %d	: trying to leave\n",*sh_count , adult_id);
					
				if((3*((*sh_adult_counter) -1)) >= *sh_child_counter){
					(*sh_count)++;
					fprintf(file,"%d	: A %d	: leave\n",*sh_count,adult_id);
					(*sh_adult_counter)--;
					sem_post(mut);
				}
				else{
					(sh_count)++;
					fprintf(file,"%d	: A %d	: waiting: 	%d: %d\n", *sh_count, adult_id, *sh_adult_counter, *sh_child_counter);
					(*sh_to_leave)++;
					sem_post(mut);
					sem_wait(qeue_A);
					sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: A %d	: leave\n", *sh_count, adult_id);
					sem_post(mut);
					sem_post(waiting_adult);
				 }
				sem_wait(mut);
					if((*sh_adult_generate) == 0){
						int f = 0;
						while(f<C){
							sem_post(qeue_C);
							f++;
						}
					}
				sem_post(mut);
					
				sem_wait(mut);
					(*sh_done)++;
					if((*sh_done) == total) sem_post(leaving_all);
				sem_post(mut);
						
				sem_wait(leaving_all);
				sem_post(leaving_all);
						
				sem_wait(mut);
					(*sh_count)++;
					fprintf(file, "%d	: A %d	: finished\n", *sh_count, adult_id);
				sem_post(mut);
				exit(0);
							
								
			}
			else if(adult_process < 0){ //nepovedlo se vygenerovat ADULT
				fprintf(stderr, "ERROR: Unable to fork process");
				return 2;
			}
		}
		int i = 0;
		while(i < A){
		wait(NULL);
		i++;
			}
		exit(0); // ukonceni GENERATORU ADULT
		}

	else if(adult_generator < 0){
		fprintf(stderr, "ERROR: Unable to fork process");
		return 2;
	}
	int x = 0;
	while(x<2){
		wait(NULL);
		x++;
	}
	
	if(destroy_semaphores() != 0) return 2;
	destroy_shared_vars();
	fclose(file);
	return 0;
}
