#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main (int argc, char * argv[], char ** envp) {
 char ascii_value = 0;
 char digit = 0;
 char offset = 0x30;
 unsigned int number = 0; //"outputs the equivalent unsigned decimal number"
 int retval = read(0, &ascii_value, 1);
 
 //Computation
 while (retval == 1){
	 //Validation 1 (Binary Value Detection)
	if(ascii_value == 0x30 || ascii_value == 0x31){
	   digit = ascii_value - offset;
	   number = (number << 1) + digit;
	   retval = read(0, &ascii_value, 1);
	}else{
		//Validation Failed or EOF, Go to Validation 2
		break;
	}		
 }
 
 //Validation 2 (Checking Validation 1 Fail Reason)
if(ascii_value == 0x30 || ascii_value == 0x31 || ascii_value == 0x0a || ascii_value == 0x4c46 || ascii_value == 0x6e6c || ascii_value == 0x6e65776c696e65){
	//Successful conversion
	printf("%u\n", number);
    return 0;
	//Validation 3 (Failed, Calculations exceeded 2^32)
	} else if (number > 4294967295) {
		printf("Error: The calculated number exceeded 2^32.\n");
		return 1;
	//Validation 4 (Failed, Non-binary digit entered)
	}else{
		printf("Error: A non-binary number was detected.\n");
		return 1;
	}
}
