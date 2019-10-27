# YawYaw

### What is YawYaw?
YawYaw is a "Looky-Loo" pan and tilt camera harness designed to be mounted onto a variety of unmanned vehicles, such as UAV's, drones, and UGV's. With its built in motor array, it will provide users with a robust way to virtually interact with the surrounding environment. The easy user interface provides a hands-free solution to pan/tilt by utilizing a sensor array to track the movements of the user's head.

### How does it work?
YawYaw uses a Teensy 4.0 microprocessor to communicate with the LSM9DS1 IMU over SPI. With this data, it calculates the required power for the motors to correct their position using PID Controllers.
