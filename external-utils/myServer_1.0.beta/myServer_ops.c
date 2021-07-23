//#include "myServer.h"
#include "myServer_ops.h"
#include "myServer_comm.h"
#include "myServer_d2xpn.h"

//char global_buffer[MAX_BUFFER_SIZE];

int aux_clear_dirs(char *path){
	int i, j;
	char ant = '\0', s[255];
	
	j=0;
	for(i=0;i < strlen(path); i++){
		switch(path[i]){
			case '/':
				if(ant != '/'){
					ant = s[j] = '/';
					j++;
				}
				break;
			default:
				ant = s[j] = path[i];
				j++;
				
		}

		s[j] = '\0';
	}
	
	strcpy(path, s);
	return 0;
}

int aux_get_dirs(char *path, int n, char *s){
	int i=0, j=0, ant=-1, pos=-1;
	int cont=-1;
	char new_path[MAXPATHLEN];
	
	strcpy(new_path, path);
	
	path = new_path;
	aux_clear_dirs(path);	
	s[0] = '\0';	
	if (path == NULL) {
		return 0;	
	}
	
	for(i=0; i<strlen(path) && cont<(n+1); i++){
		if (path[i] == '/'){
			if(ant == -1){
				ant = pos = i;
			}
			pos = i;
			cont++;
		}
	}

	if(cont<(n+1)){
		return 0;
	}
	
	for(j=ant; j<pos; j++){
		s[j] = path[j];
	}
	
	s[j] = '\0';
		
	return strlen(s);
}



int myServer_create_spacename(char *path){
	char dir[MAXPATHLEN];
	int i;
#ifdef DBG_OPS	
	printf("[OPS]%s)myServer_create_spacename: %s\n", MYSERVER_ALIAS_NAME_STRING, path);
#endif
	
	for(i=0; 0 != aux_get_dirs(path, i, dir);i++){
		mkdir(dir, 0777);
	}
	return 0;
}

/* OPERATIONAL FUNCTIONS */

/********************************** 
Read the operation to realize 
***********************************/
int myServer_read_operation(int sd, struct st_myServer_msg *head){
	int ret;

#ifdef DBG_OPS	
	printf("[OPS]%s)antes de read_operation: sizeof(struct st_myServer_msg) = %d.\n ", MYSERVER_ALIAS_NAME_STRING, sizeof(struct st_myServer_msg));
#endif
	ret = myServer_comm_readdata(sd, (char *)&head->type, sizeof(head->type), head->id);
	if(ret == -1){
		return -1;
	}
	
#ifdef DBG_OPS	
	printf("[OPS]%s)read_operation: %d ID=%s\n", MYSERVER_ALIAS_NAME_STRING,head->type,head->id);
#endif
	switch(head->type){
	case MYSERVER_OPEN_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)OPEN operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_open, sizeof(struct st_myServer_open), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_CREAT_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)CREAT operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_creat, sizeof(struct st_myServer_creat), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_READ_FILE:
#ifdef DBG_OPS	
		printf("[OPS]%s)READ operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_read, sizeof(struct st_myServer_read), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_WRITE_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)WRITE operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_write, sizeof(struct st_myServer_write), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_CLOSE_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)CLOSE operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_close, sizeof(struct st_myServer_close), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_RM_FILE:    
#ifdef DBG_OPS	
		printf("[OPS]%s)RM operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_rm, sizeof(struct st_myServer_rm), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_GETATTR_FILE:    
#ifdef DBG_OPS	
		printf("[OPS]%s)GETATTR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_getattr, sizeof(struct st_myServer_getattr), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_SETATTR_FILE:    
#ifdef DBG_OPS	
		printf("[OPS]%s)SETATTR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_setattr, sizeof(struct st_myServer_setattr), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_MKDIR_DIR: 
#ifdef DBG_OPS	
		printf("[OPS]%s)MKDIR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_mkdir, sizeof(struct st_myServer_mkdir), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_RMDIR_DIR: 
#ifdef DBG_OPS	
		printf("[OPS]%s)RMDIR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_rmdir, sizeof(struct st_myServer_rmdir), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_FLUSH_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)FLUSH operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_flush, sizeof(struct st_myServer_flush), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
	case MYSERVER_PRELOAD_FILE: 
#ifdef DBG_OPS	
		printf("[OPS]%s)PRELOAD operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_preload, sizeof(struct st_myServer_preload), head->id);
		if(ret == -1){
			return -1;
		}
	
		break;
        case MYSERVER_GETID:                                                                                         
#ifdef DBG_OPS	
                printf("[OPS]%s)GETID operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);                            
#endif
/*
		ret = myServer_comm_readdata(sd, (char *)&head->id, sizeof(MYSERVER_ID), head->id);
		if(ret == -1){
			return -1;
		}
*/	
                break; 
	case MYSERVER_FINALIZE:   
#ifdef DBG_OPS	
		printf("[OPS]%s)FINALIZE operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
/*
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_end, sizeof(struct st_myServer_end), head->id);
		if(ret == -1){
			return -1;
		}
*/	
		break;
	case MYSERVER_END:
#ifdef DBG_OPS	
		printf("[OPS]%s)END operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
/*
		ret = myServer_comm_readdata(sd, (char *)&head->u_st_myServer_msg.op_end, sizeof(struct st_myServer_end), head->id);
		if(ret == -1){
			return -1;
		}
*/	
		break;
	}
	return head->type;
}


void myServer_op_open(int sd, struct st_myServer_msg *head){
	int fd;
	char s[255];
	
	//sprintf(s,"%s", head->u_st_myServer_msg.op_open.path);
	strcpy(s,head->u_st_myServer_msg.op_open.path);

#ifdef DBG_OPS	
	printf("[OPS]%s> begin open(%s) ID=%s -> %d\n",MYSERVER_ALIAS_NAME_STRING,s,head->id,fd);
#endif		
	
	fd = open(s, O_RDWR);
	//if(fd == -1){
	//	myServer_create_spacename(s);
	//}	
#ifdef DBG_OPS
	printf("[OPS]%s> end open(%s) ID=%s ->%d\n",MYSERVER_ALIAS_NAME_STRING,s, head->id, fd);	
#endif	
	myServer_comm_writedata(sd, (char *)&fd, sizeof(int), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)OPEN operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}





void myServer_op_creat(int sd, struct st_myServer_msg *head){
	int fd;
	char s[255];

	
	//sprintf(s,"%s", head->u_st_myServer_msg.op_creat.path);
	strcpy(s,head->u_st_myServer_msg.op_creat.path);
	
	//printf("[OPS]%s)creat(%s) ID=%s ->\n",MYSERVER_ALIAS_NAME_STRING,s,head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)begin creat(%s) ID=%s ->\n",MYSERVER_ALIAS_NAME_STRING,s,head->id);
#endif		
	//fd = open(s, O_CREAT | O_TRUNC | O_RDWR, 0666);
	fd = open(s, O_CREAT | O_RDWR, 0777);
	if(fd == -1){
		myServer_create_spacename(s);
	        //fd = open(s, O_CREAT | O_TRUNC | O_RDWR, 0666);
	        fd = open(s, O_CREAT | O_RDWR, 0666);
	}	
	
#ifdef DBG_OPS	
	printf("[OPS]%s)end creat(%s) ID=%s -> %d\n",MYSERVER_ALIAS_NAME_STRING,s,head->id,fd);
#endif		
	
	myServer_comm_writedata(sd,(char *)&fd,sizeof(int), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)end CREAT operation from ID=%s ->%d\n",MYSERVER_ALIAS_NAME_STRING,head->id,fd);
#endif
}


void myServer_op_flush(int sd, struct st_myServer_msg *head){
	int ret = 0;
	//char s_exe[1024];

	
	//sprintf(s,"%s", head->u_st_myServer_msg.op_creat.path);
	//strcpy(s,head->u_st_myServer_msg.op_flush.path);
	
#ifdef DBG_OPS	
	printf("[OPS]%s)begin flush(%s) ID=%s ->\n",MYSERVER_ALIAS_NAME_STRING, head->u_st_myServer_msg.op_flush.virtual_path, head->id);
#endif	
/*	
	sprintf(s_exe,"%s %s %s\n", MYSERVER_FLUSH_EXE, 
				head->u_st_myServer_msg.op_flush.virtual_path,
				head->u_st_myServer_msg.op_flush.storage_path);
#ifdef DBG_OPS	
	printf("[OPS]begin system->%s\n",s_exe);
#endif	
	ret = system(s_exe);
#ifdef DBG_OPS	
	printf("[OPS]end system->%s\n",s_exe);
#endif	

#ifdef DBG_OPS	
	printf("[OPS]%s)open flush(%s) ID=%s -> %d\n",MYSERVER_ALIAS_NAME_STRING, 
							head->u_st_myServer_msg.op_flush.virtual_path, 
							sd, head->id,ret);
#endif		
*/	
	myServer_comm_writedata(sd, (char *)&ret, sizeof(int), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)end FLUSH operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}


void myServer_op_preload(int sd, struct st_myServer_msg *head){
	int ret;
	//char s_exe[1024];

	
	//sprintf(s,"%s", head->u_st_myServer_msg.op_creat.path);
	//strcpy(s,head->u_st_myServer_msg.op_flush.path);
	
#ifdef DBG_OPS	
	printf("[OPS]%s)begin preload(%s,%s) ID=%s\n",MYSERVER_ALIAS_NAME_STRING, 
							head->u_st_myServer_msg.op_preload.virtual_path,
							head->u_st_myServer_msg.op_preload.storage_path,
							 head->id);
#endif		
	ret = 0;

	ret = myServer_d2xpn(head->u_st_myServer_msg.op_preload.virtual_path,
                             head->u_st_myServer_msg.op_preload.storage_path,
			     head->u_st_myServer_msg.op_preload.opt);


#ifdef DBG_OPS	
	printf("[OPS]%s)end preload(%s,%s) ID=%s -> %d\n",MYSERVER_ALIAS_NAME_STRING, 
							head->u_st_myServer_msg.op_preload.virtual_path,
							head->u_st_myServer_msg.op_preload.storage_path,
							head->id, ret);
#endif		

	myServer_comm_writedata(sd, (char *)&ret, sizeof(int),  head->id);

#ifdef DBG_OPS	
	printf("[OPS]%s)end PRELOAD operation from ID=%s\n", MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}




void myServer_op_close(int sd, struct st_myServer_msg *head){
#ifdef DBG_OPS	
	printf("[OPS]%s)begin close: fd %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING,
							head->u_st_myServer_msg.op_close.fd,
							head->id);
#endif		
	
	close(head->u_st_myServer_msg.op_close.fd);
#ifdef DBG_OPS	
	printf("[OPS]%s)begin close: fd %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING,
							head->u_st_myServer_msg.op_close.fd,
							head->id);
#endif		

#ifdef DBG_OPS	
	printf("[OPS]%s)end CLOSE operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}


void myServer_op_rm(int sd, struct st_myServer_msg *head){
	char s[255];

	//sprintf(s,"%s", head->u_st_myServer_msg.op_rm.path);
	strcpy(s, head->u_st_myServer_msg.op_rm.path);

#ifdef DBG_OPS	
	printf("[OPS]%s)begin unlink: path %s ID=%s\n",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_rm.path,
						head->id);
#endif		
	unlink(s);
#ifdef DBG_OPS	
	printf("[OPS]%s)end unlink: path %s ID=%s\n",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_rm.path,
						head->id);
#endif		
#ifdef DBG_OPS	
	printf("[OPS]%s)end RM operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}

void myServer_op_read(int sd, struct st_myServer_msg *head){
	int size_req, size = 0, cont = 0;
	//char *buffer;
	struct st_myServer_read_req req;
	int SIZE;
#ifndef _MALLOC_
	char buffer[MAX_BUFFER_SIZE];
	SIZE = MAX_BUFFER_SIZE;
#ifdef DBG_OPS	
	printf("[OPS]%s)op_read: static buffer (%d) ID=%s\n",MYSERVER_ALIAS_NAME_STRING,MAX_BUFFER_SIZE,head->id);
#endif	
#else
	char *buffer;
	SIZE = 0;
#ifdef DBG_OPS	
	printf("[OPS]%s)op_read: variable buffer (%d) ID=%s\n",MYSERVER_ALIAS_NAME_STRING,MAX_BUFFER_SIZE,head->id);
#endif	
#endif
	

	//
	
#ifdef DBG_OPS	
	printf("[OPS]%s)begin read: fd %d offset %d size %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_read.fd,
						(int)head->u_st_myServer_msg.op_read.offset,
						head->u_st_myServer_msg.op_read.size,
						head->id);	
#endif

/*
#ifdef _LARGEFILE64_ 
	printf("[OPS]%s)op_read: offset %lld\n",MYSERVER_ALIAS_NAME_STRING,head->u_st_myServer_msg.op_read.offset);
#else
	printf("[OPS]%s)op_read: offset %d\n",MYSERVER_ALIAS_NAME_STRING,(int)head->u_st_myServer_msg.op_read.offset);
#endif
	printf("[OPS]%s)op_read: size %d\n",MYSERVER_ALIAS_NAME_STRING,head->u_st_myServer_msg.op_read.size);
#endif		
*/
#ifdef _MALLOC_
	SIZE = head->u_st_myServer_msg.op_read.size;
	buffer = (char *)malloc(SIZE);
	//buffer = (char *)malloc(MAX_BUFFER_SIZE);
#ifdef DBG_OPS	
	//printf("[OPS]%s)op_read: malloc(%d) ID=%s\n",MYSERVER_ALIAS_NAME_STRING,MAX_BUFFER_SIZE,head->id);
	printf("[OPS]%s)op_read: malloc(%d) ID=%s\n",MYSERVER_ALIAS_NAME_STRING,SIZE,head->id);
#endif	
#endif
	//t1 = MPI_Wtime();
	do{	
#ifdef _LARGEFILE64_	
		lseek64(head->u_st_myServer_msg.op_read.fd, 
				head->u_st_myServer_msg.op_read.offset+cont,
				0);
#else
#ifdef DBG_OPS	
	printf("[OPS]%s)lseek: fd %d offset %d size %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_read.fd,
						(int)head->u_st_myServer_msg.op_read.offset+cont,
						head->u_st_myServer_msg.op_read.size,
						head->id);	
#endif

		
		lseek(head->u_st_myServer_msg.op_read.fd, 
				head->u_st_myServer_msg.op_read.offset+cont,
				0);
#endif

		size_req = (head->u_st_myServer_msg.op_read.size - cont);
		if(size_req>SIZE){
			size_req = SIZE;
		}
	
		
/*		
		req.size = read(head->u_st_myServer_msg.op_read.fd,
		 			buffer,
       		   			size_req);
*/

		
		usleep(rand()%1000);	
		req.size = size_req;

		if(req.size < 0){
			perror("read:");
		}	
		cont += req.size;
		if((cont == head->u_st_myServer_msg.op_read.size) ||
			(req.size < size_req)){
			req.last = 1;
		}else{
			req.last = 0;
		}
		myServer_comm_writedata(sd, (char *)&req, sizeof(struct st_myServer_read_req), head->id);
#ifdef DBG_OPS	
		printf("[OPS]%s)op_read: send size %d\n",MYSERVER_ALIAS_NAME_STRING, req.size);
#endif		

		if(req.size > 0){
			myServer_comm_writedata(sd, (char *)buffer, req.size, head->id);
#ifdef DBG_OPS	
			printf("[OPS]%s)op_read: send data\n",MYSERVER_ALIAS_NAME_STRING);
#endif		
		}else{
			break;
		}
	}while((size >0)&&(!req.last));
	//t2 = MPI_Wtime();
#ifdef DBG_OPS	


        printf("[OPS]%s)end read: fd %d offset %d size %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING,                              
                                                head->u_st_myServer_msg.op_read.fd,                                         
                                                (int)head->u_st_myServer_msg.op_read.offset,                                
                                                size,
                                                head->id); 
#endif
	
#ifdef DBG_OPS	
	//printf("[OPS]%s)op_read: %f sec.\n",MYSERVER_ALIAS_NAME_STRING,t2 - t1);
	printf("[OPS]%s)op_read: new_size %d\n",MYSERVER_ALIAS_NAME_STRING,size);
#endif	
#ifdef _MALLOC_	
#ifdef DBG_OPS	
	printf("[OPS]%s)op_read: free ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif	
	free(buffer);
#endif
#ifdef DBG_OPS	
        printf("[OPS]%s)end READ: fd %d offset %d size %d ID=%s\n",MYSERVER_ALIAS_NAME_STRING,
                                                head->u_st_myServer_msg.op_read.fd,
                                                (int)head->u_st_myServer_msg.op_read.offset,
                                                size,
                                                head->id);

#endif
}

void myServer_op_write(int sd, struct st_myServer_msg *head){
	//char *buffer;
	int cont =0 ,size =0;
	struct st_myServer_write_req req;
#ifndef _MALLOC_	
	char buffer[MAX_BUFFER_SIZE];
	int SIZE = MAX_BUFFER_SIZE;
#else
	char *buffer;
	int SIZE = 0;
#endif

#ifdef DBG_OPS	
	printf("[OPS]%s)begin write: fd %d ID=%sn",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_write.fd,
						head->id);	
#endif
/*
#ifdef DBG_OPS	
	printf("[OPS]%s)op_write: fd %d\n",MYSERVER_ALIAS_NAME_STRING,head->u_st_myServer_msg.op_write.fd);
#ifdef _LARGEFILE64_ 
	printf("[OPS]%s)op_write: offset %lld\n",MYSERVER_ALIAS_NAME_STRING,head->u_st_myServer_msg.op_write.offset);
#else
	printf("[OPS]%s)op_write: offset %d\n",MYSERVER_ALIAS_NAME_STRING,(int)head->u_st_myServer_msg.op_write.offset);
#endif
	printf("[OPS]%s)op_write: size %d\n",MYSERVER_ALIAS_NAME_STRING,head->u_st_myServer_msg.op_write.size);
#endif
*/	
	//t1 = MPI_Wtime();

#ifdef _MALLOC_
	SIZE = head->u_st_myServer_msg.op_write.size;
#endif	
	do{
	size = (head->u_st_myServer_msg.op_write.size - cont);
	if(size>SIZE){
		size= SIZE;
	}
	
	if(size == 0)
		break;
	
#ifdef _MALLOC_
	buffer = (char *)malloc(SIZE);
	//buffer = (char *)malloc(head->u_st_myServer_msg.op_read.size);
	//buffer = (char *)malloc(MAX_BUFFER_SIZE);
#endif
	myServer_comm_readdata(sd,(char *)buffer, size, head->id);

#ifdef _LARGEFILE64_	
	lseek64(head->u_st_myServer_msg.op_write.fd, 
			head->u_st_myServer_msg.op_write.offset+cont,
			0);
#else
	lseek(head->u_st_myServer_msg.op_write.fd, 
			head->u_st_myServer_msg.op_write.offset+cont,
			0);
#endif

	req.size = write(head->u_st_myServer_msg.op_write.fd,
			  buffer,
		          size);
	
	cont += size;
	}while(req.size>0);
	
	if(req.size>=0){
		req.size = head->u_st_myServer_msg.op_write.size;
	}
	myServer_comm_writedata(sd,(char *)&req,sizeof(struct st_myServer_write_req), head->id);

	#ifdef _MALLOC_	
		free(buffer);
	#endif
	#ifdef DBG_OPS	
		printf("[OPS]%s)op_write: %d\n",MYSERVER_ALIAS_NAME_STRING, req.size);
	#endif		
#ifdef DBG_OPS	
	printf("[OPS]%s)end write: fd %d ID=%sn",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_write.fd,
						head->id);	
#endif
#ifdef DBG_OPS	
	printf("[OPS]%s)end WRITE operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
	
}

void myServer_op_mkdir(int sd, struct st_myServer_msg *head){
	char s[255];
	int ret;

	//sprintf(s,"%s/", head->u_st_myServer_msg.op_mkdir.path);
	strcpy(s, head->u_st_myServer_msg.op_mkdir.path);
	
	ret = mkdir(s, 0777);
	myServer_comm_writedata(sd,(char *)&ret,sizeof(int), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)end MKDIR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}

void myServer_op_rmdir(int sd, struct st_myServer_msg *head){
	char s[255];
	int ret;
	//sprintf(s,"%s/", head->u_st_myServer_msg.op_rmdir.path);
	strcpy(s, head->u_st_myServer_msg.op_rmdir.path);
	ret = rmdir(s);
	myServer_comm_writedata(sd,(char *)&ret,sizeof(int), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)end RMDIR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}

void myServer_op_setattr(int sd, struct st_myServer_msg *head){



}

void myServer_op_getattr(int sd, struct st_myServer_msg *head){
	char s[255];
	struct st_myServer_attr_req req;

#ifdef DBG_OPS	
	printf("[OPS]%s)begin getattr(%s) ID=%sn",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_getattr.path,	
						head->id);	
#endif
	//sprintf(s,"%s/", head->u_st_myServer_msg.op_rmdir.path);
	strcpy(s, head->u_st_myServer_msg.op_getattr.path);
	req.status = stat(s, &req.attr);
	myServer_comm_writedata(sd,(char *)&req,sizeof(struct st_myServer_attr_req), head->id);
#ifdef DBG_OPS	
	printf("[OPS]%s)end getattr(%s) ID=%sn",MYSERVER_ALIAS_NAME_STRING, 
						head->u_st_myServer_msg.op_getattr.path,	
						head->id);	
#endif
#ifdef DBG_OPS	
	printf("[OPS]%s)end GETATTR operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}



void myServer_op_getid(int sd, struct st_myServer_msg *head){
#ifdef DBG_OPS    
        printf("[OPS]%s)begin GETID ID=%s\n",MYSERVER_ALIAS_NAME_STRING,
                                                head->id);
#endif
        //sprintf(s,"%s/", head->u_st_myServer_msg.op_rmdir.path);
        myServer_comm_writedata(sd,(char *)head->id, MYSERVER_ID, head->id);
#ifdef DBG_OPS    
        printf("[OPS]%s)end GETID operation from ID=%s\n",MYSERVER_ALIAS_NAME_STRING,head->id);
#endif
}
