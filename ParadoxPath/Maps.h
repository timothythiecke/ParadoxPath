#pragma once

// Case #0
const unsigned char gCaseZeroMap[] =
{ 
	1,1,1,1,
	0,1,0,1,
	0,1,1,1 
};

int gCaseZeroBuffer[12];
const int gCaseZeroBufferSize = 12;

// Case #1
const unsigned char gCaseOneMap[] = 
{ 
	0, 0, 1,
	0, 1, 1, 
	1, 0, 1 
};

int gCaseOneBuffer[7];
const int gCaseOneBufferSize = 7;

// Case #2 - larger map
const unsigned char gLargerMap[] =
{
	1,1,1,1,0,
	0,0,0,1,0,
	0,0,0,1,0,
	1,1,1,1,0,
	1,0,0,0,0,
	1,1,1,1,1
};

int gLargerBuffer[16];
const int gLargerBufferSize = 16;

// Case #3 - one available map
const unsigned char gOneAvailableMap[] =
{
	1, 0,
	0, 1
};

int gOneAvialableBuffer[4];
const int gOneAvailableBufferSize = 4;

// Case #4 - small buffer
const unsigned char gSmallBufferMap[] =
{
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1
};

int gSmallBufferBuffer[4];
const int gSmallBufferBufferSize = 4;

// Case #5 - huge maps
const unsigned char gHugeMap[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
int gHugeBuffer[200];
int gHugeBufferSize = 200;