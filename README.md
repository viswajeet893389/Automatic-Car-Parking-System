# Automatic-Car-Parking-System


Software model made in proteus:

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/d5efc9b9-e7c4-4ec5-99a9-03b0ca3dc23b)

**Working**

1. The password is entered in the virtual terminal (or the RFID tag is scanned over RFID reader).

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/dca47f56-f5b9-44a9-9826-2b386c12ed34)

2. The 8051 microcontroller checks whether that password is stored in the database or not. If the password matches with the password entered by the user, the motors, which are connected with the output pins of the 8051 microcontroller, rotates clockwise.

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/cd4355a5-c36d-4efe-9eb1-c83adb6a44f2)

3. After some delay the motor rotates anticlockwise indicating closing of gate, simultaneously the LCD displays the strings like “Door Closing”, “Door Opening” etc. while the whole operating takes place. 

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/6e8bbc68-4833-43ce-bbd2-75ee9bae6761)

4.  LCD shows the number of empty slots. 

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/083b7c59-21b3-4f79-a99f-8dc7065fd0b2)

5. If the password doesn’t match with the one entered by the user and in the database, then the motor doesn’t rotate and a string is displayed “Outside Person No Slot For You”.

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/3f5553ac-c9e2-4520-9af4-55f7d696d03d)

6. When the car is going outside then the driver has to show the RFID tag again to authorize that he is the proprietor of car. If the password matches then the Exit Gate opens and after that closes.

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/f235b145-4e7a-41e8-8662-66f7f89b277a)

7. LCD shows the updated number of empty slots.

![image](https://github.com/viswajeet893389/Automatic-Car-Parking-System/assets/67750747/54cc34c8-182b-436c-a7f8-81bc34910421)






