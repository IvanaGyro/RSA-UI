RSA-UI
==
- [RSA-UI](#rsa-ui)
  - [Usage](#usage)
    - [**Set the length of the key**](#set-the-length-of-the-key)
    - [**Generate a key**](#generate-a-key)
    - [**Encrypt and decrypt**](#encrypt-and-decrypt)
  - [Licence](#licence)

![User Interface](https://i.imgur.com/X7zRy92.png)

This is a simple RSA implementation with the bigint library written on my own. The library is less effective, so it takes a lot of time to generate a pair of RSA keys.

Usage
---
1. [**Set the length of the key**](#set-the-length-of-the-key)
2. [**Generate a key**](#generate-a-key)
3. [**Encrypt and decrypt**](#encrypt-and-decrypt)
 


### **Set the length of the key**
If the radio buttons in the top-left corner is not changed after opening the form, the length of the key is **128 bits** ignoring that 1024 is checked. Users can check the radio buttons to change the setting of the key length. However, the key will not be regenerated until clicking the **Generate the key** button.

### **Generate a key**
Just click the **Generate the key** button. After generating the key, the two big prime numbers used to generate the key will be displayed in the textarea labeled P and Q in decimal form.

### **Encrypt and decrypt**
Enter the text will be encrypted into the **Plaintext** textarea and press **->** button. The encrypted text will be showed in **Ciphertext** textarea. And then, pressing the **<-** button, the ciphertext will be decrypted and the result will be showed in the **Plaintext** testarea.

Licence
---
This project is released by **GPLv3**.
