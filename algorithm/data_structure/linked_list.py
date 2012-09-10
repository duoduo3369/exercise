# coding=UTF8

class Node(object):
    def __init__(self, value, next=None):
        self.value = value
        self.next = next

class ListException(Exception):
    message = "列表元素为空"

class List(object):
    def __init__(self):
        self.head = None
        self.tail = None
        
    def push(self, value):        
        if self.head is None:
            self.head = Node(value)
            self.tail = self.head
        else:
            self.tail.next = Node(value)
            self.tail = self.tail.next

    def pop(self):
        if self.head is None:
            raise ListException      
        
        value = self.tail.value
        head = self.head
        if head.next is None:
            self.head = None
            return value
        while head.next is not self.tail:
            head = head.next
        self.tail = head
        self.tail.next = None
        return value

def test():
    l = List()
    import random
    array = random.sample(xrange(10), 10)
    for i in array:
        l.push(i)
    print l
    print l.head.value
    print l.tail.value
    print array
    print l.tail.value
    h = l.head
    while h is not None:
        print h.value,
        h = h.next
    while l.head is not None:
        print l.pop()
        
