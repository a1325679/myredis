#ifndef _GLOBAL_H
#define _GLOBAL_H
#include "RedisConnection.h"
#include <arpa/inet.h>
#include <vector>
#include <iostream>
extern RedisConnection *connePool;
void PrintIpPort(sockaddr *a);
void split(std::vector<std::string> &vec, const std::string &str, const std::string &delim);
#endif