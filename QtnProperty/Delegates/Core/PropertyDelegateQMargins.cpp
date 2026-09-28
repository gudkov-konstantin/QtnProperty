#include "PropertyDelegateQMargins.h"
#include "QtnProperty/Delegates/PropertyDelegateFactory.h"
#include "QtnProperty/PropertyDelegateAttrs.h"

#include <QLineEdit>

QtnPropertyDelegateQMargins::QtnPropertyDelegateQMargins(
    QtnPropertyQMarginsBase &owner)
    : QtnPropertyDelegateTypedEx<QtnPropertyQMarginsBase>(owner)
{
	addSubProperty(owner.createLeftProperty());
	addSubProperty(owner.createTopProperty());
	addSubProperty(owner.createRightProperty());
	addSubProperty(owner.createBottomProperty());
}

void QtnPropertyDelegateQMargins::Register(QtnPropertyDelegateFactory &factory)
{
	factory.registerDelegateDefault(&QtnPropertyQMarginsBase::staticMetaObject,
	                                &qtnCreateDelegate<QtnPropertyDelegateQMargins, QtnPropertyQMarginsBase>,
	                                "QMargins");
}

void qtnApplyQMarginsDelegateAttributes(QtnPropertyDelegate *to,
                                     const QtnPropertyDelegateInfo &info)
{
	enum
	{
		LEFT = 0,
		TOP = 1,
		RIGHT = 2,
		BOTTOM = 3,
		TOTAL
	};
	Q_ASSERT(to->subPropertyCount() == TOTAL);

	static const QtnSubPropertyInfo LTRB[TOTAL] = {
	                                               { LEFT, QtnPropertyQMargins::leftKey(), qtnLeftDisplayNameAttr(),
	                                                qtnLeftDescriptionAttr() },
	                                               { TOP, QtnPropertyQMargins::topKey(), qtnTopDisplayNameAttr(),
	                                                qtnTopDescriptionAttr() },
	                                               { RIGHT, QtnPropertyQMargins::rightKey(), qtnRightDisplayNameAttr(),
	                                                qtnRightDescriptionAttr() },
	                                               { BOTTOM, QtnPropertyQMargins::bottomKey(), qtnBottomDisplayNameAttr(),
	                                                qtnBottomDescriptionAttr() },
	                                               };
	to->applySubPropertyInfos(info, LTRB, TOTAL);

}

void QtnPropertyDelegateQMargins::applyAttributesImpl(
    const QtnPropertyDelegateInfo &info)
{
	qtnApplyQMarginsDelegateAttributes(this, info);
}

QWidget *QtnPropertyDelegateQMargins::createValueEditorImpl(
    QWidget *parent, const QRect &rect, QtnInplaceInfo *inplaceInfo)
{
	return createValueEditorLineEdit(parent, rect, true, inplaceInfo);
}

bool QtnPropertyDelegateQMargins::propertyValueToStrImpl(QString &strValue) const
{
	auto value = owner().value();

	QLocale locale;
	strValue = QString("[(%1, %2, %3, %4)]")
	        .arg(locale.toString(value.left()), locale.toString(value.top()),
	             locale.toString(value.right()), locale.toString(value.bottom()));

	return true;
}
