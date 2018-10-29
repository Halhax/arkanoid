#pragma once

class Error
{
public:
	virtual void error() = 0;
	virtual ~Error() {};
};