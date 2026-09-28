#include "PropertyQMarginsF.h"

#include "PropertyQMargins.h"

#include <QRegularExpression>

QtnProperty *QtnPropertyQMarginsFBase::createLeftProperty()
{
	return createFieldProperty(&QMarginsF::left,
	                           &QMarginsF::setLeft, QtnPropertyQMargins::leftKey(),
	                           QtnPropertyQMargins::leftString());
}

QtnProperty *QtnPropertyQMarginsFBase::createTopProperty()
{
	return createFieldProperty(&QMarginsF::top,
	                           &QMarginsF::setTop, QtnPropertyQMargins::topKey(),
	                           QtnPropertyQMargins::topString());
}

QtnProperty *QtnPropertyQMarginsFBase::createRightProperty()
{
	return createFieldProperty(&QMarginsF::right,
	                           &QMarginsF::setRight, QtnPropertyQMargins::rightKey(),
	                           QtnPropertyQMargins::rightString());
}

QtnProperty *QtnPropertyQMarginsFBase::createBottomProperty()
{
	return createFieldProperty(&QMarginsF::bottom,
	                           &QMarginsF::setBottom, QtnPropertyQMargins::bottomKey(),
	                           QtnPropertyQMargins::bottomString());
}

QtnPropertyQMarginsFBase::QtnPropertyQMarginsFBase(QObject *parent)
    : ParentClass(parent)
{
}

bool QtnPropertyQMarginsFBase::fromStrImpl(
    const QString &str, QtnPropertyChangeReason reason)
{
	static QRegularExpression parserRect(
	    "^\\s*QMarginsF\\s*\\(([^\\)]+)\\)\\s*$", QRegularExpression::CaseInsensitiveOption);
	static QRegularExpression parserParams("^\\s*(\\-?\\d+(\\.\\d{0,})?)\\s*,\\s*(\\-?\\d+"
	                                       "(\\.\\d{0,})?)\\s*,\\s*(\\d+(\\.\\d{0,})?)\\s*"
	                                       ",\\s*(\\d+(\\.\\d{0,})?)\\s*$",
	                                       QRegularExpression::CaseInsensitiveOption);

	if (!parserRect.match(str).hasMatch())
		return false;

	QStringList params = parserRect.match(str).capturedTexts();
	if (params.size() != 2)
		return false;

	if (!parserParams.match(params[1]).hasMatch())
		return false;

	params = parserParams.match(params[1]).capturedTexts();
	if (params.size() != 9)
		return false;

	bool ok = false;
	double left = params[1].toDouble(&ok);
	if (!ok)
		return false;

	double top = params[3].toDouble(&ok);
	if (!ok)
		return false;

	double right = params[5].toDouble(&ok);
	if (!ok)
		return false;

	double bottom = params[7].toDouble(&ok);
	if (!ok)
		return false;

	return setValue(QMarginsF(left, top, right, bottom), reason);
}

bool QtnPropertyQMarginsFBase::toStrImpl(QString &str) const
{
	auto v = value();

	str = QStringLiteral("QMarginsF(%1, %2, %3, %4)")
	          .arg(v.left())
	          .arg(v.top())
	          .arg(v.right())
	          .arg(v.bottom());

	return true;
}

QtnPropertyQMarginsF::QtnPropertyQMarginsF(QObject *parent)
    : QtnSinglePropertyValue<QtnPropertyQMarginsFBase>(parent)
{
}

QtnPropertyQMarginsFCallback::QtnPropertyQMarginsFCallback(QObject *parent)
    : QtnSinglePropertyCallback<QtnPropertyQMarginsFBase>(parent)
{
}

