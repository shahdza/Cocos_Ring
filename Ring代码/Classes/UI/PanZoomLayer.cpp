#include "PanZoomLayer.h"


PanZoomLayer::PanZoomLayer() 
{ 

}

PanZoomLayer::~PanZoomLayer()
{ 

}


PanZoomLayer* PanZoomLayer::create() 
{
	PanZoomLayer *pRet = new PanZoomLayer;
	if (pRet && pRet->init()) 
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}


bool PanZoomLayer::init()
{
	if (!Layer::init()) 
	{
		return false;
	}

	_touches.clear();
	_accelerationFactor = 0.0f;

	_minScale = 1.0f;
	_maxScale = 3.0f;
	_minZoomDelta = 0.0f;
	_maxZoomDelta = 0.5f;

	_isHolding = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	this->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(visibleSize);
    //CCLOG("PanZoomLayer_ContentSize: %f , %f",this->getContentSize().width,this->getContentSize().height);

	// Touch Listener
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PanZoomLayer::doTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PanZoomLayer::doTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PanZoomLayer::doTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void PanZoomLayer::onEnter()
{
	Layer::onEnter();
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}


void PanZoomLayer::onExit()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	_touches.clear();
	Layer::onExit();
}


void PanZoomLayer::update(float dt)
{
	// Skip smoothe panning when dt is high value
	if (dt > 1.0f / 55) return;

	Layer::update(dt);

	// zoomScale
	float scale = this->getScale();
	if (_touches.size() == 0)
	{
		if (scale > _maxScale)
		{
			this->setScale(scale - dt);
		}
		else if (scale < _minScale)
		{
			this->setScale(scale + dt);
		}
	}

	if (_touches.size() == 1)
	{
		_accelerationFactor *= 40 * dt * 0.95f;
	}
	else if (_touches.size() == 0)
	{
		_accelerationFactor = fabs(_accelerationFactor - 0);
		if (_accelerationFactor < FLT_EPSILON)
			return;

		if (_accelerationFactor < 0.004f)
		{
			_accelerationFactor = 0;
		}
		else
		{
			double d = dt * 60;
			if (d > 0.99) 
				d = 0.99;
			double i = (0 - _accelerationFactor) * 0.025 * d;

			_accelerationFactor = (_accelerationFactor + i) * d;

			Vec2 adder = _deltaSum;
			adder.x *= this->getContentSize().width;
			adder.y *= this->getContentSize().height;

			this->setPosition(this->getPosition() + adder * 2.5 * _accelerationFactor);
		}
	}
}


bool PanZoomLayer::doTouchBegan(Touch* pTouch, Event *pEvent)
{
	if (_isHolding) return false;

	// CCLOG("layer began");

	//Touch *pTouch;
	//int cnt = 0;
	//for (int i = 0; i < (int)pTouches.size(); i++)
	//{
	//	pTouch = (Touch *)pTouches[i];
	//	_touches.pushBack(pTouch);
	//}

	_touches.pushBack(pTouch);

	_deltaSum = Vec2(0, 0);
	_accelerationFactor = 0;
	return true;
}


void PanZoomLayer::doTouchMoved(Touch* pTouch, Event *pEvent)
{
	if (_isHolding) return;

	if (_touches.size() == 1)
	{
		Touch* touch = _touches.at(0);
		Vec2 curTouchPosition = Director::getInstance()->convertToGL(touch->getLocationInView());
		Vec2 prevTouchPosition = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
		Vec2 deltaPosition = curTouchPosition - prevTouchPosition;
		this->setPosition(this->getPosition() + deltaPosition);

		float prevAngle = CC_RADIANS_TO_DEGREES(_prevDeltaPoint.getAngle());
		float angle = CC_RADIANS_TO_DEGREES(deltaPosition.getAngle());
		if (fabs(prevAngle - angle) <= 30)
		{
			_deltaSum = Vec2(0, 0);
		}

		_prevDeltaPoint = deltaPosition;

		_deltaSum.x = _deltaSum.x + deltaPosition.x / this->getContentSize().width;
		_deltaSum.y = _deltaSum.y + deltaPosition.y / this->getContentSize().height;

		_accelerationFactor += _deltaSum.getLength() * 4.0;
	}
	else if (_touches.size() >= 2)
	{
		// Get the two first touches
		Touch* touch1 = _touches.at(0);
		Touch* touch2 = _touches.at(1);

		// Get current and previous positions of the touches
		Vec2 curPosTouch1 = Director::getInstance()->convertToGL(touch1->getLocationInView());
		Vec2 curPosTouch2 = Director::getInstance()->convertToGL(touch2->getLocationInView());
		Vec2 prevPosTouch1 = Director::getInstance()->convertToGL(touch1->getPreviousLocationInView());
		Vec2 prevPosTouch2 = Director::getInstance()->convertToGL(touch2->getPreviousLocationInView());

		// Calculate current and previous positions of the layer relative the anchor point
		Vec2 curPosLayer = (curPosTouch1 + curPosTouch2) / 2;
		Vec2 prevPosLayer = (prevPosTouch1 + prevPosTouch2) / 2;
		_scaleMidPos = curPosLayer;

		// Calculate new scale
		float prevScale = this->getScale();
		float curScale = this->getScale() * curPosTouch1.getDistance(curPosTouch2) / prevPosTouch1.getDistance(prevPosTouch2);

		this->setScale(curScale);

		// If current and previous position of the multitouch's center aren't equal -> change position of the layer
		if (!prevPosLayer.equals(curPosLayer))
		{
			this->setPosition(Vec2(this->getPosition().x + curPosLayer.x - prevPosLayer.x,
				this->getPosition().y + curPosLayer.y - prevPosLayer.y));
		}
	}
}


void PanZoomLayer::doTouchEnded(Touch* pTouch, Event *pEvent)
{
	if (_isHolding) return;

	//Touch *pTouch;
	//for (int i = 0; i < (int)pTouches.size(); i++)
	//{
	//	pTouch = (Touch *)pTouches[i];
	//	_touches.eraseObject(pTouch);
	//}

	_touches.eraseObject(pTouch);
}


void PanZoomLayer::setPosition(Vec2 position)
{
	Node::setPosition(position);

	if (_panBoundsRect.equals(Rect::ZERO) == false)
	{
		Rect boundBox;
		boundBox.origin = this->getPosition() / this->getScale();
		boundBox.size = this->getContentSize() / this->getScale();

		// OpenGL coordinate system
		float left = boundBox.getMinX();
		float right = boundBox.getMaxX();
		float top = boundBox.getMaxY();
		float bottom = boundBox.getMinY();

		float min_x = _panBoundsRect.getMinX() + boundBox.size.width;
		float max_x = _panBoundsRect.getMaxX() + boundBox.size.width;
		float min_y = _panBoundsRect.getMinY() + boundBox.size.height;
		float max_y = _panBoundsRect.getMaxY() + boundBox.size.height;

		float scale = this->getScale();
		float arLeft = min_x * scale;
		float arRight = max_x * scale - this->getContentSize().width;
		float arTop = max_y * scale - this->getContentSize().height;
		float arBottom = min_y * scale;

        //CCLOG("min: [x=%f, y=%f]", min_x, min_y);
        //CCLOG("max: [x=%f, y=%f]", max_x, max_y);
        //CCLOG("left  : %f", left);
        //CCLOG("bottom: %f", bottom);
        //CCLOG("right : %f", right);
        //CCLOG("top   : %f", top);

		if (left < min_x)
		{
			Node::setPosition(arLeft, this->getPosition().y);
		}

		if (right > max_x)
		{
			Node::setPosition(arRight, this->getPosition().y);
		}

		if (top > max_y)
		{
			Node::setPosition(this->getPosition().x, arTop);
		}

		if (bottom < min_y)
		{
			Node::setPosition(this->getPosition().x, arBottom);
		}
	}
}


void PanZoomLayer::setScale(float scale)
{
	scale = MIN(MAX(scale, _minScale - _minZoomDelta), _maxScale + _maxZoomDelta);
	Vec2 realCurPosLayer = this->convertToNodeSpaceAR(_scaleMidPos);
	Vec2 diff = (scale - this->getScale()) * realCurPosLayer;

	Layer::setScale(scale);
	this->setPosition(this->getPosition() - diff);
}


void PanZoomLayer::setPanBoundsRect(cocos2d::Rect rect)
{
	//Fit the screen
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float wFactor = winSize.width / rect.size.width;
	float hFactor = winSize.height / rect.size.height;
	float minScale = MAX(wFactor, hFactor);

	rect.origin += origin;
	_panBoundsRect = rect;

	_scaleMidPos = winSize / 2;
	setMinScale(minScale);
	
    //CCLOG("PanZoomLayer_Bound_winSize: %f , %f", winSize.width, winSize.height);
    //CCLOG("PanZoomLayer_Bound_origin     : %f , %f",origin.x,origin.y);
    //CCLOG("PanZoomLayer_Bound_rect       : %f , %f , %f , %f", rect.origin.x, rect.origin.y,rect.size.width, rect.size.height);
}
