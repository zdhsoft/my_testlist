#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#define MAX_BUF_SIZE 1024

int main(int argc, char* argv[])
{
	// ����������
	if (argc != 2) {
		printf("Usage: md5 filename\n");
		return -1;
	}

	// ���ļ�
	FILE* fp = fopen(argv[1], "rb");
	if (!fp) {
		printf("Can't open file %s\n", argv[1]);
		return -1;
	}

	// �����ļ�����
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// �����ȡ������
	char* buf = (char*)malloc(MAX_BUF_SIZE);
	if (!buf) {
		printf("Can't allocate memory\n");
		fclose(fp);
		return -1;
	}

	// ��ʼ��MD5������
	MD5_CTX md5_ctx;
	MD5_Init(&md5_ctx);

	// ��ȡ�ļ�������MD5
	long read_size = 0;
	while (read_size < file_size) {
		size_t buf_size = (file_size - read_size) < MAX_BUF_SIZE ? (file_size - read_size) : MAX_BUF_SIZE;
		fread(buf, 1, buf_size, fp);
		MD5_Update(&md5_ctx, buf, buf_size);
		read_size += buf_size;
	}

	// �������յ�MD5ֵ
	unsigned char md5_value[MD5_DIGEST_LENGTH];
	MD5_Final(md5_value, &md5_ctx);

	// ���MD5ֵ
	printf("MD5(%s) = ", argv[1]);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x", md5_value[i]);
	}
	printf("\n");

	// �ͷ���Դ
	free(buf);
	fclose(fp);

	return 0;
}
