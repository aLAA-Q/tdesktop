/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014 John Preston, https://desktop.telegram.org
*/
#pragma once

#ifndef TDESKTOP_DISABLE_AUTOUPDATE

#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QNetworkReply>

class UpdateDownloader : public QObject {
	Q_OBJECT

public:
	UpdateDownloader(QThread *thread, const QString &url);

	void unpackUpdate();

	int32 ready();
	int32 size();

	static void clearAll();

	~UpdateDownloader();

public slots:

	void start();
	void partMetaGot();
	void partFinished(qint64 got, qint64 total);
	void partFailed(QNetworkReply::NetworkError e);
	void sendRequest();

private:
	void initOutput();

	void fatalFail();

	QString updateUrl;
	QNetworkAccessManager manager;
	QNetworkReply *reply;
	int32 already, full;
	QFile outputFile;

	QMutex mutex;

};

bool checkReadyUpdate();

#endif
