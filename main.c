#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#define MAC_START 5L
#define MAC_SIZE 6L
#define MAC_END (MAC_START+MAC_SIZE)
#define GET_TWO_CHARS(FROM) sprintf(tmp, "%c%c",FROM[1],FROM[2]);
typedef enum{false,true}bool;
static const char * PATHES_NVDATA[]={
	"/vendor/nvdata/APCFG/APRDEB/WIFI",
	"/mnt/nvdata/APCFG/APRDEB/WIFI",
	"/mnt/nvram/APCFG/APRDEB/WIFI",
	"/data/nvram/APCFG/APRDEB/WIFI",
	"/data/nvdata/APCFG/APRDEB/WIFI",
	"/nvdata/APCFG/APRDEB/WIFI",
	"./WIFI"

};
int main(int argc, char ** argv){
	//unsigned short new_mac[128];
	unsigned char new_mac[MAC_SIZE];
	unsigned char count_mac=0;
	if(argc < 2)return fprintf(stderr,"%s B6:B8:B9:B0:B1:B2\n", argv[0]); 
	char * b;
	bool isFirst=true;
	while( (b = strstr(argv[1],":")) != NULL){
		char tmp[3];
		bzero(tmp,sizeof(tmp));
		if(isFirst){
			sprintf(tmp, "%c%c", argv[1][0], argv[1][1]);
			new_mac[count_mac++]=strtol(tmp, NULL, 16); 
			isFirst=false;
		}
		if(count_mac > sizeof(new_mac)) return fprintf(stderr, "Mac size...\n");
		printf("%c%c,", b[1],b[2]);
		sprintf(tmp, "%c%c", b[1],b[2]);
		new_mac[count_mac++]=strtol(tmp, NULL, 16); 
		printf("Wroted: %s\n", tmp);
		argv[1] = b+1;
	}
	puts("");
	FILE * mac_file;
	for(unsigned short i = 0; i < sizeof(PATHES_NVDATA);i++){
		mac_file = fopen(PATHES_NVDATA[i], "r+");
		if( mac_file != NULL ){
			fseek(mac_file, MAC_START-1, SEEK_SET);
			for(unsigned char i = 0;i<sizeof(new_mac);i++){
				fprintf(mac_file, "%c", new_mac[i]);
				printf("%d:%02x ", i,new_mac[i]);
			}
			puts("");
			fclose(mac_file);
			puts("Check your MAC file now");
			return 0;
		}//if
	}
}
