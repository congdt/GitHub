#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 10000

int counter_word = 0; 
int counter_file = 0;
int findString( char*string1, char*string2);


// trả về độ dài một xâu được trỏ bởi "s"
int length(char *s)
{
	int i;
	int count = 0;
	for(i = 0; i < MAX_LENGTH; i++ ){
		if(s[i] != 0) count++;
		else break;
	}
	return count;
}



// tìm xâu string1 trong string2.- thực ra string2 mình dùng là 1 câu. 
int findString(char *string1,char *string2)
{
	int i, j;
	char *s1, *s2;
	int l1 = length(string1), l2 = length(string2);
	
	if(l1 > l2) return -1;
	s1 = (char *)malloc(l1 + 1);
	s2 = (char *) malloc(l2 + 1); 
	strcpy(s1, string1);
	strcpy(s2, string2);
	char* temp;
	temp = strstr(s2, s1);	
	if(temp == NULL) 	/* nếu ko có xâu s1 trong s2 thì trả về -1 */
	{
		free(s1);
		free(s2);
		return -1;
	 	
	 }
	 /* biết có xâu s1 trong s2 rồi -> vòng for: đếm số lần xâu s1 xuất hiện trong s2, cộng vào conter đếm chung*/
	for(i = 0; i < l2 - l1 + 1; i++){
		for(j = 0; j < l1; j++){
			if(s1[j] != s2[j+i]) break;
		}
		if(j == l1) counter_word++;		/* cộng số từ tìm đc trong câu vào biến Toàn cục counter_word.  */
	}
	free(s1);
	free(s2);
	return 1;
}


/* tìm kiếm xâu findWord trong file tên là fileName. nếu có xâu trong file trả về 1, nếu không trả về 0.
*/
int findFile(char *findWord, const char* fileName)
{
	FILE *f;
	char* sen;
	int size, returnNum = 0;
	char temp;
	f = fopen(fileName, "r");
	if(f == NULL){
		printf("file cant be read");
		return returnNum;
	}
	
	
	while(1){
		size = 1;
		sen = (char*) malloc (sizeof(char));
		while(1){
			if(fscanf(f, "%c", &temp) == EOF) break;
			
			if(temp == '.' || temp == '?' || temp == '!' || temp == '\n') break;
			size++;
		
			sen = (char*)realloc (sen, size * sizeof(char));
			sen[size - 2] = temp; 
		}
	
		sen[size -1] = '\0';
		// phần trên là đọc 1 câu từ file lưu vào "sen" 
		// sau đó dưới đây tìm xâu mẫu trong câu đó. 
		if(findString(findWord, sen) == 1){
		
			
			printf("%s \n", sen); 
			returnNum = 1;
		}
		free(sen);
		if(feof(f)) break;
	}

	fclose(f);
	return returnNum;
}

// tìm từ *findWord trên tập file có tên lưu trong **fileName 
int find( char *findWord,  char** fileName, int numFile)
{
	int i;
	int count = 0;
	for(i = 0; i < numFile; i++)
	{
		if(findFile(findWord, fileName[i]) == 1)
			count++;
	
	}
	return count;
}


/*
void readFile(const char* fileName)
{
	FILE *f, *f1;
	char temp, temp1;
	f = fopen(fileName, "r");
	if(f == NULL){
		printf("error\n");
		return;
	}
	while (1){
		if(fscanf(f,"%c", &temp) == EOF) return;
		printf("%c(%d)", temp, temp);

	}
	fclose(f);
}

*/

int xacdinhChuoi(char *s)
{
	int i;
	for(i = 0; i < length(s); i++)
	{
		if(s[i] == '*') return 1;
	}
	return 0;
}

// truong hop tim kiem voi du lieu nhap vao co "?"
int find_1(char * s)
{
	
}

char* test()
{
	char *s = (char*) malloc (2 * sizeof(char));
	s[0] = 'c';
	s[1] = '\0';
//	free(s);
	return s;
}

int main()
{
	char**listFile;
	char temp[100];
	char *word;
	listFile = (char**) malloc (2*sizeof(char*));
	listFile[0] = "test1.txt";
	listFile[1] = "test2.txt";
	printf("nhap tu khoa tim kiem: ");
	scanf("%s", temp);
	word = (char*)malloc(length(temp) + 1);
	strcpy(word, temp);
	printf("%s *\n", word);
	
	// test tim kiem trong dsach listFile 
	find(word, listFile, 2);
	
	free(word);
	free(listFile);
	char *s = test();
	puts(s);
	free(s);

	return 0;
}
