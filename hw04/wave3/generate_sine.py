"""This file contains code used in "Think DSP",
by Allen B. Downey, available from greenteapress.com

Copyright 2013 Allen B. Downey
License: GNU GPLv3 http://www.gnu.org/licenses/gpl.html
"""

import thinkdsp
import thinkplot

import matplotlib.pyplot as pyplot


def print_reverse_tables(intA):
    f = open('signal', 'w')
    f.write('int reverseWave[] = {')
    for n in intA:
        f.write('%d,' % int('{:08b}'.format(n)[::-1], 2),)
    print '\n'
    # for i in range(200):
    #         print '%d,' % int('{:08b}'.format(intA)[i][::-1], 2),


def print_c_wave(wave, name='wave1'):
    print 'int %s[] = {' % name
    ys = 0.7 + (4.3) * (wave.ys + 1) / 2
    zs = [int(y * 256 / 5) for y in ys]
    t = [str(z) for z in zs]
    print ','.join(t)
    print '};'
    print_reverse_tables(zs);

def make_sine():

    framerate = 8000
    signal = thinkdsp.SinSignal(440, amp=1.0, offset=0)
    duration = signal.period
    wave = signal.make_wave(duration=duration, start=0, framerate=framerate)

    print 'Number of samples', len(wave.ys)
    print 'Timestep in ms', 1.0 / framerate * 1000

    # plot the segment
    #wave.plot()
    #thinkplot.Show(
    #    xlabel='time (s)',
    #    axis=[0, duration, -1.05, 1.05])
    
    print_c_wave(wave, 'signal')


def file_example(start=0.0, duration=2.75):
    """Demonstrates methods in the thinkdsp module.
    """
    # read the file recording
    wave = thinkdsp.read_wave('woman.wav')

    # extract a segment
    segment = wave.segment(start, duration)

    # make the spectrum
    spectrum = segment.make_spectrum()

    # apply a filter
    spectrum.low_pass(600)

    # invert the spectrum
    filtered = spectrum.make_wave()

    # prepare the original and filtered segments
    filtered.normalize()
    filtered.apodize()
    segment.apodize()

    print_c_wave(filtered)

    # write the original and filtered segments to a file
    filename = 'filtered.wav'
    wfile = thinkdsp.WavFileWriter(filename, segment.framerate)
    wfile.write(segment)
    wfile.write(filtered)
    wfile.close()

    thinkdsp.play_wave(filename)


def main():
    # make_sine()
    file_example()


if __name__ == '__main__':
    main()
