#ifndef PROPERTY_DELEGATE_QMARGINS_H
#define PROPERTY_DELEGATE_QMARGINS_H

#include "QtnProperty/Delegates/Utils/PropertyDelegateMisc.h"
#include "QtnProperty/Core/PropertyQMargins.h"

class QTN_IMPORT_EXPORT QtnPropertyDelegateQMargins
    : public QtnPropertyDelegateTypedEx<QtnPropertyQMarginsBase>
{
	Q_DISABLE_COPY(QtnPropertyDelegateQMargins)

public:
	QtnPropertyDelegateQMargins(
	    QtnPropertyQMarginsBase &owner);

	static void Register(QtnPropertyDelegateFactory &factory);

protected:
	virtual void applyAttributesImpl(
	    const QtnPropertyDelegateInfo &info) override;

	virtual QWidget *createValueEditorImpl(QWidget *parent, const QRect &rect,
	                                       QtnInplaceInfo *inplaceInfo = nullptr) override;

	virtual bool propertyValueToStrImpl(QString &strValue) const override;
};

#endif // PROPERTY_DELEGATE_QMARGINS_H
