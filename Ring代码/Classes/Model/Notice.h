#ifndef __Notice_H__
#define __Notice_H__

#include "Public.h"


class Notice : public cocos2d::Node
{
public:
    static Notice* create(string text);
    virtual bool init(string text);
    
    void showUI(string text);
    void remove();

private:
    
};

#endif // __Notice_H__
