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

#include "camera_wrapper.h"

/**
 * @brief class CameraWrapperWithFpsControl
 * 
 */
class CameraWrapperWithFpsControl : public CameraWrapper
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Camera Wrapper With Fps Control object
     * 
     * @param publisher 
     * @param camera_name 
     * @param width 
     * @param height 
     * @param maxFps 
     */
    CameraWrapperWithFpsControl(
        eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
        std::string &camera_name, uint16_t width, uint16_t height,
        uint16_t maxFps);

    /**
     * @brief Destroy the Camera Wrapper With Fps Control object
     * 
     */
    ~CameraWrapperWithFpsControl();

    /**
     * @brief capture
     * 
     */
    void capture();

private:
    qint64 frameIntervalInMs;
    qint64 lastFrameTimestamp;
};