# PREPARING VScode
After VS code extentions are installed, it can be configured. By the use of *Nordic Tab in VScode*, which has been added after the installation of the pack, you can find the welcome page.
There exists quick setup part. there you need to browse for the toolchain manager path and nRF connect SDK. After setting up these parts, you can go for the first app of yours run on the board.

![alt text](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/nRF%20connect/setup.jpg)

# CREATING THE APP

First we need to create an app. In the welcome page click on *create a new application from sample...* if it is the first time creating an app. if you created an app previously, you can use the *add an existing application* option to open your previous app.

![alt text](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/nRF%20connect/create%20app.jpg)

then the below fields apear. you need to fill the fields with appropriate information. It is recommended thet you have your board connected to the PC.
Avove there exist to options, you can go for the *freestanding* one. This option works when the SDK is preinstalled. 
There you can still find the SDK installation INFOs. Then you need to name the app and place its location. The remaining field provides built-in example apps. here we use Blinky built-in app which turns LED1 on and off every second.  

![alt text](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/nRF%20connect/app%20fields.jpg)

![alt text](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/nRF%20connect/built%20in%20apps.jpg)

# BUILDING CONFIGURATION
After the previous part, now we need to build a configuration. the output here will be a build folder in the specified directory
the previous part creates some additional files which are used to create the build file here in this step.these files are as follows:

![alt text](https://github.com/Sharif-Smart-and-Secure-Edge-Cloud-Lab/nRF52840/blob/farbod-yadollahi/nRF%20connect/app%20files.jpg)

Here it is really crucial to have the previous steps done correctly. I myself encountered some randomized problem with CMAKE  that i still don't know how to solve them or how they can be solved. these problems occured randomly and solved randomly, too. These problems result in the build process not going properly
for creating build files there exist a icon next to the application where the build fields can be visible there. it is like below:


