An IoT-based smart shopping cart system using ESP32-CAM module and Wi-Fi
for automated billing in supermarkets.

---

## 📌 Project Overview
This project aims to automate the billing process in shopping malls
using IoT technology. Each product is associated with an RFID tag,
and the cart scans items automatically to calculate the total bill.

## 📸 Project Images

### Web Page
<img src="IoT webpage.jpeg" alt="Web Page" width="500"/>

### System Model
<img src="Iot Model.jpeg" alt="System Model" width="500"/>

### IoT Connection
<img src="IoT connection.jpeg" alt="IoT Connection" width="500"/>


---

## 🎯 Objectives
- Reduce checkout waiting time
- Automate billing process
- Improve shopping efficiency using IoT

---

## 🛠 Hardware Components
- ESP32-CAM
- ESP 32
- RFID Tags
- LCD Display

---

## 💻 Software Components
- Arduino IDE
- Embedded C / Arduino Programming
- MySQL for database
- php for frontend and database integration
- html, CSS and Javascript

---

## ⚙️ Working Principle
1. Products contain RFID tags
2. ESP 32 CAM module scans the product
3. ESP32 processes product data
4. Price is displayed on LCD
5. Billing data is sent over Wi-Fi

---

## 🌐 IoT & Networking Concepts Used
- Wi-Fi Communication
- Client–Server Architecture
- TCP/IP Protocol
- Real-time Data Transfer

---

## 📂 Project Structure
iot-based-smart-shopping-cart/
├── README.md
├── hardware/
│ ├── components_list.txt
│ └── circuit_diagram.png
├── software/
│ ├── cart_controller.ino
│ └── server_code.py
├── architecture/
│ └── system_architecture.png
├── screenshots/
│ ├── lcd_display.jpg
│ └── output_screen.png
├── demo/
│ └── demo_video_link.txt
└── report/
└── smart_shopping_cart_report.pdf

---

## 🎥 Project Demonstration

(https://youtube.com/shorts/Amb7axc3yww?si=_SnB9IrceqsSALrs)

📝 Note: This demo video does not contain audio.  
On-screen text has been added to explain the working of the project.

## 💻 Source Code
The main controller code for the smart shopping cart is available in the
`software/cart_controller.ino` file. It handles RFID scanning, bill
calculation, LCD display, and Wi-Fi communication.

📝 Note: The frontend files are static and shown for demonstration purposes only.

## 🗄️ Database Design (SQL)
The project uses an SQL database to store product information and billing
details. The database schema and queries are available in the
`software/database/smart_cart.sql` file.
---

## 🚀 Future Enhancements
- Mobile application integration
- Cloud-based billing
- Inventory management system

