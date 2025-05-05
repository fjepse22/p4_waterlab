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
#[how to run this script] in the terminal: use the command sudo`python3 script.py`(remember to run it in the same directory as the script and pcapng file)
