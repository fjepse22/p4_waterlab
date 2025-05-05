import subprocess
import time

command = ["tcpreplay", "-i", "enp4s0", "modbus_attack.pcapng"]

while True:
    result = subprocess.run(command)
    
    # Check for errors
    if result.returncode != 0:
        print("Error running tcpreplay. Exiting...")
        break

    time.sleep(1)  # Optional delay between replays
