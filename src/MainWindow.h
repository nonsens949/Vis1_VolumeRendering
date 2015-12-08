
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"
#include "../VolVis.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>
#include <QBitmap>
#include <QPainter>


class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();
		void								setPixel(int x, int y, int density = 255);
		void								setColoredPixel(int x, int y, float r, float g, float b, int density = 255);
		void								clear();
		void								render();
	
	protected slots :

		void								 openFileAction();
		void								 closeAction();
		

	private:

		// USER INTERFACE ELEMENTS

		Ui_MainWindow						*m_Ui;


		// DATA 

		enum DataType
		{
			VOLUME					= 0,
			VECTORFIELD				= 1,
			MULTIVARIATE			= 2
		};

		struct FileType
		{
			QString			filename;
			DataType		type;
		}									 m_FileType;

		Volume								*m_Volume;						// for Volume-Rendering
		VectorField							*m_VectorField;					// for Flow-Visualisation
		MultiSet							*m_MultiSet;					// for Multivariate Data
		VolVis								*m_VolVis;
		QPixmap								pixmap;
		QPainter							painter;
		QPen								pen;
		int									currentDensity;
};

#endif
