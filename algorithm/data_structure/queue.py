# coding=UTF8

class QueueException(Exception):
    message = "队列元素为空"
    
class Queue(object):
    __queue = list()
    length = len(__queue)
    def __init__(self):
        super(Queue,self).__init__()
        
    def push(self,num):
        self.__queue.append(num)
        self.length += 1
    def pop(self):
        if len(self.__queue) is 0:
            raise __queueException
        num = self.__queue[0]
        self.length -= 1
        self.__queue = self.__queue[1:]
        return num
    def get_queue(self):
        return self.__queue
    
class CycleQueueExcption(Exception):
    #message = "队列元素为空"
    pass
    
class CycleQueue(object):
    
    def __init__(self,length):
        super(CycleQueue,self).__init__()
        self.length = length
        self.__length = length + 1
        self.__queue = [None for i in xrange(self.__length)]
        
        self.top,self.tail = 0,-1

    def isEmpty(self):
        if (self.top - self.tail + self.__length) % self.__length is 1:
            return True
        else:
            return False
        
    def isFull(self):
        if (self.tail + 2) % self.__length == self.top:
            return True
        else:
            return False

    def push(self,num):
        if self.isFull() is True:
            raise CycleQueueExcption
        self.tail = (self.tail + 1) % self.__length
        self.__queue[self.tail] = num
        
    def pop(self):
        if self.isEmpty() is True:
            raise CycleQueueExcption
        num,self.__queue[self.top] = self.__queue[self.top],None
        self.top = (self.top + 1) % self.__length
        return num
    def get_queue(self):
        return self.__queue
