#pragma once

class IZoomable
{
public:
	struct zoomIn;
	struct zoomOut;
public:
	struct zoomIn{
		zoomOut mirror() const { return zoomOut(); }
		auto get() const { return &IZoomable::_zoomIn; }
	};
	struct zoomOut{
		zoomIn mirror() const { return zoomIn(); }
		auto get() const { return &IZoomable::_zoomOut; }
	};	
protected:
	virtual void _zoomIn() = 0;
	virtual void _zoomOut() = 0;
	virtual ~IZoomable() {}
};
