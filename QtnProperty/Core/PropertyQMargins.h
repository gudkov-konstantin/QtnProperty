#ifndef PROPERTYQMARGINS_H
#define PROPERTYQMARGINS_H

#include "QtnProperty/Auxiliary/PropertyTemplates.h"
#include "PropertyInt.h"
#include "QtnProperty/StructPropertyBase.h"
#include <QMargins>

class QTN_IMPORT_EXPORT QtnPropertyQMarginsBase
    : public QtnStructPropertyBase<QMargins, QtnPropertyIntCallback>
{
	Q_OBJECT

private:
	QtnPropertyQMarginsBase(const QtnPropertyQMarginsBase &other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQMarginsBase(QObject *parent);

	QtnProperty *createLeftProperty();
	QtnProperty *createTopProperty();
	QtnProperty *createRightProperty();
	QtnProperty *createBottomProperty();

protected:
	// string conversion implementation
	bool fromStrImpl(
	    const QString &str, QtnPropertyChangeReason reason) override;
	bool toStrImpl(QString &str) const override;

	P_PROPERTY_DECL_MEMBER_OPERATORS(QtnPropertyQMarginsBase)
};

P_PROPERTY_DECL_EQ_OPERATORS(QtnPropertyQMarginsBase, QMargins)

class QTN_IMPORT_EXPORT QtnPropertyQMarginsCallback
    : public QtnSinglePropertyCallback<QtnPropertyQMarginsBase>
{
	Q_OBJECT

private:
	QtnPropertyQMarginsCallback(
	    const QtnPropertyQMarginsCallback &other) Q_DECL_EQ_DELETE;

public:
	Q_INVOKABLE explicit QtnPropertyQMarginsCallback(QObject *parent = nullptr);

	P_PROPERTY_DECL_MEMBER_OPERATORS2(
	    QtnPropertyQMarginsCallback, QtnPropertyQMarginsBase)
};

class QTN_IMPORT_EXPORT QtnPropertyQMargins
    : public QtnSinglePropertyValue<QtnPropertyQMarginsBase>
{
	Q_OBJECT

private:
	QtnPropertyQMargins(const QtnPropertyQMargins &other) Q_DECL_EQ_DELETE;

public:
	Q_INVOKABLE explicit QtnPropertyQMargins(QObject *parent = nullptr);

	static QString leftKey();
	static QString leftString();
	static QString topKey();
	static QString topString();
	static QString rightKey();
	static QString rightString();
	static QString bottomKey();
	static QString bottomString();

	P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQMargins, QtnPropertyQMarginsBase)
};

#endif // PROPERTYQMARGINS_H
