import os
import time
import sys
import subprocess
import numpy

def calculateStatistics(filename, bestSolution):

    results = []
    initialSolutions = []
    executionTimes = []

    with open(filename, 'r') as f:
        for line in f:
            print line
            a,b,c,d = line.split(";")
            initialSolutions.append(float(a))
            results.append(float(b))
            executionTimes.append(float(c))

    print initialSolutions
    print results
    print executionTimes

    meanSolution = numpy.mean(results)
    meanTime = numpy.mean(executionTimes)
    meanInitialSolution = numpy.mean(initialSolutions)
    stdv = numpy.std(results)
    print (meanSolution - bestSolution)
    print ((meanSolution - bestSolution) / bestSolution);
    percentualDeviation = 100 * ((meanSolution - bestSolution) / bestSolution);

    with open("statistics"+filename, 'w') as f2:
        f2.write( "Mean initial solution: " + str(meanInitialSolution) + "\n"  )
        f2.write( "Mean solutions: " + str(meanSolution) + "\n"  )
        f2.write( "Standard deviation solutions: " + str(stdv) + "\n"  )
        f2.write( "Mean percentual deviation: " + str(percentualDeviation) + "\n"  )
        f2.write( "Mean execution time: " + str(meanTime) + "\n"  )


def evalAll(minExec, maxExec):
    os.system("g++ -std=c++11 main.cpp")

    for i in xrange(minExec,maxExec):
	print "ESC07" + str(i)
	os.system("./a.out ../instances/ESC07.sop " + str(i) + " >> ESC07sol.txt")
    calculateStatistics("ESC07sol.txt", 2125)

    for i in xrange(minExec,maxExec):
	print "ESC12" + str(i)
        os.system("./a.out ../instances/ESC12.sop " + str(i) + " >> ESC12sol.txt")
    calculateStatistics("ESC12sol.txt", 1675)

    for i in xrange(minExec,maxExec):
        print "ESC25" + str(i)
	os.system("./a.out ../instances/ESC25.sop " + str(i) + " >> ESC25sol.txt")
    calculateStatistics("ESC25sol.txt", 1681)

    for i in xrange(minExec,maxExec):
	print "ESC47" + str(i)
	os.system("./a.out ../instances/ESC47.sop " + str(i) + " >> ESC47sol.txt")
    calculateStatistics("ESC47sol.txt", 1288)

    for i in xrange(minExec,maxExec):
	print "ESC78" + str(i)
	os.system("./a.out ../instances/ESC78.sop " + str(i) + " >> ESC78sol.txt")
    calculateStatistics("ESC78sol.txt", 18230)

    for i in xrange(minExec,maxExec):
	print "ft70.1" + str(i)
	os.system("./a.out ../instances/ft70.1.sop " + str(i) + " >> ft70.1sol.txt")
    calculateStatistics("ft70.1sol.txt", 39313)

    for i in xrange(minExec,maxExec):
	print "prob100" + str(i)
	os.system("./a.out ../instances/prob.100.sop " + str(i) + " >> prob.100sol.txt")
    calculateStatistics("prob.100sol.txt", 1163)

    for i in xrange(minExec,maxExec):
	print "rbg109a" + str(i)
	os.system("./a.out ../instances/rbg109a.sop " + str(i) + " >> rbg109asol.txt")
    calculateStatistics("rbg109asol.txt", 1038)

    for i in xrange(minExec,maxExec):
	print "rbg150a" + str(i)
	os.system("./a.out ../instances/rbg150a.sop " + str(i) + " >> rbg150asol.txt")
    calculateStatistics("rbg150asol.txt", 1750)

    for i in xrange(minExec,maxExec):
	print "rbg174a" + str(i)
	os.system("./a.out ../instances/rbg174a.sop " + str(i) + " >> rbg174asol.txt")
    calculateStatistics("rbg174asol.txt", 2033)


minExec = int(sys.argv[1])
maxExec = int(sys.argv[2]) + 1
evalAll(minExec, maxExec)
