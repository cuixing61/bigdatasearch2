/****hash.h****/
#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


unsigned int RSHash  ( char* str, unsigned int len);
unsigned int JSHash  ( char* str, unsigned int len);
unsigned int PJWHash ( char* str, unsigned int len);
unsigned int ELFHash ( char* str, unsigned int len);
unsigned int BKDRHash( char* str, unsigned int len);
unsigned int SDBMHash( char* str, unsigned int len);
unsigned int DJBHash ( char* str, unsigned int len);
unsigned int DEKHash ( char* str, unsigned int len);
unsigned int BPHash  ( char* str, unsigned int len);
unsigned int FNVHash ( char* str, unsigned int len);
unsigned int APHash  ( char* str, unsigned int len);
void insertword(char*c,char* BITMAP,unsigned int(*p)( char*,unsigned int ));
int searchWord(char* c,char* BITMAP,unsigned int(*p)( char*,unsigned int ));

#endif
