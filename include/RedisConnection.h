#ifndef _REDIS_CONNECTION_
#define _REDIS_CONNECTION_
struct event_base;
struct bufferevent;
class RedisConnection
{
public:
	RedisConnection();
	~RedisConnection();
	bool init(int fd,event_base *base);
	static void ReadCB(struct bufferevent *bev, void *args);
	static void WriteCB(struct bufferevent *bev, void *args);
	static void EventCB(struct bufferevent *bev, short what, void *arg);

private:
	int sockfd;
	struct event_base *base = 0;
	struct bufferevent *bev = 0;
};
#endif