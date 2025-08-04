#!/bin/bash

#A simple script to display basic Linux system specifications.

# Function to print a formatted header
print_header() {
    echo
    echo "==================================================="
    echo "$1"
    echo "==================================================="
}

# Function to get Operating System Information
get_os_specs() {
    print_header "Operating System Information"
    # 'uname -a' -> kernel information
    uname -a
    echo
    if [ -f /etc/os-release ]; then
        cat /etc/os-release
    else
        echo "OS release information not found in /etc/os-release."
    fi
}

# Function to get CPU Information
get_cpu_specs() {
    print_header "CPU (Processor) Information"
    # 'lscpu' -> CPU architecture
    lscpu
}

# Function to get Memory (RAM) Information
get_memory_specs() {
    print_header "Memory (RAM) Information"
    # 'free -h' shows memory usage in a human-readable format
    free -h
}

# Function to get Disk Usage Information
get_disk_specs() {
    print_header "Disk Storage Information"
    # 'df -h' shows disk usage for all mounted filesystems in a human-readable format
    df -h
}

# Function to get GPU Information
get_gpu_specs() {
    print_header "GPU (Graphics Card) Information"
    # 'lspci' lists all PCI devices. We filter for graphics-related terms.
    lspci | grep -i 'vga\|3d\|display'
}

# Function to get Network Information
get_network_specs() {
    print_header "Network Information"
    # 'ip addr'-> network interfaces and addresses
    ip addr
}


# Main script execution
# Clear the screen for a clean report
clear

echo "Gathering Linux System Specifications..."
echo "Generated on: $(date)"

# Call all the functions to generate the report
get_os_specs
get_cpu_specs
get_memory_specs
get_disk_specs
get_gpu_specs
get_network_specs

# Add a final message
echo
echo "--- End of Report"
echo