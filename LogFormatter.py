#!/usr/bin/env python3

inFile = open("ALEALog.txt", "r")
outFile = open("ALEATracing.json", "w")
outFile.write("")
outFile.close()
outFile = open("ALEATracing.json", "a")

outFile.write("[\n");

lines = inFile.readlines()
for line in lines:
	if (line.find("GBA Serial") > 0):
		continue
	
	g = line.replace("[WARN] GBA Debug: ", "");
	outFile.write(g);

inFile.close()
inFile = open("ALEALog.txt", "w")
inFile.write("")
inFile.close()
outFile.close()

