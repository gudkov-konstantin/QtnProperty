#include "PropertyQMargins.h"

#include <QRegularExpression>

QtnProperty *QtnPropertyQMarginsBase::createLeftProperty()
{
	return createFieldProperty(&QMargins::left,
	                           &QMargins::setLeft, QtnPropertyQMargins::leftKey(),
	                           QtnPropertyQMargins::leftString());
}

QtnProperty *QtnPropertyQMarginsBase::createTopProperty()
{
	return createFieldProperty(&QMargins::top,
	                           &QMargins::setTop, QtnPropertyQMargins::topKey(),
	                           QtnPropertyQMargins::topString());
}

QtnProperty *QtnPropertyQMarginsBase::createRightProperty()
{
	return createFieldProperty(&QMargins::right,
	                           &QMargins::setRight, QtnPropertyQMargins::rightKey(),
	                           QtnPropertyQMargins::rightString());
}

QtnProperty *QtnPropertyQMarginsBase::createBottomProperty()
{
	return createFieldProperty(&QMargins::bottom,
	                           &QMargins::setBottom, QtnPropertyQMargins::bottomKey(),
	                           QtnPropertyQMargins::bottomString());
}

QtnPropertyQMarginsBase::QtnPropertyQMarginsBase(QObject *parent)
    : ParentClass(parent)
{
}

bool QtnPropertyQMarginsBase::fromStrImpl(
    const QString &str, QtnPropertyChangeReason reason)
{
	static QRegularExpression parserRect(
	    "^\\s*QMargins\\s*\\(([^\\)]+)\\)\\s*$", QRegularExpression::CaseInsensitiveOption);
	static QRegularExpression parserParams(
	    "^\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*$",
	    QRegularExpression::CaseInsensitiveOption);

	if (!parserRect.match(str).hasMatch())
		return false;

	QStringList params = parserRect.match(str).capturedTexts();
	if (params.size() != 2)
		return false;

	if (!parserParams.match(params[1]).hasMatch())
		return false;

	params = parserParams.match(params[1]).capturedTexts();
	if (params.size() != 5)
		return false;

	bool ok = false;
	int left = params[1].toInt(&ok);
	if (!ok)
		return false;

	int top = params[2].toInt(&ok);
	if (!ok)
		return false;

	int right = params[3].toInt(&ok);
	if (!ok)
		return false;

	int bottom = params[4].toInt(&ok);
	if (!ok)
		return false;

	return setValue(QMargins(left, top, right, bottom), reason);
}

bool QtnPropertyQMarginsBase::toStrImpl(QString &str) const
{
	auto v = value();

	str = QStringLiteral("QMargins(%1, %2, %3, %4)")
	          .arg(v.left())
	          .arg(v.top())
	          .arg(v.right())
	          .arg(v.bottom());

	return true;
}

QtnPropertyQMargins::QtnPropertyQMargins(QObject *parent)
    : QtnSinglePropertyValue<QtnPropertyQMarginsBase>(parent)
{
}

QString QtnPropertyQMargins::leftKey()
{
	return tr("left");
}

QString QtnPropertyQMargins::leftString()
{
	return tr("Left");
}

QString QtnPropertyQMargins::topKey()
{
	return tr("top");
}

QString QtnPropertyQMargins::topString()
{
	return tr("Top");
}

QString QtnPropertyQMargins::rightKey()
{
	return tr("right");
}

QString QtnPropertyQMargins::rightString()
{
	return tr("Right");
}

QString QtnPropertyQMargins::bottomKey()
{
	return tr("bottom");
}

QString QtnPropertyQMargins::bottomString()
{
	return tr("Bottom");
}

QtnPropertyQMarginsCallback::QtnPropertyQMarginsCallback(QObject *parent)
    : QtnSinglePropertyCallback<QtnPropertyQMarginsBase>(parent)
{
}
