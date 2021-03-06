#pragma once

#include<QWidget>

#include <Aspect_Window.hxx>

class OccWindow :
	public Aspect_Window
{
public:
	OccWindow(QWidget* aWidget);
	~OccWindow();


	//! Returns native Window handle
	virtual Aspect_Drawable NativeHandle() const;

	//! Returns parent of native Window handle.
	virtual Aspect_Drawable NativeParentHandle() const;

	//! Applies the resizing to the window <me>
	virtual Aspect_TypeOfResize DoResize() const;

	//! Returns True if the window <me> is opened
	//! and False if the window is closed.
	virtual Standard_Boolean IsMapped() const;

	//! Apply the mapping change to the window <me>
	//! and returns TRUE if the window is mapped at screen.
	virtual Standard_Boolean DoMapping() const { return Standard_True; }

	//! Opens the window <me>.
	virtual void Map() const;

	//! Closes the window <me>.
	virtual void Unmap() const;

	virtual void Position(Standard_Integer& theX1, Standard_Integer& theY1,
		Standard_Integer& theX2, Standard_Integer& theY2) const;

	//! Returns The Window RATIO equal to the physical
	//! WIDTH/HEIGHT dimensions.
	virtual Standard_Real Ratio() const;

	virtual void Size(Standard_Integer& theWidth, Standard_Integer& theHeight) const;

	virtual Aspect_FBConfig NativeFBConfig() const Standard_OVERRIDE { return NULL; }

	DEFINE_STANDARD_RTTIEXT(OccWindow, Aspect_Window)

private:
	QWidget*		myWidget;
	Standard_Integer myXLeft;
	Standard_Integer myYTop;
	Standard_Integer myXRight;
	Standard_Integer myYBottom;
};

