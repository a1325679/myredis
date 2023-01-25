#ifndef _OBJECT_SAVE_
#define _OBJECT_SAVE_
#include <string>
#include <unordered_map>
#include <iostream>
class ObjectSave
{
public:
	~ObjectSave()
	{
	}
	static ObjectSave *GetInstance()
	{
		if (m_instance == nullptr)
		{
			if (m_instance == nullptr)
			{
				m_instance = new ObjectSave();
			}
		}
		return m_instance;
	}
	void setStringMap(std::string &key, std::string &value)
	{
		if (stringMap.find(key) != stringMap.end())
		{
			return;
		}
		stringMap[key] = value;
		std::cout << "key: " << key << ","
							<< "value: " << stringMap[key] << std::endl;
	}
	std::string getStringMap(std::string &key)
	{
		if (stringMap.find(key) != stringMap.end())
		{
			return stringMap[key];
		}
		return "";
	}

private:
	class CGarge
	{
	public:
		~CGarge()
		{
			if (m_instance)
				delete m_instance;
		}
		CGarge() {}

	private:
	};
	ObjectSave() {}
	static ObjectSave *m_instance;
	std::unordered_map<std::string, std::string> stringMap;
	CGarge c;
};
#endif