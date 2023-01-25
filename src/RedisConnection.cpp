#include "RedisConnection.h"
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <assert.h>
#include <iostream>
#include <string>
#include "Global.h"
#include <string.h>
#include "ObjectSave.h"
void split(std::vector<std::string> &vec, const std::string &str, const std::string &delim)
{
	if (str == "" || delim == "")
		return;
	char *temp = new char[str.size() + 1];
	strcpy(temp, str.c_str());
	char *p = strtok(temp, delim.c_str());
	while (p != NULL)
	{
		vec.push_back(p);
		p = strtok(NULL, delim.c_str());
	}
	std::string fin = vec[vec.size()-1];
	if(fin[fin.size()-1]=='\n')
		fin.pop_back();
	vec[vec.size() - 1] = fin;
	return;
}
RedisConnection::RedisConnection()
{
}
RedisConnection::~RedisConnection()
{
	if(bev)
	{
		bufferevent_free(bev);
		bev = 0;
	}
}
bool RedisConnection::init(int fd, event_base *base)
{
	bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	assert(bev != nullptr);
	this->sockfd = fd;
	this->bev = bev;
	this->base = base;
	bufferevent_setcb(bev, ReadCB, WriteCB, EventCB, this);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
	std::string msg = "220 Welcome to RedisServer\r\n";
	bufferevent_write(bev, msg.c_str(), msg.size());
	return true;
}
void RedisConnection::ReadCB(struct bufferevent *bev, void *args)
{
	RedisConnection *conn = (RedisConnection *)args;
	char data[1024] = {0};
	for (;;)
	{
		int len = bufferevent_read(bev, data, sizeof(data) - 1);
		std::cout << "len: " << len << std::endl;
		if (len <= 6)
			return;
		std::cout <<"data : "<<data << std::endl;
		data[len] = '\0';
		std::string str = data;
		std::vector<std::string> vec;
		std::string delim = " ";
		split(vec, str, delim);
		if (vec[0] == "set")
		{
			ObjectSave::GetInstance()->setStringMap(vec[1], vec[2]);
		}
		else if (vec[0] == "get")
		{
			std::string value = ObjectSave::GetInstance()->getStringMap(vec[1]);
			bufferevent_write(bev, value.c_str(), value.size());
		}
	}
}
void RedisConnection::WriteCB(struct bufferevent *bev, void *args)
{
}
void RedisConnection::EventCB(struct bufferevent *bev, short what, void *arg)
{
}