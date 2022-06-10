import os
import shutil

drives = [chr(x) + ":" for x in range(65, 91) if os.path.exists(chr(x) + ":")]  # TODO: Find the stackoverflow page

drives.remove("C:")
drives.remove("D:")
drives.remove("E:")

for drive in drives:
    print(f"Transferring to {drive}")
    shutil.copy("MICROBIT.hex", drive)

