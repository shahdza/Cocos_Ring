#ifndef _PAN_ZOOM_LAYER_H_
#define _PAN_ZOOM_LAYER_H_

#include "cocos2d.h"
using namespace cocos2d;


class PanZoomLayer : public Layer
{
public:
	PanZoomLayer();
	virtual ~PanZoomLayer();

	static PanZoomLayer* create();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);
	//virtual void onTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent);
	//virtual void onTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent);
	//virtual void onTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent);
	virtual bool doTouchBegan(Touch* pTouch, Event *pEvent);
	virtual void doTouchMoved(Touch* pTouch, Event *pEvent);
	virtual void doTouchEnded(Touch* pTouch, Event *pEvent);

	//overload
	virtual void setScale(float scale);
	virtual void setPosition(Vec2 position);
	virtual void setPosition(float x, float y) { this->setPosition(Vec2(x,y)); }
	
	//BoundRect
    void setPanBoundsRect(cocos2d::Rect rect);

	inline void setMinScale(float minScale) { _minScale = minScale; }
	inline float getMinScale() { return _minScale; }

	inline void setMaxScale(float maxScale) { _maxScale = maxScale; }
	inline float getMaxScale() { return _maxScale; }

	// limit scale range [ MinScale + minZoomdelta , MaxScale - maxZoomdelta ]
	inline void setZoomDelta(float minZoomdelta = 0.05, float maxZoomdelta = 0.2)  { _minZoomDelta = minZoomdelta; _maxZoomDelta = maxZoomdelta; }
	inline float getMinZoomDelta() { return _minZoomDelta; }
	inline float getMaxZoomDelta() { return _maxZoomDelta; }

	// the Point of Scale Center
	inline void setScaleMidPos(Vec2 v) { _scaleMidPos = v; }
	inline Vec2 getScaleMidPos() { return _scaleMidPos; }

	// enable/disable Touch
	inline void holding() { _isHolding = true; }
	inline void unHolding() { _isHolding = false; }
    
    
private:
    Vector<Touch*> _touches;
    Vec2 _beganTouchPoint;
    Vec2 _endedTouchPoint;
    Vec2 _deltaSum;
    Vec2 _prevDeltaPoint;
    Vec2 _scaleMidPos;
    
    CCRect _panBoundsRect;
    double _accelerationFactor;
    
    float _minScale;
    float _maxScale;
    float _minZoomDelta;
    float _maxZoomDelta;
    
    bool _isHolding;
};


#endif