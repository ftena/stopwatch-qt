#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDateTime>
#include <QTime>
#include <QLabel>
#include <iostream>

class StopWatch : public QWidget
{
	Q_OBJECT
	public:
		explicit StopWatch(QWidget * parent = 0)
			: QWidget(parent)
				, mRunning(false)
			   , mStartTime()
				, mLabel(new QLabel("000:00:00:000"))
				, zero('0')
	{
		QHBoxLayout * hBoxLayout = new QHBoxLayout(this);
		QPushButton * startButton = new QPushButton("Start");
		QPushButton * stopButton = new QPushButton("Stop");

		QFont f( "Arial", 32, QFont::Bold);
		mLabel->setFont( f);

		hBoxLayout->addWidget(startButton);
		hBoxLayout->addWidget(stopButton);
		hBoxLayout->addWidget(mLabel);

		connect(startButton, SIGNAL(clicked()), SLOT(start()));
		connect(stopButton, SIGNAL(clicked()), SLOT(stop()));

		startTimer(0);
	}

		public slots:
			void start(void)
			{
				mStartTime = QTime::currentTime();
				mRunning = true;
			}

		void stop(void)
		{
			mRunning = false;
		}

	protected:
		void timerEvent(QTimerEvent *)
		{
			if(mRunning)
			{
				qint64 ms = mStartTime.msecsTo(QTime::currentTime());
				int h = ms / 1000 / 60 / 60;
				int m = (ms / 1000 / 60) - (h * 60);
				int s = (ms / 1000) - (m * 60);
				ms = ms - (s * 1000) - (m * 60000) - (h * 3600000);
				QString diff = QString("%1:%2:%3:%4").
									arg(h, 3, 10, zero).
									arg(m, 2, 10, zero).
									arg(s, 2, 10, zero).
									arg(ms, 3, 10, zero);
				mLabel->setText(diff);
			}
		}

	private:
		bool mRunning;
		QTime mStartTime;
		QLabel * mLabel;
		const QChar zero;
};

