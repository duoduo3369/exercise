#coding=utf8
from Queue import Queue

import random

import threading
import subprocess
import time
import shlex
import ctypes

#Producer thread

class Producer(threading.Thread):

    def __init__(self, t_name, queue):
        threading.Thread.__init__(self, name=t_name)
        self.data=queue

    def run(self):
        while True:
            con.acquire()
            if len(self.data.queue) > 0:
                con.wait()
            else:
                i = raw_input("input test case: ")
                self.data.put(i)
                con.notify()
            con.release()
            time.sleep(random.randrange(3)/5)

        print "%s: %s finished!" %(time.ctime(), self.getName())



#Consumer thread

class Consumer(threading.Thread):

    def __init__(self, t_name, queue):
        threading.Thread.__init__(self, name=t_name)
        self.data=queue

    def run(self):
        while True:
            con.acquire()
            if len(self.data.queue) is 0:
                con.wait()
            else:
                val = self.data.get()
                args = [exepath]
                args.extend(shlex.split(val))
                pipe = subprocess.Popen(args,
                stdin = subprocess.PIPE,
                stdout = subprocess.PIPE,
                stderr = subprocess.PIPE, shell = False)
                print pipe.stdout.read()
                ctypes.windll.kernel32.TerminateProcess(int(pipe._handle), -1)
                #print  "output: %s" % (val)
                con.notify()
            con.release()
            time.sleep(random.randrange(3)/5)

        print "%s: %s finished!" %(time.ctime(), self.getName())

def main():

    queue = Queue()
    producer = Producer('Pro.', queue)
    consumer = Consumer('Con.', queue)
    producer.start()
    consumer.start()
    producer.join()
    consumer.join()

    print 'All threads terminate!'



con = threading.Condition()
exepath = "add.exe"
if __name__ == '__main__':

    main()
