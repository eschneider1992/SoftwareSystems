"""Modified version of the example code from Janert,
Feedback Control For Computer Systems

This modified version requires pandas, numpy, and matplotlib.

If you use apt:

sudo apt-get install python-pandas python-numpy python-matplotlib
"""

import numpy
import pandas
import random
import matplotlib.pyplot as pyplot

class Buffer:
    def __init__( self, max_wip, max_flow ):
        """Initializes the buffer:

        max_wip: maximum work in progress
        max_flow: maximum work completed per time step
        """
        self.queued = 0
        self.wip = 0             # work-in-progress ("ready pool")

        self.max_wip = max_wip
        self.max_flow = max_flow # avg outflow is max_flow/2

    def work( self, u ):
        # Add to ready pool
        u = max( 0, int(round(u)) )
        u = min( u, self.max_wip )
        self.wip += u

        # Transfer from ready pool to queue
        r = int( round( random.uniform( 0, self.wip ) ) )
        self.wip -= r
        self.queued += r

        # Release from queue to downstream process
        r = int( round( random.uniform( 0, self.max_flow ) ) )
        r = min( r, self.queued )
        self.queued -= r

        return self.queued

class Controller:
    def __init__( self, kp, ki, kd ):
        """Initializes the controller.

        kp: proportional gain
        ki: integral gain
        kp: derivative gain
        """
        self.kp, self.ki, self.kd = kp, ki, kd
        self.i = 0       # Cumulative error ("integral")

        self.memory = 0  # Previous value, for computing RoC on the error
        self.d = 0;      # RoC on error ("derivative")

    def work( self, e ):
        """Computes the number of jobs to be added to the ready queue.

        e: error

        returns: float number of jobs
        """
        self.i += e
        self.d = self.memory-e;

        return self.kp*e + self.ki*self.i + self.kd*self.d;

# ============================================================

def closed_loop( c, p, tm=5000 ):
    """Simulates a closed loop control system.

    c: Controller object
    p: Buffer object
    tm: number of time steps

    returns: tuple of sequences (times, targets, errors)
    """
    def setpoint( t ):
        ## Sloped line
        # return t/10
        ## OR
        ## Step function
        if t < 100: return 0
        if t < 300: return 50
        return 10
    
    y = 0
    res = []
    for t in range( tm ):
        r = setpoint(t)
        e = r - y
        u = c.work(e)
        y = p.work(u)

        #print t, r, e, u, y
        res.append((t, r, e, u, y))

    return zip(*res)

# ============================================================

def find_best_performers(RMS, p, i, d):
    """Finds the 5 best RMS values in a simulation and records the PID values used

    RMS: Root Mean Square error of a recently performed simulation
    p, i, d: The PID constants that produced the given RMS

    No return, alters the 'best_performers' dictionary
    """

    max_RMS = max(best_performers.keys())
    if len(best_performers) < 5:
        RMS = int(RMS * 100) / 100.0
        best_performers[RMS] = [p, i, d]
    elif RMS < max_RMS:
        del best_performers[max_RMS]
        RMS = int(RMS * 100) / 100.0
        best_performers[RMS] = [p, i, d]

# ============================================================

# set up the parameter sweeps to find the best PID values
best_performers = {100: [0, 0, 0]}
p_vals = []; i_vals = []; d_vals = [];
for x in range(0, 15, 1):
    p_vals.append(x/10.0)
    i_vals.append(x/100.0)
    # i_vals.append(0) ## Uncomment this to see what a zeroed integral term does
    d_vals.append(x/100.0)
print p_vals

for i in range(len(p_vals)):
    for j in range(len(i_vals)):
        for k in range(len(d_vals)):
            c = Controller( p_vals[i], i_vals[j], d_vals[k] )
            p = Buffer( 50, 10 )

            # run the simulation
            ts, rs, es, us, ys = closed_loop( c, p, 1000 )

            # find RMS and compare it to previous runs
            RMS = numpy.sqrt(numpy.mean(numpy.array(es)**2));
            find_best_performers(RMS, p_vals[i], i_vals[j], d_vals[k])

print best_performers

pid = best_performers[min(best_performers.keys())]
c = Controller( pid[0], pid[1], pid[2] )
p = Buffer( 50, 10 )

# run the simulation
ts, rs, es, us, ys = closed_loop( c, p, 1000 )

# find RMS and compare it to previous runs
RMS = numpy.sqrt(numpy.mean(numpy.array(es)**2));
print 'RMS error', RMS

# generate the smoothed curve using a rolling mean
# (I think the curves in the book use loess)
ys_smooth = pandas.rolling_mean(numpy.array(ys), 20)

# make the plot
pyplot.plot(ts, rs, color='green', label='target')
pyplot.plot(ts, ys, color='red', label='queue length')
pyplot.plot(ts, ys_smooth, color='blue', label='trend')
pyplot.show()