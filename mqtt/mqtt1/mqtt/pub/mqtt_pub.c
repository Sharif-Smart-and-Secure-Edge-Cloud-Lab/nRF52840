#include<stdio.h>
#include<mosquitto.h>
#include<string.h>
#include<stdlib.h>

void substr(char s[],char sub[],int start,int end);
int main(){
	int rc;
	FILE *fp;
	char clientID[100]="0";
	char topic[100];
	printf("enter the base of topic\n");
	scanf("%[^\n]%*c",topic);
	strcat(topic,"/");
	char payload[100];
	struct mosquitto *mqtt_pub;
	mosquitto_lib_init();
	mqtt_pub=mosquitto_new(clientID,true,NULL);
	rc= mosquitto_connect(mqtt_pub,"192.168.1.220",1883,60);
	if(rc !=0){
		printf("client could not connect. error code:%d\n",rc);
		mosquitto_destroy(mqtt_pub);
		return -1;
	}

	printf("connected\n");
	while(true){
		fp=fopen("message.txt","a+");
		if (NULL == fp) {
			printf("file can't be opened \n");
			return -1;
		}
		while (true) {
			char message[100]="";
			if (feof(fp)){
				break;
			}
			fscanf(fp,"%[^\n]%*c",message);
			if (strlen(message)==0){
				break;
			}
			fscanf(fp,"%[^\n]%*c",payload);
			char sub_topic[100]="";
			char new_message[100]="";
			char new_topic[100]="";
			substr(message,new_message,0,2);
			strcat(new_message,payload);
			substr(message,sub_topic,2,strlen(message));
			strcat(new_topic,topic);
			strcat(new_topic,sub_topic);
			printf("message= %s\n", new_message);
			printf("topic= %s\n",new_topic);
			printf("-----------\n");
			mosquitto_publish(mqtt_pub,NULL,new_topic,strlen(new_message),new_message,0,false);
			system("sed -i '1,2d' message.txt");
			//char ch = getc(fp);
			if (feof(fp)){
                                break;
                        }

		}
		fclose(fp);
	}
	
	mosquitto_disconnect(mqtt_pub);
	mosquitto_destroy(mqtt_pub);
	mosquitto_lib_cleanup();
	return 0;
}
void  substr(char s[],char sub[], int start,int end){
	int c = start;
	while(c<end){
		sub[c-start]=s[c];
		c++;
	}

}
