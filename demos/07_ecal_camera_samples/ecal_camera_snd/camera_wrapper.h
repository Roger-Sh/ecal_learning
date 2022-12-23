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

#include <QCamera>
#include <QCameraImageCapture>
#include <QObject>
#include <QScopedPointer>

#include <ecal/msg/protobuf/publisher.h>

#include "compressed_image.pb.h"

/**
 * @brief CameraWrapper for QCamera
 * 
 */
class CameraWrapper : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Construct a new Camera Wrapper object
     * 
     * @param publisher 
     * @param camera_name 
     * @param width 
     * @param height 
     */
    CameraWrapper(
        eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
        std::string &camera_name, uint16_t width, uint16_t height);

    /**
     * @brief Destroy the Camera Wrapper object
     * 
     */
    ~CameraWrapper();

    /**
     * @brief isReadyForCapture, check if camera data is ready
     * 
     * @return true 
     * @return false 
     */
    bool isReadyForCapture();

    /**
     * @brief printAvailableCameras, print avaliable camera names
     * 
     */
    void printAvailableCameras();

protected:
    /**
     * @brief capture camera data
     * 
     */
    virtual void capture();

private slots:
    /**
     * @brief set camera width, height, framerate, connect and pub image data with protobuf
     * 
     * @param cameraInfo 
     */
    void setCamera(const QCameraInfo &cameraInfo);

private:
    /**
     * @brief check resolution supported
     * 
     * @return true 
     * @return false 
     */
    bool isGivenResolutionSupported();
    std::string supportedResolutionsList();

    // qt camera related
    QScopedPointer<QCamera> camera_;
    QScopedPointer<QCameraImageCapture> imageCapture_;

    // ecal publisher with protobuf msgs
    eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher_;

    // camera image info
    std::string cameraName_;
    uint16_t width_;
    uint16_t height_;
    size_t photosTaken_;

signals:
    void photoSentSignal();
};
