#we'll also develop a Python option, since
#we have not administrator permissions, hence
#won't be able to compile (have no compiler installed),
#nor execute programs

import glob

targetPattern = r"C:\Test\**\*.txt"
glob.glob(targetPattern)
