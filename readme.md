# eCAL Learning Note

## Introduction

-   eCAL (**e**nhanced **C**ommunication **A**bstraction **L**ayer) 

-   publish-subscribe middleware

    -   inter-process: **Shared memory**
    -   inter-host: **UDP/TCP**

    

## Resources

-   [Homepage](https://eclipse-ecal.github.io/ecal/)
-   [Github](https://github.com/eclipse-ecal/ecal)



## Install

-   Install on Ubuntu

    ```bash
    # install latest version
    sudo add-apt-repository ppa:ecal/ecal-latest
    sudo apt-get update
    sudo apt-get install ecal
    
    # install 5.11
    sudo add-apt-repository ppa:ecal/ecal-5.11
    sudo apt-get update
    sudo apt-get install ecal
    ```

    

## Samples

-   Topic 传输

    -   ecal_sample_person_snd/rec

        ```bash
        # 发送节点: 发送person信息
        ecal_sample_person_snd
        
        # 接受节点: 接受person信息
        ecal_sample_person_rec
        ```

    -   同一发布节点开启多次, 会在同一topic下发布不同节点的内容
    -   同一接受节点开启多次, 也会接受同一topic下不同内容



-   Service 传输

    -   ecal_sample_math_server/client

        ```bash
        # server: 负责接受数学计算的请求和提供数学计算
        ecal_sample_math_server
        
        # client: 负责发出数学计算的请求和接受结果
        ecal_sample_math_client
        ```

    -   同一server节点开启多次, 都会接受到对应service topic的请求

    -   同一client开启多次, 也会与同一名字的server连接





## Applications

-   eCAL Monitor

    -   show topics, msgs, processes, hosts, services, log, system infos, configs ...

        ```bash
        # start ecal monitor
        ecal_mon_gui
        ```

        

-   eCAL Recorder

    -   record data through eCAL network

        -   centralized recording
            -   record all topics on main machine
        -   distributed recording
            -   each machine  record its own topics

    -   save data as HDF5 format

    -   ```bash
        # start eCAL Recorder
        ecal_rec_gui
        ```

        

-   eCAL Player

    -   play recorded data

    -   ```bash
        # start eCAL player
        ecal_play_gui
        
        # 配合 ecal_mon_gui 查看数据
        ```

        

-   eCAL Sys

    -   an application for starting, stopping and monitoring applications on one or multiple machines.

    -   ```bash
        # start ecal_sys_gui
        
        ```

        

## Development - C++

### Dependencies

-   ```bash
    sudo apt install cmake g++ libprotobuf-dev protobuf-compiler
    ```

    

### Hello World

-   example: helloworld_puber.cpp
-   example: helloworld_suber.cpp



### Hello World with protobuf

-   example: helloworld_proto_puber.cpp
-   example: helloworld_proto_suber.cpp