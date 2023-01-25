#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include "Global.h"
#include "Macor.h"
#include "ObjectSave.h"
using namespace std;
#define PORT 9090

ObjectSave *ObjectSave::m_instance = nullptr;
RedisConnection *connePool = new RedisConnection[CONNECTION_MAX_NUMBER];
void PrintIpPort(sockaddr *a)
{
	struct sockaddr_in *sock = (struct sockaddr_in *)a;
	int port = ntohs(sock->sin_port); // linux上打印方式
	struct in_addr in = sock->sin_addr;
	char str[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN这个宏系统默认定义 16
	// // 成功的话此时IP地址保存在str字符串中。
	inet_ntop(AF_INET, &in, str, sizeof(str));
	std::cout << "ip:port " << str << " " << port << std::endl;
}
void listen_cb(struct evconnlistener *e, evutil_socket_t s, struct sockaddr *a, int socklen, void *args)
{
	PrintIpPort(a);
	event_base *base = (event_base*)args;
	connePool[s].init(s, base);
}
int main()
{
	event_base *base = event_base_new();
	assert(base != nullptr);
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	evconnlistener *ev = evconnlistener_new_bind(base, listen_cb, base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 10, (sockaddr *)&sin, sizeof(sin));
	assert(ev != nullptr);
	event_base_dispatch(base);
	if (ev)
		evconnlistener_free(ev);
	if (base)
		event_base_free(base);
	return 0;
}
