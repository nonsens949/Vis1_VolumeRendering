#pragma once
#include "..\lib\qt\include\QtWidgets\qlabel.h"
#include "..\generated\ui_MainWindow.h"

class DisplayWindow :
	public QLabel
{
public:
	DisplayWindow(QLabel *parent = 0);
	~DisplayWindow();
};

