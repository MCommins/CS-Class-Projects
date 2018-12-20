#########################################################################################
# Here you need to write some basic tests to make sure your Stack implementation runs correctly
# You can run them by running 'python StackTests.py' from the command line
#########################################################################################

from Stack import Stack

stack = Stack()

print "Checking basic variable initializations..."

# TODO: tests here

assert stack._size == stack.size()

stack.print_stack()
print "done\n"

###################################

print "Checking is_empty and size..."

# TODO: tests here
assert stack.is_empty()
assert stack.size() == 0

stack.print_stack()
print "done\n"

###################################

print "Checking push, top..."

# TODO: tests here
stack.push(1)
stack.push(2)
assert stack.size() == 2
assert stack.top() == 2

stack.print_stack()
print "done\n"

###################################

print "Checking pop..."

# TODO: tests here
assert stack.pop() == 2

stack.print_stack()
print "done\n"

###################################

stack.print_stack()
print "All checks passed"