#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
class PlayerXmlConfig
{
public:
	PlayerXmlConfig();
	~PlayerXmlConfig();
public:
	void setXmlContent(const char* xmlContent);
	void setXmlUrl(const char* xmlUrl);

	const char* getXmlContent() const;

private:
	char* xmlContent;
	char* xmlUrl;
};

