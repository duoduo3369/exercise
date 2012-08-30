class Node(object):
    def __init__(self,value,next=None):
        self.value = value
        self.next = next

"""
>>> L = Node('a')
>>> L
<__main__.Node object at 0x028822F0>
>>> L.value
'a'
>>> L.next=(Node('b',Node('c')))
>>> L
<__main__.Node object at 0x028822F0>
>>> L.next
<__main__.Node object at 0x028B5570>
>>> L.next.value
'b'
>>> L.next.next
<__main__.Node object at 0x028822D0>
>>> L.next.next.value
'c'
"""
