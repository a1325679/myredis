#include <iostream>
#include <string.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> //sockaddr_in
#include <assert.h>
#include <string.h>
using namespace std;
#define PORT 9090
int main()
{
	sockaddr_in seraddr;
	int serfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(serfd >= 3);
	printf("创建套接字%d成功\n", serfd);
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORT);
	seraddr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int ret = connect(serfd, (sockaddr *)(&seraddr), sizeof(sockaddr));
	assert(ret == 0);
	printf("连接成功\n");
	char sendbuf[1024] = {0};
	char readbuf[1024] = {0};
	// {
	// 	strcpy(sendbuf, "set zhangpengbin_score 89");
	// 	send(serfd, sendbuf, sizeof(sendbuf), 0);
	// 	usleep(200 * 100);
	// 	strcpy(sendbuf, "set key value");
	// 	send(serfd, sendbuf, sizeof(sendbuf), 0);
	// 	usleep(200 * 100);
	// 	strcpy(sendbuf, "set zhangpengbin 1235679");
	// 	send(serfd, sendbuf, sizeof(sendbuf), 0);
	// 	usleep(200 * 100);
	// }
	{
		strcpy(sendbuf, "get key");
		send(serfd, sendbuf, sizeof(sendbuf), 0);
		recv(serfd, readbuf, sizeof(readbuf), 0);
		printf("%s\n", readbuf);
		memset(&readbuf, 0, sizeof(readbuf));
		usleep(200 * 100);
	}
	{
		strcpy(sendbuf, "get zhangpengbin");
		send(serfd, sendbuf, sizeof(sendbuf), 0);
		recv(serfd, readbuf, sizeof(readbuf), 0);
		printf("%s\n", readbuf);
		memset(&readbuf, 0, sizeof(readbuf));
		usleep(200 * 100);
	}
	{
		strcpy(sendbuf, "get zhangpengbin_score");
		send(serfd, sendbuf, sizeof(sendbuf), 0);
		recv(serfd, readbuf, sizeof(readbuf), 0);
		printf("%s\n", readbuf);
		memset(&readbuf, 0, sizeof(readbuf));
		usleep(200 * 100);
	}
	close(serfd);
	return 0;
}