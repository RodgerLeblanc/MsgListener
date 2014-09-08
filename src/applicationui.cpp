/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <QSettings>

using namespace bb::cascades;

ApplicationUI::ApplicationUI() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    // Creates the MessageService object
    m_messageService = new bb::pim::message::MessageService(this);
    // Connect to the messageAdded signal
    connect(m_messageService, SIGNAL(messageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)), SLOT(onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)));
    connect(m_messageService, SIGNAL(messageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate)), SLOT(onMessageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate)));
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("MsgListener_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::onMessageAdded(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId, bb::pim::message::MessageKey messageId)
{
    qDebug() << "TRIGGERED: onMessageAdded accountId: " << accountId << ", conversationId: " << conversationId << ", messageId: " << messageId;
    analyzeThis(accountId, conversationId, messageId);
}

void ApplicationUI::onMessageUpdated(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId, bb::pim::message::MessageKey messageId, bb::pim::message::MessageUpdate data)
{
    qDebug() << "TRIGGERED: onMessageUpdated accountId: " << accountId << ", conversationId: " << conversationId << ", messageId: " << messageId << data.isValid();
//    bb::pim::message::ConversationKey conversationId = bb::pim::message::ConversationKey();
    analyzeThis(accountId, NULL, messageId);
}

void ApplicationUI::analyzeThis(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId, bb::pim::message::MessageKey messageId)
{
    bb::pim::message::Message message = m_messageService->message(accountId, messageId);

    // Return if message was initiated by the user but not sent yet
    if (!message.isInbound())
        if (!message.status().testFlag(bb::pim::message::MessageStatus::Sent))
            return;

    // Retrieve sender of message
    bb::pim::message::MessageContact messageContact = message.sender();
    qDebug() << messageContact.address() << messageContact.name();

    // Retrieve recipients of message
    QList<bb::pim::message::MessageContact> listOfMessageContact = message.recipients();

    QSettings settings;
    QString toDelete = settings.value("toDelete").toString();
    qDebug() << "toDelete:" << toDelete;

    bool senderNeedsToBeDeleted = messageContact.address().contains(toDelete, Qt::CaseInsensitive);

    bool recipientNeedsToBeDeleted = false;
    for (int i = 0; i < listOfMessageContact.size(); i++)
        if (listOfMessageContact[i].address().contains(toDelete, Qt::CaseInsensitive))
            recipientNeedsToBeDeleted = true;

    qDebug() << senderNeedsToBeDeleted << recipientNeedsToBeDeleted;

    if (senderNeedsToBeDeleted || recipientNeedsToBeDeleted) {
        // Remove last message (used for email)
        m_messageService->remove(accountId, messageId);
        // Remove last conversation (used for SMS)
        if (!conversationId.isNull())
            m_messageService->remove(accountId, conversationId);
    }
}

void ApplicationUI::setValue(const QString key, const QVariant value)
{
    QSettings settings;
    settings.setValue(key, value);
}

QVariant ApplicationUI::value(const QString key, const QVariant defaultValue)
{
    QSettings settings;
    return settings.value(key, defaultValue);
}
