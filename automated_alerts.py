
import smtplib
from email.mime.text import MIMEText
import time

CPU_THRESHOLD = 80
MEMORY_THRESHOLD = 75
DISK_THRESHOLD = 85

ALERT_EMAIL = "admin@example.com"
SMTP_SERVER = "smtp.example.com"
SMTP_PORT = 587
SMTP_USER = "alert@example.com"
SMTP_PASS = "your_password"

def send_alert(subject, message):
    msg = MIMEText(message)
    msg['Subject'] = subject
    msg['From'] = SMTP_USER
    msg['To'] = ALERT_EMAIL

    with smtplib.SMTP(SMTP_SERVER, SMTP_PORT) as server:
        server.starttls()
        server.login(SMTP_USER, SMTP_PASS)
        server.sendmail(SMTP_USER, ALERT_EMAIL, msg.as_string())

def read_system_metrics():
    with open("system_metrics.txt", "r") as file:
        cpu_usage = float(file.readline().strip())
        memory_usage = float(file.readline().strip())
        disk_usage = float(file.readline().strip())
    
    return cpu_usage, memory_usage, disk_usage

def monitor():
    while True:
        cpu_usage, memory_usage, disk_usage = read_system_metrics()
        
        if cpu_usage > CPU_THRESHOLD:
            send_alert("High CPU Usage Alert", f"CPU usage exceeded: {cpu_usage}%")
        
        if memory_usage > MEMORY_THRESHOLD:
            send_alert("High Memory Usage Alert", f"Memory usage exceeded: {memory_usage}%")
        
        if disk_usage > DISK_THRESHOLD:
            send_alert("High Disk Usage Alert", f"Disk usage exceeded: {disk_usage}%")
        
        time.sleep(60)

if __name__ == "__main__":
    monitor()
