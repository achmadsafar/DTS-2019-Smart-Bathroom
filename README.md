# DTS-2019-Smart-Bathroom
Final Project Digitalent Scholarship 2019 about smart bathroom

Smart Bathroom is IoT for helping user for monitoring, controling environment in bathroom using two microcontroller ESP32. For monitoring i measure temperature using LM35 and water discarge using ultrasonic sensor.then can control two tap water, for bathtub and shower. tap water can control using IoT Platfrom Blynk and shower using ultrasonic, just standing in front of the sensor with a predetermined distance. i use stepper motor for open tap water. there should be using another actuator but i just have stepper so it can replace with better actuator. communication that i used from ESP32 to blynk for storing data temperature and debit is WiFi module and protocol MQTT
and Node-Red for gateway, here is the rule chain : 
![Node red](https://user-images.githubusercontent.com/17356265/64408311-9d191900-d0b0-11e9-9ee2-22eaed0eba40.PNG)
