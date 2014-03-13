# WRONG
print 'int reverse1[] = {'
for i in range(64):
    s = bin(i)[2:].zfill(6)
    print '%d,' % int(s[::-1], 2),
print '};'

# WRONG
print 'int reverse2[] = {'
for i in [0, 2, 1, 3]:
    print '%d,' % (i * 64),
print '};'

# RIGHT
print 'int reverse3[] = {'
for n in [0, 1, 2, 3, 4, 5, 6]:
	print '%d,' % int('{:08b}'.format(n)[::-1], 2),