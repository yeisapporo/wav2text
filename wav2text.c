#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	FILE *src;
	FILE* dst;
	int ret;
	int cnt;
	unsigned char buf[1024];
	unsigned char temp_byte;

	src = fopen("lovesong.wav", "rb");
	cnt = 0;
	// skip header
	do {
		ret = fread(&buf[cnt], 1, 1, src);
		if (cnt >= 3 && (buf[cnt - 3] == 'd' && 
			             buf[cnt - 2] == 'a' && 
			             buf[cnt - 1] == 't' &&
			             buf[cnt    ] == 'a')) {
			// skip sub chunk size
			cnt += 4;
			break;
		}
		cnt++;
	} while (ret != 0 && cnt < 1024);


	dst = fopen("lovesong.h", "w");
	do {
		ret = fread(&temp_byte, 1, 1, src);
		if (ret != 0) {
			if (cnt % 16 == 0) {
				fprintf(dst, "0x%02x,\n", temp_byte);
			}
			else {
				fprintf(dst, "0x%02x, ", temp_byte);
			}
			cnt++;
		}
	} while (ret != 0);



	return 0;
}
