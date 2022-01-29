#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int main(int argc, char** argv){
	CharBuffer* pBuffer;


	pBuffer = create_buffer(50);
	pBuffer->contents[0] = 'h';	
	pBuffer->contents[1] = 'e';
	pBuffer->contents[2] = 'l';
	pBuffer->contents[3] = 'l';
	pBuffer->contents[4] = 'o';
	pBuffer->contents[5] = ' ';
	pBuffer->contents[6] = 'w';
	pBuffer->contents[7] = 'o';
	pBuffer->contents[8] = 'r';
	pBuffer->contents[9] = 'l';
	pBuffer->contents[10] = 'd';
	pBuffer->contents[11] = '!';

	printf("%s", pBuffer->contents);
}
