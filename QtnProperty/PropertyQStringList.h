#pragma once

#include "Auxiliary/PropertyTemplates.h"
#include "Delegates/Utils/PropertyDelegateMisc.h"

#include <QStringList>

class QTN_IMPORT_EXPORT QtnPropertyQStringListBase
	: public QtnSinglePropertyBase<QStringList>
{
	Q_OBJECT

private:
	QtnPropertyQStringListBase(
		const QtnPropertyQStringListBase &other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQStringListBase(QObject *parent);
};

class QTN_IMPORT_EXPORT QtnPropertyQStringListCallback
	: public QtnSinglePropertyCallback<QtnPropertyQStringListBase>
{
	Q_OBJECT

private:
	QtnPropertyQStringListCallback(
		const QtnPropertyQStringListCallback &other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQStringListCallback(QObject *parent = nullptr);
};

class QTN_IMPORT_EXPORT QtnPropertyQStringList
	: public QtnSinglePropertyValue<QtnPropertyQStringListBase>
{
	Q_OBJECT

private:
	QtnPropertyQStringList(const QtnPropertyQStringList &other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQStringList(QObject *parent);

	static QString getPlaceholderStr();
};

class QTN_IMPORT_EXPORT QtnPropertyDelegateStringList
	: public QtnPropertyDelegateTyped<QtnPropertyQStringListBase>
{
	Q_DISABLE_COPY(QtnPropertyDelegateStringList)

public:
	QtnPropertyDelegateStringList(QtnPropertyQStringListBase &owner);

	static void Register(QtnPropertyDelegateFactory &factory);

protected:
	virtual bool acceptKeyPressedForInplaceEditImpl(
		QKeyEvent *keyEvent) const override;

	virtual QWidget *createValueEditorImpl(QWidget *parent, const QRect &rect,
		QtnInplaceInfo *inplaceInfo = nullptr) override;

	virtual bool propertyValueToStrImpl(QString &strValue) const override;
};
