/****main.c****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"hash.h"


int main()

{
	

    char* BITMAP=(char*)malloc(MAXBITMAP*sizeof(char));		//由于数据量比较大，所以采用动态数组，自己分配内存，在结束时利用free释放 
    memset(BITMAP,0,MAXBITMAP);								//把动态数组的所有元素置零 												 
	FILE *fp, *fp1,*fpw;									//定义文件指针 
	
	//读取文件内容缓冲
	char buf[BUF_SIZE];								 
	char buf1[BUF_SIZE];
	
	//文件读取返回值 
	char* ret;												
	char* ret1;
	
	//文件句柄初始化为NULL
	fp=NULL;						
	fp1=NULL;
	fpw=NULL;		
	

	
	
	/*---------------打开文件-------------------*/ 
	if((fp=fopen("C:\\cuixing\\127w.txt", "r")) == NULL)
	{
    	printf("The 12 file can not be opened.\n");
    	return 1; 
	}
	if((fp1=fopen("C:\\cuixing\\98w_gb.txt", "r")) == NULL)
	{
    	printf("The 98 file can not be opened.\n");
    	return 2; 
	}
	if((fpw=fopen("C:\\cuixing\\out.txt", "w")) == NULL)
	{
    	printf("The out file can not be opened.\n");
    	return 3; 
	}
	printf("success open\n");

	

	/*----把127的文件放到bitmap中，建立bitmap----- */
	do
	{
		ret=NULL;
		memset(buf,0,BUF_SIZE);			//void *memset(void *s, int ch, size_t n);将buf后面bufsize个值用0代替并返回bf 
		ret=fgets(buf, BUF_SIZE-1, fp);//char *fgets(char *buf, int bufsize, FILE *stream);
		if(ret==NULL)
		{
			//判断是否读取到文件结尾 
			if(feof(fp)) printf("finish read the file! \n");//int feof(FILE *stream);
			else printf("something error!\n");
			break;
		}
		else
		{
		//	printf("read [%s] from files\n", buf);
		/****调用插入函数，传入要插入的元素buf，bitmap，hash函数的指针，调用结束后bitmap的相应位置会被赋值为1****/ 
			insertword(buf, BITMAP,RSHash);					 
			insertword(buf, BITMAP,JSHash);
			insertword(buf, BITMAP,PJWHash);
			insertword(buf, BITMAP,ELFHash);
			insertword(buf, BITMAP,BKDRHash);
			insertword(buf, BITMAP,SDBMHash);
			insertword(buf, BITMAP,DJBHash);
			insertword(buf, BITMAP,DEKHash);
			insertword(buf, BITMAP,APHash);
			insertword(buf, BITMAP,BPHash);
			insertword(buf, BITMAP,FNVHash);
		}
		
	} while (1);
	printf("success build\n");
	memset(buf,0,BUF_SIZE);	//缓冲使用完成后要清理 
	fclose(fp);				//关闭文件 
	

	/*-----把98的文件放到buf1里并进行匹配-----*/
	do
	{
 	ret1=NULL;
		memset(buf1,0,BUF_SIZE);			//void *memset(void *s, int ch, size_t n);将buf后面bufsize个值用0代替并返回bf 
		ret1=fgets(buf1, BUF_SIZE-1, fp1);  //char *fgets(char *buf, int bufsize, FILE *stream);
		if(ret1==NULL)
		{
			//判断是否读取到文件结尾 
		if(feof(fp1)) printf("finish read the file!\n");//int feof(FILE *stream);
			else printf("something error!\n");
			break;
		}
		else
		{
			/****调用search函数，传入要检索的元素buf，bitmap，hash函数的指针，如果某一hash函数下检索存在则返回值为1，否则返回零
			     当所有的hash函数下返回值都是1时则可能存在（布隆过滤器保不存在性）********************************************/ 
			if(searchWord(buf1,BITMAP,RSHash)&&searchWord(buf1,BITMAP, JSHash)&&searchWord(buf1,BITMAP, PJWHash)&&searchWord(buf1,BITMAP, ELFHash)&&searchWord(buf1,BITMAP, BKDRHash)&&searchWord(buf1,BITMAP, SDBMHash)&&searchWord(buf1,BITMAP, DJBHash)&&searchWord(buf1,BITMAP, DEKHash)&&searchWord(buf1,BITMAP, APHash)&&searchWord(buf1,BITMAP, BPHash)&&searchWord(buf1,BITMAP,FNVHash))
			{
				printf("[%s] yes\n", buf1);
				fputs(buf1,fpw);
				fputs("yes\n",fpw);
			}
			else
			{
				printf("[%s] no\n", buf1);
				fputs(buf1,fpw);
				fputs("no\n",fpw);
			}
		}
	} while (1); 
    memset(buf1,0,BUF_SIZE);	//缓冲使用完成后要清理 
 
	fclose(fp1);
	fclose(fpw);
	free(BITMAP);

 	 return 0;

}

