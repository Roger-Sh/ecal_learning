/* ========================= LICENSE =================================
 *
 * Copyright (C) 2022 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= LICENSE =================================
 */

#pragma once

#include <ecal/mon/plugin.h>
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/dynamic_subscriber.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <memory>
#include <mutex>

#include <QtWidgets/QLabel>

#include "ui_plugin_widget.h"

#include "compressed_image.pb.h"

class PluginWidget : public QWidget, public eCAL::mon::PluginWidgetInterface
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Plugin Widget object
     * 
     * @param topic_name 
     * @param topic_type 
     * @param parent 
     */
    PluginWidget(const QString &topic_name, const QString &topic_type, QWidget *parent = Q_NULLPTR);

    /**
     * @brief Destroy the Plugin Widget object
     * 
     */
    virtual ~PluginWidget();

    /**
     * @brief Get the Widget object
     * 
     * @return QWidget* 
     */
    virtual QWidget *getWidget();

public slots:

    /**
     * @brief on update mode
     * 
     */
    virtual void onUpdate();

    /**
     * @brief on resume mode
     * 
     */
    virtual void onResume();

    /**
     * @brief on pause mode
     * 
     */
    virtual void onPause();

protected:
    Ui::PluginWidget ui_;

private slots:
    /**
     * @brief Actual Content Update
     * 
     */
    void updateContent();

private:
    // subscriber
    eCAL::protobuf::CSubscriber<foxglove::CompressedImage> compressed_image_subscriber_;
    std::mutex proto_message_mutex_;
    foxglove::CompressedImage *last_received_photo_;
    eCAL::Time::ecal_clock::time_point last_message_publish_timestamp_;

    QString topic_name_, topic_type_;
    bool new_msg_available_;
    int received_message_counter_;

    /**
     * @brief eCAL subscriber Callback
     *
     * @param compressed_image_msg
     * @param send_time_usecs
     */
    void photoReceivedMessageCallback(const foxglove::CompressedImage &message, long long send_time_usecs);
    void updatePublishTimeLabel();
};
