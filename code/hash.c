/****hash.c****/
#include<stdlib.h>
#include"hash.h"
/****需要用到的十一个哈希函数****/ 
unsigned int RSHash( char* str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


unsigned int JSHash( char* str, unsigned int len)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}
/* End Of JS Hash Function */


unsigned int PJWHash( char* str, unsigned int len)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;
   unsigned int i                 = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << OneEighth) + (*str);

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int ELFHash( char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << 4) + (*str);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash( char* str, unsigned int len)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash( char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash( char* str, unsigned int len)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}
/* End Of DJB Hash Function */


unsigned int DEKHash( char* str, unsigned int len)
{
   unsigned int hash = len;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }
   return hash;
}
/* End Of DEK Hash Function */


unsigned int BPHash( char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int i    = 0;
   for(i = 0; i < len; str++, i++)
   {
      hash = hash << 7 ^ (*str);
   }

   return hash;
}
/* End Of BP Hash Function */


unsigned int FNVHash( char* str, unsigned int len)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash      = 0;
   unsigned int i         = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash *= fnv_prime;
      hash ^= (*str);
   }

   return hash;
}
/* End Of FNV Hash Function */


unsigned int APHash( char* str, unsigned int len)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}
/* End Of AP Hash Function */

/****插入函数 
void insertword(char*c,char* BITMAP,unsigned int(*p)( char*,unsigned int ))
{
	unsigned n=(*p)(c,strlen(c))%(8*MAXBITMAP);	//n代表哈希值 
	int m=1;						//用于位运算的的加数 
	int y;							//y代表哈希值的余数 ， c[x]的里面的第y个bit进行位运算 
	int x;							//x代表哈希值的整数部分 ，c[x]上进行操作 
	int j;						//i,j是循环变量 
	
//	printf("the hash of this is %u\n",n);//输出哈希值 
	y=n%8;
	x=n/8;
	for(j=0;j<y;j++)				//算出实际位运算上加上的值 
	{
		m=m*2;
	 } 
	
	BITMAP[x]=BITMAP[x]|m;		//在范围内时候放到第一个数组里，否则放入二号数组 
//	printf("bitmap[%d] is %d\n",x,BITMAP[x]);
		
}

int searchWord(char* c,char* BITMAP,unsigned int(*p)( char*,unsigned int ))
{
	unsigned n=((*p)(c,strlen(c)))%(8*MAXBITMAP);	//n代表哈希值 
	int m=1;						//用于位运算的的加数 
	int y;							//y代表哈希值的余数 ， c[x]的里面的第y个bit进行位运算 
	int x;							//x代表哈希值的整数部分 ，c[x]上进行操作 
	int j;						//i,j是循环变量 

	y=n%8;
	x=n/8;
	for(j=0;j<y;j++)				//算出实际位运算上加上的值 
	{
		m=m*2;
	 } 
	if(BITMAP[x]&m) {
//	printf("found one BITMAP[%d],m=%d\n",x,m);
	return 1;
	}
	
	else {
//	printf("not found one %s\n",c);
	return 0;
	}
}
