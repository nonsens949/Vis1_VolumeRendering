#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWidget>

class OpenGLWindow : public QWidget
{
	//Q_OBJECT

public:
	explicit OpenGLWindow(QWidget *parent = 0);
	~OpenGLWindow();
};
#endif