#ifndef PROPERTYQMARGINSF_H
#define PROPERTYQMARGINSF_H

#include "QtnProperty/Auxiliary/PropertyTemplates.h"
#include "PropertyDouble.h"
#include "QtnProperty/StructPropertyBase.h"
#include <QMarginsF>

class QTN_IMPORT_EXPORT QtnPropertyQMarginsFBase
    : public QtnStructPropertyBase<QMarginsF, QtnPropertyDoubleCallback>
{
	Q_OBJECT

private:
	QtnPropertyQMarginsFBase(const QtnPropertyQMarginsFBase &other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQMarginsFBase(QObject *parent);

	QtnProperty *createLeftProperty();
	QtnProperty *createTopProperty();
	QtnProperty *createRightProperty();
	QtnProperty *createBottomProperty();

protected:
	// string conversion implementation
	bool fromStrImpl(
	    const QString &str, QtnPropertyChangeReason reason) override;
	bool toStrImpl(QString &str) const override;

	P_PROPERTY_DECL_MEMBER_OPERATORS(QtnPropertyQMarginsFBase)
};

P_PROPERTY_DECL_EQ_OPERATORS(QtnPropertyQMarginsFBase, QMarginsF)

class QTN_IMPORT_EXPORT QtnPropertyQMarginsFCallback
    : public QtnSinglePropertyCallback<QtnPropertyQMarginsFBase>
{
	Q_OBJECT

private:
	QtnPropertyQMarginsFCallback(
	    const QtnPropertyQMarginsFCallback &other) Q_DECL_EQ_DELETE;

public:
	Q_INVOKABLE explicit QtnPropertyQMarginsFCallback(QObject *parent = nullptr);

	P_PROPERTY_DECL_MEMBER_OPERATORS2(
	    QtnPropertyQMarginsFCallback, QtnPropertyQMarginsFBase)
};

class QTN_IMPORT_EXPORT QtnPropertyQMarginsF
    : public QtnSinglePropertyValue<QtnPropertyQMarginsFBase>
{
	Q_OBJECT

private:
	QtnPropertyQMarginsF(const QtnPropertyQMarginsF &other) Q_DECL_EQ_DELETE;

public:
	Q_INVOKABLE explicit QtnPropertyQMarginsF(QObject *parent = nullptr);

	P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQMarginsF, QtnPropertyQMarginsFBase)
};

#endif // PROPERTYQMARGINSF_H
