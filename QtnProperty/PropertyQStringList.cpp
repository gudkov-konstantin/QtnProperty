/*******************************************************************************
Copyright (c) 2026 Gudkov Konstantin <gudkov.danger@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include "PropertyQStringList.h"

#include "QObjectPropertySet.h"
#include "Delegates/PropertyDelegateFactory.h"
#include "Delegates/Utils/PropertyEditorAux.h"
#include "Delegates/Utils/PropertyEditorHandler.h"

#include "CustomPropertyEditorDialog.h"

#include <QKeyEvent>

class QtnPropertyQStringListEditBttnHandler
	: public QtnPropertyEditorBttnHandler<QtnPropertyQStringListBase,
		  QtnLineEditBttn>
{
public:
	QtnPropertyQStringListEditBttnHandler(
		QtnPropertyDelegate *delegate, QtnLineEditBttn &editor);

protected:
	virtual void revertInput() override;
	virtual void onToolButtonClick() override;
	virtual void updateEditor() override;

private:
	void onToolButtonClicked(bool);
	void onApplyData(const QVariant &data);

	CustomPropertyEditorDialog *dialog;
	DialogContainerPtr dialogContainer;
};

QtnPropertyQStringListBase::QtnPropertyQStringListBase(QObject *parent)
	: QtnSinglePropertyBase(parent)
{
}

QtnPropertyQStringListCallback::QtnPropertyQStringListCallback(QObject *parent)
	: QtnSinglePropertyCallback<QtnPropertyQStringListBase>(parent)
{
}

QtnPropertyQStringList::QtnPropertyQStringList(QObject *parent)
	: QtnSinglePropertyValue<QtnPropertyQStringListBase>(parent)
{
}

QString QtnPropertyQStringList::getPlaceholderStr()
{
	return tr("(List)");
}

QtnPropertyDelegateStringList::QtnPropertyDelegateStringList(
	QtnPropertyQStringListBase &owner)
	: QtnPropertyDelegateTyped<QtnPropertyQStringListBase>(owner)
{
}

void QtnPropertyDelegateStringList::Register(QtnPropertyDelegateFactory &factory)
{
	factory.registerDelegateDefault(&QtnPropertyQStringListBase::staticMetaObject,
		&qtnCreateDelegate<QtnPropertyDelegateStringList,
			QtnPropertyQStringListBase>,
		"QStringList");
}

bool QtnPropertyDelegateStringList::acceptKeyPressedForInplaceEditImpl(
	QKeyEvent *keyEvent) const
{
	if (QtnPropertyDelegateTyped<QtnPropertyQStringListBase>::
			acceptKeyPressedForInplaceEditImpl(keyEvent))
		return true;

	// accept any printable key
	return qtnAcceptForLineEdit(keyEvent);
}

QWidget *QtnPropertyDelegateStringList::createValueEditorImpl(
	QWidget *parent, const QRect &rect, QtnInplaceInfo *inplaceInfo)
{
	auto editor = new QtnLineEditBttn(parent);
	editor->setGeometry(rect);

	new QtnPropertyQStringListEditBttnHandler(this, *editor);

	qtnInitLineEdit(editor->lineEdit, inplaceInfo);
	return editor;
}

bool QtnPropertyDelegateStringList::propertyValueToStrImpl(
	QString &strValue) const
{
	strValue = QtnPropertyQStringList::getPlaceholderStr();

	return true;
}

QtnPropertyQStringListEditBttnHandler::QtnPropertyQStringListEditBttnHandler(
	QtnPropertyDelegate *delegate, QtnLineEditBttn &editor)
	: QtnPropertyEditorHandlerType(delegate, editor)
	, dialog(new CustomPropertyEditorDialog(&editor))
{
	dialogContainer = connectDialog(dialog);
	updateEditor();

	editor.lineEdit->installEventFilter(this);
	editor.lineEdit->setReadOnly(true);
	editor.lineEdit->setPlaceholderText(QtnPropertyQStringList::getPlaceholderStr());

	QObject::connect(editor.toolButton, &QToolButton::clicked, this,
		&QtnPropertyQStringListEditBttnHandler::onToolButtonClicked);

	QObject::connect(dialog, &CustomPropertyEditorDialog::apply, this,
		&QtnPropertyQStringListEditBttnHandler::onApplyData);
}

void QtnPropertyQStringListEditBttnHandler::revertInput()
{
	reverted = true;
}

void QtnPropertyQStringListEditBttnHandler::onToolButtonClick()
{
	onToolButtonClicked(false);
}

void QtnPropertyQStringListEditBttnHandler::updateEditor()
{
}

void QtnPropertyQStringListEditBttnHandler::onToolButtonClicked(bool)
{
	auto property = &this->property();
	QVariant data = property->value();

	reverted = true;
	dialog->setReadOnly(!stateProperty()->isEditableByUser());
	dialog->setPropertyOptionsEnable(false);
	dialog->setPropertyFixedAddType(QMetaType::QString);
	QtnPropertyDelegateInfo info;
	info.attributes["multiline_edit"] = false;
	dialog->setPropertyDelegateInfo(&info);

	volatile bool destroyed = false;
	auto connection = QObject::connect(this, &QObject::destroyed,
		[&destroyed]() mutable { destroyed = true; });

	if (dialog->execute(property->name(), data) && !destroyed)
		property->setValue(data.toStringList(), delegate()->editReason());

	if (!destroyed)
	{
		QObject::disconnect(connection);
		updateEditor();
	}
}

void QtnPropertyQStringListEditBttnHandler::onApplyData(const QVariant &data)
{
	property().setValue(data.toStringList(), delegate()->editReason());
	updateEditor();
}
