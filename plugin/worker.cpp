#include "systemCalls.h"
#include <QString>
#include <QVector>
#include <QDebug>
#include <QCoreApplication>
#include <QtNetwork/QNetworkInterface>
#include "worker.h"
#define SUCCESS 0
#define CANNOT_START 1
#define NO_INTERNET 2
#define CONFLICTS 3

QString Worker::getAURHelper()
{
	qDebug() <<"get aur helper called";
	//searches /usr/bin for AUR helpers and returns the first entry without trailing \n
	QProcess *getAURHelperProcess = new QProcess(this);
	QStringList arguments;
	arguments << "/usr/bin/ | egrep '(apacman|aura|aurget|bauerbill|burgaur|cowerpacaur|pacget|packer|pkgbuilder|spinach|trizen|wrapaur|yaourt|yay)' | head -n1 | tr -d '\n'";
	
	getAURHelperProcess->start("/usr/bin/ls", arguments);
	if (getAURHelperProcess->waitForStarted(3000))
	{
		qDebug() << "get aur helper started" << endl;

		//DEBUGGING WILL REMOVE
		if (getAURHelperProcess->waitForReadyRead(-1))
		{
			getAURHelperProcess->waitForFinished(-1);
			qDebug() << "===========";
			qDebug() <<"PRoCESS" << getAURHelperProcess->readAllStandardOutput();
			qDebug() <<"============";
		}
		else{qDebug() <<"cannot read from get aur helper";}
		
	}
	
	else{ qDebug() << "cannot start getAURHelper";}
	return getAURHelperProcess->readAllStandardOutput();
};


QStringList Worker::getAURHelperCommands(QString AURHelper)
{
	QStringList arguments;

	if (AURHelper == "apacman")
	{
		arguments << "apacman" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "aura")
	{
		arguments << "aura" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	//aurget only upgrades aur need to run pacman too
	else if (AURHelper == "aurget")
	{
		arguments << "aurget" << "-Syu" << "--noconfirm" << "&&" << "pacman" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "bauerbill")
	{
		arguments << "bauerbill" << "-Syyu" << "--aur" << "--noconfirm";
		return arguments;
	}

	//burgaur only upgrades aur need to run pacman too
	else if (AURHelper == "burgaur")
	{
		arguments << "burgaur" << "-su" << "--noconfirm" << "&&" << "pacman" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	//cower only runs aur need to run pacman too
	else if (AURHelper == "cower")
	{
		arguments << "cower" << "-ud" << "--noconfirm" << "&&" << "pacman" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "pacaur")
	{
		arguments << "pacaur" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "pacget")
	{
		arguments << "pacget" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "packer")
	{
		arguments << "packer" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "pkgbuilder")
	{
		arguments << "pkgbuilder" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	//spinach only does AUR need to run pacman too
	else if (AURHelper == "spinach")
	{
		arguments << "spinach" << "-u" << "--noconfirm" << "&&" << "pacman" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "trizen")
	{
		arguments << "trizen" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "wrapaur")
	{
		arguments << "wrapaur" << "-u" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "yaourt")
	{
		arguments << "yaourt" << "-Syua" << "--noconfirm";
		return arguments;
	}

	else if (AURHelper == "yay")
	{
		arguments << "yay" << "-Syyu" << "--noconfirm";
		return arguments;
	}

	else
	{
		return QStringList();
	}
}

void Worker::checkUpdates(bool namesOnly, bool aur)
{
	QString aurPackages;
	QStringList aurResultsVector;
	qDebug() << "clicked" << endl;
	//starts checkupdates as new qProcess
	QProcess *checkUpdatesProcess = new QProcess(this);

	if (aur)
	{
		qDebug() << "=========== AUR ===========";
		QProcess *checkUpdatesAURProcess = new QProcess(this);
		checkUpdatesAURProcess->start("/usr/bin/checkupdates-aur");

		if (checkUpdatesAURProcess->waitForReadyRead(-1))
		{
			checkUpdatesAURProcess->waitForFinished(-1);
			aurPackages = checkUpdatesAURProcess->readAllStandardOutput();
// 			qDebug() <<aurPackages;
		}

		aurResultsVector = aurPackages.split(((QRegExp) "\n"));
		aurResultsVector.removeAt(aurResultsVector.length() - 1);
		qDebug() << aurResultsVector;
	}

	checkUpdatesProcess->start("/usr/bin/checkupdates");

	//waits until started 3000 msec timeout
	if (checkUpdatesProcess->waitForStarted(3000))
	{
		qDebug() << "check updates started" << endl;

		//DEBUGGING WILL REMOVE
		if (checkUpdatesProcess->waitForReadyRead(-1))
		{
			checkUpdatesProcess->waitForFinished(-1);
			QString results = checkUpdatesProcess->readAllStandardOutput();
			qDebug() << "org.kde.archUpdate:  ================CHECKUPDATES CALL===================" << results;
			//split into vector by \n
			QStringList resultsVector = results.split(((QRegExp) "\n"));
			//remove trailing ""
			resultsVector.removeAt(resultsVector.length() - 1);

			//add aur packages
			for (int i = 0; i < aurResultsVector.length(); i++)
			{
				resultsVector.push_back(aurResultsVector[i]);
			}

			//sort vector so aur packages aren't at the bottom
			qSort(resultsVector.begin(), resultsVector.end());
			qDebug() << "org.kde.archUpdate:  =========CHECK UPDATES SPLIT============" << resultsVector;
			//if namesOnly is supplied as argument, return only package names without version upgrade information
			QStringList namesOnlyResults;

			if (namesOnly)
			{
				QVector<QStringList> tmp;

				for (int i = 0; i < resultsVector.length(); i++)
					tmp.push_back(resultsVector[i].split((QRegExp) " "));

				for (int i = 0; i < tmp.length(); i++)
					namesOnlyResults.push_back(tmp[i][0]);

				qDebug() << "org.kde.archUpdate:  ==========NAMES ONLY================" << namesOnlyResults;
				this->updates = namesOnlyResults;
			}

			else
				this->updates = resultsVector;
		}

		else
		{
			qDebug() << "org.kde.archUpdate: Your system is up to date, checkupdates returned nothing";
			QStringList err = QStringList();
			this->updates = err;
		}
	}

	else
	{
		qDebug() << "org.kde.archUpdate: Cannot start /usr/bin/checkupdates" << endl;
		qDebug() << checkUpdatesProcess->error() << endl << checkUpdatesProcess->errorString();
		QStringList err = QStringList();
		err << "cannot start checkupdates";
		this->updates = err;
	}
};


int Worker::upgradeSystem(bool konsoleFlag, bool aur,QString AURHelper)
{
	QProcess *systemUpdateProcess = new QProcess(this);
	qDebug() << "KONSOLE FLAG" << konsoleFlag;

	if (konsoleFlag && aur)
	{
		QStringList arguments;
		// start with konsole --hold -e sudo **aur helper**
		arguments << "--hold" << "-e" << "sudo";
		//add to arguments aur helper specific command to update
		// apacman is -Syu versus yaort is -Syua etc
		qDebug() << "AUr hELPER======" << AURHelper;
		QStringList AURCommands = getAURHelperCommands(AURHelper);

		for (int i = 0; i < AURCommands.size(); i++)
		{
			arguments << AURCommands[i];
		}

		//start system update process for konsole
		systemUpdateProcess->start("/usr/bin/konsole", arguments);
// 				connect(systemUpdateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(showProgressInqDebug()));
		qDebug() << "KONSOLE FLAG" << konsoleFlag;
	}

	//if user selects show in konsole in settings display in konsole
	else if (konsoleFlag && aur == false)
	{
		QStringList arguments;
		arguments << "--hold" << "-e" << "sudo" << "pacman" << "-Syyu" << "--noconfirm";
		systemUpdateProcess->start("/usr/bin/konsole", arguments);
	}

	else if (aur && konsoleFlag == false)
	{
		QStringList arguments;
		//start with aur helper add aur helper specific commands
		// apacman is -Syyu yaourt -s -Syyua
		QStringList AURCommands = getAURHelperCommands(AURHelper);

		for (int i = 0; i < AURCommands.size(); i++)
		{
			arguments << AURCommands[i];
		}

		systemUpdateProcess->start("pkexec", arguments);
	}

	else
	{
		QStringList arguments;
		arguments << "/usr/bin/pacman" << "-Syyu" << "--noconfirm";
		//if user does not select show in konsole run pexec
		{
			systemUpdateProcess->start("pkexec", arguments);
		}
	}

	// calls Qprocess for "pexec pacman -Syu --noconfirm --force"

	//wait to start 3000 msec timeout
	if (systemUpdateProcess->waitForStarted(3000))
	{
		qDebug() << "STARTED";
		QString log = systemUpdateProcess->readAllStandardOutput();

		//wait for finish no timeout
		if (systemUpdateProcess->waitForFinished(-1))
		{
			if (log.indexOf("file exists") != -1)
			{
				return CONFLICTS;
			}

			qDebug() << "=====UPDATE COMPLETE";
			this->updates = QStringList();
			return SUCCESS;
		}

		else
		{
			qDebug() << "org.kde.archUpdate:  cannot finish update";
			return systemUpdateProcess->exitCode();
		}
	}

	else
	{
		qFatal("org.kde.archUpdate: cannot start");
		qDebug() << systemUpdateProcess->error() << endl << systemUpdateProcess->errorString();
		return CANNOT_START;
	}
};