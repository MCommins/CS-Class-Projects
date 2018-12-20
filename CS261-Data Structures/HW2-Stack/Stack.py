from DynamicArray import DynamicArray

# The Stack Class
# Python has all kinds of powerful stuff that does what your Stack needs to do
# No, you CAN'T use any of that
# You need to use your Dynamic Array implementation instead
class Stack(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._size = 0
        self._dynamic_array = DynamicArray()

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    def is_empty(self):
        return self._size == 0

    def size(self):
        return self._dynamic_array.size()

    def top(self):
        return self._dynamic_array.get(self._dynamic_array.size() - 1)

    def push(self, value):
        self._dynamic_array.add(value)


    def pop(self):
        return self._dynamic_array.remove(self._dynamic_array.size() - 1)

    # DO NOT MODIFY THIS PRINT
    def print_stack(self):
        print '====\n' + '\n----\n'.join([str(v) for v in self._dynamic_array._data[:self._size]]) + '\n^^^^'
