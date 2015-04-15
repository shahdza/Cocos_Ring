#ifndef __GameOverDialog_H__
#define __GameOverDialog_H__

#include "Public.h"


class GameOverDialog : public cocos2d::Layer
{
public:
    static GameOverDialog* create(int state, int c1, int c2, int c3, int c4, int exp);
    virtual bool init(int state, int c1, int c2, int c3, int c4, int exp);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();

    void updateData();
    
    void backCallback(Ref* sender, Widget::TouchEventType type);

private:
    int _state;
    int _c1;
    int _c2;
    int _c3;
    int _c4;
    int _exp;
};

#endif // __GameOverDialog_H__
