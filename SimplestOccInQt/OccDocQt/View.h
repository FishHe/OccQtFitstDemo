#pragma once

#include <QWidget>
#include <QAction>
#include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <AIS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>

class TopoDS_Shape;
class QRubberBand;

class View
	: public QWidget
{
	Q_OBJECT

protected:
	enum CurrentAction3d {
		CurAction3d_Nothing, CurAction3d_DynamicZooming,
		CurAction3d_WindowZooming, CurAction3d_DynamicPanning,
		CurAction3d_GlobalPanning, CurAction3d_DynamicRotation,
		CurrentAction3d_DrawLine, CurrentAction3d_DrawPoint,
		CurrentAction3d_DrawCube0, CurrentAction3d_DrawCube1, CurrentAction3d_DrawCube2,
		CurrentAction3d_DrawPoly, CurrentAction3d_Extrude
	};

public:
	enum ViewAction {
		ViewFitAllId, ViewFitAreaId, ViewZoomId, ViewPanId, ViewGlobalPanId,
		ViewFrontId, ViewBackId, ViewTopId, ViewBottomId, ViewLeftId, ViewRightId,
		ViewAxoId, ViewRotationId, ViewResetId, ViewHlrOffId, ViewHlrOnId,
		ViewChangeDisplayModeId
	};
	enum RaytraceAction { ToolRaytracingId, ToolShadowsId, ToolReflectionsId, ToolAntialiasingId };

	enum DrawAction
	{
		DrawPiontId, DrawLineId, DrawPolyId, DrawCubeId, ExtrudeId
	};

	View(Handle(AIS_InteractiveContext) theContext, QWidget* parent);

	~View();

	virtual void                  init();
	bool                          dump(Standard_CString theFile);
	QList<QAction*>*              getViewActions();
	QList<QAction*>*              getRaytraceActions();
	void                          noActiveActions();
	bool                          isShadingMode();

	void                          EnableRaytracing();
	void                          DisableRaytracing();

	void                          SetRaytracedShadows(bool theState);
	void                          SetRaytracedReflections(bool theState);
	void                          SetRaytracedAntialiasing(bool theState);

	bool                          IsRaytracingMode() const { return myIsRaytracing; }
	bool                          IsShadowsEnabled() const { return myIsShadowsEnabled; }
	bool                          IsReflectionsEnabled() const { return myIsReflectionsEnabled; }
	bool                          IsAntialiasingEnabled() const { return myIsAntialiasingEnabled; }

	static QString                GetMessages(int type, TopAbs_ShapeEnum aSubShapeType,
		TopAbs_ShapeEnum aShapeType);
	static QString                GetShapeType(TopAbs_ShapeEnum aShapeType);

	Standard_EXPORT static void   OnButtonuseraction(int ExerciceSTEP,
		Handle(AIS_InteractiveContext)&);
	Standard_EXPORT static void   DoSelection(int Id,
		Handle(AIS_InteractiveContext)&);
	Standard_EXPORT static void   OnSetSelectionMode(Handle(AIS_InteractiveContext)&,
		Standard_Integer&,
		TopAbs_ShapeEnum& SelectionMode,
		Standard_Boolean&);
	virtual QPaintEngine*         paintEngine() const;
signals:
	void                          selectionChanged();

	public slots:
	void                          fitAll();
	void                          fitArea();
	void                          zoom();
	void                          pan();
	void                          globalPan();
	void                          front();
	void                          back();
	void                          top();
	void                          bottom();
	void                          left();
	void                          right();
	void                          axo();
	void                          rotation();
	void                          reset();
	void                          hlrOn();
	void                          hlrOff();
	void                          updateToggled(bool);
	void                          onBackground();
	void                          onEnvironmentMap();
	void                          onRaytraceAction();


	void						  drawLine();
	void						  drawPoint();
	void						  drawCube();
	void						  drawPoly();
	void						  changeDisplayMode();
	void						  extrude();

protected:
	virtual void                  paintEvent(QPaintEvent*);
	virtual void                  resizeEvent(QResizeEvent*);
	virtual void                  mousePressEvent(QMouseEvent*);
	virtual void                  mouseReleaseEvent(QMouseEvent*);
	virtual void                  mouseMoveEvent(QMouseEvent*);
	virtual void				  mouseDoubleClickEvent(QMouseEvent *);

	virtual void                  addItemInPopup(QMenu*);

	Handle(V3d_View)&                     getView();
	Handle(AIS_InteractiveContext)&       getContext();
	void                                  activateCursor(const CurrentAction3d);
	void                                  Popup(const int x, const int y);
	CurrentAction3d                       getCurrentMode();

	virtual void                          onLButtonDown(const int nFlags, const QPoint point);
	virtual void                          onMButtonDown(const int nFlags, const QPoint point);
	virtual void                          onRButtonDown(const int nFlags, const QPoint point);
	virtual void                          onLButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onMButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onRButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onMouseMove(Qt::MouseButtons nFlags, const QPoint point);
	virtual void						  onLButtonDblClick(const int nFlags, const QPoint point);

private:
	void                          initCursors();
	void                          initViewActions();
	void                          initRaytraceActions();
	void                          DragEvent(const int x, const int y, const int TheState);
	void                          InputEvent(const int x, const int y);
	void                          MoveEvent(const int x, const int y);
	void                          MultiMoveEvent(const int x, const int y);
	void                          MultiDragEvent(const int x, const int y, const int TheState);
	void                          MultiInputEvent(const int x, const int y);
	void                          DrawRectangle(const int MinX, const int MinY,
		const int MaxX, const int MaxY, const bool Draw);

	void initDrawActions();
private:
	bool                            myIsRaytracing;
	bool                            myIsShadowsEnabled;
	bool                            myIsReflectionsEnabled;
	bool                            myIsAntialiasingEnabled;

	bool                            myDrawRect;           // set when a rect is used for selection or magnify 
	Handle(V3d_View)                myView;
	Handle(AIS_InteractiveContext)  myContext;
	CurrentAction3d                 myCurrentMode;
	Standard_Integer                myXmin;			//mouse point x when button down
	Standard_Integer                myYmin;			//mouse point y when button down
	Standard_Integer                myXmax;			//mouse point x when button up and mouse move
	Standard_Integer                myYmax;			//mouse point y when button up and mouse move
	Standard_Real                   myCurZoom;
	Standard_Boolean                myHlrModeIsOn;
	QList<QAction*>*                myViewActions;
	QList<QAction*>*                myRaytraceActions;
	QList<QAction*>*                myDrawActions;
	QMenu*                          myBackMenu;
	QRubberBand*                    myRectBand; //!< selection rectangle rubber band

	Handle(AIS_Shape)				myCurrentShape;	//drawing shape
	gp_Pnt							myCubePnt1;		//drawing a cube
	gp_Pnt							myCubePnt2;		//drawing a cube
	QList<gp_Pnt>*					myPolyPnts;		//drawing a Polygon
	TopoDS_Wire						myExtrudeWire;
	Handle(AIS_Shape)				myExtrudePrism;
	gp_Pnt							myExtrudeCenter;
};

