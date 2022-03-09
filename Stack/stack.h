#pragma once

#include <stdio.h>
#include <wchar.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

typedef int data_t;
typedef int canary_t;

typedef struct stack {
	canary_t canary1;
	size_t capacity;
	size_t size;
	char *data;
	unsigned long long hash;
	canary_t canary2;
} stack_t;

enum Errors {
	NO_ERRORS = 0,
	NULL_POINTER = 1,
	CANARY_KILLED = 2,
	DATA_INVASION = 3,
	SIZE_ERROR = 4,
	CAPACITY_ERROR = 5,
	STACK_HASH_ERROR = 6,
	DATA_HASH_ERROR = 7,
	STACK_EMPTE = 8
};

// ToDo: global const - write in CAPS
size_t StackIsEmpty (stack_t *stk);
unsigned long long GetCRC (char* data, size_t start, size_t end);
unsigned long long GetDataHash (stack_t* stk);
unsigned long long GetStackHash (stack_t* stk);
void StackConstruct (stack_t *stk);
void StackDestruct (stack_t *stk);
void StackSizeUp (stack_t *stk);
void StackSizedDown (stack_t *stk);
void StackPush (stack_t *stk, data_t value);
data_t StackPop (stack_t *stk);
size_t GetStackSize (stack_t *stk);
size_t GetStackCapacity (stack_t *stk);
int StackError (stack_t *stk);
char *Timenow ();
void PrintStackLogs (stack_t *stk);
void Dump (stack_t *stk, int error, const char *function, const int line);
