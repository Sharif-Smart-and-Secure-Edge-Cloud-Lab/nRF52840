#include<stdio.h>
#include<stdlib.h>
#include<mosquitto.h>
#include<string.h>
#include<math.h>
//#include"sqlite3.h"
char ID[100]="zgw";
char topic[100]="zgw/#";
int qos=0;
//sqlite3* DB;
//int exit = 0;
//char* messaggeError;
//char sql_comand[1000];
char mac[200][9];
void  substr(char s[],char sub[], int start,int end){
        int c = start;
        while(c<end){
                sub[c-start]=s[c];
                c++;
        }
	sub[end]='\0';

}

void on_connect(struct mosquitto *msq, void *obj,int rc){
        printf("ID: %s\n ",  (char *)obj);
        if (rc){
                printf("error with result code : %d\n",rc);
                exit(-1);
        }
        mosquitto_subscribe(msq,NULL,topic,qos);
}
void on_message(struct mosquitto *msq, void *obj,const struct mosquitto_message *message){
        printf("new message arrived \t topic: %s   message: %s \n",message->topic,(char *)message->payload);
	char *mesg=(char *)message->payload;
	char type[5]="";
	substr(mesg,type,0,2);
	char *top=(char *)message->topic;
	char pic[1000]="";
	substr(top,pic,4,strlen(top));
	char data[100]="";
	substr(mesg,data,2,strlen(mesg));
	int macCount=0;
	char run[100]="sudo ./table.sh ";
	strcat(run,pic);
	strcat(run," ");
	strcat(run,type);
	strcat(run, " ");
	strcat(run,data);
	strcat(run," ");
	int length;
	int compare;
	for (int i =0;i<200; i++){
		length=strcmp(mac[i],"");
		compare=strcmp(pic,mac[i]);
		if(length==0){
			strcat(run,"0");
			system(run);
			strcpy(mac[i],pic);
			macCount=0;
			break;
		}
		else if(compare==0){
			strcat(run,"1");
			system(run);
			macCount=0;
			break;
		}
		macCount++;
	}

}
int main (){
        int rc;
	system("sudo chmod 777 create_database.sh");
	system("sudo chmod 777 table.sh");
	system("sudo chmod 777 del_db.sh");
	system("sudo ./create_database.sh");
	//for(int i=0;i<200;i++){
	//	strcpy(mac[i],"");
	//}
	//exit = sqlite3_open("example.db", &DB);
        mosquitto_lib_init();
	char exitcode[100]="exit";
	char exit[100];
        struct mosquitto *msq;
        msq=mosquitto_new(ID,true,ID);
        mosquitto_connect_callback_set(msq,on_connect);
        mosquitto_message_callback_set(msq,on_message);
        rc =mosquitto_connect(msq,"localhost",1883,10);
        if(rc){
                printf("unable to connect. return code: %d\n",rc);
                return -1;
        }
        mosquitto_loop_start(msq);
        printf("press enter\"exit\" to quit .....\n");
	while(abs(strcmp(exitcode,exit))!=0){
		scanf("%s",exit);
		system("sudo ./del_db.sh");
		mosquitto_loop_stop(msq,true);
	}
        mosquitto_disconnect(msq);
        mosquitto_destroy(msq);
        mosquitto_lib_cleanup();
        return 0;
}
//void create_table(char name[]){
//	char ct[1000]="CREATE TABLE ";
//	strcat(ct,name);
//	strcat(ct,"(");
//	char columns[1000]="TYPE INT NOT NULL,VALUE REAL );";
//	strcat(ct,columns);
//	sql_comand=ct;
//}
