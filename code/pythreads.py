#process control block
#PROCESSS ID PID
#statement
#COUNTER
#REGISTER
#MEMORY LIMITS
#LIST OF OPEN FILES


# -------------- thread control block
# parent process pointer
# thread id TID
# thread state
# program counter
# register set
# stack pointer



# -------------- processs memory
#stack
#data
#text import time  class PID:
# """PID Controller     """      def __init__(self, P=0.2, I=0.0, D=0.0):
# self.Kp = P         self.Ki = I         self.Kd = D          self.sample_time = 0.00
#self.current_time = time.time()         self.last_time = self.current_time   self.clear() ...

from datetime import datetime
import time
import numpy as np
from THREADSCAN import *
import threading

def main():
    # creating thread
    t1 = threading.Thread(target=print_square, args=(10,))
    t2 = threading.Thread(target=print_cube, args=(10,))

    # starting thread 1
    t1.start()
    # starting thread 2
    t2.start()

    # wait until thread 1 is completely executed
    t1.join()
    # wait until thread 2 is completely executed
    t2.join()

    # both threads completely executed
    print("Done!\n")


if __name__ == "__main__":
    start = time.time()
    main()
    end = time.time()

    print ("Time elapsed: %.2f secs" % ( end - start))
