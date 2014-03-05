#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// int main() {
// 	char array[] = "hellllooooo Gregggggg What are you doing?";
// 	int arraysize = sizeof(array)/sizeof(array[0]);
// 	char new_array[arraysize];

// 	for (int i = 0; i<arraysize-1; i++) {
// 		if ((array[i]>=97) && (array[i]<=122))
// 			new_array[i] = array[i]^0x20;
// 		else
// 			new_array[i] = array[i];
// 	}
// 	printf("%s\n", array);
// 	printf("%s\n", new_array);

// 	return 0;
// }

int main() {
	char array[] = "teststring";
	int arraysize = sizeof(array);
	
	uint16_t new_array[arraysize/2];
	uint16_t *p = (uint16_t *) array;

	int i;
	for (i = 0; i < arraysize/2; i++) {
		new_array[i] = p[i]^0x2020;
	}

	printf("%s\n", array);
	printf("%s\n", new_array);

	return 0;
}