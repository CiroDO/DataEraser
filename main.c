#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <conio.h>
#include <math.h>

void setFileName(char *buffer, char **filename, char *extension);
int getFileSize(char *filename, struct stat file_stat);
void generateOverwriteData(char **_str, int _fileSize);
void arrayDump(char *_str);

int main(){
	printf("start main function...\n");
	struct stat file_stat;
	char buffer[50];
	//char extension[6] = {'.','j','p','e','g','\0'};
	char extension[5] = {'.','j','p','g','\0'};
	char *filename;
	char A = 'A';
	char buff[255];
	
	printf("\nWrite your file name: ");
	gets(buffer);
	
	setFileName(buffer,&filename,extension);
	printf("\nThis is the name of your file: %s",filename);
	
	
	printf("\nI'm going to retrieve the size of your %s file... ",extension);
	printf("\nYour %s file has a total of %d bytes\n",extension,getFileSize(filename,file_stat));
	
	FILE *_file;
	_file = fopen(filename,"r+");
	
	if(!_file){
		printf("Unable to open your %s file!\n",extension);
		exit(0);
	}
	else{
		printf("%s file oppened, press any key to continue...\n\n",extension);
		rewind(_file);
		getch();
	}
	
	int _metadataStart = 623; //for jpeg or jpg files
	
	//Main objective: metadata manipulation, in this case, all the data since 0x26F in virtual memory
	printf("This is the reference value of 'A' in ASCII: %d\n",A);
	//this function gets the pointer to the exact position of the metadata that describe directly the jpeg file 
	fseek(_file,_metadataStart,SEEK_SET);
	char test = fgetc(_file);
	printf("It was the first character that defines directly the %s file: %c\nAnd its value in ASCII: %d\n",extension,test,test);
	
	//getting back to the position again, so I can try to modify the first char
	fseek(_file,_metadataStart,SEEK_SET);
	
	char *_data;
	int _dataArraySize = getFileSize(filename,file_stat) - _metadataStart + 1;
	generateOverwriteData(&_data,_dataArraySize);
	arrayDump(_data);
	
	int _i;
	for( _i = 0 ; _i < strlen(_data) ; _i++ )
		fputc(_data[_i],_file);
	
	//DON'T FORGET TO CLOSE YOUR FILES, MOTHERF*CKA
	fclose(_file);
	
	printf("\nend main function\n");
	return 0;
}

void setFileName(char *buffer, char **filename, char *extension){
	*filename = (char*)malloc(strlen(buffer)*sizeof(char)+strlen(extension)*sizeof(char)+sizeof(char));
	strcpy(*filename,buffer);
	strcat(*filename,extension);
	return;
}

int getFileSize(char *name, struct stat file_stat){
	stat(name,&file_stat);
	int size = file_stat.st_size;
	return size;
}

void generateOverwriteData(char **_str, int _fileSize){
	int _i;
	(*_str) = (char*)malloc(_fileSize*sizeof(char));
	for( _i = 0 ; _i < _fileSize ; _i++ )
		(*_str)[_i] = 48+rand()%78;
	(*_str)[_fileSize-3] = 255;
	(*_str)[_fileSize-2] = 217;
	(*_str)[_fileSize-1] = '\0';
	printf("generated a string with %d characters\n",strlen(*_str));
	return;
}

void arrayDump(char *_array){
	if(_array == NULL){
		printf("arrayDump failed\n");
		exit(0);
	}
	int _i;
	for( _i = 0 ; _i < strlen(_array) ; _i++ )
		printf("%c ",_array[_i]);
	return;
}