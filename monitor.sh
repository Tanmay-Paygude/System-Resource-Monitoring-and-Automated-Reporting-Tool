
#!/bin/bash

# Function to get CPU usage
get_cpu_usage() {
  top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}'
}

# Function to get memory usage
get_memory_usage() {
  free | grep Mem | awk '{print $3/$2 * 100.0}'
}

# Function to get disk usage
get_disk_usage() {
  df -h | grep '/dev/sda1' | awk '{print $5}' | sed 's/%//'
}

# Monitor system every minute
while true; do
  CPU=$(get_cpu_usage)
  MEMORY=$(get_memory_usage)
  DISK=$(get_disk_usage)

  echo "CPU Usage: $CPU%"
  echo "Memory Usage: $MEMORY%"
  echo "Disk Usage: $DISK%"

  echo "$CPU\n$MEMORY\n$DISK" > system_metrics.txt

  sleep 60
done
