#########################################################################################
# Here are some basic tests to make sure your Bag implementation runs correctly
# You can run them by running 'python BagTests.py' from the command line
#########################################################################################

from Bag import *

bag = Bag()

print "Checking basic variable initializations..."

# TODO: check that your inits are ok
assert bag.is_empty()
assert bag.size() == 0

bag.print_bag()
print "done\n"

###################################

print "Checking add, contains, functions..."

#TODO: check that your add and contains operate as expected
bag.add(1)
assert bag.size() == 1
assert bag.contains(1)
bag.print_bag()

bag.add(3)
bag.add(2)
bag.add(4)

bag.print_bag()
assert bag.contains(4)
assert bag.size() == 4

print "done\n"

###################################

print "Checking remove, function(s)..."

#TODO: check that your remove operates as expected
bag.remove(3)
assert bag.contains(3) == False
assert bag.contains(2)
assert bag.size() == 3

bag.print_bag()
print "done\n"

###################################

print "Checking that all of the above didn't break things"

#TODO: check that everything works and that the order in which you call your 
bag.add(8)
bag.remove(2)
bag.add(7)
bag.add(2)
bag.remove(7)
assert bag.contains(2)
assert bag.contains(7) == False

bag.print_bag()
print "All checks passed"