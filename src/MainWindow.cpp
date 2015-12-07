#include "MainWindow.h"

#include <QFileDialog>

#include <iostream>



MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0),
	pixmap(1000, 500), painter(&pixmap), pen(QColor(0, 0, 0), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin), currentDensity(255)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);

	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));

	//initialize pixmap
	painter.setPen(pen);
}

MainWindow::~MainWindow()
{
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
}


//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::openFileAction()
{
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			success = m_Volume->loadFromFile(filename, m_Ui->progressBar);

			//render density to screen

			//clear pixmap
			clear();

			//calculate RayCasting
			m_VolVis = new VolVis(m_Volume);
			std::vector<float> densities = m_VolVis->calculateRayCasting();


			//set pixels to correct intensity on screen
	/*		for (int x = 0; x < m_Ui->DisplayWindow->width(); x++)
			{
				for (int y = 0; y < m_Ui->DisplayWindow->height(); y++)
				{
					Voxel& maxDensity = Voxel();
					for (int z = 0; z < 100; z++)
					{
						if (m_Volume->voxel(x, y, z).operator>(maxDensity))
						{
							maxDensity = m_Volume->voxel(x, y, z);
						}
					}
					int intensity = (int)(maxDensity.getValue() * 255);
					setPixel(x, y, intensity);
				}
			}*/
			
			
			int iter = 0;
			int size = densities.size();
			for (int x = 0; x < m_Ui->DisplayWindow->width(); x++)
			{
				float maxDensity = 0;
				for (int y = 0; y < m_Ui->DisplayWindow->height(); y++)
				{
					float maxDensity = densities.at(iter);
					int intensity = (int)(maxDensity * 255);
					setPixel(x, y, intensity);
					if (iter < 100){
						iter++;
					}
					
					
				}
			}
			
			

			//render
			render();
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);

		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME) type = "VOLUME";
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}
	}
}

void MainWindow::closeAction()
{
	close();
}

//clear the pixmap
void MainWindow::clear()
{
	//fill window with white color
	pixmap.fill(QColor(255, 255, 255));
}

//sets the pixels on the screen
void MainWindow::setPixel(int x, int y, int density)
{
	if (density != currentDensity)
	{
		pen.setColor(QColor(0, 0, 0, density));
		painter.setPen(pen);
		currentDensity = density;
	}
	//performs painting on widgets like QLabels
	painter.drawPoint(x, y);
	
}

//set pixmap to the right values
void MainWindow::render()
{
	m_Ui->DisplayWindow->setPixmap(pixmap);
}



