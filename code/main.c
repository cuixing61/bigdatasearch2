/****main.c****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"hash.h"


int main()

{
	

    char* BITMAP=(char*)malloc(MAXBITMAP*sizeof(char));		//�����������Ƚϴ����Բ��ö�̬���飬�Լ������ڴ棬�ڽ���ʱ����free�ͷ� 
    memset(BITMAP,0,MAXBITMAP);								//�Ѷ�̬���������Ԫ������ 												 
	FILE *fp, *fp1,*fpw;									//�����ļ�ָ�� 
	
	//��ȡ�ļ����ݻ���
	char buf[BUF_SIZE];								 
	char buf1[BUF_SIZE];
	
	//�ļ���ȡ����ֵ 
	char* ret;												
	char* ret1;
	
	//�ļ������ʼ��ΪNULL
	fp=NULL;						
	fp1=NULL;
	fpw=NULL;		
	

	
	
	/*---------------���ļ�-------------------*/ 
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

	

	/*----��127���ļ��ŵ�bitmap�У�����bitmap----- */
	do
	{
		ret=NULL;
		memset(buf,0,BUF_SIZE);			//void *memset(void *s, int ch, size_t n);��buf����bufsize��ֵ��0���沢����bf 
		ret=fgets(buf, BUF_SIZE-1, fp);//char *fgets(char *buf, int bufsize, FILE *stream);
		if(ret==NULL)
		{
			//�ж��Ƿ��ȡ���ļ���β 
			if(feof(fp)) printf("finish read the file! \n");//int feof(FILE *stream);
			else printf("something error!\n");
			break;
		}
		else
		{
		//	printf("read [%s] from files\n", buf);
		/****���ò��뺯��������Ҫ�����Ԫ��buf��bitmap��hash������ָ�룬���ý�����bitmap����Ӧλ�ûᱻ��ֵΪ1****/ 
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
	memset(buf,0,BUF_SIZE);	//����ʹ����ɺ�Ҫ���� 
	fclose(fp);				//�ر��ļ� 
	

	/*-----��98���ļ��ŵ�buf1�ﲢ����ƥ��-----*/
	do
	{
 	ret1=NULL;
		memset(buf1,0,BUF_SIZE);			//void *memset(void *s, int ch, size_t n);��buf����bufsize��ֵ��0���沢����bf 
		ret1=fgets(buf1, BUF_SIZE-1, fp1);  //char *fgets(char *buf, int bufsize, FILE *stream);
		if(ret1==NULL)
		{
			//�ж��Ƿ��ȡ���ļ���β 
		if(feof(fp1)) printf("finish read the file!\n");//int feof(FILE *stream);
			else printf("something error!\n");
			break;
		}
		else
		{
			/****����search����������Ҫ������Ԫ��buf��bitmap��hash������ָ�룬���ĳһhash�����¼��������򷵻�ֵΪ1�����򷵻���
			     �����е�hash�����·���ֵ����1ʱ����ܴ��ڣ���¡���������������ԣ�********************************************/ 
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
    memset(buf1,0,BUF_SIZE);	//����ʹ����ɺ�Ҫ���� 
 
	fclose(fp1);
	fclose(fpw);
	free(BITMAP);

 	 return 0;

}

