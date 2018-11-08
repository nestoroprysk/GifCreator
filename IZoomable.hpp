#pragma once

class IZoomable
{
public:
	virtual void zoomIn() = 0;
	virtual void zoomOut() = 0;
	virtual ~IZoomable() {}
};
