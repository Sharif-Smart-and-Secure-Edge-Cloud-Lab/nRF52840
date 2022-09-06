# zigbee gateway

in this project we are going to create a zigbee gateway. this gateway must initiate the zigbee network, communicate with the connected devices, and send their data to the server. In this project, we are going to use nRF 52840 dk, nRF 52840 dongle and orange pi zero plus
from the zigbee introduction, it is obvious that the gateway must work as a zigbee coordinator. Due to the fact that nRF52840 doesn't support wifi connection, orange pi zero plus does handle the connection to the server.
this project can be divided into several parts: zigbee network configuration, zigbee network co processor app development, connection to the server from clients, and server side task handling.

## zigbee network configuration

first thing first it is needed to find a way to implement the network coordinator. zigbee network co-processor (zigbee NCP) does handle the whole network processors as well as drive RF transceivers. in order to implement a zigbee NCP there must be a zigbee supporting device available. Nordic Semiconductor developed some good boards for this goal. nRF52840 module (dk and dongle) can support different protocol stacks like Thread, Zigbee, ANT, etc. in addition, Nordic offers these modules with fairly affordable price. ( you can buy a nRF52840 dongle for only 10$. come on!! it only costs you two meals ordering a big mac from your neighborhood MacDonald's :joy::rofl:)
nRf52840 provides a powerful tool to implement a zigbee network. there are plenty of useful examples. For getting to know the module it is recommended that the basic examples like "hello_world", "Blinky", or "Threads" be demonstrated. Nordeic provides 3 zigbee examples: network_coordinator, light_bulb, light_switch; which are really useful. the thing is these zigbee examples are totally standalone and they are only running on the nRF chip. Therefor, there is no user specified functionality after the built file gets flashed on the module. This characteristic isn't the ideal for this project, because the desired functionalites mostly come from the server in a real time manner. Fortunately, Nordic provides a solution for this usage. NCP (Network Co-Processor) is the solution. The idea comes from the fact that a processor is needed to handle the whole zigbee protocol stack right till the Application layer, and let you program the application layer so you can control the zigbee network real time. this acan be done by having a processor handling the zigbee protocol stack and ;et you connect to the processor to send commands on the desired functionalities by the use of other communication protocols like UART, USB, etc. NCP provides such a thing. in this example, the whole protocol stack breaks into two parts. the zigbee stack can be built like a hex file etc. that can be flashed to the nRF52840 and the desired functionalities can be implemented by a C programming communicating with the processor through UART or USB (That's cool :blush::smile:). For your more information on different zigbee architecture and NCP, take a look at [this link](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_zigbee_architectures.html#ug-zigbee-platform-design-ncp-details) 

![architecture](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/architecture.jpg)

 #### for information on how to use and run SoC based architecture take a look at this [link](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/tree/farbod-yadollahi/nRF%20connect). just use the zugbee examples like light bulb or network coordinator examples.
 [Here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/samples/zigbee/ncp/README.html) you can find the step by step process of running a demo. 
As mentioned, the processor side is called NCP and the host side is called NCPHost. below you can find the connection diagram. 

![NCP connection](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/2022-08-22_14-38-14.jpg)
 
 For this demonstration you first need to download and extract the [ZBOSS NCP Host zip file](https://developer.nordicsemi.com/Zigbee/ncp_sdk_for_host/ncp_host_v2.2.0.zip). For NCP side, you can rely on the nRF connect SDK you had installed before. (seems easy ha? :smiling_imp: wait for getting excruciatingly stuck building the application :nerd_face: :smirk:). There you need to open VScode and create a new NCP application. so you need to specify a location to save the application as well as a name for it. Then the next step will be building the applicatin you just created. Here the configurations are really really important ( a single mistake results in struggle).
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
 
$ nrfjprog --program ncp_fw/<firmware> --chiperase
$ nrfjprog --program ncp_fw/<firmware> --reset
 
 ```
and for nRF52840dongle use :
```

$ sudo nrfutil dfu usb-serial -pkg ncp_fw/ncp.usb.nrf52840dongle_nrf52840.zip -p /dev/ttyACMx

```
and for that x in the ttyACMx I'll explain in the board connection part

some notes:
1. for using "nrfjprog" you need to install nRF commandline tools. [here](https://github.com/bus710/nrf-development-in-linux) is how to install that:

```
$ wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/Desktop-software/nRF-command-line-tools/sw/Versions-10-x-x/10-13-0/nRF-Command-Line-Tools_10_13_0_Linux64.zip
$ unzip nRF-Command-Line-Tools_10_13_0_Linux-amd64.zip -d tools

$ cd tools/nRF-Command-Line-Tools_10_13_0_Linux64
$ tar xvf nRF-Command-Line-Tools_10_13_0_Linux-amd64.tar.gz 
$ sudo dpkg -i JLink_Linux_V750b_x86_64.deb
$ sudo dpkg -i nRF-Command-Line-Tools_10_13_0_Linux-amd64.deb

```
2. nrfutil is a python package so you should go through [this](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrfutil%2FUG%2Fnrfutil%2Fnrfutil_installing.html):

```
$ pip install nrfutil

```

### board connection:

#### nRF52840dk:
For connecting nRF52840dk you need two USB cables. the first one should be connected to the J2 port of the board (external supply). the second one must be connected to the nRF USB. the first one works as the power source of the board while the second one is used for the communication between the NCP firmware on the board and the NCP Host applicaton on the linux ( or orange pi etc.). For programming the board using "nrfjprog" you need to use the J2 infos. 
now you need to know the communication interface of your host. For that you need to do this:
```

$ sudo dmesg -w

```
if the board has been programmed well then the output of the above command is:

![board2](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/board%20connection%202.jpg)

remmember the ttyACM numbers. the Jlink one is asociated to the J2 connector and the zigbee NCP one is associated with the nRF USB connector.


#### nRF52840 dongle:
nRF52840 dongle can only support USB connection. therefore the connection is simple. you just plug in your dongle to a USB port like other USB devices of yours. Like before, you need to find the communication interface:
```

$ sudo dmesg -w

```
and if the board connects properly the resultant output will be like this:

![board3](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/board%20connection%203.jpg)

And again remmember the ttyACM number.
if the computer can't detect dongle try uninstalling the device in the device manager.

### running the application
Now the next step is to run the application. nordic application layer development uses C language. Nordic provides a platform for DSR ZBOSS zigbee stack SDK. [here](https://dsr-zboss.com/#!/) you can find information about ZBOSS. Nordic provides bunch of application samples for ncp architecture including simple_gw, light_bulb, dimmable_light etc.
To run a ncp architecture examples, you need to build the library first. for that, you need to go to the src directory of the ncp Host zip file. Then use these command to build the libraries:
```

$ make rebuild make zbosses

```
Then get back to the ncp Host directory ( one dirctory above src) and use:
```

$ make 

```
to build the applications. Then go  to "ncpHost/application" to see the available applications. here we use simple_gw so the directory would be "ncpHost/application/simple_gw" here run the below code:
```

$ sudo NCP_SLAVE_PTY=/dev/ttyACMx ./<simple_gw>

```
Running the above command creates log files in the directory at which it run. you can open the log files by many ways. one of them is:
```

$ tail -f <log_file_name>

```

unfortunately the ZBOSS libraries could not be built on opi zero plus. some processor architecture assertion failure caused the problem. It seems there is a problem with cross compiling issues. 
#### testing
For testing, you can run a single protocol SoC architecture light bulb example on one of the nRF52840 dk using vscode. The steps are:
1. run the simple_gw example
2. run the light bulb example
3. LED 1 of light bulb starts blinking indicating that its main thread is running
4. when the light bulb connects to a zigbee network, then LED 3 turns on;
5. LED 4 on the light bulb is the original bulb. meaning that whatever command gateway sends, LED 4 gets effected.

![dongle_dk](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/dongle-dk.jpg)

![dk-dk](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/dk-dk.jpg)

you can use your creativity to furthur design tests bu the use of available examples like you can use light switch and light bulb connecting to the gateway.

![b-s-g](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/b-s-g.jpg)

[here](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/tree/farbod-yadollahi/ncp/result%20videos) you can find some videos of the demonstrations.
### adding clusters:
[here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_zigbee_adding_clusters.html) is how you can add a new  cluster to the gateway the codes are:( make sure to add them in an appropriate place in the simple_gw.c)
``` c
#include <addons/zcl/zb_zcl_temp_measurement_addons.h>


struct zb_device_ctx {
        zb_zcl_basic_attrs_t            basic_attr;
        zb_zcl_identify_attrs_t         identify_attr;
        zb_uint8_t                      on_off_switch_type_attr;
        zb_uint8_t                      on_off_switch_actions_attr;
        zb_zcl_temp_measurement_attrs_t temp_measure_attrs;
};


ZB_ZCL_DECLARE_TEMP_MEASUREMENT_ATTRIB_LIST(temp_measurement_attr_list,
                                            &dev_ctx.temp_measure_attrs.measure_value,
                                            &dev_ctx.temp_measure_attrs.min_measure_value,
                                            &dev_ctx.temp_measure_attrs.max_measure_value,
                                            &dev_ctx.temp_measure_attrs.tolerance);

```
``` c
ZB_HA_DECLARE_TEMPERATURE_SENSOR_CLUSTER_LIST(temperature_sensor_clusters, basic_attr_list, identify_attr_list, temp_measurement_attr_list);
```
``` c
#define TEMPERATURE_SENSOR_ENDPOINT  12

ZB_HA_DECLARE_TEMPERATURE_SENSOR_EP(temperature_sensor_ep, TEMPERATURE_SENSOR_ENDPOINT, temperature_sensor_clusters);
```
``` c

ZBOSS_DECLARE_DEVICE_CTX_3_EP(app_template_ctx, temperature_sensor_ep, on_off_switch_ep, app_template_ep);

```
[here](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/tree/farbod-yadollahi/ncp/simple_gw_1) is the link to the added cluster gw code.

### connectivity of sensors to the gateway
here we try to connect the available zigbee devices to the gateway. there are two temperature sensors of xiaomi and sonoff co. being used. To do that we long press the only available buttons on the sensors for 5 second, so the built in led on them blinks three time. here the sensors enter pairing mode. then we run the gatewway app and observe the generated logs for any useful information corresponding to the sensors' connectivity. there can be a tinge of evidence rgarding the fact that the sensors do get conneted to the gateway but they are not satisfyingly acceptable. No transfered data has been written in the logfile. so we go through checking the connectivity of the sensor to the sonoff gateway. here we used the eWeLink android app to monitor and control the network:
sonoff gateway:
![sonoff_gateway](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/sonoff%20gateway.jpg)

gateway and sensors:
![gw_and_sensors](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/gw%20and%20sensors.jpg)

user interface:
![gw_sensor_connectivity](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/gw%20s%20connectivity.jpg)

then we tried to see the transfered data between different sonoff's gateway modules on osciloscope but nothing has been shown. it seems that either the transfer media differ or the rate of transfer is so low.
to solve this problem we tried to implement zigbee sniffer to sniff zigbee packets all around. for this, go through the below [procedure](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_sniffer_802154%2FUG%2Fsniffer_802154%2Fintro_802154.html):
1. installing the sniffer firmware: here is the [link](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_sniffer_802154%2FUG%2Fsniffer_802154%2Fintro_802154.html).
2. configuring wireshark: here is the [link](https://infocenter.nordicsemi.com/topic/ug_sniffer_802154/UG/sniffer_802154/installing_sniffer_802154_linux.html).
 [here](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/datasheets/nRF_Sniffer_802154_User_Guide_v0.7.2.pdf) you can find the whole compact procedure.
 then open the wireshark and with the nRF interface determine the channel to receive the packets.
 unfortunately we couldn't receive any packets in any channel so we tried to check whether the  RF module works properly; therefore, Bluetooth LE implementation was what we did next.
  To implement bluetooth LE sniffer follow this[Link](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/datasheets/nRF_Sniffer_BLE_UG_v4.1.0.pdf).
  you can find the received packets [here](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/ble.pcap).
  ![ble_pcap](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/ncp/blepcap.jpg)
  
  ##### data acquisition
  you can find some useful information on how to read data from the zigbee devices in the links below. there you can find some API  and code snippets to read data. these codes should be added to the gateway code.
  1. [first link](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsdk_tz_v4.1.0%2Fusing_zigbee__z_c_l.html&cp=7_3_3_4&anchor=cluster_declaration_custom)
  2. [second link](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsdk_tz_v4.1.0%2Fzigbee_prog_principles.html&anchor=zigbee_stack_memory_mgmt)
 
 
 
## connection between opi and the server
in this part we are using mqtt to handle messaging between the opi and the server 
MQTT (Message Queuing Telemetry Transport) is a publish/subscribe messaging protocol that works on top of the TCP/IP protocol. The first version of the protocol was developed by Andy Stanford-Clark of IBM and Arlen Nipper of Cirrus Link in 1999. What makes MQTT faster than say sending HTTP requests with your IoT device is MQTT messages can be as small as 2 bytes, whereas HTTP requires headers which contains a lot of information that other devices might not care about. Also, if you have multiple devices waiting for a request with HTTP, you'll need to send a POST action to each client. With MQTT, when a server receives information from one client, it will automatically distribute that information to each of the interested clients.
first we go through handling the situation using command line. first it is needed to have the mqtt dependencies installed on the machine:

```
$ sudo apt install mosquitto mosquitto-clients

```
then you can simply use the below command to subscribe to a topic:
```

$ mosquitto_sub -h HOST -t "<topic>"

```
for publishing a message you can use:

```
$ mosquitto_pub -h Host -m "ON" -t "<topic>"

```

for handling the requests and saving them we need to use sql.SQL stands for Structured Query Language. SQL is used to create, remove, alter the database and database objects in a database management system and to store, retrieve, update the data in a database. SQL is a standard language for creating, accessing, manipulating database management system. you can use this [link](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/sql/server.sh) to get to know the sql commands.


as this commandline api doesn't work as expected it is great to have mosquitto and sql merged together in a c file. the mosquitto side is implemented in c to add functionality of using sql in it. for sql side we use some bash snippets which are run by the c program. to install sql:
```

$ wget -c https://repo.mysql.com//mysql-apt-config_0.8.13-1_all.deb
$ sudo dpkg -i mysql-apt-config_0.8.13-1_all.deb 
$ sudo apt-get install mysql-server
$ sudo systemctl start mysql.service

```
you can find the c codes for publishing and subscribing [here](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/tree/farbod-yadollahi/mqtt/mqtt1/mqtt)

to run the subscriber side, run this command in the appropriate directory:
```
$ sudo ./mqtt_sub
```
then on the orange pi go to the appropriate directory and run the below command. make sure that the message.txt have information. for a sample example you can use the data in message2.txt and copy them to message.txt if message.txt is empty. it is the message.txt being used while the mqtt is running.

```
$ ./mqtt_pub
```
here you can find the result:

![opiAndUbuntu](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/mqtt/mqtt1/mqtt/results/opi%20and%20ubuntu.jpg)
here you can find the sql side:

![sql](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/mqtt/mqtt1/mqtt/results/sql.jpg)

to see the result videos refer o this [link](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/mqtt/mqtt1/mqtt/results/VID_20220906_170106_692.mp4)


  
  









