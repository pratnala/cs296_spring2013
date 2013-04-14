#import os
import subprocess
import re

def runAndRead(command):
   proc = subprocess.Popen(command, stdout = subprocess.PIPE)
   output = proc.stdout.read()
   return output


cmd = './bin/g01_perf'
c1 = 100 
c2 = 100

writeout = open('./data/lab09_g01_data.csv', 'w')

for i in range(c1):
   for j in range (c2):
      strappend = str(i + 1)
      cmdcall = [cmd, strappend]
      result = str(runAndRead(cmdcall))
      numlist = re.findall(r'[0-9]+(?:[.][0-9]+)?', result)
      writeout.write(str(j + 1)+','+numlist[0]+','+numlist[1]+','+numlist[2]+','+numlist[3]+','+numlist[4]+','+numlist[5]+'\n')
