#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>

#include "Volume.h"

/*
This class represents a widget for rendering OpenGL graphics
*/
class GLWidget : public QGLWidget
{

public:
	explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

protected:
	//needed to perform typical OpenGL tasks
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);
	virtual void paintGL();

private:
	
	Volume						*volume;

	float						stepSize;
	int							windowWidth;
	int							windowHeight;

	void						draw();

};
#endif