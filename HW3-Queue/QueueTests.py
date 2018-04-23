#########################################################################################
# Here you need to write some basic tests to make sure your Queue implementation runs correctly
# You can run them by running 'python QueueTests.py' from the command line
#########################################################################################

from Queue import Queue

queue = Queue()

print "Checking basic variable initializations..."

assert queue.is_empty()
assert queue.size() == 0

queue.print_queue()
print "done\n"

###################################

print "Checking is_empty and size..."

assert queue.is_empty()
assert queue.size() == 0

queue.print_queue()
print "done\n"

###################################

print "Checking back, addBack..."

queue.addBack(0)
queue.addBack(1)
assert queue.back() == 1

queue.print_queue()
print "done\n"

###################################

print "Checking front, removeFront..."

assert queue.front() == 0
queue.removeFront()
assert queue.front() == 1

queue.print_queue()
print "done\n"

###################################

queue.print_queue()
print "All checks passed"