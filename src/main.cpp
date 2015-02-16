#include <QApplication>
#include <QDesktopWidget>
#include "StopWatch.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);  

	StopWatch *q = new StopWatch();
	q->setWindowTitle("Stopwatch 0.2");
	q->show();

	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT ( quit() ) );

	return app.exec();
}
