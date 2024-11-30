<h1 align ='center'>Object Following Robot Using Vision </h1>

## Demonstration Video
### [Click Here](https://youtu.be/8Woyg90sMEw) to see the video on youtube.

# About
We have developed and submitted the Object Following Robot Using Vision as our project for the Control System Engineering Lab. 

## Technologies
We have used Arduino, Computer Vision, Webcam and Bluetooth modules for this project.

## Range
The range of its tracking is more than eight meters.

## Use cases
We can use this kind of robot in a wide range of areas such as - Human Following shopping cart, transporting medical equipment or patients at the hospitals, Inventory management by automatically tracking, transporting crops, soil, or other materials around a farm or greenhouse, etc.


We're thrilled with the results of our project and look forward to making it more sophisticated.

# Coding Part
## Image Processing
[This Notebook](https://github.com/shahriar193/Object-following-robot-using-computer-vision/blob/main/test_v3.ipynb) is for image processing which track the target object and gets its coordintes, then send it to the bluetooth module

## Arduino Coding
[This](https://github.com/shahriar193/Object-following-robot-using-computer-vision/blob/main/arduino/with_l298n/with_l298n.ino) is our Arduino coding part which received the coordinate from bluetooth module and make the motors to follow that coordinate.
