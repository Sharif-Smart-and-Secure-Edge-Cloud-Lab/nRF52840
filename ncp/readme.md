# zigbee gateway

in this project we are going to create a zigbee gateway. this gateway must initiate the zigbee network, communicate with the connected devices, and send their data to the server. In this project, we are going to use nRF 52840 dk, nRF 52840 dongle and orange pi zero plus
from the zigbee introduction, it is obvious that the gateway must work as a zigbee coordinator. Due to the fact that nRF52840 doesn't support wifi connection, orange pi zero plus does handle the connection to the server.
this project can be divided into several parts: zigbee network configuration, zigbee network co processor app development, connection to the server from clients, and server side task handling.

## zigbee network configuration

first thing first it is needed to find a way to implement the network coordinator. zigbee network co-processor (zigbee NCP) does handle the whole network processors as well as drive RF transceivers. in order to implement a zigbee NCP there must be a zigbee supporting device available. Nordic Semiconductor developed some good boards for this goal. nRF52840 module (dk and dongle) can support different protocol stacks like Thread, Zigbee, ANT, etc. in addition, Nordic offers these modules with fairly affordable price. ( you can buy a nRF52840 dongle for only 10$. come on!! it only costs you two meals ordering a big mac from your neighborhood MacDonald's :joy::rofl:)
nRf52840 provides a powerful tool to implement a zigbee network. there are plenty of useful examples. For getting to know the module it is recommended that the basic examples like "hello_world", "Blinky", or "Threads" be demonstrated. Nordeic provides 3 zigbee examples: network_coordinator, light_bulb, light_switch; which are really useful. the thing is these zigbee examples are totally standalone and they are only running on the nRF chip. Therefor, there is no user specified functionality after the built file gets flashed on the module. This characteristic isn't the ideal for this project, because the desired functionalites mostly come from the server in a real time manner. Fortunately, Nordic provides a solution for this usage. NCP (Network Co-Processor) is the solution. The idea comes from the fact that a processor is needed to handle the whole zigbee protocol stack right till the Application layer, and let you program the application layer so you can control the zigbee network real time. this acan be done by having a processor handling the zigbee protocol stack and ;et you connect to the processor to send commands on the desired functionalities by the use of other communication protocols like UART, USB, etc. NCP provides such a thing. in this example, the whole protocol stack breaks into two parts. the zigbee stack can be built like a hex file etc. that can be flashed to the nRF52840 and the desired functionalities can be implemented by a C programming communicating with the processor through UART or USB.(That's cool :blush::smile:). [Here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/samples/zigbee/ncp/README.html) you can find the step by step process of running a demo. 
As mentioned, the processor side is called NCP and the host side is called NCPHost. below you can find the connection diagram. 

![NCP connection](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/2022-08-22_14-38-14.jpg)
 
 For this demonstration you first need to download and extract the [ZBOSS NCP Host zip file](https://developer.nordicsemi.com/Zigbee/ncp_sdk_for_host/ncp_host_v2.2.0.zip). For NCP side, you can rely on the nRF connect SDK you had installed before. (seems easy ha? :smiling_imp: wait for getting excruciatingly stock building the application :nerd_face: :smirk:). There you need to open VScode and create a new NCP application. so you need to specify a location to save the application as well as a name for it. Then the next step will be building the applicatin you just created. Here the configurations are really really important ( a single mistake results in struggle).
 steps to follow for nRF52840 dk:
 ##### 1. choose your board:
 here you need to choose the board with which you are working.
 ###### don't try to choose nRF52840 dongle here. nRF52840 dongle has no debugger on it. In addition, it doesn't support J-Link. FIY, VScode can't detect modules that don't support J-Link.
 
 ![choosing board](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/ch%20b.jpg)
 
 ##### 2. choosing configuration:
 here you need to choose the configuration. For NCP there exist two configurations: prj.conf and prj_usb. conf. Depending on your NCP and NCP Host connection medium, you need to choose the configuration. Prj.conf configures a UART medium while prj_usb.conf does that for usb. My experience shows that the proj.conf has a problem building. I can't at least find a solution to getting this conf file work fine. in the middle of building, it generates an error declaring that a header file can't be found. adding that header file to the compiler path and cmake file didn't work. Thus i firmly recommend you using the USB medium instead of UART and choose prj_usb. conf as the configuration  for your convenience.
 ###### nRF52840dk supports UART and USB. nRF52840 dongle only supports USB.
 
 ![configuring board](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/config.jpg)
 
 now you can hit that "build configuration" button to have your application built. Hopefully, you can see that the building process has finished great.
 
 ##### 3. flash the board:
 the last step after building the application is to flash it on the board.
 
 if all the above steps work fine, then you have your nRF52840 programmed to handle the zigbee network specifications
 
 ##### alternatively you can rely on that NCP Host file you have downloaded. In it, you can find a pre built firmware for some boards in the ncp_fw directory. using this, you can program both the nRF52840dk and nRF52840dongle through the terminal but with different syntax
 
  here is the files contained in the ncp_fw directory:
  
 ![ncp_fw](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/ncp_fw.jpg)
 
 For nRF52840dk communicating through UART use "ncp.nrf52840dk_nrf52840.hex", For nRF52840dk communicating through USB use "ncp.usb.nrf52840dk_nrf52840.hex", and for nRF52840 dongle use "ncp.usb.nrf52840dongle_nrf52840.zip".
 for programing the boards through command line use this [link](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/zboss/3.11.2.0/zboss_ncp_host.html)

 For nRF52840 dk use this command:
 
 ```
 
 nrfjprog –program ncp_fw/<firmware> –chiperase –reset
 
 ```
and for nRF52840dongle use :
```

nrfutil dfu usb-serial -pkg ncp_fw/ncp.usb.nrf52840dongle_nrf52840.zip -p /dev/ttyACMx

```
and for that x in the ttyACMx I'll explain in the board connection part
